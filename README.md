# 3D Face Reconstrction - Personal Project

I built this out of my personal interst in 2018 in my free time as a senior CS undergraduate. 

This program is able to reconstruct a 3D face model from a single front-face image with the help of C++, QT, OpenGL, OpenCV, eos/dlib libraries and surrey face model. Also, it automatically reads the .obj file with its texture and display the full model in front of you right after the reconstruction process!

The interactive UI was implemented using C++ Qt. It deserves some refinements when I have time.

Following is the model viewer UI, as you can adjust the model angles with sliders or drag with your mouse to adjust the pose of the model generated!
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/obj_model_viewer_2.jpeg"></img>

## Dependencies
I used Visual Studio 2018 on Windows to do my project.
* In order to compile the program, you need to configure the following dependencies in order:

OpenCV -> OpenGL -> dlib -> eos -> Qt

* referenced Libraries: 

https://github.com/patrikhuber/eos

http://dlib.net

## The Surrey Face Model

I used a shape-only version of the Surrey Morphable Face Model as the skeleton of the model.

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sfm_shape_3448_mesh.png" width=20% alt="Surrey Face Model shape picture"></img>

The full model is available at [http://www.cvssp.org/facemodel](http://www.cvssp.org/facemodel).


## Face Landmark Detection

Here is the face landmark detection part. By selecting 68 landmarks, a face could be identified and located in the image. 
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/face_landmarks.jpeg"></img>

Given the input sample photo:

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_4.png"></img>

By running face detection module, th program identified the front face and its outline and some interest points, e.g. nose and eyes.

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/obj_model_viewer_1.png"></img>


## Texture Extraction

By implementing the texture extraction API, combined with Dlib face landmark detection data, the texture can be extracted fro the original image.

The face texture could be presented in this sturcture:
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/texture_mesh.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/texture_sample.png"></img>

## Face Reconstruction

Here comes the most challanging part.

* First, the program fits the original model to different face image, adjusts its surface parameters in order to present more natural and realistic outputs.

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/fitted_models_1.jpeg"></img>

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/fitted_models_2.jpeg"></img>


* Secondly, given an extracted texture of the face and the surrey face model, the program calculates a mapping between the coordinates from a 2D image to a 3D model.

Some final outputs:

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/models_with_texture.jpeg"></img>


<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_1.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_1.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_2.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_2.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_4.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_4.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_3.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_3.png"></img>
