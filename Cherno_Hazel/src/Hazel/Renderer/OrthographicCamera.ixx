#include "hzpch.h"

#include <glm\glm.hpp>

export module OrthographicCamera;

export namespace Hazel {

    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

        const glm::vec3& GetPostion() const { return m_Position; }
        void SetPostion(glm::vec3& position)
        {
            m_Position = position;
            RecalculateViewMatrix();
        }

        const float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation)
        {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }

    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position;
        float m_Rotation;
    };

} // namespace Hazel