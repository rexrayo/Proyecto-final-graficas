#include "EDClientpch.h"



#include "EasyDIPAPI/Loaders.h"
#include "EasyDIPAPI/Objff.h"



#ifndef __ED_CLIENT_APPLICATION__
#define __ED_CLIENT_APPLICATION__

class Application
{
	float test = 0;
	//template <typename TT> using ptr = std::shared_ptr<TT>;
	//ImGui::FileBrowser fileDialog;
	GLFWwindow *window;

	unsigned int texId = 0;
	unsigned int texOGImg = 0;
	bool pA = 1;
	int sel = -1;
	int windowWidth = 1024;
	int windowHeight = 750;
	int widthConv = 1;
	int heightConv = 1;
	float color[7][7][4];
	float cFondo[3] = { 0.0f, 0.0f, 0.0f };
	float cPuntos[3] = { 0.0f,0.0f,1.0f };
	float cFull[3] = { 0.0f,0.0f,1.0f };
	float cLine[3] = { 1.0f,0.0f,0.0f };
	int pivotX = 0, pivotY = 0;
	float Near = 1.0f, Pluz = 0.5f;
	bool show_demo_window = true, pun = false, lin = false, full = true, bfc=false, zb=true, box=false, Nv=false, Nf=false, mause=false;
	bool isLuz = false, plane = false, blinn = true, pongFace = true, gurond = false, eme = false;
	bool fin = false, mus = true, fullscreen = false, start = true, terror = false;
public:
	Application();
	~Application();
	
	void MainLoop();
	void Render();
	void ImGui();
	void ImGui2();
	void Init();
	void ponerLuz();
	void Game();
	
	static void HelpMarker(const char* desc);

};

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
#endif // !1

