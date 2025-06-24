#include "scene_main.h"

void SceneMain::init() {
    world_size_ = game_.getScreenSize() * 3.0f;
    camera_position_ = glm::vec2(-100.0f);
}

void SceneMain::handleEvent(SDL_Event& event) {

}

void SceneMain::update(float deltaTime) {
    camera_position_ += glm::vec2(5.0f, 5.0f) * deltaTime; // Example camera movement
}

void SceneMain::render() {
    renderBackground();
}

void SceneMain::clean() {

}

void SceneMain::renderBackground() {
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.drawGrid(start, end, 80.0f, SDL_FColor{ 0.5f, 0.5f, 0.5f, 1.0f });
    game_.drawBoundary(start, end, 5.0f, SDL_FColor{ 1.0f, 1.0f, 1.0f, 1.0f });
}