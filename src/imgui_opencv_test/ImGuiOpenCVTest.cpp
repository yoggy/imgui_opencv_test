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
#include "ImGuiOpenCVTest.h"
#include <random>

ImGuiOpenCVTest::ImGuiOpenCVTest() : ImgGUIOpenGLTest(), texture_(0)
{
}

ImGuiOpenCVTest::~ImGuiOpenCVTest()
{
}

bool ImGuiOpenCVTest::on_setup(int argc, char* argv[])
{
	if (ImgGUIOpenGLTest::on_setup(argc, argv) == false) {
		fprintf(stderr, "ERROR : ImgGUIOpenGLTest::on_setup failed...\n");
		return false;
	}

	img_.create(cv::Size(256, 256), CV_8UC4);
	img_.setTo(200);

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_.cols, img_.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_.data);

	return true;
}

void ImGuiOpenCVTest::on_imgui()
{
	ImGui::Begin("ImGUI window");

	ImGui::Text("cv::Mat");

	// update image data
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> rand255(0, 255);

	for (int y = 0; y < img_.rows; ++y) {
		for (int x = 0; x < img_.cols; ++x) {
			cv::Vec4b &p = img_.at<cv::Vec4b>(y, x);
			p[0] = rand255(mt); // R
			p[1] = rand255(mt); // B
			p[2] = rand255(mt); // B
			p[3] = 255; // A
		}
	}

	// see also... https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples

	// rewrite texture data
	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img_.cols, img_.rows, GL_RGBA, GL_UNSIGNED_BYTE, img_.data);

	// show texture image in ImGUI window
	ImGui::Image((ImTextureID)texture_, ImVec2((float)img_.cols, (float)img_.rows));

	ImGui::End();
}

void ImGuiOpenCVTest::on_dispose()
{
	glDeleteTextures(1, &texture_);
	texture_ = 0;
}