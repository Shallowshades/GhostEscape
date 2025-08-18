#include "actor.h"
#include "scene.h"

void Actor::move(float deltaTime) {
    setWorldPosition(world_position_ + velocity_ * deltaTime);
    world_position_ = glm::clamp(world_position_, glm::vec2(0, 0), game_.getCurrentScene()->getWorldSize());
}
