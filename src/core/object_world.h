#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"

class ObjectWorld : public ObjectScreen {
public:
    virtual void update(float deltaTime) override;
    glm::vec2 getWorldPosition() const { return world_position_; }
    void setWorldPosition(const glm::vec2& position);
    virtual void setRenderPosition(const glm::vec2& position) override;

    virtual void init() override { setType(ObjectType::OBJECT_WORLD); }

protected:
    glm::vec2 world_position_ = glm::vec2(0, 0);
};


#endif // OBJECT_WORLD_H