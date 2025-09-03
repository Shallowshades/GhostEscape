#ifndef HUD_SKILL_H
#define HUD_SKILL_H

#include "../core/object_screen.h"

class Sprite;
class HUDSkill : public ObjectScreen {
public:
    static HUDSkill* addHUDSkillChild(Object* parent, const std::string& filePath, glm::vec2& position, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    virtual void render() override;
public:
    Sprite* getIcon() const { return icon_; }
    void setIcon(Sprite* sprite) { icon_ = sprite; }
    float getPercentage() const { return percentage_; }
    void setPercentage(float percentage);
protected:
    Sprite* icon_ = nullptr;
    float percentage_ = 1.0f;
};

#endif