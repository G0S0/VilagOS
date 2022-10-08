Game2D() : Layer("Game2D")
{
	auto &window = GetApp().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());
	Init();
}

void OnAttach()
{
	m_Level.Init();
	ImGuiIO io = GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/VT323-Regular.ttf", 120.0f);
	m_GameState = MainMenu;
}

void OnDetach()
{
}

void OnUpdate(DeltaTime dt)
{
	if (m_Level.IsGameOver())
		m_GameState = GameOver;

	switch (m_GameState)
	{
	case InGame:
		m_Level.OnUpdate(dt);
		break;
	}

	Clear(vec4(0.0f, 0.0f, 0.0f, 1));
	BeginScene(*m_Camera);
	EndScene();
}

void OnUIRender()
{
	auto pos = GetWindowPos();
	pos.x -= 40.0f;
	pos.y -= 20.0f;
	toPrint.precision(2);
	toPrint << "Time: " << std::fixed << m_Level.GetTime() << "s\n"
			<< "Round: " << m_Level.GetRounds();
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
	if (m_GameState == GameOver)
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
	float camHeight = 8.0f;
	float bottom = -camHeight;
	float top = camHeight;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera.reset(new OrthographicCamera(left, right, bottom, top));
}