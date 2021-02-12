#include "App.h"
#include "OrthographicCamera.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Timer.h"

// == Global Variables ==
extern bool g_IsLooping;
extern bool g_IsUpdateFixed;
extern float g_TimePerFrame;

Engine::App::App()
{
	if (!Initialize())
		throw InitialisationFailedException{};
}

Engine::App::~App()
{
	SAFE_DELETE(m_pCamera);

	TextureManager::GetInstance()->CleanUp();
	InputManager::GetInstance()->Cleanup();

	ShutDown();
}

//void Engine::App::Start()
//{
//	if (!InitializeCamera())
//		throw InitialisationFailedException{};
//
//	m_HasStarted = true;
//}

bool Engine::App::Initialize()
{
	uint32_t width = 600;
	uint32_t height = 400;

#pragma region SDL Stuff
	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	m_pWindow = SDL_CreateWindow(
		"Grapple Hook - Rhidian De Wit",
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
#pragma endregion

	// == Set Window Size For InputManager ==
	InputManager::GetInstance()->SetWindowSize(width, height);

	// == Seed rand() ==
	srand(static_cast<unsigned int>(time(nullptr)));

	// == Set Window Size == 
	m_WindowWidth = width;
	m_WindowHeight = height;

	// == Make The Timer And Start The Timer == 
	m_pTimer = std::make_unique<Timer>();

	return true;
}

bool Engine::App::InitializeCamera()
{
	m_pCamera = new OrthographicCamera{ m_WindowWidth,m_WindowHeight,GetLevelBoundaries() };
	return m_pCamera != nullptr;
}

void Engine::App::FinishInitialisationOfApp()
{
	Start();
	if (!InitializeCamera())
		throw InitialisationFailedException{};

	m_IsInitialisationFinished = true;
	m_HasStarted = true;
}

void Engine::App::ShutDown()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Engine::App::Run()
{
	if (!m_IsInitialisationFinished)
		FinishInitialisationOfApp();

	if(!m_HasStarted)
		throw RuntimeInitialisationFailed{};

	float fpsTimer{};
	float timeSinceLastUpdate{};

	// == Event Loop ==
	while (g_IsLooping)
	{
#pragma region Update Application
		if (g_IsUpdateFixed)
		{
			while (timeSinceLastUpdate > g_TimePerFrame)
			{
				// == Handle Input ==
				InputManager::GetInstance()->HandleInput(g_TimePerFrame);

				// == Update ==
				UpdateApplication(g_TimePerFrame);

				timeSinceLastUpdate -= g_TimePerFrame;
			}
		}
		else
		{
			// == Handle Input ==
			InputManager::GetInstance()->HandleInput(m_pTimer->GetElapsedSeconds());

			// == Update ==
			UpdateApplication(m_pTimer->GetElapsedSeconds());
		}
#pragma endregion

		// == Render ==
		TransformCameraAndRender();

		// == Update Timer ==
		m_pTimer->Update();

		// == Count FPS ==
		fpsTimer += m_pTimer->GetElapsedSeconds();
		timeSinceLastUpdate += m_pTimer->GetElapsedSeconds();
		if (fpsTimer >= 1.f)
		{
			// one second has passed, so we can print how many frames we have
			std::cout << "Timer FPS: " << m_pTimer->GetFPS() << std::endl;
			fpsTimer = 0.f;
			timeSinceLastUpdate = 0.f;
		}
	}
}

void Engine::App::TransformCameraAndRender() const
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

void Engine::App::UpdateApplication(const float elapsedSeconds)
{
	Update(elapsedSeconds);

	// == THE UPDATE NEEDS m_Target TO BE SET AT THE END FOR THE CAMERA POSITIONING ==
	m_Target = GetTarget();
}

void Engine::App::SetWindowSize(const uint32_t windowWidth, const uint32_t windowHeight)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
}

const uint32_t Engine::App::GetWindowWidth() const
{
	return m_WindowWidth;
}

const uint32_t Engine::App::GetWindowHeight() const
{
	return m_WindowHeight;
}

void Engine::App::ClearBackground() const
{
	glClearColor(192.f / 255.f, 192.f / 255.f, 192.f / 255.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}