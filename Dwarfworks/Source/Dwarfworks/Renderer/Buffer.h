#ifndef GRAPHICS_BUFFER_H
#define GRAPHICS_BUFFER_H

#include "Dwarfworks/Core/Log/Log.h"

namespace Dwarfworks
{
enum class ShaderDataType : uint8_t
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
    // Struct // for UBOs
};

/**
 * @brief
 *
 * @param type
 * @return ENGINE_API
 */
ENGINE_API static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        default:
            // fall-through
        case ShaderDataType::None: break;
        case ShaderDataType::Float: return sizeof(float);
        case ShaderDataType::Float2: return sizeof(float) * 2;
        case ShaderDataType::Float3: return sizeof(float) * 3;
        case ShaderDataType::Float4: return sizeof(float) * 4;
        case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
        case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;
        case ShaderDataType::Int: return sizeof(std::int32_t);
        case ShaderDataType::Int2: return sizeof(std::int32_t) * 2;
        case ShaderDataType::Int3: return sizeof(std::int32_t) * 3;
        case ShaderDataType::Int4: return sizeof(std::int32_t) * 4;
        // The size of a GLSL bool is in terms of uniform blocks is the same size as uint: 32-bits.
        case ShaderDataType::Bool: return sizeof(std::uint32_t);
    }

    DW_CORE_ASSERT(false, "Unkown ShaderDataType!");
    return 0;
}

/**
 * @brief
 *
 */
struct ENGINE_API BufferElement final
{
    // TODO: Add index to serve as an ID for a proxy viewer

    // must be defined on creation
    ShaderDataType Type;
    std::string    Name;

    // updated by the Layout logic
    uint32_t Size;
    uint32_t Offset {0};

    // optional
    bool Normalized {false};

    BufferElement() = default;
    // Most common BufferElement definition
    BufferElement(ShaderDataType type, std::string_view name)
        : Type {type}, Name {name}, Size {ShaderDataTypeSize(type)}, Offset {0}, Normalized {false}
    {
    }
    BufferElement(ShaderDataType type, std::string_view name, bool normalized)
        : Type {type}, Name {name}, Size {ShaderDataTypeSize(type)}, Offset {0}, Normalized {normalized}
    {
    }
    // More explicit BufferElement definition
    BufferElement(ShaderDataType type, std::string_view name, uint32_t size, uint32_t offset)
        : Type {type}, Name {name}, Size {size}, Offset {offset}, Normalized {false}
    {
    }
    BufferElement(ShaderDataType type, std::string_view name, uint32_t size, uint32_t offset, bool normalized)
        : Type {type}, Name {name}, Size {size}, Offset {offset}, Normalized {normalized}
    {
    }

    inline void SetNormalized(bool normalized) { Normalized = normalized; }

    uint32_t GetComponentCount() const noexcept
    {
        switch (Type)
        {
            default:
                // fall-through
            case ShaderDataType::None: break;
            case ShaderDataType::Float: return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3: return 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4;
            case ShaderDataType::Int: return 1;
            case ShaderDataType::Int2: return 2;
            case ShaderDataType::Int3: return 3;
            case ShaderDataType::Int4: return 4;
            case ShaderDataType::Bool: return 1;
        }

        DW_CORE_ASSERT(false, "Unkown ShaderDataType!");
        return 0;
    }

    static std::size_t GetElementParamCount() noexcept
    {
        // TODO(georgi): Double-check this...
        std::size_t count = 0;
        count += sizeof(Type) / sizeof(decltype(Type));
        count += sizeof(Name) / sizeof(decltype(Name));
        count += sizeof(Size) / sizeof(decltype(Size));
        count += sizeof(Offset) / sizeof(decltype(Offset));
        count += sizeof(Normalized) / sizeof(decltype(Normalized));
        return count;
    }
};

/**
 * @brief
 *
 */
class ENGINE_API BufferLayout final
{
    template <class T>
    using ContainerType = std::vector<T>;

  public:
    BufferLayout() = default;

    explicit BufferLayout(const ContainerType<BufferElement>& elements) : m_Elements(elements) { Initialize(); }

    // implicit, because I want to be able to do this:
    // BufferLayout layout = { {type, name}, ... };
    BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) { Initialize(); }

    void Append(const BufferElement& element)
    {
        // add the element at the back of the layout
        m_Elements.push_back(element);
        // update the offset stride with the element's size
        auto& appendedElement = m_Elements.back();
        SetElementOffset(appendedElement);
        UpdateStride(appendedElement.Size);
    }

    template <ShaderDataType Type, class... Params>
    void Append(Params&&... params) noexcept
    {
        // check if the number of Params does not exceed the max params that can be passed,
        // excluding Type because it is a template param outside of the ...Params pack
        DW_CORE_ASSERT(sizeof...(params) <= BufferElement::GetElementParamCount() - 1, "Passed too many parameters.");
        // add the element at the back of the layout
        m_Elements.emplace_back(Type, std::forward<Params>(params)...);
        // update the offset stride with the element's size
        auto& appendedElement = m_Elements.back();
        SetElementOffset(appendedElement);
        UpdateStride(appendedElement.Size);
    }

    const ContainerType<BufferElement>& GetElements() const { return m_Elements; }

    size_t GetElementCount() const noexcept { return m_Elements.size(); }

    std::uint32_t GetStride() const { return m_Stride; }
    void          UpdateStride(std::uint32_t size) { m_Stride += size; }

    void SetElementOffset(BufferElement& element) { element.Offset = m_Stride; }

    ContainerType<BufferElement>::iterator begin() { return m_Elements.begin(); }
    ContainerType<BufferElement>::iterator end() { return m_Elements.end(); }

    ContainerType<BufferElement>::const_iterator begin() const { return m_Elements.cbegin(); }
    ContainerType<BufferElement>::const_iterator end() const { return m_Elements.cend(); }

  private:
    void Initialize()
    {
        // calculates offsets and strides
        if (m_Stride > 0)
        {
            m_Stride = 0;
        }
        for (auto& element : m_Elements)
        {
            element.Offset = m_Stride;
            m_Stride += element.Size;
        }
    }

  private:
    ContainerType<BufferElement> m_Elements;
    uint32_t                     m_Stride = 0;
};

/**
 * @brief
 *
 */
class ENGINE_API VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual const BufferLayout& GetLayout() const                     = 0;
    virtual void                SetLayout(const BufferLayout& layout) = 0;

    static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
};

/**
 * @brief
 *
 */
class ENGINE_API IndexBuffer
{
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
};

// TODO(georgi): Implement
// UniformBuffer in OpenGL/Vulkan, ConstantBuffer in DirectX
class ENGINE_API UniformBuffer
{
};

// TODO(georgi): Implement
class ENGINE_API FrameBuffer
{
};

} // namespace Dwarfworks

#endif // GRAPHICS_BUFFER_H
