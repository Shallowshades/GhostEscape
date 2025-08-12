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

    glm::vec2 worldToScreenPosition(const glm::vec2& worldPosition) const {
        return worldPosition - camera_position_;
    }
    glm::vec2 screenToWorldPosition(const glm::vec2& screenPosition) const {
        return screenPosition + camera_position_;
    }

    glm::vec2 getCameraPosition() const { return camera_position_; }
    void setCameraPosition(const glm::vec2& position);
    glm::vec2 getWorldSize() const { return world_size_; }
    void setWorldSize(const glm::vec2& size) { world_size_ = size; }
protected:
    glm::vec2 camera_position_ = glm::vec2(0);
    glm::vec2 world_size_ = glm::vec2(0);
    std::vector<Object*> objects_;
};

#endif // SCENE_H