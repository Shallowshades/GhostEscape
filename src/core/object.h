#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "game.h"
#include "defines.h"

class Object {
public:
    Object() = default;
    virtual ~Object() = default;
public:
    virtual void init() {};
    virtual void handleEvents(SDL_Event& event);
    virtual void update(float deltaTime);
    virtual void render();
    virtual void clean();

    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }

    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }

protected:
    Game& game_ = Game::GetInstance();
    ObjectType type_ = ObjectType::NONE;
    std::vector<Object*> children_;
};


#endif // OBJECT_H