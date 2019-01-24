/**
*  @FaceLandmarkDetect函数
*  利用OpenCV + dlib库实现了：
*  1 68个人脸特征点特征点提取
*  2 特征点格式化输出为.pts
*  pts文件包含了一个68*2的矩阵，对应68个特征点及对应的x/y坐标
*/


#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>  

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <string>
#include <exception>
#include "Functions.h"

using namespace dlib;
using namespace std;

void FaceLandmarkDetect(string picDir)
{
	string gtmp = "tmp.txt";
	string gpts = "out.pts";

	try
	{


		// 初始化dlib训练的人脸特征检测器frontal_face_detector
		frontal_face_detector detector = get_frontal_face_detector();

		// 利用dlib模型，我们还需要构建特征提取器shape_predictor.它在给定的图片和bounding box中预测人脸位置
		// 这里我采用官方训练好的模型shape_predictor_68_face_landmarks.dat
		// 如果有足够样本，dlib也有相关训练方法，可以训练自己的模型
		shape_predictor sp;
		deserialize("shape_predictor_68_face_landmarks.dat") >> sp;
		//image_window win, win_faces;
		// 创建一个二维矩阵，rgb编码形式存储图片
		array2d<rgb_pixel> img;

		try
		{
			load_image(img, picDir);
		}
		catch (const std::exception& e)
		{
			cout << "Error loading the original image: " << e.what() << endl;
			cout << e.what() << endl;
			cout << "Press any button to exit." << endl;
			cin.get();
			return;
		}

		// 若图片中人脸较小，可以允许使用该函数进行图片采样放大，便于检测
		//pyramid_up(img);

		// 在图片的人脸周边，利用特征检测器，确定bounding box
		std::vector<rectangle> dets = detector(img);

		// 利用特征提取器，获取68个特征点，存放在shapes容器中
		// full_object_detection 亦包含了bounding box rectangle
		std::vector<full_object_detection> shapes;
		std::ofstream tmpfile(gtmp);
		// 当然.利用dets可以针对同一张照片多张人脸进行同时检测，存入shapes.
		// 本系统只检测一张人脸
		full_object_detection shape = sp(img, dets[0]);
		cout << "number of points: " << shape.num_parts() << endl;
		tmpfile << "version: 1" << endl << "n_points:  68" << endl << '{' << endl;
		for (int i = 0; i < shape.num_parts(); i++)
		{
			tmpfile << shape.part(i) << endl;
		}
		tmpfile << '}';
		tmpfile.close();

		// 和ibug数据格式统一
		std::ifstream infile2(gtmp);
		string tmp{ istreambuf_iterator<char>(infile2), istreambuf_iterator<char>() };
		infile2.close();

		strReplace(tmp, "(", "");
		strReplace(tmp, ")", "");
		strReplace(tmp, ",", " ");

		//将特征点坐标保存至.pts文件
		std::ofstream outfile(gpts);
		outfile << tmp;
		outfile.close();
		shapes.push_back(shape);

		/* 独立的人脸特征点模块可允许下列函数进行显示，系统就不需要了
		// 在屏幕上显示描绘了特征点折线的人脸
		// 清空图像窗口
		win.clear_overlay();
		// 显示输入的图片
		win.set_image(img);
		// 在图片检测到的人脸上绘制特征点折线
		win.add_overlay(render_face_detections(shapes));

		// 同时，显示一个裁剪的、旋转至标准化姿势的人脸,进行对比
		dlib::array<array2d<rgb_pixel> > face_chips;
		extract_image_chips(img, get_face_chip_details(shapes), face_chips);
		win_faces.set_image(tile_images(face_chips));

		*/

		//cout << "Hit enter to continue..." << endl;
		//cin.get();

	}
	catch (exception& e)
	{

		cout << "\nexception thrown during face detection module!" << endl;
		cin.get();
		cout << e.what() << endl;
		std::terminate();
	}

}

