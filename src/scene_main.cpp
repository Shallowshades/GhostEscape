#include "scene_main.h"
#include "player.h"

void SceneMain::init() {
    world_size_ = game_.getScreenSize() * 3.0f;
    camera_position_ = world_size_ / 2.f - game_.getScreenSize() / 2.f;
    player_ = new Player;
    player_->init();
    player_->setWorldPosition(world_size_ / 2.f);
}

void SceneMain::handleEvents(SDL_Event& event) {

}

void SceneMain::update(float deltaTime) {
    player_->update(deltaTime);
}

void SceneMain::render() {
    renderBackground();
    player_->render();
}

void SceneMain::clean() {
    if (player_) {
        player_->clean();
        delete player_;
        player_ = nullptr;
    }
}

void SceneMain::renderBackground() {
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.drawGrid(start, end, 80.0f, SDL_FColor{ 0.5f, 0.5f, 0.5f, 1.0f });
    game_.drawBoundary(start, end, 5.0f, SDL_FColor{ 1.0f, 1.0f, 1.0f, 1.0f });
}