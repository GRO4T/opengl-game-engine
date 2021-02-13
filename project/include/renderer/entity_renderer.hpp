#pragma once

#include <vector>

#include "entity/entity.hpp"
#include "shader/entity_shader.hpp"

namespace game_engine {

class EntityRenderer {
public:
    EntityRenderer(const glm::mat4& projection_matrix);
    void render(std::vector<Entity*>& entities, const Camera& camera,
                std::vector<PointLight*>& point_lights, DirLight* dir_light,
                std::vector<SpotLight*>& spot_lights,
                Light* global_light);

private:
    void unbind();
    void prepareInstance(const Entity& entity);
    void renderChildren(Entity& parent, glm::mat4 combined_transform);

    EntityShader shader;
};

}  // namespace game_engine