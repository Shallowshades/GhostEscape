#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"

class SceneTitle : public Scene {
public:
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float delta) override;
    void render() override;
    void clean() override;
private:
    void renderBackground();
    void updateColor();
protected:
    SDL_FColor boundaryColor_ = { 0.5, 0.5, 0.5, 1 };
    float colorTimer_ = 0.f;
};

#endif // SCENE_TITLE_H