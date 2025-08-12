#include "player.h"
#include "core/scene.h"

void Player::init() {
    Actor::init();
    max_speed_ = 10.0f; // Set a reasonable max speed for the player
}

void Player::handleEvents(SDL_Event& event) {
    Actor::handleEvents(event);
}

void Player::update(float deltaTime) {
    Actor::update(deltaTime);
    keyboardControl();
    velocity_ *= 0.9f;
    move(deltaTime);
    syncCamera();
}

void Player::render() {
    Actor::render();
    game_.drawBoundary(render_position_, render_position_ + glm::vec2(20.f), 5.0f, { 1.f, 0.f, 0.f, 1.f });
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

void Player::move(float deltaTime) {
    setWorldPosition(world_position_ + velocity_ * deltaTime);
    SDL_Log("dt: %f, pos: (%f, %f), vel: (%f, %f)", deltaTime, world_position_.x, world_position_.y, velocity_.x, velocity_.y);
    world_position_ = glm::clamp(world_position_, glm::vec2(0), game_.getCurrentScene()->getWorldSize());
}

void Player::syncCamera() {
    game_.getCurrentScene()->setCameraPosition(world_position_ - game_.getScreenSize() / 2.0f);
}
