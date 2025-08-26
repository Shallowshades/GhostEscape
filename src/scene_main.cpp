#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"

void SceneMain::init() {
    world_size_ = game_.getScreenSize() * 3.0f;
    camera_position_ = world_size_ / 2.f - game_.getScreenSize() / 2.f;
    player_ = new Player;
    player_->init();
    player_->setWorldPosition(world_size_ / 2.f);
    addChild(player_);

    spawner_ = new Spawner;
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);

    // auto enemy = new Enemy();
    // enemy->init();
    // enemy->setTarget(player_);
    // enemy->setWorldPosition(world_size_ / 2.f + glm::vec2(200.f));
    // Effect::addEffectChild(this, "assets/effect/184_3.png", world_size_ / 2.f + glm::vec2(200.f), 1.0f, enemy);
}

void SceneMain::handleEvents(SDL_Event& event) {
    Scene::handleEvents(event);
}

void SceneMain::update(float deltaTime) {
    Scene::update(deltaTime);
}

void SceneMain::render() {
    renderBackground();
    Scene::render();
}

void SceneMain::clean() {
    Scene::clean();
}

void SceneMain::renderBackground() {
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.drawGrid(start, end, 80.0f, SDL_FColor{ 0.5f, 0.5f, 0.5f, 1.0f });
    game_.drawBoundary(start, end, 5.0f, SDL_FColor{ 1.0f, 1.0f, 1.0f, 1.0f });
}