class Window
{
public:
	using EventCallbackFn = std::function<void(Event &)>;
	Window(const WindowProps &props);
	virtual ~Window();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return m_Data.Width; };
	inline unsigned int GetHeight() const override { return m_Data.Height; };

	inline void SetEventCallback(const EventCallbackFn &callback) override
	{
		m_Data.EventCallback = callback;
	}
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

private:
	void Init(const WindowProps &props);
	void Shutdown();

	GLFWwindow *m_Window;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
		EventCallbackFn EventCallback;
	};

	WindowData m_Data;
};