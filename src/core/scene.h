#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <glm/glm.hpp>

#include "object.h"

class Scene : public Object {
public:
    Scene() = default;
    virtual ~Scene() = default;
public:
    virtual void init() override {};
    virtual void handleEvents(SDL_Event& event) override {};
    virtual void update(float deltaTime) override {};
    virtual void render() override {};
    virtual void clean() override {};
protected:
    glm::vec2 camera_position_ = glm::vec2(0);
    std::vector<Object*> objects_;
};

#endif // SCENE_H