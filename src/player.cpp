#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_animation.h"
#include "affiliate/collider.h"
#include "raw/stats.h"

void Player::init() {
    Actor::init();
    max_speed_ = 10.0f;
    sprite_idle_ = SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghost-idle.png", 2.f);
    sprite_move_ = SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghost-move.png", 2.f);
    sprite_move_->setActive(false);
    collider_ = Collider::addColliderChild(this, sprite_idle_->getSize() / 2.f);
    stats_ = Stats::addStatsChild(this);
    effect_ = Effect::addEffectChild(nullptr, "assets/effect/1764.png", glm::vec2(0.f), 2.f);
}

void Player::handleEvents(SDL_Event& event) {
    Actor::handleEvents(event);
}

void Player::update(float deltaTime) {
    Actor::update(deltaTime);
    keyboardControl();
    velocity_ *= 0.9f;
    checkState();
    move(deltaTime);
    syncCamera();
    // isAlive();
    checkIsDead();
}

void Player::render() {
    Actor::render();
    // game_.drawBoundary(render_position_, render_position_ + glm::vec2(20.f), 5.0f, { 1.f, 0.f, 0.f, 1.f });
}

void Player::clean() {
    Actor::clean();
}

void Player::keyboardControl() {
    auto currentKeyStates = SDL_GetKeyboardState(nullptr);
    if (currentKeyStates[SDL_SCANCODE_W]) {
        velocity_.y = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        velocity_.y = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        velocity_.x = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        velocity_.x = max_speed_;
    }

    if (glm::length(velocity_) != 0) {
        velocity_ = glm::normalize(velocity_) * max_speed_;
    }
}

void Player::syncCamera() {
    game_.getCurrentScene()->setCameraPosition(world_position_ - game_.getScreenSize() / 2.0f);
}

void Player::checkState() {
    if (velocity_.x < 0) {
        sprite_move_->setFlip(true);
        sprite_idle_->setFlip(true);
    }
    else {
        sprite_move_->setFlip(false);
        sprite_idle_->setFlip(false);
    }

    bool new_is_moving = (velocity_.x != 0 || velocity_.y != 0);
    if (new_is_moving != is_moving_) {
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
}

void Player::changeState(bool isMoving) {
    if (isMoving) {
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
    }
    else {
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}

void Player::checkIsDead() {
    if (!stats_->isAlive()) {
        SDL_Log("Player: is dead\n");
        effect_->setActive(false);
        effect_->setWorldPosition(getWorldPosition());
        game_.getCurrentScene()->safeAddChild(effect_);
        setActive(false);
    }
}
