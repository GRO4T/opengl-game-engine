#include "renderer/entity_renderer.hpp"

#include "utils.hpp"

namespace game_engine {

using utils::Transform;

EntityRenderer::EntityRenderer(const glm::mat4& projection_matrix) {
    shader.use();
    shader.setProjectionMatrix(projection_matrix);
}

void EntityRenderer::render(std::vector<Entity*>& entities,
                            const Camera& camera,
                            std::vector<PointLight*>& point_lights,
                            DirLight* dir_light,
                            std::vector<SpotLight*>& spot_lights,
                            Light* global_light) {
    shader.use();
    shader.setViewMatrix(camera);

    for (auto& entity : entities) {
        const auto& model = entity->getMaterializedModel().getModel();
        glm::mat4 transform_matrix;
        utils::createTransformMatrix(transform_matrix, entity->getTransform());
        shader.setTransformationMatrix(transform_matrix);
        prepareInstance(*entity);

        shader.setVec3("camera_position", camera.getPosition());
        if (dir_light != nullptr) shader.setDirLight("dir_light", *dir_light);
        for (const auto& light : point_lights) {
            shader.setPointLight("point_light", *light);
        }
        for (const auto& light : spot_lights) {
            shader.setSpotLight("spot_light", *light);
        }
        if (global_light != nullptr)
            shader.setGlobalLight("global_light", *global_light);

        model.draw();
        unbind(model);
        renderChildren(*entity, transform_matrix);
    }
}

void EntityRenderer::renderChildren(Entity& parent,
                                    glm::mat4 combined_transform) {
    for (auto& child : parent.getChildren()) {
        Entity& entity = (Entity&)*child;
        glm::mat4 transform_matrix;
        utils::createTransformMatrix(transform_matrix, entity.getTransform());
        shader.setTransformationMatrix(combined_transform * transform_matrix);
        prepareInstance(entity);
        entity.getMaterializedModel().getModel().draw();
        unbind(entity.getMaterializedModel().getModel());
        renderChildren(entity, combined_transform * transform_matrix);
    }
}

void EntityRenderer::unbind(const Model& model) { glBindVertexArray(0); }

void EntityRenderer::prepareInstance(const Entity& entity) {
    auto& materialized_model = entity.getMaterializedModel();
    const auto& material = materialized_model.getMaterial();
    glBindVertexArray(materialized_model.getModel().getVao());
    shader.setMaterial("material", material);
}

}  // namespace game_engine