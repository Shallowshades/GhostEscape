#include <fstream>

#include "scene_main.h"
#include "scene_title.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "raw/bg_star.h"

void SceneMain::init() {
    Scene::init();
    SDL_HideCursor();
    Game::GetInstance().playMusic("assets/bgm/OhMyGhost.ogg");
    worldSize_ = Game::GetInstance().getScreenSize() * 3.0f;
    cameraPosition_ = worldSize_ / 2.f - Game::GetInstance().getScreenSize() / 2.f;
    player_ = new Player;
    player_->init();
    player_->setWorldPosition(worldSize_ / 2.f);
    addChild(player_);

    BgStar::addBgStarChild(this, 2000, 0.2f, 0.5f, 0.7f);

    endTimer_ = Timer::addTimerChild(this);

    spawner_ = new Spawner;
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);

    buttonPause_ = HUDButton::addHUDButtonChild(this, Game::GetInstance().getScreenSize() - glm::vec2(230.f, 30.f), "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    buttonRestart_ = HUDButton::addHUDButtonChild(this, Game::GetInstance().getScreenSize() - glm::vec2(140.f, 30.f), "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    buttonBack_ = HUDButton::addHUDButtonChild(this, Game::GetInstance().getScreenSize() - glm::vec2(50.f, 30.f), "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    hudStats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.f));
    hudTextScore_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(Game::GetInstance().getScreenSize().x - 120.f, 30.f), glm::vec2(200, 50));

    uiMouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.f, Anchor::CENTER);

}

bool SceneMain::handleEvents(SDL_Event& event) {
    if (Scene::handleEvents(event)) {
        return true;
    }
    return false;
}

void SceneMain::update(float deltaTime) {
    checkSlowDown(deltaTime);
    Scene::update(deltaTime);
    updateScore();
    checkButtonRestart();
    checkButtonPause();
    checkButtonBack();
    if (player_ && !player_->isActive()) {
        endTimer_->start();
        saveData("assets/score.dat");
    }
    checkEndTimer();
}

void SceneMain::render() {
    renderBackground();
    Scene::render();
}

void SceneMain::clean() {
    Scene::clean();
}

void SceneMain::saveData(const std::string& filePath) {
    auto score = Game::GetInstance().getHighScore();
    std::ofstream file(filePath, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&score), sizeof(score));
        file.close();
    }
}

void SceneMain::renderBackground() {
    auto start = -cameraPosition_;
    auto end = worldSize_ - cameraPosition_;
    Game::GetInstance().drawGrid(start, end, 80.0f, SDL_FColor{ 0.5f, 0.5f, 0.5f, 1.0f });
    Game::GetInstance().drawBoundary(start, end, 5.0f, SDL_FColor{ 1.0f, 1.0f, 1.0f, 1.0f });
}

void SceneMain::updateScore() {
    hudTextScore_->setText("Score: " + std::to_string(Game::GetInstance().getScore()));
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
    saveData("assets/score.dat");
    Game::GetInstance().setScore(0);
    auto scene = new SceneMain();
    Game::GetInstance().safeChangeScene(scene);
}

void SceneMain::checkButtonBack() {
    if (!buttonBack_->getIsTrigger()) {
        return;
    }
    saveData("assets/score.dat");
    Game::GetInstance().setScore(0);
    auto scene = new SceneTitle();
    Game::GetInstance().safeChangeScene(scene);
}

void SceneMain::checkEndTimer() {
    if (!endTimer_->timeOut()) {
        return;
    }
    pause();
    Game::GetInstance().resumeMusic();
    buttonRestart_->setRenderPosition(Game::GetInstance().getScreenSize() / 2.f - glm::vec2(200.f, 0.f));
    buttonRestart_->setScale(4.f);
    buttonBack_->setRenderPosition(Game::GetInstance().getScreenSize() / 2.f + glm::vec2(200.f, 0.f));
    buttonBack_->setScale(4.f);
    buttonPause_->setActive(false);
    endTimer_->stop();
}

void SceneMain::checkSlowDown(float& delta) {
    if (Game::GetInstance().getMouseButtons() & SDL_BUTTON_RMASK) {
        delta *= 0.4;
    }
}
