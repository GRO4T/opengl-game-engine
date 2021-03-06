#pragma once

#include <memory>

#include "entity.hpp"
#include "model/materialized_mesh.hpp"
#include "model/model.hpp"
#include "utils.hpp"

namespace game_engine {

using utils::Transform;

class Transformable {
public:
    Transformable() {}
    Transformable(const Transform& t) : transform(t) {}

    void setTransform(const Transform& transform) {
        this->transform = transform;
    }
    const Transform& getTransform() const { return transform; }

    void setPosition(const glm::vec3& pos) { transform.position = pos; }
    const glm::vec3& getPosition() const { return transform.position; }
    void move(const glm::vec3& translation) {
        transform.position += translation;
    }

    void setRotation(const glm::vec3& rot) { transform.rotation = rot; }
    const glm::vec3& getRotation() const { return transform.rotation; }
    void rotate(const glm::vec3& rot) { transform.rotation += rot; }

    void setScale(const glm::vec3& scale) { transform.scale = scale; }
    const glm::vec3& getScale() const { return transform.scale; }

protected:
    Transform transform;
};

}  // namespace game_engine