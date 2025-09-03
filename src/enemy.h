#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "affiliate/sprite_animation.h"

class Enemy : public Actor {
private:
    enum class State {
        NORMAL,
        HURT,
        DEAD
    };
public:
    virtual void init() override;
    virtual void update(float deltaTime) override;
public:
    void animationTarget(Player* target);
    void checkState();
    void changeState(State state);
    void attack();
    void remove();
    static Enemy* addEnemyChild(Object* parent, const glm::vec2& position, Player* target);
public:
    void setTarget(Player* target) { target_ = target; }
    Player* getTarget() const { return target_; }
private:
    Player* target_ = nullptr;
    SpriteAnimation* currentAnimation_ = nullptr;
    SpriteAnimation* normalAnimation_ = nullptr;
    SpriteAnimation* hurtAnimation_ = nullptr;
    SpriteAnimation* deadAnimation_ = nullptr;
    State currentState_ = State::NORMAL;
    float timer_ = 0.f;
    int score_ = 10;
};

#endif // ENEMY_H