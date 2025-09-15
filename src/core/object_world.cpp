#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float deltaTime) {
    ObjectScreen::update(deltaTime);
    render_position_ = Game::GetInstance().getCurrentScene()->worldToScreenPosition(world_position_);
}

void ObjectWorld::setWorldPosition(const glm::vec2& position) {
    world_position_ = position;
    render_position_ = Game::GetInstance().getCurrentScene()->worldToScreenPosition(world_position_);
}

void ObjectWorld::setRenderPosition(const glm::vec2& position) {
    render_position_ = position;
    world_position_ = Game::GetInstance().getCurrentScene()->screenToWorldPosition(render_position_);
}
