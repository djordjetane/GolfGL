#include <precomp.h>

#include "Ball.h"
#include "ballDefault.h"

namespace Entities
{
    Ball::Ball()
        : Render::Model("Resources/Objects/golfBall/golfBall.obj")
        , Entity("entity")
        , m_speed(ballDefault::speed)
        , m_acceleration(0.f)
        , m_direction(0.f)
        , m_frictionFactor(ballDefault::frictionFactor)
        , m_angle(ballDefault::angle)        
    {
        this->position = ballDefault::position;
        m_scaleMatrix *= ballDefault::scale;
        model          = glm::translate(Math::I4, position);
        m_UpdateModelMatrix();

        // diffuse texture is loaded in parent class
        m_diffuseMap = (*std::find_if(textures_loaded.begin(), textures_loaded.end(), [](Render::Texture &t) {
                           return t.GetType() == TDIFFUSE;
                       })).GetID();

        shader.ActivateShader();
        shader.SetValue("material.diffuse", 0);
        setUniformPVM();
    }

    void Ball::Update(float delta)
    {
        shader.ActivateShader();
        m_HandleTransformations(delta);
        m_SetLightUniforms();
        setUniformPVM();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_diffuseMap);


        Draw(&shader);

        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
    }

    inline void Ball::m_SetLightUniforms() const
    {

        shader.setVec3("light.position", Light::LightPosition);
        shader.setVec3("viewPos", CAMERA.GetCameraPos());
        shader.setVec3("light.ambient", Light::Ambient);
        shader.setVec3("light.diffuse", Light::Diffuse);
        shader.setVec3("light.specular", Light::Specular);

        shader.setVec3("material.specular", ballDefault::material_specular);
        shader.SetValue("material.shininess", ballDefault::material_shininess);

        shader.setMat4("view", view);
        shader.setMat4("model", model);
    }

    void Ball::m_UpdateModelMatrix()
    {
        model = glm::translate(Math::I4, position) * m_rotationMatrix * m_scaleMatrix;
    }

    inline void Ball::m_HandleTransformations(float delta)
    {
        if (m_speed != glm::vec3{0.f})
        {
            auto rot = m_NormalOnVec(m_speed);            
            m_angle = (delta / 3.14f)* glm::length(m_speed);            

            m_rotationMatrix = glm::rotate(Math::I4, -m_angle, rot) * m_rotationMatrix;
            m_UpdateModelMatrix();
        }
        else if (m_ShootEvent())
        {
            m_speed = ballDefault::shootSpeed * glm::normalize(CAMERA.GetCameraFront());
        }
    }
} // namespace Entities
