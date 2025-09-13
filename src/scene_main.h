#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H    

#include "core/scene.h"
#include "player.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "world/spell.h"
#include "raw/timer.h"

class SceneMain : public Scene {
public:
    SceneMain() = default;
    virtual ~SceneMain() = default;
public:
    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void saveData(const std::string& filePath);
private:
    void renderBackground();
    void updateScore();
    void checkButtonPause();
    void checkButtonRestart();
    void checkButtonBack();
    void checkEndTimer();
private:
    // glm::vec2 world_size_ = glm::vec2(0);
    Player* player_ = nullptr;
    Spawner* spawner_ = nullptr;
    UIMouse* uiMouse_ = nullptr;
    HUDStats* hudStats_ = nullptr;
    HUDText* hudTextScore_ = nullptr;
    HUDButton* buttonPause_ = nullptr;
    HUDButton* buttonRestart_ = nullptr;
    HUDButton* buttonBack_ = nullptr;
    Timer* endTimer_ = nullptr;
};

#endif // SCENE_MAIN_H