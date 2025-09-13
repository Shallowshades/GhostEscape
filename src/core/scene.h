#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "object.h"
#include "object_world.h"

class Scene : public Object {
public:
    Scene() = default;
    virtual ~Scene() = default;
public:
    virtual void init() override {};
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void addChild(Object* child) override;
    virtual void removeChild(Object* child) override;  // remove but not delete

    virtual void saveData([[maybe_unused]] const std::string& filePath) {}
    virtual void loadData([[maybe_unused]] const std::string& filePath) {}

    glm::vec2 worldToScreenPosition(const glm::vec2& worldPosition) const {
        return worldPosition - camera_position_;
    }
    glm::vec2 screenToWorldPosition(const glm::vec2& screenPosition) const {
        return screenPosition + camera_position_;
    }

    void pause();
    void resume();
public:
    glm::vec2 getCameraPosition() const { return camera_position_; }
    void setCameraPosition(const glm::vec2& position);
    glm::vec2 getWorldSize() const { return world_size_; }
    void setWorldSize(const glm::vec2& size) { world_size_ = size; }
    std::vector<ObjectWorld*> getWorldChildren() const { return children_world_; }
    std::vector<ObjectScreen*> getScreenChildren() const { return children_screen_; }
protected:
    glm::vec2 camera_position_ = glm::vec2(0);
    glm::vec2 world_size_ = glm::vec2(0);
    std::vector<ObjectWorld*> children_world_;
    std::vector<ObjectScreen*> children_screen_;
    bool isPause_ = false;
};

#endif // SCENE_H