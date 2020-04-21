#include "Application.h"


using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();
ISound* music;

extern Shader* bwShader;
extern Shader* luzShader;
vector<Objff*> models;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float xoffset;
float yoffset;

float yaw = -90.0f;	
float pitch = 0.0f;

unsigned int VBO = 0;
unsigned int VAO = 0;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//camera
Camera  camera(glm::vec3(-42.0f, 0.0f, -25.0f));
GLfloat lastX = 1024.0f / 2.0;
GLfloat lastY = 750.0f / 2.0;
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


Application::Application() {

	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		__debugbreak();
		return;
	}

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
	

	// Create window with graphics context
	 window = glfwCreateWindow(windowWidth, windowHeight, "LCD", NULL, NULL);
	 
	 if (window == NULL) {
		__debugbreak();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync


	bool err = gladLoadGL() == 0;

	printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		__debugbreak();
		return;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsLight();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	/*Objff* objeto = Objff::Instance();
	
	CG::Load("../Models/cube.off", objeto);
	models.push_back(objeto);

	//models[0]->Draw();

	Shader* bwShader = new Shader("bw.vert", "bw.frag");
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();

	

	bwShader->use();*/

	//CG::Model model = CG::Load("../Models/modelo.obj", );
	//models.push_back(model);
	//	Scene.LoadModel("pelota.obj")
	bwShader = new Shader("bw.vert", "bw.frag");
	ponerLuz();
	Game();
	
	//ponerLuz();
	//luzShader = new Shader("bw.vert", "luz.frag");
	//	Scene.add("pelota");

	//Scene.Save("escena_de_prueba");
	//Scene.Load("escena_de_prueba.graficas");
	//
	//void Scene::Load(std::string path) {
	//	LoadScene(path);
	//}

	// (optional) set browser properties
	//fileDialog.SetTitle("title");
	//fileDialog.SetTypeFilters({ ".jpg", ".png", ".jpeg" });
	Init();
}

Application::~Application() {

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	//delete img;
	//delete composite;
	//delete bw;
}


void Application::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
		glClearColor(cFondo[0], cFondo[1], cFondo[2], 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//if (show_demo_window)
			//ImGui::ShowDemoWindow(&show_demo_window);

		ImGui();
		ImGui2();

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Rendering

		if (mus)
		{
			mus = false;
			music = SoundEngine->play3D("../audio/horror.mp3", //Archivo de sonido 
				vec3df(0, 0, 0), // Posición  
				true, //ejecutar indefinidamente (looped) 
				false,
				true //retornar un puntero al sonido para poder controlarlo (track)    
			);
		}
		if (((int(camera.GetPosition().x) == -34 && int(camera.GetPosition().z) == -38)
			||(int(camera.GetPosition().x) == -33 && int(camera.GetPosition().z) == -37) 
			||(int(camera.GetPosition().x) == -32 && int(camera.GetPosition().z) == -36))
			&& !fin) {
			gurond = false;
			fin = true;
			music->stop();
			music = SoundEngine->play3D("../audio/breakout.mp3", //Archivo de sonido 
				vec3df(0, 0, 0), // Posición  
				true, //ejecutar indefinidamente (looped) 
				false,
				true //retornar un puntero al sonido para poder controlarlo (track)    
			);
		}

		if (((int(camera.GetPosition().x) == 35 && int(camera.GetPosition().z) == 14)
			|| (int(camera.GetPosition().x) == 36 && int(camera.GetPosition().z) == 15)
			|| (int(camera.GetPosition().x) == 34 && int(camera.GetPosition().z) == 13))
			&& !terror) {
			terror = true;
			music->stop();
			music = SoundEngine->play3D("../audio/horror2.mp3", //Archivo de sonido 
				vec3df(0, 0, 0), // Posición  
				true, //ejecutar indefinidamente (looped) 
				false,
				true //retornar un puntero al sonido para poder controlarlo (track)    
			);
		}

		if (start && 
			((int(camera.GetPosition().x) == -38 && int(camera.GetPosition().z) == -25)
			|| (int(camera.GetPosition().x) == -37 && int(camera.GetPosition().z) == -26)
			|| (int(camera.GetPosition().x) == -39 && int(camera.GetPosition().z) == -24)))
		{
			gurond = true;

			start = false;
		}
		
		ImGui::Render();
		Render();


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
}

void Application::Render()
{
	int ii = 0;
	int ij = models.size() - 1;

	while(ii <= ij)
	{	
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 Projection = glm::mat4(1.0f);
		

		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));


		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		glm::mat4 View;
		View = camera.GetViewMatrix();

		if (pA == 1)
		{
			Projection = glm::perspective(camera.GetZoom(), (float)windowWidth / (float)windowHeight, Near, 100.0f);
		}
		else
		{
			Projection = glm::ortho(-(float)windowWidth / 800.0f, (float)windowWidth / 800.0f, -(float)windowHeight / 800.0f, (float)windowHeight / 800.0f, Near, 100.0f);
		}
		/*glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);*/

		glm::mat4 scale = glm::mat4(1.0f);
		glm::mat4 rota = glm::mat4(0.0f);
		glm::mat4 rotax = glm::mat4(0.0f);
		glm::mat4 rotay = glm::mat4(0.0f);
		glm::mat4 rotaz = glm::mat4(0.0f);
		glm::mat4 tran = glm::mat4(0.0f);

		
		bwShader->use();

		bwShader->setVec3("objectColor", glm::vec3(models[ii]->cFull[0], models[ii]->cFull[1], models[ii]->cFull[2]));
		bwShader->setVec3("viewPos", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		bwShader->setInt("blinn", blinn);
		//bwShader->setVec3("lightPos", models[0]->t-0.5f);
		bwShader->setVec3("lightColor", glm::vec3(models[0]->cFull[0], models[0]->cFull[1], models[0]->cFull[2]));
		bwShader->setBool("isLuz", models[ii]->isLuz);
		bwShader->setBool("pongFlat", pongFace);
		bwShader->setBool("blinn", blinn);
		bwShader->setBool("gurond", gurond);
		bwShader->setBool("off", models[0]->off);

		if (models[0]->off)
		{
		}
		else {
			bwShader->setVec3("light.position", models[0]->t - 0.5f);
			bwShader->setVec3("light.ambient", models[0]->ambient);
			bwShader->setVec3("light.diffuse", models[0]->diffuse);
			bwShader->setVec3("light.specular", models[0]->specular);
		}


		bwShader->setVec3("material.ambient", models[ii]->ambient);
		bwShader->setVec3("material.diffuse", models[ii]->diffuse);
		bwShader->setVec3("material.specular", models[ii]->specular);
		bwShader->setFloat("material.shininess", models[ii]->shininess);

		bwShader->setMat4("proj", Projection);
		bwShader->setMat4("view", View);

		rotax = glm::rotate(Model, models[ii]->rot.x, glm::vec3(1, 0, 0));
		rotay = glm::rotate(Model, models[ii]->rot.y, glm::vec3(0, 1, 0));
		rotaz = glm::rotate(Model, models[ii]->rot.z, glm::vec3(0, 0, 1));
		rota = rotax * rotay * rotaz;

		if (models[ii]->isLuz)
		{
			tran = glm::translate(Model, glm::vec3(models[ii]->t)+ glm::vec3(0.0f, 5.0f, 0.0f));
			scale = glm::scale(Model, glm::vec3(models[ii]->scale.x, models[ii]->scale.y, models[ii]->scale.z) * 0.2f);
		}
		else
		{
			tran = glm::translate(Model, glm::vec3(models[ii]->t + 0.5f));
			scale = glm::scale(Model, glm::vec3(models[ii]->scale.x, models[ii]->scale.y, models[ii]->scale.z) * 4.0f);
		}

		Model = tran * scale * rota;

		bwShader->setMat4("model", Model);
		
		glBindVertexArray(models[ii]->VAO);

		//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		if (models[ii]->Nv)
		{
			models[ii]->Nvert();
		}

		if (models[ii]->Nf)
		{
			models[ii]->Nface();
		}
		
		if (models[ii]->full)
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			bwShader->setFloat("R", models[ii]->cFull[0]);
			bwShader->setFloat("G", models[ii]->cFull[1]);
			bwShader->setFloat("B", models[ii]->cFull[2]);
			glPolygonOffset(8.0f, 8.0f);
			glDrawArrays(GL_TRIANGLES, 0, models[ii]->drawArrays.size());
			glDisable(GL_POLYGON_OFFSET_FILL);
		//glDrawArrays(GL_TRIANGLES, 0, models[ii]->drawArrays.size());
		}
		if (models[ii]->pun)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			bwShader->setFloat("R", models[ii]->cPuntos[0]);
			bwShader->setFloat("G", models[ii]->cPuntos[1]);
			bwShader->setFloat("B", models[ii]->cPuntos[2]);
			glPointSize(5.0f);
			glDrawArrays(GL_TRIANGLES, 0, models[ii]->drawArrays.size());
			glPointSize(1.0f);

		}
		if (models[ii]->lin)
		{
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			bwShader->setFloat("R", models[ii]->cLine[0]);
			bwShader->setFloat("G", models[ii]->cLine[1]);
			bwShader->setFloat("B", models[ii]->cLine[2]);
			glPolygonOffset(8.0f, 8.0f);
			glDrawArrays(GL_TRIANGLES, 0, models[ii]->drawArrays.size());
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		ii++;
	}
}

void Application::ponerLuz(){
	isLuz = true;
	Objff* objeto = new Objff();
	objeto->isLuz = true;
	objeto->shininess = 8.0f;
	CG::Load("../Models/luz.obj", objeto);
	models.push_back(objeto);
	sel++;

	unsigned int& VBO = objeto->VBO, & VAO = objeto->VAO, & EBO = objeto->EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, models[sel]->drawArrays.size() * sizeof(glm::vec3), &models[sel]->drawArrays[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}

void Application::Game() {
	Objff* objeto = new Objff();
	objeto->isLuz = false;
	objeto->shininess = 8.0f;
	CG::Load("../Models/Labyrinth.obj", objeto);
	models.push_back(objeto);
	sel++;
	int last = sel;
	unsigned int& VBO = objeto->VBO, & VAO = objeto->VAO, & EBO = objeto->EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, objeto->drawArrays.size() * sizeof(glm::vec3), &objeto->drawArrays[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//normales vert
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, objeto->vnArrays.size() * sizeof(glm::vec3), &objeto->vnArrays[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//normales faces
	GLuint normalFacebuffer;
	glGenBuffers(1, &normalFacebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalFacebuffer);
	glBufferData(GL_ARRAY_BUFFER, objeto->fArray.size() * sizeof(glm::vec3), &objeto->fArray[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalFacebuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

}



void Application::ImGui2()
{
	ImGui::Begin("Escapa rapido");
		ImGui::Text("Escapa rapido");
		ImGui::Text("Escapa rapido");
		ImGui::Text("Escapa rapido");
		ImGui::Text("Escapa rapi..");
		ImGui::Text("Escapa ra..");
		ImGui::Text("Escapa...");
		ImGui::Text("Esc...");
		ImGui::Text("...");
		ImGui::Text("..");
		ImGui::Text(".");
	ImGui::End();
}




void Application::ImGui()
{

	//ImGui::SliderFloat("test", &test, 0, 1);

	// w=87, a=65, s=83,d=68,

	ImGui::Begin("Opciones:");
	static bool alpha_preview = true;
	static bool alpha_half_preview = false;
	static bool drag_and_drop = true;
	static bool options_menu = true;
	static bool hdr = false;
	ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
	
	ImGuiIO& io = ImGui::GetIO();
	ImGuiBackendFlags backend_flags = io.BackendFlags;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.BackendFlags |= ImGuiBackendFlags_HasGamepad;



	for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) {
		if (ImGui::IsKeyPressed(i)) {
			if (i == 67) { mause = !mause; }
		}
	}
	ImGui::Checkbox("mause", &mause);
	if (mause)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (ImGui::IsMousePosValid()) {
			if (firstMouse)
			{
				lastX = io.MousePos.x;
				lastY = io.MousePos.y;
				firstMouse = false;
			}
			GLfloat xOffset = io.MousePos.x - lastX;
			GLfloat yOffset = lastY - io.MousePos.y;  // Reversed since y-coordinates go from bottom to left

			lastX = io.MousePos.x;
			lastY = io.MousePos.y;

			camera.ProcessMouseMovement(xOffset, yOffset);

			/*xoffset = io.MousePos.x - lastX;
			yoffset = lastY - io.MousePos.y;
			lastX = io.MousePos.x;
			lastY = io.MousePos.y;

			const float sensitivity = 0.05f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;*/
		}
		/*yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);*/
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}


	const float cameraSpeed = 0.05f;
	for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) {
		if (ImGui::IsKeyPressed(i)) {
			if (i == 87) { 
				//cameraPos += cameraSpeed * cameraFront;
				camera.ProcessKeyboard(FORWARD, deltaTime);
				//std::cout << "position x: " << int(camera.GetPosition().x);
				//std::cout << "position z: " << int(camera.GetPosition().z);
			}
		}
		if (ImGui::IsKeyPressed(i)) {
			if (i == 65) { 
				//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; 
				camera.ProcessKeyboard(LEFT, deltaTime);
			}
		}
		if (ImGui::IsKeyPressed(i)) {
			if (i == 83) { 
				//cameraPos -= cameraSpeed * cameraFront; 
				camera.ProcessKeyboard(BACKWARD, deltaTime);
			}
		}
		if (ImGui::IsKeyPressed(i)) {
			if (i == 68) { 
				//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; 
				camera.ProcessKeyboard(RIGHT, deltaTime);
			}
		}
		if (ImGui::IsKeyPressed(i)) {
			if (i == 88) {
				//cameraPos +=  cameraUp * cameraSpeed; 
				camera.ProcessKeyboard(UP, deltaTime);
			}
		}
		if (ImGui::IsKeyPressed(i)) {
			if (i == 90) {
				//cameraPos -= cameraUp * cameraSpeed; 
				camera.ProcessKeyboard(DOWN, deltaTime);
			}
		}
		if (ImGui::IsKeyPressed(i)) {
			if (i == 70) {
				fullscreen = !fullscreen;
				glfwSetWindowMonitor(window, fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, windowWidth, windowHeight, GLFW_DONT_CARE);
			}
		}
		if (ImGui::IsKeyPressed(i)) {
			if (i == 75) {
				ImGui_ImplOpenGL3_Shutdown();
				ImGui_ImplGlfw_Shutdown();
				ImGui::DestroyContext();

				glfwDestroyWindow(window);
				glfwTerminate();
			}
		}
	}

	for (int i = 0; i < IM_ARRAYSIZE(io.NavInputs); i++) {

		if (io.NavInputs[i] > 0.0f) {
			if (i == 11) {
				camera.ProcessKeyboard(FORWARD, deltaTime);
			}
		}
		if (io.NavInputs[i] > 0.0f) {
			if (i == 8) {
				camera.ProcessKeyboard(LEFT, deltaTime);
			}
		}
		if (io.NavInputs[i] > 0.0f) {
			if (i == 9) {
				camera.ProcessKeyboard(RIGHT, deltaTime);
			}
		}
		if (io.NavInputs[i] > 0.0f) {
			if (i == 10) {
				camera.ProcessKeyboard(BACKWARD, deltaTime);
			}
		}
	}


	if (ImGui::Button("File")) {
		isLuz = false;
		OPENFILENAME ofn;
		wchar_t szFile[100];
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = L"All Files\0*.OBJ;*.OFF";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		GetOpenFileName(&ofn);
		std::string file;
		std::wstring aux(szFile);
		std::string str(aux.begin(), aux.end());
		file = str;

		if (file == "")
		{
			std::cout << "No selecciono ningun archivo";
		}
		else
		{
			Objff* objeto = new Objff();
			objeto->isLuz = false;
			objeto->shininess = 8.0f;
			CG::Load(file, objeto);
			models.push_back(objeto);
			sel++;
			int last = sel;
			unsigned int &VBO = objeto->VBO, &VAO = objeto->VAO, &EBO = objeto->EBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);


			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, objeto->drawArrays.size() * sizeof(glm::vec3), &objeto->drawArrays[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			//normales vert
			GLuint normalbuffer;
			glGenBuffers(1, &normalbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glBufferData(GL_ARRAY_BUFFER, objeto->vnArrays.size() * sizeof(glm::vec3), &objeto->vnArrays[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			//normales faces
			GLuint normalFacebuffer;
			glGenBuffers(1, &normalFacebuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalFacebuffer);
			glBufferData(GL_ARRAY_BUFFER, objeto->fArray.size() * sizeof(glm::vec3), &objeto->fArray[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, normalFacebuffer);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
	}


	ImGui::Text("Color fondo:");
	ImGui::ColorEdit3("MyColor##4", (float*)&cFondo, misc_flags);

	

	//if (texOGImg)
	//{
		//ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
	//}

	//if (ImGui::Button("recompile"))
	//{
		//delete bwShader;
		//std::string vert = Shader::GetSrcFromFile("bw.vert");
		//std::string frag = Shader::GetSrcFromFile("bw.frag");


		//bwShader = Shader::FromString(vert.c_str(), frag.c_str());

		
		//std::cout << "recompiled" << std::endl;

		//std::unique_ptr<RawData> negative{ EDNegativeHA(img->data, img->GetWidth(), img->GetHeight()) };
		//texId = GetTexture(negative.get(), img->GetWidth(), img->GetHeight());


	//}

	//if (ImGui::Button("Save Image"))
	//{
	//	ImGui::SameLine();
	//	//ImGui::InputText("imgFile")
	//}

	/*if (ImGui::Button("Load Image"))
	{
		Objff* objeto = new Objff();

		CG::Load("../Models/Porsche_911_GT2.obj", objeto);
		models.push_back(objeto);
		sel++;

		unsigned int &VBO = objeto->VBO, &VAO = objeto->VAO, &EBO = objeto->EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);


		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		glBufferData(GL_ARRAY_BUFFER, models[sel]->drawArrays.size() * sizeof(glm::vec3), &models[sel]->drawArrays[sel], GL_STATIC_DRAW);


		//glBufferData(GL_ARRAY_BUFFER, models[0]->v.size() * sizeof(glm::vec3), &models[0]->v[0], GL_STATIC_DRAW);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, models[0]->f.size() * sizeof(glm::uvec3), &models[0]->f[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}*/

	//	fileDialog.Display();

	//if (ImGui::DragFloat("Near", &Near, 0.01f));

	ImGui::Checkbox("BFC", &bfc);

	if (bfc)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	ImGui::Checkbox("ZB", &zb);
	if (zb)
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	//if (ImGui::Checkbox("Box", &box));

	//if (box)
	//{
	//	models[sel]->Box();
	//}

	if (models[sel]->isLuz)
	{
		ImGui::Checkbox("Prender/Apagar", &models[0]->off);
	}


	if (models.size() > 0)
	{
		//if (ImGui::Checkbox("Normales por vert", &models[sel]->Nv));

		//if (ImGui::Checkbox("Normales por cara", &models[sel]->Nf));
		
		//if (ImGui::Checkbox("Perspective/Ortogonal", &pA));

		ImGui::Checkbox("Pong/Flat", &pongFace);
		ImGui::Checkbox("Blinn", &blinn);
		ImGui::Checkbox("Gurond", &gurond);

		ImGui::Text("Prop:");
		ImGui::ColorEdit3("ambient", (float*)&models[sel]->ambient, ImGuiColorEditFlags_Float | misc_flags);
		ImGui::ColorEdit3("diffuse", (float*)&models[sel]->diffuse, ImGuiColorEditFlags_Float | misc_flags);
		ImGui::ColorEdit3("specular", (float*)&models[sel]->specular, ImGuiColorEditFlags_Float | misc_flags);
		ImGui::SliderFloat("shininess", &models[sel]->shininess, 0.0f, 64.0f, "%.3f", (1.0f));

		ImGui::Checkbox("Obsidian", &models[sel]->material1);
		if (models[sel]->material1)
		{
			models[sel]->material3 = false, models[sel]->material2 = false, models[sel]->white = false;
			models[sel]->ambient = glm::vec3(0.05375, 0.05, 0.06625);
			models[sel]->diffuse = glm::vec3(0.18275, 0.17, 0.22525);
			models[sel]->specular = glm::vec3(0.332741, 0.328634, 0.346435);
			models[sel]->shininess = 0.3f;
		}

		ImGui::Checkbox("Gold", &models[sel]->material2);
		if (models[sel]->material2)
		{
			models[sel]->material1 = false, models[sel]->material3 = false, models[sel]->white = false;
			models[sel]->ambient = glm::vec3(0.24725, 0.1995, 0.0745);
			models[sel]->diffuse = glm::vec3(0.75164, 0.60648, 0.22648);
			models[sel]->specular = glm::vec3(0.628281, 0.555802, 0.366065);
			models[sel]->shininess = 0.4f;
		}

		ImGui::Checkbox("Cyan rubber", &models[sel]->material3);
		if (models[sel]->material3)
		{
			models[sel]->material1 = false, models[sel]->material2 = false, models[sel]->white = false;
			models[sel]->ambient = glm::vec3(0.0, 0.05, 0.05);
			models[sel]->diffuse = glm::vec3(0.4, 0.5, 0.5);
			models[sel]->specular = glm::vec3(0.04, 0.7, 0.7);
			models[sel]->shininess = 0.078125f;
		}

		ImGui::Checkbox("White", &models[sel]->white);
		if(models[sel]->white)
		{
			models[sel]->material1 = false, models[sel]->material2 = false, models[sel]->material3 = false;
			models[sel]->ambient = glm::vec3(1, 1, 1);
			models[sel]->diffuse = glm::vec3(1, 1, 1);
			models[sel]->specular = glm::vec3(1, 1, 1);
			models[sel]->shininess = 8.0f;
		}

		//if (ImGui::Checkbox("Puntos", &models[sel]->pun));
		//ImGui::Text("Color puntos:");
		//ImGui::ColorEdit3("MyColor##1", (float*)&models[sel]->cPuntos, misc_flags);

		//if (ImGui::Checkbox("Full", &models[sel]->full));
		//ImGui::Text("Color full:");
		ImGui::ColorEdit3("Color:", (float*)&models[sel]->cFull, misc_flags);

		//if (ImGui::Checkbox("Lineas", &models[sel]->lin));
		//ImGui::Text("Color lineas:");
		//ImGui::ColorEdit3("MyColor##3", (float*)&models[sel]->cLine, misc_flags);
	}
		
	if (models.size() > 0)
	{
		
		ImGui::Text("Escalar:");
		ImGui::SliderFloat("Esca X", &models[sel]->scale.x, 0.001f, 4.0f, "%.3f", (1.0f));
		ImGui::SliderFloat("Esca Y", &models[sel]->scale.y, 0.001f, 4.0f, "%.3f", (1.0f));
		ImGui::SliderFloat("Esca Z", &models[sel]->scale.z, 0.001f, 4.0f, "%.3f", (1.0f));
		if (ImGui::SliderFloat("Esca All", &models[sel]->all, 0.001f, 4.0f, "%.3f", (1.0f))) {
			models[sel]->scale.x = models[sel]->all;
			models[sel]->scale.y = models[sel]->all;
			models[sel]->scale.z = models[sel]->all;
		}
		
	}

	if (models.size() > 0)
	{
		ImGui::Text("Rotar:");
		ImGui::DragFloat("X", &models[sel]->rot.x, 0.1f);
		ImGui::DragFloat("Y", &models[sel]->rot.y, 0.1f);
		ImGui::DragFloat("Z", &models[sel]->rot.z, 0.1f);
		//ImGui::SliderFloat("Rotar X", &models[sel]->rot.x, -180.0f, 180.0f, "%.4f", (1.0f));
		//ImGui::SliderFloat("Rotar Y", &models[sel]->rot.y, -180.0f, 180.0f, "%.4f", (1.0f));
		//ImGui::SliderFloat("Rotar Z", &models[sel]->rot.z, -180.0f, 180.0f, "%.4f", (1.0f));

	}

	if (models.size() > 0)
	{
		ImGui::Text("Transladar:");
		ImGui::SliderFloat("Transl X", &models[sel]->t.x, -6.0f, 6.0f, "%.3f", (1.0f));
		ImGui::SliderFloat("Transl Y", &models[sel]->t.y, -6.0f, 6.0f, "%.3f", (1.0f));
		ImGui::SliderFloat("Transl Z", &models[sel]->t.z, -6.0f, 6.0f, "%.3f", (1.0f));

	}

	if (models.size() > 0)
	{
		ImGui::Text("Seleccione objeto con el slider");
		ImGui::SliderInt("Modelo numero: ", &sel, 0, models.size() - 1);
	}

	//if (fileDialog.HasSelected())
	//{
	//	std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
	//	
	//	fileDialog.Close();
	//	fileDialog.ClearSelected();
	//}


	ImGui::End();

}

void Application::Init() {}

void Application::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
