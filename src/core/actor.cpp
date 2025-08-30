#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"

void Actor::move(float deltaTime) {
    setWorldPosition(world_position_ + velocity_ * deltaTime);
    world_position_ = glm::clamp(world_position_, glm::vec2(0, 0), game_.getCurrentScene()->getWorldSize());
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
        SDL_Log("Enemy attack player for %f damage", stats_->getDamage());
        stats_->takeDamage(amount);
    }
}

bool Actor::isAlive() const {
    if (!stats_) return true;
    return stats_->isAlive();
}
