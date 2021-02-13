#pragma once

#include <light.hpp>
#include <shader/light_shader.hpp>

#include "opengl_all.hpp"

namespace game_engine {

class LightRenderer {
public:
    LightRenderer(const glm::mat4& projection_matrix) {
        shader.use();
        shader.setProjectionMatrix(projection_matrix);
    }

    void render(std::vector<PhysicalLight*>& lights, const Camera& camera) {
        shader.use();
        shader.setViewMatrix(camera);

        for (auto& light : lights) {
            const auto& model = light->getModel();
            glm::mat4 transform_matrix;
            utils::createTransformMatrix(transform_matrix,
                                         light->getTransform());
            shader.setTransformationMatrix(transform_matrix);
            prepareInstance(*light);
            model.draw();
            unbind(model);
        }
    }

private:
    void unbind(const Mesh& model) { glBindVertexArray(0); }
    void prepareInstance(const PhysicalLight& light) {
        glBindVertexArray(light.getModel().getVao());
        shader.setLight("light", light);
    }

    LightShader shader;
};

}  // namespace game_engine