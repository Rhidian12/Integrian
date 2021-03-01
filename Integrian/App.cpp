#include "App.h"
#include "OrthographicCamera.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Timer.h"
#include "Logger.h"

// == Global Variables ==
extern bool g_IsLooping;

Integrian::App::App()
{
	if (!Initialize())
		throw InitialisationFailedException{};
}

Integrian::App::~App()
{
	for (GameObject* pGameObject : m_pGameObjects)
		SafeDelete(pGameObject);
	m_pGameObjects.clear();

	for (Command* pCommand : m_pCommands)
		SafeDelete(pCommand);
	m_pCommands.clear();
	
	ShutDown();
}

bool Integrian::App::Initialize()
{
	uint32_t width = 640;
	uint32_t height = 480;

	Logger& logger{ Logger::GetInstance() };

#pragma region SDL Stuff
	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

	m_pWindow = SDL_CreateWindow(
		"Programming 4 Assignment - Rhidian De Wit",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL);

	if (!m_pWindow)
	{
		logger.Log("Error: m_pWindow failed in App::Initialize()\n", ErrorLevel::severeError);
		return false;
	}

	SDL_GLContext context = SDL_GL_CreateContext(m_pWindow);
	if (context == nullptr)
		logger.Log("App::Initialize() CreateContext() failed\n", ErrorLevel::severeError);

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		logger.Log("App::Initialize() error when calling SDL_GL_SetSwapInterval ", ErrorLevel::error);
		logger.Log(SDL_GetError(), ErrorLevel::error);
		logger.Log("\n", ErrorLevel::error);
		return false;
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, width, 0, height); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangu	lar region of the window where the image is drawn.
	glViewport(0, 0, width, height);

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize PNG loading
	const int pngFlags{ IMG_INIT_PNG };
	const int jpgFlags{ IMG_INIT_JPG };
	if (!(IMG_Init(pngFlags) & pngFlags) || !(IMG_Init(jpgFlags) & jpgFlags))
		logger.Log("SDL_image could not initialize! SDL_image Error: %s\n", ErrorLevel::severeError);

	if (TTF_Init() != 0)
		logger.Log(SDL_GetError(), ErrorLevel::severeError);
#pragma endregion

#pragma region ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
#pragma endregion

	// == Set Window Size For InputManager ==
	InputManager::GetInstance().SetWindowSize(width, height);

	// == Seed rand() ==
	srand(static_cast<unsigned int>(time(nullptr)));

	// == Set Window Size == 
	m_WindowWidth = width;
	m_WindowHeight = height;

	// Initialise Datapath
	TextureManager::GetInstance().Init("Data/");

	return true;
}

bool Integrian::App::InitializeCamera()
{
	m_pCamera = std::make_unique<OrthographicCamera>(m_WindowWidth, m_WindowHeight, GetLevelBoundaries());
	return m_pCamera != nullptr;
}

void Integrian::App::FinishInitializationOfApp()
{
	Start();
	if (!InitializeCamera())
		throw InitialisationFailedException{};

	Logger::GetInstance().Log("Initialisation finished!\n", ErrorLevel::noWarning);

	m_IsInitializationFinished = true;
	m_HasStarted = true;
}

void Integrian::App::ShutDown()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Integrian::App::Run()
{
	if (!m_IsInitializationFinished)
		FinishInitializationOfApp();

	if (!m_HasStarted)
		throw RuntimeInitialisationFailed{};

	Timer& timer = Timer::GetInstance();

	float timeSinceLastUpdate{};

	// == Event Loop ==
	while (g_IsLooping)
	{
		// == Update Timer ==
		timer.Update();

		// == Handle Input ==
		InputManager::GetInstance().HandleInput();

		// == Update ==
		UpdateApplication(timeSinceLastUpdate);

		// == Render ==
		TransformCameraAndRender();

		// == Update The Timer For The Fixed Update ==
		timeSinceLastUpdate += timer.GetElapsedSeconds();
	}
}

void Integrian::App::TransformCameraAndRender() const
{
	ClearBackground();
	// == YOU CAN CHANGE THE TYPE OF THE CAMERA ==
	// == DO NOT CHANGE THE IMPLENTATION OF THIS FUNCTION UNLESS YOU EXPLICITLY WANT TO CHANGE HOW THE CAMERA WORKS ==
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	glPushMatrix();
	{
		m_pCamera->Transform(m_Target);
		Render();
	}
	glPopMatrix();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	// == Swap back- and frontbuffer ==
	SDL_GL_SwapWindow(m_pWindow);
}

void Integrian::App::UpdateApplication(float& timeSinceLastUpdate)
{
	Timer& timer = Timer::GetInstance();

	while (timeSinceLastUpdate > timer.GetTimePerFrame())
	{
		FixedUpdate(timer.GetTimePerFrame());
		timeSinceLastUpdate -= timer.GetTimePerFrame();
	}
	
	const float dt{ timer.GetElapsedSeconds() };

	Update(dt);

	LateUpdate(dt);

	// == THE UPDATE NEEDS m_Target TO BE SET AT THE END FOR THE CAMERA POSITIONING ==
	m_Target = GetTarget();
}

void Integrian::App::SetWindowSize(const uint32_t windowWidth, const uint32_t windowHeight)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
}

uint32_t Integrian::App::GetWindowWidth() const
{
	return m_WindowWidth;
}

uint32_t Integrian::App::GetWindowHeight() const
{
	return m_WindowHeight;
}

void Integrian::App::ClearBackground() const
{
	glClearColor(192.f / 255.f, 192.f / 255.f, 192.f / 255.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}