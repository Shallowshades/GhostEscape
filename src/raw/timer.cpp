#include "timer.h"

Timer* Timer::addTimerChild(Object* parent, float interval) {
    Timer* timer = new Timer();
    timer->setInterval(interval);
    if (parent) {
        parent->addChild(timer);
    }
    timer->setActive(false);
    return timer;
}

void Timer::update(float delta) {
    timer_ += delta;
    if (timer_ >= interval_) {
        timer_ = 0;
        timeOut_ = true;
    }
}

bool Timer::timeOut() {
    if (timeOut_) {
        timeOut_ = false;
        return true;
    }
    return false;
}
