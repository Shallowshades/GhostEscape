#include "enemy.h"
#include "core/scene.h"
#include "affiliate/sprite_animation.h"
#include "affiliate/collider.h"
#include "raw/stats.h"

void Enemy::init() {
    Actor::init();
    normalAnimation_ = SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    hurtAnimation_ = SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    deadAnimation_ = SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    hurtAnimation_->setActive(false);
    deadAnimation_->setActive(false);
    deadAnimation_->setLoop(false);
    currentAnimation_ = normalAnimation_;

    setMaxSpeed(100.0f);
    collider_ = Collider::addColliderChild(this, currentAnimation_->getSize());
    stats_ = Stats::addStatsChild(this);
    setType(ObjectType::ENEMY);
}

void Enemy::update(float deltaTime) {
    Actor::update(deltaTime);
    if (target_->isAlive()) {
        animationTarget(target_);
        move(deltaTime);
        attack();
    }
}

void Enemy::animationTarget(Player* target) {
    if (target == nullptr) {
        return;
    }
    auto direction = glm::normalize(target->getWorldPosition() - getWorldPosition());
    setVelocity(direction * getMaxSpeed());
}

void Enemy::checkState() {

}

void Enemy::changeState(State state) {
    if (currentState_ == state) {
        return;
    }

    currentState_ = state;
    currentAnimation_->setActive(false);
    switch (state) {
    case State::NORMAL:
        currentAnimation_ = normalAnimation_;
        break;
    case State::HURT:
        currentAnimation_ = hurtAnimation_;
        break;
    case State::DEAD:
        currentAnimation_ = deadAnimation_;
        break;
    }

    if (currentAnimation_) {
        currentAnimation_->setActive(true);
    }
}

void Enemy::remove() {
    if (deadAnimation_ != nullptr && deadAnimation_->isFinished()) {
        isNeedRemove_ = true;
    }
}

Enemy* Enemy::addEnemyChild(Object* parent, const glm::vec2& position, Player* target) {
    auto enemy = new Enemy;
    enemy->init();
    enemy->setWorldPosition(position);
    enemy->setTarget(target);
    if (parent) {
        parent->addChild(enemy);
    }
    return enemy;
}

void Enemy::attack() {
    if (!collider_ || !target_ || !target_->getCollider()) {
        return;
    }
    if (collider_->isColliding(target_->getCollider())) {
        if (stats_ != nullptr && target_->getStats() != nullptr) {
            target_->takeDamage(stats_->getDamage());
        }
    }
}
