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

#include <SDL.h>
#include <SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl2.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

class ImGuiSDLWindow
{
public:
	ImGuiSDLWindow();
	~ImGuiSDLWindow();

	void quit();
	void background_color(const float& r, const float& b, const float& g);

	bool setup(int argc, char* argv[]);
	void dispose();
	void main_loop();

	virtual bool on_setup(int argc, char* argv[]) { return true; };
	virtual void on_draw() {};
	virtual void on_imgui() {};
	virtual void on_dispose() {};

protected:
	SDL_Window* window_;
	SDL_GLContext gl_context_;
	bool break_main_loop_flag_;
	glm::vec3 background_color_;
};
