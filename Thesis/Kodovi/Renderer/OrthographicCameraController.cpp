class OrthographicCameraController
{
public:
	OrthographicCameraController() {}
	OrthographicCameraController(float aspectRatio);
	OrthographicCameraController(float left, float right, float bottom, float top, float aspectRatio);

	void OnUpdate(DeltaTime dt);
	void OnEvent(Event &e);

	inline OrthographicCamera GetCamera() { return m_Camera; }
	inline OrthographicCamera *GetCameraRef() { return &m_Camera; }

private:
	bool OnMouseScrolledEvent(MouseScrolledEvent &e);
	bool OnWindowResizedEvent(WindowResizeEvent &e);

private:
	float m_AspectRatio;
	float m_ZoomLevel = 1.0f;
	OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = glm::vec3(0.0f);
	float m_CameraRotation = 0.0f;

	float m_CameraMovementSpeed = 2.5f, m_CameraRotationSpeed = 90.0f;
};
