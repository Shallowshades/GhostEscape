#include <cmath>

#include "scene_title.h"
#include "scene_main.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"

void SceneTitle::init() {
    Scene::init();
    auto size = glm::vec2(game_.getScreenSize().x / 2.f, game_.getScreenSize().y / 3.f);
    HUDText::addHUDTextChild(this, "幽 灵 逃 生", game_.getScreenSize() / 2.f - glm::vec2(0, 100), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
    auto scoreText = "最高分: " + std::to_string(game_.getHighScore());
    HUDText::addHUDTextChild(this, scoreText, game_.getScreenSize() / 2.f + glm::vec2(0, 100), glm::vec2(200, 50), "assets/font/VonwaonBitmap-16px.ttf", 32);
    buttonStart_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.f + glm::vec2(-200.f, 200.f), "assets/UI/A_Start1.png", "assets/UI/A_Start2.png", "assets/UI/A_Start3.png", 2.f);
    buttonCredits_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.f + glm::vec2(0.f, 200.f), "assets/UI/A_Credits1.png", "assets/UI/A_Credits2.png", "assets/UI/A_Credits3.png", 2.f);
    buttonQuit_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.f + glm::vec2(200.f, 200.f), "assets/UI/A_Quit1.png", "assets/UI/A_Quit2.png", "assets/UI/A_Quit3.png", 2.f);
}

void SceneTitle::handleEvents(SDL_Event& event) {
    Scene::handleEvents(event);
}

void SceneTitle::update(float delta) {
    Scene::update(delta);
    colorTimer_ += delta;
    updateColor();
    checkButtonQuit();
    checkButtonStart();
}

void SceneTitle::render() {
    renderBackground();
    Scene::render();
}

void SceneTitle::clean() {
    Scene::clean();
}

void SceneTitle::renderBackground() {
    game_.drawBoundary(glm::vec2(30.f), game_.getScreenSize() - glm::vec2(30.f), 10.f, boundaryColor_);
}

void SceneTitle::updateColor() {
    boundaryColor_.r = 0.5f + 0.5f * sinf(colorTimer_ * 0.9f);
    boundaryColor_.g = 0.5f + 0.5f * sinf(colorTimer_ * 0.8f);
    boundaryColor_.b = 0.5f + 0.5f * sinf(colorTimer_ * 0.7f);
}

void SceneTitle::checkButtonQuit() {
    if (buttonQuit_->getIsTrigger()) {
        game_.quit();
    }
}

void SceneTitle::checkButtonStart() {
    if (buttonStart_->getIsTrigger()) {
        auto scene = new SceneMain();
        game_.safeChangeScene(scene);
    }
}
