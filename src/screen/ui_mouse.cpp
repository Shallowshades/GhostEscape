#include "ui_mouse.h"

UIMouse* UIMouse::addUIMouseChild(Object* parent, const std::string& filePath1, const std::string& filePath2, float scale, Anchor anchor) {
    auto uiMouse = new UIMouse();
    uiMouse->init();
    uiMouse->sprite1_ = Sprite::addSpriteChild(uiMouse, filePath1, scale, anchor);
    uiMouse->sprite2_ = Sprite::addSpriteChild(uiMouse, filePath2, scale, anchor);
    if (parent) {
        parent->addChild(uiMouse);
    }
    return uiMouse;
}

void UIMouse::update(float delta) {
    timer_ += delta;
    if (timer_ < 0.3f) {
        sprite1_->setActive(true);
        sprite2_->setActive(false);
    }
    else if (timer_ < 0.6f) {
        sprite1_->setActive(false);
        sprite2_->setActive(true);
    }
    else {
        timer_ = 0.f;
    }
    setRenderPosition(game_.getMousePosition());
}
