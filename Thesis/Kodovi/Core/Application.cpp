class Application
{
public:
	Application();
	virtual ~Application();
	void run();
	void OnEvent(Event &e);
	void PushLayer(Layer *Layer);
	void PushOverlay(Layer *Layer);

	inline WindowMaster &GetWindow() { return *m_Window; };
	inline static Application &GetApp() { return *s_Instance; };

private:
	bool OnWindowClose(WindowCloseEvent &event);
	bool OnWindowResize(WindowResizeEvent &event);
	static Application *s_Instance;

	bool m_Running = true;
	bool m_Minimized = false;

	std::unique_ptr<WindowMaster> m_Window;

	LayerStack m_LayerStack;
	DeltaTime m_TimeOfLastFrame = 0.0f;
};
