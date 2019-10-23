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
#include "ImgGUIOpenGLTest.h"

static const GLdouble vertex[][3] = {
	{-0.5, -0.5, -0.5},
	{0.5, -0.5, -0.5},
	{0.5, 0.5, -0.5},
	{-0.5, 0.5, -0.5},
	{-0.5, -0.5, 0.5},
	{0.5, -0.5, 0.5},
	{0.5, 0.5, 0.5},
	{-0.5, 0.5, 0.5} };

static const int edge[][2] = {
	{0, 1},
	{1, 2},
	{2, 3},
	{3, 0},
	{4, 5},
	{5, 6},
	{6, 7},
	{7, 4},
	{0, 4},
	{1, 5},
	{2, 6},
	{3, 7} };

ImgGUIOpenGLTest::ImgGUIOpenGLTest() : ImGuiSDLWindow()
{
	position_mat_ = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f, -2.0f));
	rotation_mat_ = glm::identity<glm::mat4>();
}

ImgGUIOpenGLTest::~ImgGUIOpenGLTest()
{
}

void ImgGUIOpenGLTest::on_draw()
{
	auto& io = ImGui::GetIO();

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::mat4 perspective_mat = glm::perspective(45.0f, (float)io.DisplaySize.x / (float)io.DisplaySize.y, 0.1f, 1000.0f);
	glMultMatrixf(glm::value_ptr(perspective_mat));

	// origin , direction, up-vector
	glm::mat4 camera_mat = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glMultMatrixf(glm::value_ptr(camera_mat));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	rotation_mat_ = glm::rotate(rotation_mat_, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
	rotation_mat_ = glm::rotate(rotation_mat_, 0.02f, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation_mat_ = glm::rotate(rotation_mat_, 0.03f, glm::vec3(0.0f, 0.0f, 1.0f));

	glMultMatrixf(glm::value_ptr(position_mat_ * rotation_mat_));

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 12; i++)
	{
		glVertex3dv(vertex[edge[i][0]]);
		glVertex3dv(vertex[edge[i][1]]);
	}
	glEnd();
}

