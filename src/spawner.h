#ifndef SPAWNER_H
#define SPAWNER_H

#include "core/object.h"

class Player;

class Spawner : public Object {
public:
    virtual void update(float delta) override;

    // getter and setter
    int getNum() const { return num_; }
    void setNum(int num) { num_ = num; }
    float getTimer() const { return timer_; }
    void setTimer(float timer) { timer_ = timer; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    Player* getTarget() const { return target_; }
    void setTarget(Player* target) { target_ = target; }

protected:
    int num_ = 3;
    float timer_ = 0;
    float interval_ = 3.f;
    Player* target_ = nullptr;
};

#endif