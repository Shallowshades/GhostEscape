#ifndef TIMER_H
#define TIMER_H

#include "../core/object.h"

class Timer : public Object {
public:
    static Timer* addTimerChild(Object* parent, float interval = 3.f);
    virtual void update(float delta) override;
    void start() { is_active_ = true; }
    void stop() { is_active_ = false; }
    bool timeOut();
    float getProgress() { return timer_ / interval_; }

    float getTimer() const { return timer_; }
    void setTimer(float timer) { timer_ = timer; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }

protected:
    float timer_ = 0.f;
    float interval_ = 3.f;
    bool timeOut_ = false;
};

#endif // TIMER_H