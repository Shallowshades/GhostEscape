#include "scene_main.h"
#include "scene_title.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"

void SceneMain::init() {
    Scene::init();
    SDL_HideCursor();
    game_.playMusic("assets/bgm/OhMyGhost.ogg");
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

    buttonPause_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() - glm::vec2(230.f, 30.f), "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    buttonRestart_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() - glm::vec2(140.f, 30.f), "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    buttonBack_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() - glm::vec2(50.f, 30.f), "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    hudStats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.f));
    hudTextScore_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(game_.getScreenSize().x - 120.f, 30.f), glm::vec2(200, 50));

    uiMouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.f, Anchor::CENTER);

}

bool SceneMain::handleEvents(SDL_Event& event) {
    if (Scene::handleEvents(event)) {
        return true;
    }
    return false;
}

void SceneMain::update(float deltaTime) {
    Scene::update(deltaTime);
    updateScore();
    checkButtonRestart();
    checkButtonPause();
    checkButtonBack();
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

void SceneMain::updateScore() {
    hudTextScore_->setText("Score: " + std::to_string(game_.getScore()));
}

void SceneMain::checkButtonPause() {
    if (!buttonPause_->getIsTrigger()) {
        return;
    }
    if (isPause_) {
        resume();
    }
    else {
        pause();
    }
}

void SceneMain::checkButtonRestart() {
    if (!buttonRestart_->getIsTrigger()) {
        return;
    }
    auto scene = new SceneMain();
    game_.safeChangeScene(scene);
}

void SceneMain::checkButtonBack() {
    if (!buttonBack_->getIsTrigger()) {
        return;
    }
    auto scene = new SceneTitle();
    game_.safeChangeScene(scene);
}
