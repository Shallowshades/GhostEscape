#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen {
public:
    virtual void init() override { setType(ObjectType::OBJECT_WORLD); }
    virtual void update(float deltaTime) override;
    virtual glm::vec2 getWorldPosition() const override { return world_position_; }
    void setWorldPosition(const glm::vec2& position);
    virtual void setRenderPosition(const glm::vec2& position) override;
    Collider* getCollider() const { return collider_; }
    void setCollider(Collider* collider) { this->collider_ = collider; }
protected:
    glm::vec2 world_position_ = glm::vec2(0, 0);
    Collider* collider_ = nullptr;
};


#endif // OBJECT_WORLD_H