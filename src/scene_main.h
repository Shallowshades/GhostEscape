#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H    

#include "core/scene.h"
#include "player.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"

class SceneMain : public Scene {
public:
    SceneMain() = default;
    virtual ~SceneMain() = default;
public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
private:
    void renderBackground();
private:
    // glm::vec2 world_size_ = glm::vec2(0);
    Player* player_ = nullptr;
    Spawner* spawner_ = nullptr;
    UIMouse* uiMouse_ = nullptr;
    HUDStats* hudStats_ = nullptr;
};

#endif // SCENE_MAIN_H