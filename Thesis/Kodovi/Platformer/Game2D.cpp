Game2D() : Layer("Game2D")
{
	auto &window = GetApp().GetWindow();
	Game2D
		CreateCamera(window.GetWidth(), window.GetHeight());

	Init();
}

void OnAttach()
{
	m_Level.Init();
	ImGuiIO io = GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/VT323-Regular.ttf", 120.0f);
	m_BackgroundTexture.reset(new Texture2D("assets/textures/saul.png"));
	m_WallTexture.reset(new Texture2D("assets/textures/wall.png"));
	m_GameState = MainMenu;
}

void OnDetach()
{
}

void OnUpdate(DeltaTime dt)
{
	// OnUpdate
	if (m_Level.IsGameOver())
		m_GameState = GameOver;
	if (m_Level.IsVictorious())
		m_GameState = Victory;

	switch (m_GameState)
	{
	case InGame:
		m_Level.OnUpdate(dt);
		break;
	}

	if ((IsKeyPressedStatic(VOS_KEY_LEFT_ALT)))
	{
		m_CameraController->OnUpdate(dt);
		m_CameraController->GetCameraRef()->SetPosition(clamp(m_CameraController->GetCameraRef()->GetPosition(),
															  vec3{-15.75f / (8.0f * m_AspectRatio), -2.5f / 8.0f, 0.0f}, vec3{57.0f / (8.0f * m_AspectRatio), 35.0f / 8.0f, 0.0f}));
	}
	else
	{
		m_CameraController->GetCameraRef()->SetPosition({m_Level.GetPlayer().GetPosition().x / (8.0f * m_AspectRatio), (m_Level.GetPlayer().GetPosition().y + 2.0f) / 8.0f, 0.0f});
	}

	// OnRender
	Clear(vec4(0.0f, 0.0f, 0.0f, 1));
	BeginScene(m_CameraController->GetCamera());
	DrawQuad(vec3{-24.5f, 18.0f, -0.1f}, vec2{16.0f, 60.0f}, m_WallTexture, 3.0f);
	DrawQuad(vec3{66.5f, 18.0f, -0.1f}, vec2{16.0f, 60.0f}, m_WallTexture, 3.0f);
	DrawRotatedQuad(vec3{-4.75f, 45.5f, -0.1f}, vec2{19.0f, 130.0f}, 90.0f, m_WallTexture, 4.0f);
	DrawQuad(vec3{0.0f + m_CameraController->GetCameraRef()->GetPosition().x * 8.0f * m_AspectRatio * 0.95, 2.0f + m_CameraController->GetCameraRef()->GetPosition().y * 8.0f * 0.95, -0.9f}, vec2{2.0f * 8.0f * m_AspectRatio + 5.0f, (2.0f * 8.0f) + 5.0f}, m_BackgroundTexture);
	m_Level.OnRender();

	EndScene();
}

float Round(float var)
{
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}

void OnImGuiRender()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
							 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;
	Begin("Score", new bool(true), flags);
	auto width = GetApp().GetWindow().GetWidth();
	auto height = GetApp().GetWindow().GetHeight();
	std::stringstream toPrint;

	auto pos = GetWindowPos();
	pos.x -= 40.0f;
	pos.y -= 20.0f;

	toPrint << "HP: ";
	switch (m_Level.GetPlayer().GetHp())
	{
	case 3:
		toPrint << "Redovan student"
				<< "\n";
		break;
	case 2:
		toPrint << "Apsolventska"
				<< "\n";
		break;
	case 1:
		toPrint << "Ponavlja godinu"
				<< "\n";
		break;
	case 0:
		toPrint << "Neslavno diplomirao"
				<< "\n";
		break;
	default:
		break;
	}
	toPrint.precision(0);
	toPrint << "Score: " << m_Level.GetScore() << "\n";
	toPrint.precision(2);
	toPrint << "Time: " << std::fixed << m_Level.GetTime() << "s";
	GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, toPrint.str().c_str());

	switch (m_GameState)
	{
	case GameOver:
	{
		pos = GetWindowPos();
		pos.x += width * 0.5f - 275.0f;
		GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, "Click left mouse button to restart.");
		break;
	}
	case MainMenu:
	{
		pos = GetWindowPos();
		pos.x += width * 0.5f - 275.0f;
		GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, "Click left mouse button to continue.");
		break;
	}
	case Victory:
	{
		pos = GetWindowPos();
		pos.x += width * 0.5f - 250.0f;
		GetForegroundDrawList()->AddText(m_Font, 35.0f, pos, 0Xffffffff, "YOU'VE GRADUATED GOOD JOB!");
		break;
	}
	}
	End();
}
void OnEvent(Event &e)
{
	EventDispatcher dispatcher = EventDispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(VOS_BIND_EVENT_FN(Resize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(VOS_BIND_EVENT_FN(OnMousePressed));
}

bool Resize(WindowResizeEvent &e)
{
	CreateCamera(e.getSizes().first, e.getSizes().second);
	return false;
}

bool OnMousePressed(MouseButtonPressedEvent &e)
{
	if (m_GameState == GameOver || m_GameState == Victory)
	{
		m_Level.Reset();
		m_GameState = InGame;
	}

	if (m_GameState == InGame)
		m_GameState = MainMenu;

	else if (m_GameState == MainMenu)
		m_GameState = InGame;

	return false;
}

void CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = float(width) / float(height);
	float camHeight = 8.0f; // Setting up screen units
	float bottom = -camHeight;
	float top = camHeight;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_AspectRatio = aspectRatio;
	// VOS_CLIENT_INFO("{0}", m_AspectRatio);
	m_CameraController.reset(new OrthographicCameraController(left, right, bottom, top, aspectRatio));
}