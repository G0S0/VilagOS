class OrthographicCamera
{
public:
	OrthographicCamera() {}
	OrthographicCamera(float left, float right, float bottom, float top);

	void SetProjection(float left, float right, float bottom, float top);

	glm::vec3 GetPosition() { return m_Position; }
	inline void SetPosition(const glm::vec3 &position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	inline void SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	const inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const inline glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	const inline glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	const inline float GetRotation() const { return m_Rotation; }

private:
	void RecalculateViewMatrix();
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;
	float m_Rotation = 0.0f;

	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
};