#ifndef HUD_STATS_H
#define HUD_STATS_H

#include "../core/object_screen.h"

class Sprite;
class Actor;
class HUDStats : public ObjectScreen {
public:
    static HUDStats* addHUDStatsChild(Object* parent, Actor* target, glm::vec2 renderPosition);
    virtual void init() override;
    virtual void update(float delta) override;
public:
    void setTarget(Actor* target) { target_ = target; }
    Actor* getTarget() const { return target_; }
    Sprite* getHealthBar() const { return healthBar_; }
    Sprite* getHealthBarBg() const { return healthBarBg_; }
    Sprite* getHealthIcon() const { return healthIcon_; }
    Sprite* getManaBar() const { return manaBar_; }
    Sprite* getManaBarBg() const { return manaBarBg_; }
    Sprite* getManaIcon() const { return manaIcon_; }

    float getHealthPercentage() const { return healthPercentage_; }
    float getManaPercentage() const { return manaPercentage_; }
    void setHealthPercentage(float healthPercentage) { healthPercentage_ = healthPercentage; }
    void setManaPercentage(float manaPercentage) { manaPercentage_ = manaPercentage; }
private:
    void updateHealthBar();
    void updateManaBar();
protected:
    Actor* target_ = nullptr;
    Sprite* healthBar_ = nullptr;
    Sprite* healthBarBg_ = nullptr;
    Sprite* healthIcon_ = nullptr;
    Sprite* manaBar_ = nullptr;
    Sprite* manaBarBg_ = nullptr;
    Sprite* manaIcon_ = nullptr;

    float healthPercentage_ = 1.f;
    float manaPercentage_ = 1.f;

    // TODO: 更加细致设置大小
};

#endif