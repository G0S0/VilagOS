class ShaderLibrary
{
public:
    void Add(const std::shared_ptr<Shader> &shader);
    void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
    std::shared_ptr<Shader> Load(const std::string &filepath);
    std::shared_ptr<Shader> Load(const std::string &name, const std::string &filepath);

    std::shared_ptr<Shader> Get(const ::std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};