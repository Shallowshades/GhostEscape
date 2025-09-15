#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float deltaTime) {
    ObjectScreen::update(deltaTime);
    renderPosition_ = Game::GetInstance().getCurrentScene()->worldToScreenPosition(worldPosition_);
}

void ObjectWorld::setWorldPosition(const glm::vec2& position) {
    worldPosition_ = position;
    renderPosition_ = Game::GetInstance().getCurrentScene()->worldToScreenPosition(worldPosition_);
}

void ObjectWorld::setRenderPosition(const glm::vec2& position) {
    renderPosition_ = position;
    worldPosition_ = Game::GetInstance().getCurrentScene()->screenToWorldPosition(renderPosition_);
}
