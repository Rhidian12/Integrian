#include "IntegrianPCH.h" // Precompiler Header
#include "App.h" // Header
#include "OrthographicCamera.h" // Camera
#include "Timer.h" // Timer
#include "Logger.h" // Logger
#include "InputManager.h" // InputManager
#include "TextureManager.h" // TextureManager
#include "EventQueue.h" // EventQueue
#include "ThreadManager.h" // ThreadManager
#include "AudioLocator.h" // AudioLocator
#include "App_Selector.h" // App_Selector

// == Global Variables ==
extern std::atomic<bool> volatile g_IsLooping; // Used by the inputmanager, threadmanager and App::Run() to see when SDL_Quit event gets fired

Integrian::App::App(const std::string& name)
	: m_AppName{ name }
	, m_GameObjectID{}
	, m_TimeSinceLastUpdate{}
	, m_ClearColour{ 192.f, 192.f, 192.f }
{
	if (!Initialize())
		throw InitialisationFailedException{};

	if (!m_IsLibraryInitialised)
	{
		InitializeLibraries();
		m_IsLibraryInitialised = true;
	}

	//App_Selector::GetInstance().AddApplication(this);
}

void Integrian::App::RemoveCommand(const std::string& commandName)
{
	using UMapIterator = std::unordered_map<std::string, std::function<void()>>::iterator;
#ifdef _DEBUG
	const UMapIterator it{ m_Commands.find(commandName) };
	if (it != m_Commands.end())
	{
		InputManager::GetInstance().RemoveCommand(it->second);
		m_Commands.erase(commandName);
	}
	else
		Logger::LogWarning("RemoveCommand() did not find a command with name: " + commandName + "\n");
#else
	const UMapIterator it{ m_Commands.find(commandName) };
	if (it != m_Commands.end())
	{
		InputManager::GetInstance().RemoveCommand(it->second);
		m_Commands.erase(commandName);
	}
#endif // _DEBUG
}

Integrian::App::~App()
{
	for (std::pair<GameObjectInformation, GameObject*> pGameObject : m_pGameObjects)
		SafeDelete(pGameObject.second);

	m_pGameObjects.clear();

	AudioLocator::Cleanup();

	if (!m_IsLibraryDestroyed)
	{
		ShutDown();
		m_IsLibraryDestroyed = true;
	}
}

bool Integrian::App::Initialize()
{
	m_WindowWidth = 640;
	m_WindowHeight = 480;

	// == Set Window Size For InputManager ==
	InputManager::GetInstance().SetWindowSize(m_WindowWidth, m_WindowHeight);

	// == Seed rand() ==
	srand(static_cast<unsigned int>(time(nullptr)));

	return true;
}

bool Integrian::App::InitializeCamera()
{
	m_pCamera = std::make_unique<OrthographicCamera>(m_WindowWidth, m_WindowHeight, GetLevelBoundaries());
	return m_pCamera != nullptr;
}

bool Integrian::App::InitializeLibraries()
{
#pragma region SDL Stuff
	//Create window + surfaces
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) == -1)
		Logger::LogSevereError(std::string{ "SDL_Init failed:" } + SDL_GetError() + "\n");

	m_pWindow = SDL_CreateWindow(
		"Programming 4 Assignment - Rhidian De Wit",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_WindowWidth, m_WindowHeight,
		SDL_WINDOW_OPENGL);

	if (!m_pWindow)
	{
		Logger::LogSevereError("Error: m_pWindow failed in App::Initialize()\n");
		return false;
	}

	SDL_GLContext context = SDL_GL_CreateContext(m_pWindow);
	if (context == nullptr)
		Logger::LogSevereError("App::Initialize() CreateContext() failed\n");

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		Logger::LogError(std::string{ "App::Initialize() error when calling SDL_GL_SetSwapInterval " } + SDL_GetError() + "\n");
		return false;
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_WindowWidth, 0, m_WindowHeight); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangu	lar region of the window where the image is drawn.
	glViewport(0, 0, m_WindowWidth, m_WindowHeight);

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
		Logger::LogSevereError(std::string{ "SDL_image could not initialize! SDL_image Error: " } + SDL_GetError() + "\n");

	if (TTF_Init() != 0)
		Logger::LogSevereError(SDL_GetError());
#pragma endregion

#pragma region ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
#pragma endregion

#pragma region SDL_Mixer
	// this final parameter is the chunk size of the audio, this might have to be made larger if too much hooks are getting used
	// TODO: Load in all filesizes of music in our folder, and take the average of that
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 8, 2048) == -1)
		Logger::LogSevereError(std::string{ "SDL_Mixer failed to open! " } + Mix_GetError() + "\n");

	// == Initialize SDL_Mixer == 
	const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
	if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
		Logger::LogSevereError(std::string{ "SDL_Mixer failed to initialize!" } + Mix_GetError() + "\n");
#pragma endregion

	return true;
}

void Integrian::App::FinishInitializationOfApp()
{
	Start();

	for (const std::pair<GameObjectInformation, GameObject*>& pGameObject : m_pGameObjects)
		pGameObject.second->PostInitialize();

	if (!InitializeCamera())
		throw InitialisationFailedException{};

	Logger::LogNoWarning("Initialisation finished!\n");

	m_IsInitializationFinished = true;
	m_HasStarted = true;
}

void Integrian::App::ShutDown()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	Mix_CloseAudio();
	Mix_Quit();

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

	// == Event Loop ==
	//while (continueRunning)
	{
		// == Update Timer ==
		timer.Update();

		// == Handle Input ==
		InputManager::GetInstance().HandleInput();

		// == Update ==
		UpdateApplication();

		// == Render ==
		TransformCameraAndRender();

		// == Send New Frame ==
		//EventQueue::GetInstance().QueueEvent(Event{ "EndOfFrame" });
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

		for (const std::pair<GameObjectInformation, GameObject*>& pGameObject : m_pGameObjects)
			pGameObject.second->Render();

		Render();
	}
	glPopMatrix();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	// == Swap back- and frontbuffer ==
	SDL_GL_SwapWindow(m_pWindow);
}

void Integrian::App::UpdateApplication()
{
	Timer& timer = Timer::GetInstance();

	const float timePerFrame{ timer.GetTimePerFrame() };

	while (m_TimeSinceLastUpdate > timePerFrame)
	{
		for (const std::pair<GameObjectInformation, GameObject*> pGameObject : m_pGameObjects)
			pGameObject.second->FixedUpdate(timePerFrame);

		FixedUpdate(timePerFrame);
		m_TimeSinceLastUpdate -= timePerFrame;
	}

	const float dt{ timer.GetElapsedSeconds() };

	// Update the timer for the fixed update
	m_TimeSinceLastUpdate += dt;

	for (const std::pair<GameObjectInformation, GameObject*> pGameObject : m_pGameObjects)
		pGameObject.second->Update(dt);

	Update(dt);

	AudioLocator::GetAudio()->Update(dt); // update the audio
	EventQueue::GetInstance().Update(); // Update the event queue

	for (const std::pair<GameObjectInformation, GameObject*> pGameObject : m_pGameObjects)
		pGameObject.second->LateUpdate(dt);

	LateUpdate(dt);

	// == THE UPDATE NEEDS m_Target TO BE SET AT THE END FOR THE CAMERA POSITIONING ==
	m_Target = GetTarget();
}

void Integrian::App::SetWindowSize(const uint32_t windowWidth, const uint32_t windowHeight)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
}

bool Integrian::App::OnEvent(const Event& event)
{
	const std::string& eventName{ event.GetEvent() };

	if (eventName == "GC" || eventName == "Garbage Collection" || eventName == "Garbage_Collection")
	{
		for (auto it{ m_pGameObjects.begin() }; it != m_pGameObjects.end(); ++it)
		{
			if (it->second->GetIsMarkedForDeletion())
			{
				it = m_pGameObjects.erase(it);
			}
		}

		return true;
	}

	return false;
}

uint32_t Integrian::App::GetWindowWidth() const
{
	return m_WindowWidth;
}

uint32_t Integrian::App::GetWindowHeight() const
{
	return m_WindowHeight;
}

std::string Integrian::App::GetAppName() const
{
	return m_AppName;
}

Integrian::GameObject* Integrian::App::GetGameObject(const std::string& name) const
{
	for (const std::pair<GameObjectInformation, GameObject*>& pGameObject : m_pGameObjects)
		if (pGameObject.first.m_Identifier == name)
			return pGameObject.second;

#ifdef _DEBUG
	Logger::LogError("GameObject with name: " + name + " was not found and returned a nullptr!\n");
#endif // _DEBUG

	return nullptr;
}

const std::map<Integrian::GameObjectInformation, Integrian::GameObject*, Integrian::GameObjectInformationComparer>& Integrian::App::GetGameObjects() const
{
	return m_pGameObjects;
}

const Integrian::RGBColour& Integrian::App::GetClearColour() const noexcept
{
	return m_ClearColour;
}

void Integrian::App::AddGameObject(const std::string& name, GameObject* pGameObject)
{
	m_pGameObjects.insert(std::make_pair(GameObjectInformation{ name, m_GameObjectID++ }, pGameObject));
	pGameObject->Initialize();
}

void Integrian::App::RemoveGameObject(const std::string& name) noexcept
{
	for (const std::pair<GameObjectInformation, GameObject*>& pGameObject : m_pGameObjects)
	{
		if (pGameObject.first.m_Identifier == name)
		{
			pGameObject.second->SetIsActive(false);
			pGameObject.second->MarkForDeletion();
			return;
		}
	}

#ifdef _DEBUG
	Logger::LogError("App::RemoveGameObject() > name: " + name + " was not found!\n");
#endif // _DEBUG
}

void Integrian::App::SetClearColour(const RGBColour& colour) noexcept
{
	m_ClearColour = colour;
}

void Integrian::App::ClearBackground() const
{
	glClearColor(m_ClearColour.r / 255.f, m_ClearColour.g / 255.f, m_ClearColour.b / 255.f, m_ClearColour.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Integrian::App::OnAppEnter()
{
	if (!m_CC.empty())
	{
		for (uint8_t i{}; i < 4; ++i)
			InputManager::GetInstance().SetControllerCommands(m_CC[i], i);
	}

	if (!m_KC.empty())
		InputManager::GetInstance().SetKeyboardCommands(m_KC);

	if (!m_MC.empty())
		InputManager::GetInstance().SetMouseCommands(m_MC);
}

void Integrian::App::OnAppExit()
{
	using CC = std::unordered_map<ControllerInput, std::vector<CommandAndButton>>;
	using KC = std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>;
	using MC = std::unordered_map<MouseButton, std::vector<CommandAndButton>>;

	for (uint8_t i{}; i < 4; ++i)
		m_CC[i] = std::remove_reference_t<CC>(InputManager::GetInstance().GetControllerCommands(i));

	m_KC = std::remove_reference_t<KC>(InputManager::GetInstance().GetKeyboardCommands());

	m_MC = std::remove_reference_t<MC>(InputManager::GetInstance().GetMouseCommands());

	InputManager::GetInstance().RemoveAllCommands();
	InputManager::GetInstance().ResetInputs();

	// TODO: Make this just a second delay instead of forcing this a million times
	for (int i{}; i < 1'000'000; ++i)
	{
		SDL_FlushEvents(SDL_QUIT, SDL_LASTEVENT);
		SDL_PumpEvents();
	}
}
