class Renderer
{
public:
	Renderer();
	~Renderer();

	void static Init();
	void static OnWindowResize(uint32_t width, uint32_t height);

	void static BeginScene(OrthographicCamera &Camera);
	void static EndScene();

	void static SubmitData(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

private:
	struct SceneData
	{
		glm::mat4 m_ViewProjectionMatrix;
	};
	static SceneData *m_SceneData;
};