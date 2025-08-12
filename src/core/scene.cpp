#include "scene.h"

void Scene::setCameraPosition(const glm::vec2& position) {
    camera_position_ = position;
    camera_position_ = glm::clamp(camera_position_, glm::vec2(-30), world_size_ - game_.getScreenSize() + glm::vec2(30));
}