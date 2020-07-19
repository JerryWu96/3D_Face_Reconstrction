/**
*  @Reconstruct函数
*  利用eos库实现了：
*  1 读取形变模型，进行2D-3D坐标对应关系的处理
*  2 利用正交相机(Orthographic Camera)进行姿势的估计和拟合
*  3 提取并保存纹理
*  最终的输出，包含了模型文件.obj, 纹理图片.png和对应的材料库文件.mtl(指出模型对应的纹理文件名称)
*/

#include "eos/core/Image.hpp"
#include "eos/core/Image_opencv_interop.hpp"
#include "eos/core/Landmark.hpp"
#include "eos/core/LandmarkMapper.hpp"
#include "eos/core/read_pts_landmarks.hpp"
#include "eos/fitting/RenderingParameters.hpp"
#include "eos/fitting/linear_shape_fitting.hpp"
#include "eos/fitting/orthographic_camera_estimation_linear.hpp"
#include "eos/morphablemodel/MorphableModel.hpp"
#include "eos/render/texture_extraction.hpp"
#include "eos/render/utils.hpp"
#include "Eigen/Core"
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Functions.h"

#include <QImage>
#include <QLabel>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace eos;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

using eos::core::Landmark;
using eos::core::LandmarkCollection;
using Eigen::Vector2f;
using Eigen::Vector4f;
using cv::Mat;
using std::cout;
using std::endl;
using std::string;
using std::vector;

bool Reconstruct()
{
	using namespace std::chrono;
	auto start = steady_clock::now();

	string outputbasename = "out";
	string gpts = "out.pts";
	// 读取待处理图片
	string imgDir = "Pic.txt";

	//读取选取的图片路径
	std::ifstream infile(imgDir);
	string img{ istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };
	infile.close();
	// 检测人脸特征点，并存储为.pts
	try
	{
		FaceLandmarkDetect(img);
	}
	catch (const std::runtime_error& e)
	{
		//cout << "Error processing face landmark detection: " << e.what() << endl;
		//cin.get();
		//return EXIT_FAILURE;
		std::terminate();
	}

	Mat image = cv::imread(img);
	LandmarkCollection<Eigen::Vector2f> landmarks;

	// 读取pts文件
	try
	{
		landmarks = core::read_pts_landmarks(gpts);
	}
	catch (const std::runtime_error& e)
	{
		//cout << "Error reading the landmarks: " << e.what() << endl;
		//cin.get();
		//return EXIT_FAILURE;
		std::terminate();

	}


	// 读取形变模型
    // Special note here: sfm_shape_16759 and sfm_shape_29587 are not publicly available. I am not permitted to upload them here directly, but sfm_shape_3448.bin is good to go. Please email them for higher-resolution models. Their contacts could be found in my README.md
	morphablemodel::MorphableModel morphable_model;
	try
	{
		/*
		cout << "Which resolution do you prefer considering the Surrey Face Model?" << endl;
		cout << "Low resolution: input 1. Medium resolution: input 2. High resolution: input 3." << endl;
		int choice;
		cin >> choice;
		while (choice < 1 || choice > 3)
		{
		cout << "Error! Please input an integer from 1 to 3:" << endl;
		cin.get();
		cin >> choice;
		}
		switch (choice)
		{
		case 1:
		morphable_model = morphablemodel::load_model("sfm_shape_3448.bin");
		break;
		case 2:
		morphable_model = morphablemodel::load_model("sfm_shape_16759.bin");
		break;
		case 3:
		morphable_model = morphablemodel::load_model("sfm_shape_29587.bin");
		break;
		default:
		morphable_model = morphablemodel::load_model("sfm_shape_29587.bin");
		}
		*/
        morphable_model = morphablemodel::load_model("sfm_shape_3448.bin");
	}
	catch (const std::runtime_error& e)
	{
		//cout << "Error loading the Morphable Model: " << e.what() << endl;
		//cin.get();
		//return EXIT_FAILURE;
		std::terminate();

	}


	// LandmarkMapper类对象，将dlib的二维坐标点转换为顶点id( vertex ids)
	core::LandmarkMapper landmark_mapper;
	try
	{
		landmark_mapper = core::LandmarkMapper("dlib_to_sfm.txt");
	}
	catch (const std::exception& e)
	{
		//cout << "Error loading the landmark mappings: " << e.what() << endl;
		//cin.get();
		//return EXIT_FAILURE;
		std::terminate();
	}

	try
	{
		// 绘制读入的坐标点
		Mat outimg = image.clone();
		for (auto&& lm : landmarks)
		{
			//以输入的两点pt1和pt2为对角线 描绘矩形边框
			cv::rectangle(outimg, cv::Point2f(lm.coordinates[0] - 2.0f, lm.coordinates[1] - 2.0f),
				cv::Point2f(lm.coordinates[0] + 2.0f, lm.coordinates[1] + 2.0f), { 255, 0, 0 });
		}
	}
	catch (const std::exception& e)
	{
		//cout << "Error drawing the landmarks: " << e.what() << endl;
		//cin.get();
		//return EXIT_FAILURE;
		std::terminate();
	}

	// 定义最终用于拟合的数据点
	std::vector<Vector4f> model_points; // 三维形变模型的点
	std::vector<int> vertex_indices;    // 顶点索引
	std::vector<Vector2f> image_points; // 对应的二维坐标点

	try
	{
		// 对每一个坐标点进行判断，依据dlib_to_sfm.txt规定的2D-3D对应关系，查询模型上对应的三维坐标点（利用哈希表）
		for (int i = 0; i < landmarks.size(); ++i)
		{
			// 本模块采用68个点，name即为1-68，converted_name为dlib_to_sfm.txt右值.若后续更改为更多关键点，则自适应
			auto converted_name = landmark_mapper.convert(landmarks[i].name);
			if (!converted_name)
			{ // 若没有对应的点，则忽略
				continue;
			}
			int vertex_idx = std::stoi(converted_name.value());
			// 返回一个3x1的容器，包含了x-y-x坐标
			auto vertex = morphable_model.get_shape_model().get_mean_at_point(vertex_idx);
			model_points.emplace_back(Vector4f(vertex.x(), vertex.y(), vertex.z(), 1.0f));
			vertex_indices.emplace_back(vertex_idx);
			image_points.emplace_back(landmarks[i].coordinates);
		}

		// 根据2D - 3D对应关系，正交投影估计模型的姿势（camera/pose）OpenCV参数为true
		fitting::ScaledOrthoProjectionParameters pose =
			fitting::estimate_orthographic_projection_linear(image_points, model_points, true, image.rows);
		fitting::RenderingParameters rendering_params(pose, image.cols, image.rows);

		// 获取三维人脸角度
		const float yaw_angle = glm::degrees(glm::yaw(rendering_params.get_rotation()));
		// 获取仿射变换矩阵
		const Eigen::Matrix<float, 3, 4> affine_from_ortho =
			fitting::get_3x4_affine_camera_matrix(rendering_params, image.cols, image.rows);		
		// 通过将模型与特征点拟合，估计模型的参数

		const std::vector<float> fitted_coeffs = fitting::fit_shape_to_landmarks_linear(
			morphable_model.get_shape_model(), affine_from_ortho, image_points, vertex_indices);

		// 依据获得的参数，获取完整的网格模型
		const core::Mesh mesh = morphable_model.draw_sample(fitted_coeffs, std::vector<float>());

		// 依据网格模型和姿势参数，从原图中提取纹理
		const core::Image4u isomap = render::extract_texture(mesh, affine_from_ortho, core::from_mat(image));

		// 将网格模型保存为.obj
		fs::path outputfile = outputbasename + ".obj";
		core::write_textured_obj(mesh, outputfile.string());

		//保存isomap纹理文件
		outputfile.replace_extension(".isomap.png");
		cv::imwrite(outputfile.string(), core::to_mat(isomap));
		auto end = steady_clock::now();
		ofstream c("count.txt");
		c << "Reconstruction time: " << duration_cast<milliseconds>(end - start).count() << "miliseconds";
		c.close();
	}
	catch (const std::exception& e)
	{
		//cout << "Error processing the mesh and texture: " << e.what() << endl;
		//cin.get();
		std::terminate();
		//return EXIT_FAILURE;
	}
	return 1;
}
