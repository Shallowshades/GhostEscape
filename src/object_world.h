#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include <glm/glm.hpp>
#include "core/object.h"
#include "object_screen.h"

class WorldObject : public ObjectScreen {
public:
    // Getter and setter for world position
    glm::vec2 getWorldPosition() const { return world_position_; }
    void setWorldPosition(const glm::vec2& position) { world_position_ = position; }
protected:
    // World-specific properties can be added here
    glm::vec2 world_position_ = glm::vec2(0, 0); // Position in the world
}

#endif // OBJECT_SCREEN_H