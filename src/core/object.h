#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"

class Object {
public:
    Object() = default;
    virtual ~Object() = default;
public:
    virtual void init() = 0;
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;

protected:
    Game& game_ = Game::GetInstance();
};


#endif // OBJECT_H