#include "hzpch.h"

#include <glm\glm.hpp>

export module Shader;

export namespace Hazel {

    class Shader {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };

} // namespace Hazel
