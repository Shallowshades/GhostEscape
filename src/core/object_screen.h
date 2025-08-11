#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include <glm/glm.hpp>

#include "object.h"

class ObjectScreen : public Object {
public:
    // getter and setter
    glm::vec2 getRenderPosition() const { return render_position_; }
    void setRenderPosition(const glm::vec2& position) { render_position_ = position; }

protected:
    glm::vec2 render_position_ = glm::vec(0, 0);
};

#endif // OBJECT_SCREEN_H