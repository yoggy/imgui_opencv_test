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
#include "ImGuiSDLWindow.h"

class ImgGUIOpenGLTest : public ImGuiSDLWindow
{
public:
	ImgGUIOpenGLTest();
	~ImgGUIOpenGLTest();

	virtual void on_draw();

private:
	glm::mat4 position_mat_;
	glm::mat4 rotation_mat_;
};

