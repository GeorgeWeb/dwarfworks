#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks
{
class ENGINE_API Shader
{
  public:
    virtual ~Shader() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual void SetInt(const std::string& name, int value) const                            = 0;
    virtual void SetIntArray(const std::string& name, int* values, uint32_t count) const     = 0;
    virtual void SetFloat(const std::string& name, float value) const                        = 0;
    virtual void SetFloatArray(const std::string& name, float* values, uint32_t count) const = 0;
    virtual void SetFloat2(const std::string& name, const glm::vec2& value) const            = 0;
    virtual void SetFloat3(const std::string& name, const glm::vec3& value) const            = 0;
    virtual void SetFloat4(const std::string& name, const glm::vec4& value) const            = 0;
    virtual void SetMat2(const std::string& name, const glm::mat2& value) const              = 0;
    virtual void SetMat3(const std::string& name, const glm::mat3& value) const              = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) const              = 0;

    virtual const std::string& GetName() const = 0;

    static Ref<Shader> Create(const std::string& filepath);
    static Ref<Shader> Create(const std::string& name, std::string& vertexSource, const std::string& fragmentSource);

    bool isBound() const { return true; }

  protected:
    // TODO(georgi): required so we can have a proper copy constructor/assignment (Maybe move Release into a Copyable
    // interface!) virtual void Retain()  = 0; virtual void Release() = 0;
};

class ShaderLibrary
{
  public:
    void        Add(const std::string& name, const Ref<Shader>& shader);
    void        Add(const Ref<Shader>& shader);
    Ref<Shader> Load(const std::string& filepath);
    Ref<Shader> Load(const std::string& name, const std::string& filepath);

    Ref<Shader> Get(const std::string& name);

    bool Exists(const std::string& name) const;

  private:
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};

} // namespace Dwarfworks

#endif // GRAPHICS_SHADER_H
