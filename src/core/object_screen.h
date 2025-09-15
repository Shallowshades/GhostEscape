#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include <glm/glm.hpp>

#include "object.h"

class ObjectScreen : public Object {
public:
    // getter and setter
    glm::vec2 getRenderPosition() const { return renderPosition_; }
    virtual void setRenderPosition(const glm::vec2& position) { renderPosition_ = position; }
    virtual glm::vec2 getWorldPosition() const { return glm::vec2(0.f, 0.f); }

    virtual void init() override { setType(ObjectType::OBJECT_SCREEN); }

protected:
    glm::vec2 renderPosition_ = glm::vec2(0, 0);
};

#endif // OBJECT_SCREEN_H