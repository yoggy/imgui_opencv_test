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
#include "ImGuiSDLWindow.h"

ImGuiSDLWindow::ImGuiSDLWindow()
	: window_(nullptr), gl_context_(nullptr), break_main_loop_flag_(false), background_color_(0.0f, 0.0f, 0.2f)
{
}

ImGuiSDLWindow::~ImGuiSDLWindow()
{
	on_dispose();
	dispose();
}

void ImGuiSDLWindow::quit()
{
	break_main_loop_flag_ = true;
}

void ImGuiSDLWindow::background_color(const float& r, const float& b, const float& g)
{
	background_color_ = glm::vec3(r, g, b);
}

bool ImGuiSDLWindow::setup(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "errror: SDL_Init() : %s \n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	window_ = SDL_CreateWindow(argv[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, window_flags);
	if (window_ == nullptr)
	{
		fprintf(stderr, "errror: SDL_CreateWindow() : %s \n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	gl_context_ = SDL_GL_CreateContext(window_);
	SDL_GL_MakeCurrent(window_, gl_context_);
	SDL_GL_SetSwapInterval(1);
	SDL_ShowWindow(window_);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.WantCaptureKeyboard = false;
	io.WantCaptureMouse = false;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window_, gl_context_);
	ImGui_ImplOpenGL2_Init();

	return on_setup(argc, argv);;
}

void ImGuiSDLWindow::dispose()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (gl_context_ != nullptr)
	{
		SDL_GL_DeleteContext(gl_context_);
		gl_context_ = nullptr;
	}
	if (window_ != nullptr)
	{
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}
	SDL_Quit();
}

void ImGuiSDLWindow::main_loop()
{
	SDL_Event evt;
	while (!break_main_loop_flag_)
	{
		while (SDL_PollEvent(&evt))
		{
			ImGui_ImplSDL2_ProcessEvent(&evt);
			switch (evt.type)
			{
			case SDL_KEYUP:
				switch (evt.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit();
					break;
				default:
					break;
				}
				break;
			case SDL_QUIT:
				quit();
				break;
			default:
				break;
			}
		}

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(window_);
		ImGui::NewFrame();

		on_imgui();

		ImGui::Render();
		ImGuiIO& io = ImGui::GetIO();

		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(background_color_.x, background_color_.y, background_color_.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		on_draw();

		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(window_);
	}
}

