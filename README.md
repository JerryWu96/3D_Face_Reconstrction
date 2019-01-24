# 3D Face Reconstrction - Personal Project

I built this out of my personal interst in 2018 in my free time as a senior CS student. 

This program is able to reconstruct a 3D face model from a single front-face image with the help of C++, QT, OpenGL, OpenCV, eos/dlib libraries and surrey face model. Also, it automatically read the .obj file with its texture and display the full model in front of you right after the reconstruction process!

The program UI was implemented using C++ QT. When i got time, it deserves some refinements!

The model viewer UI, with sliders you could adjust the model angles from any degree!
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/obj_model_viewer_2.jpeg"></img>

## Dependencies
* In order to compile the program, you need to configure the following dependencies in order:
OpenCV -> OpenGL -> dlib -> eos -> QT

referenced Libraries: 

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

By running face detection module, th program identified the front face and its location.
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/obj_model_viewer_1.png"></img>


## Texture Extraction

By implementing the texture extraction API, combined with Dlib face landmark detection data, the texture can be extracted fro the original image.

The face texture could be presented in this sturcture:
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/texture_mesh.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/texture_sample.png"></img>

## Face Reconstruction

Here comes the most challanging part.

* First, we need to fit the original model to different face image, adjust its surface parameters in order to present more natural and realistic outputs.

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/fitted_models_1.jpeg"></img>

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/fitted_models_2.jpeg"></img>

* Second, Given an extracted texture of the face, the surrey face model, we need to make a mapping between the coordinates from a 2D image to a 3D model.

Here are some final outputs:

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/models_with_texture.jpeg"></img>


<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_1.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_1.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_2.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_2.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_3.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_3.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_4.png"></img>
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/model_4.png"></img>
