#ifndef UI_MOUSE_H
#define UI_MOUSE_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class UIMouse : public ObjectScreen {
public:
    static UIMouse* addUIMouseChild(Object* parent, const std::string& filePath1, const std::string& filePath2, float scale = 1.f, Anchor anchor = Anchor::CENTER);
    virtual void update(float delta) override;
public:
    Sprite* getSprite1() const { return sprite1_; }
    Sprite* getSprite2() const { return sprite2_; }
    void setSprite1(Sprite* sprite) { sprite1_ = sprite; }
    void setSprite2(Sprite* sprite) { sprite2_ = sprite; }
protected:
    Sprite* sprite1_ = nullptr;
    Sprite* sprite2_ = nullptr;
    float timer_ = 0;
};

#endif //UI_MOUSE_H