#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"
#include "screen/hud_button.h"
#include "screen/hud_text.h"
#include "screen/ui_mouse.h"

class SceneTitle : public Scene {
public:
    void init() override;
    bool handleEvents(SDL_Event& event) override;
    void update(float delta) override;
    void render() override;
    void clean() override;
    virtual void loadData(const std::string& filePath) override;
private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();
    void checkButtonStart();
    void checkButtonCredits();
protected:
    SDL_FColor boundaryColor_ = { 0.5, 0.5, 0.5, 1 };
    float colorTimer_ = 0.f;
    HUDButton* buttonStart_ = nullptr;
    HUDButton* buttonCredits_ = nullptr;
    HUDButton* buttonQuit_ = nullptr;
    HUDText* creditsText_ = nullptr;
    UIMouse* uiMouse_ = nullptr;
};

#endif // SCENE_TITLE_H