#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_animation.h"
#include "affiliate/collider.h"
#include "affiliate/text_label.h"
#include "raw/stats.h"
#include "raw/timer.h"

void Player::init() {
    Actor::init();
    flashTimer_ = Timer::addTimerChild(this, 0.4f);
    flashTimer_->start();
    maxSpeed_ = 500.0f;
    spriteIdle_ = SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghost-idle.png", 2.f);
    spriteMove_ = SpriteAnimation::addSpriteAnimationChild(this, "assets/sprite/ghost-move.png", 2.f);
    spriteMove_->setActive(false);
    collider_ = Collider::addColliderChild(this, spriteIdle_->getSize() / 2.f);
    stats_ = Stats::addStatsChild(this);

    // 直接挂载到场景,但是不激活
    effect_ = Effect::addEffectChild(Game::GetInstance().getCurrentScene(), "assets/effect/1764.png", glm::vec2(0.f), 2.f);
    effect_->setActive(false);

    weaponThunder_ = WeaponThunder::addWeaponThunderChild(this, 2.f, 40.f);
    // TextLabel::addTextLabelChild(this, "这是主角", "assets/font/VonwaonBitmap-16px.ttf", 16);
}

bool Player::handleEvents(SDL_Event& event) {
    if (Actor::handleEvents(event)) {
        return true;
    }
    return false;
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
    if (stats_->isInvincible() && flashTimer_->getProgress() < 0.5f) {
        return;
    }
    Actor::render();
    // Game::GetInstance().drawBoundary(renderPosition_, renderPosition_ + glm::vec2(20.f), 5.0f, { 1.f, 0.f, 0.f, 1.f });
}

void Player::clean() {
    Actor::clean();
}

void Player::takeDamage(float damage) {
    if (!stats_ || stats_->isInvincible()) {
        return;
    }
    Actor::takeDamage(damage);
    Game::GetInstance().playSound("assets/sound/hit-flesh-02-266309.mp3");
}

void Player::keyboardControl() {
    auto currentKeyStates = SDL_GetKeyboardState(nullptr);
    if (currentKeyStates[SDL_SCANCODE_W]) {
        velocity_.y = -maxSpeed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        velocity_.y = maxSpeed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        velocity_.x = -maxSpeed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        velocity_.x = maxSpeed_;
    }

    if (glm::length(velocity_) != 0) {
        velocity_ = glm::normalize(velocity_) * maxSpeed_;
    }
}

void Player::syncCamera() {
    Game::GetInstance().getCurrentScene()->setCameraPosition(worldPosition_ - Game::GetInstance().getScreenSize() / 2.0f);
}

void Player::checkState() {
    if (velocity_.x < 0) {
        spriteMove_->setFlip(true);
        spriteIdle_->setFlip(true);
    }
    else {
        spriteMove_->setFlip(false);
        spriteIdle_->setFlip(false);
    }

    bool new_is_moving = (velocity_.x != 0 || velocity_.y != 0);
    if (new_is_moving != isMoving_) {
        isMoving_ = new_is_moving;
        changeState(isMoving_);
    }
}

void Player::changeState(bool isMoving) {
    if (isMoving) {
        spriteIdle_->setActive(false);
        spriteMove_->setActive(true);
        spriteMove_->setCurrentFrame(spriteIdle_->getCurrentFrame());
        spriteMove_->setFrameTimer(spriteIdle_->getFrameTimer());
    }
    else {
        spriteIdle_->setActive(true);
        spriteMove_->setActive(false);
        spriteIdle_->setCurrentFrame(spriteMove_->getCurrentFrame());
        spriteIdle_->setFrameTimer(spriteMove_->getFrameTimer());
    }
}

void Player::checkIsDead() {
    if (!stats_->isAlive()) {
        effect_->setWorldPosition(getWorldPosition());
        effect_->setActive(true);
        setActive(false);
        Game::GetInstance().playSound("assets/sound/female-scream-02-89290.mp3");
    }
}
