#include "enemy.h"
#include "affiliate/sprite_animation.h"

void Enemy::init() {
    Actor::init();
    SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    setMaxSpeed(10.0f);
}

void Enemy::update(float deltaTime) {
    Actor::update(deltaTime);
    animationTarget(target_);
    move(deltaTime);
}

void Enemy::animationTarget(Player* target) {
    if (target == nullptr) {
        return;
    }
    auto direction = glm::normalize(target->getWorldPosition() - getWorldPosition());
    setVelocity(direction * getMaxSpeed());
}
