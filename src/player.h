#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"

class Player : public Actor {
public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
public:
    void keyboardControl();
    void move(float deltaTime);
    void syncCamera();
};

#endif // PLAYER_H