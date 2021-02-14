#include "App.h"
#include "OrthographicCamera.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Timer.h"

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
		SAFE_DELETE(pGameObject);
	
	InputManager::GetInstance()->Cleanup();

	ShutDown();
}

bool Integrian::App::Initialize()
{
	uint32_t width = 640;
	uint32_t height = 480;

#pragma region SDL Stuff
	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	m_pWindow = SDL_CreateWindow(
		"Programming 4 Assignment - Rhidian De Wit",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL);

	if (!m_pWindow)
	{
		std::cerr << "Error: m_pWindow failed" << std::endl;
		return false;
	}

	SDL_GLContext context = SDL_GL_CreateContext(m_pWindow);
	if (context == nullptr)
		std::cerr << "Error: App.cpp CreateContext() failed" << std::endl;

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
		std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << std::endl;

	if (TTF_Init() != 0)
		std::cout << SDL_GetError() << std::endl;
#pragma endregion

	// == Set Window Size For InputManager ==
	InputManager::GetInstance()->SetWindowSize(width, height);

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

	m_IsInitializationFinished = true;
	m_HasStarted = true;
}

void Integrian::App::ShutDown()
{
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

	float fpsTimer{};
	float timeSinceLastUpdate{};

	// == Event Loop ==
	while (g_IsLooping)
	{
		// == Update Timer ==
		timer.Update();
		const float dt{ timer.GetElapsedSeconds() };

		// == Handle Input ==
		InputManager::GetInstance()->HandleInput(dt);

		// == Update ==
		UpdateApplication(timeSinceLastUpdate);

		// == Render ==
		TransformCameraAndRender();

		// == Count FPS ==
		fpsTimer += dt;
		timeSinceLastUpdate += dt;

		if (fpsTimer >= 1.f)
		{
			// one second has passed, so we can print how many frames we have
			std::cout << "Timer FPS: " << timer.GetFPS() << std::endl;
			fpsTimer = 0.f;
			timeSinceLastUpdate = 0.f;
		}
	}
}

void Integrian::App::TransformCameraAndRender() const
{
	ClearBackground();
	// == YOU CAN CHANGE THE TYPE OF THE CAMERA ==
	// == DO NOT CHANGE THE IMPLENTATION OF THIS FUNCTION UNLESS YOU EXPLICITLY WANT TO CHANGE HOW THE CAMERA WORKS ==
	glPushMatrix();
	{
		m_pCamera->Transform(m_Target);
		Render();
	}
	glPopMatrix();

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
	
	Update(timer.GetElapsedSeconds());

	LateUpdate(timer.GetElapsedSeconds());

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