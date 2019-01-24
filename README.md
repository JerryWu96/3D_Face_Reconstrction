# 3D Face Reconstrction - Personal Project
I built this out of my personal interst in 2018 during my free time as a senior CS student. 

This program is able to reconstruct a 3D face model from a single front-face image with the help of C++, QT, OpenGL, OpenCV, eos/dlib libraries and surrey face model. 
The UI was implemented using C++ QT, and when i have time, it deserves some refinements!

Libraries:
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

The face texture could be presented in this sturcture:
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/texture_mesh.png"></img>

By implementing the texture extraction API, combined with Dlib face landmark detection data, the texture can be extracted fro the original image.

<img src:"https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/texture_sample.png"></img>

