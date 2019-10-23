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

int main(int argc, char* argv[])
{
	ImGuiSDLWindow* window = new ImGuiOpenCVTest();

	if (window->setup(argc, argv) == false)
	{
		fprintf(stderr, "errror: init() failed...\n");
		delete(window);
		return -1;
	}

	window->main_loop();

	// dispose
	delete(window);
	window = nullptr;

	return 0;
}
