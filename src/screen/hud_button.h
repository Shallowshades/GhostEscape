#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class HUDButton : public ObjectScreen {
public:
    static HUDButton* addHUDButtonChild(Object* parent, glm::vec2 renderPosition, const std::string& filePath1, const std::string& filePath2, const std::string& filePath3, float scale = 1.f, Anchor anchor = Anchor::CENTER);
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float delta) override;
    void checkHover();
    void checkState();

    Sprite* getSpriteNormal() const { return spriteNormal_; }
    Sprite* getSpriteHover() const { return spriteHover_; }
    Sprite* getSpritePress() const { return spritePress_; }
    bool getIsHover() const { return isHover_; }
    bool getIsPress() const { return isPress_; }
    bool getIsTrigger();
    void setIsHover(bool isHover) { isHover_ = isHover; }
    void setIsPress(bool isPress) { isPress_ = isPress; }
    void setIsTrigger(bool isTrigger) { isTrigger_ = isTrigger; }
protected:
    Sprite* spriteNormal_ = nullptr;
    Sprite* spriteHover_ = nullptr;
    Sprite* spritePress_ = nullptr;
    bool isHover_ = false;
    bool isPress_ = false;
    bool isTrigger_ = false;
};

#endif // HUD_BUTTON_H