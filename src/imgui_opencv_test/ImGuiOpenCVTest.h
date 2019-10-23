//
//imgui_opencv_test - Sample code for ImGUI and OpenCV
//
// github :
//     https://github.com/yoggy/imgui_opencv_test
//
// license :
//     Copyright(c) 2019 yoggy <yoggy0@gmail.com>
//     Released under the MIT license
//     http://opensource.org/licenses/mit-license.php;
//
#pragma once
#include "ImgGUIOpenGLTest.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

class ImGuiOpenCVTest : public ImgGUIOpenGLTest
{
public:
	ImGuiOpenCVTest();
	~ImGuiOpenCVTest();

	virtual bool on_setup(int argc, char* argv[]);
	virtual void on_imgui();
	virtual void on_dispose();

private:
	cv::Mat img_;
	GLuint texture_;
};

