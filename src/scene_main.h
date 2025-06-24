#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H    

#include "core/scene.h"

class SceneMain : public Scene {
public:
    SceneMain() = default;
    virtual ~SceneMain() = default;
public:
    virtual void init() override;
    virtual void handleEvent(SDL_Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
private:
    void renderBackground();
private:
    glm::vec2 world_size_ = glm::vec2(0);
};

#endif // SCENE_MAIN_H