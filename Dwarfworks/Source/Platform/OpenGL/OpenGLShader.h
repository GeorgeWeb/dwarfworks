#ifndef PLATFORM_OPENGL_OPENGL_SHADER_H
#define PLATFORM_OPENGL_OPENGL_SHADER_H

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Renderer/Shader.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks
{
class ENGINE_API OpenGLShader final : public Shader
{
    // typedef GLenum rather than including glad for all OpenGL definitions.
    typedef unsigned int GLenum;

  public:
    explicit OpenGLShader(const std::string& filepath);
    explicit OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

    ~OpenGLShader() override final;

    void Bind() const override final;
    void Unbind() const override final;

    void SetInt(const std::string& name, int value) const override final;
    void SetIntArray(const std::string& name, int* values, uint32_t count) const override final;
    void SetFloat(const std::string& name, float value) const override final;
    void SetFloatArray(const std::string& name, float* values, uint32_t count) const override final;
    void SetFloat2(const std::string& name, const glm::vec2& value) const override final;
    void SetFloat3(const std::string& name, const glm::vec3& value) const override final;
    void SetFloat4(const std::string& name, const glm::vec4& value) const override final;
    void SetMat2(const std::string& name, const glm::mat2& value) const override final;
    void SetMat3(const std::string& name, const glm::mat3& value) const override final;
    void SetMat4(const std::string& name, const glm::mat4& value) const override final;

    inline const std::string& GetName() const override final { return m_Name; }

    void UploadUniformBool(const std::string& name, bool value) const;
    void UploadUniformInt(const std::string& name, int value) const;
    void UploadUniformIntArray(const std::string& name, int* values, uint32_t count) const;
    void UploadUniformFloat(const std::string& name, float val) const;
    void UploadUniformFloatArray(const std::string& name, float* values, uint32_t count) const;
    void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
    void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
    void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const;
    void UploadUniformMat2(const std::string& name, const glm::mat2& value) const;
    void UploadUniformMat3(const std::string& name, const glm::mat3& value) const;
    void UploadUniformMat4(const std::string& name, const glm::mat4& value) const;

    // void UploadUniformBuffer() const;

  private:
    std::string                             ReadFile(const std::string& filepath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
    void                                    Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

  private:
    uint32_t    m_RendererId;
    std::string m_Name;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_SHADER_H
