class Renderer2D
{
public:
	static void Init();
	static void Shutdown();

	static void BeginScene(const OrthographicCamera &camera);
	static void EndScene(){};
	static void DrawQuad(const vec2 &position, vec2 size, const vec4 &color);
	static void DrawQuad(const vec3 &position, vec2 size, const vec4 &color);
	static void DrawQuad(const vec2 &position, vec2 size, const std::shared_ptr<Texture2D> &texture, float tiling = 1.0f);
	static void DrawQuad(const vec3 &position, vec2 size, const std::shared_ptr<Texture2D> &texture, float tiling = 1.0f);

	static void DrawRotatedQuad(const vec2 &position, vec2 size, float rotation, const vec4 &color);
	static void DrawRotatedQuad(const vec3 &position, vec2 size, float rotation, const vec4 &color);
	static void DrawRotatedQuad(const vec2 &position, vec2 size, float rotation, const std::shared_ptr<Texture2D> &texture, float tiling = 1.0f);
	static void DrawRotatedQuad(const vec3 &position, vec2 size, float rotation, const std::shared_ptr<Texture2D> &texture, float tiling = 1.0f);
	static void DrawRotatedQuadZ(const vec3 &position, vec2 size, float rotation, const std::shared_ptr<Texture2D> &texture, float tiling = 1.0f);
};