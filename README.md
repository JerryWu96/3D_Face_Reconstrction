# 3D Face Reconstrction - Personal Project

I built this out of my personal interst back to 2018 when I was a senior undergraduate in Compute Science. The total time that i spent on this project was a week.

The main goal of the program is to reconstruct a 3D face model from a single front-face image with the help of C++, QT, OpenGL, OpenCV, eos/dlib libraries and surrey face modesl. it extracts face texture, constructs a face model in.obj format, and reconstructs the full 3D model.

The interactive UI was implemented using C++ Qt.

Following is a screenshot of the model viewer UI. You could adjust the model angles with sliders or drag with your mouse to adjust the pose of the model at east.
<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/obj_model_viewer_2.jpeg"></img>

## Dependencies
I used Visual Studio 2018 on Windows to do my project.
* In order to compile the program, you need to configure the following dependencies in order:

OpenCV -> OpenGL -> dlib -> eos -> Qt

- you could find the following two files in dependencies folder:
  - dlib_to_sfm.txt: mapping bettween dlib and sfm model
  - expression_blendshapes_3448.bin: basic sfm model. 

* Some useful links: 

https://github.com/patrikhuber/eos

http://dlib.net

## The Surrey Face Model

I used a shape-only version of the Surrey Morphable Face Model as the skeleton of the model.

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sfm_shape_3448_mesh.png" width=20% alt="Surrey Face Model shape picture"></img>

The full models with higher resolution are available at [http://www.cvssp.org/facemodel](http://www.cvssp.org/facemodel).


## Face Landmark Detection

Here is the face landmark detection part. By selecting 68 landmarks, a face could be identified and located in the image. 

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/face_landmarks.jpeg"></img>

Given the input sample photo:

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/sample_4.png"></img>

By running face detection module, my program identified the front face and its outline and some interest points, e.g. nose and eyes.

<img src="https://github.com/JerryWu96/3D_Face_Reconstrction/blob/master/program%20screenshots/obj_model_viewer_1.png"></img>


## Texture Extraction

By implementing the texture extraction API, combined with Dlib face landmark detection data, the texture can be extracted from the original image.

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



## Special Note

You may have noticed that in Reconstruct.cpp, code that reads higher-resolution sfm model has been commented out, since these models are not publicly available, and i am not permitted to upload them here. 

Sometime in 2019, they have updated their face models with new formats and python code to handle them, which i haven't looked into yet. My program uses a deprecated version which was updated in 2018. Please email them if you still want to get versions that are compatible with my program. Their website is in Reference

I have received more than 10 emails asking whether i will add support to the new Surrey face model. Note that currently I do not have the plan to use their new versions since it will add some extra overhead to the code. Please understand that this is a project i spent a week working on, and refactoring could take efforts since i no longer have any Windows laptop with me.

However, i am happy to discuss with you the questions about the current code. It is up to you to decide if you would like to make it better:) 

Please submit PRs if you decide to have a major update, thanks!