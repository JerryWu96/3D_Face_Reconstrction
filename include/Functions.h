
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string>
#include <iostream>
//字符串替换函数 声明
void strReplace(std::string& str, const std::string& oldStr, const std::string& newStr);

//图像特征点提取模块 声明
void FaceLandmarkDetect(std::string img);

//人脸重建模块 声明
//void Reconstruct();
bool Reconstruct();
//接收图像选取ui时控制时间
void delay(int second);

#endif