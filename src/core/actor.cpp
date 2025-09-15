#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"

void Actor::move(float deltaTime) {
    setWorldPosition(world_position_ + velocity_ * deltaTime);
    // world_position_ = glm::clamp(world_position_, glm::vec2(0, 0), Game::GetInstance().getCurrentScene()->getWorldSize());

    // 根据碰撞盒大小限制移动区域
    glm::vec2 marginTopLeft = glm::vec2(0.f);
    glm::vec2 marginBottomRight = glm::vec2(0.f);
    if (collider_) {
        marginTopLeft = collider_->getOffset();
        marginBottomRight = collider_->getOffset() + collider_->getSize();
    }
    world_position_ = glm::clamp(world_position_, glm::vec2(0.f) - marginTopLeft, Game::GetInstance().getCurrentScene()->getWorldSize() - marginBottomRight);
}

void Actor::updateHealthBar() {
    if (!stats_ || !healthBar_) {
        return;
    }
    healthBar_->setPercentage(stats_->getHealth() / stats_->getMaxHealth());
}

void Actor::update(float delta) {
    ObjectWorld::update(delta);
    updateHealthBar();
}

void Actor::takeDamage(float amount) {
    if (stats_ != nullptr && stats_->isAlive() && stats_->isInvincible() == false) {
        stats_->takeDamage(amount);
    }
}

bool Actor::isAlive() const {
    if (!stats_) return true;
    return stats_->isAlive();
}
