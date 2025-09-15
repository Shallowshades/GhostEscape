#include "hud_button.h"

HUDButton* HUDButton::addHUDButtonChild(Object* parent, glm::vec2 renderPosition, const std::string& filePath1, const std::string& filePath2, const std::string& filePath3, float scale, Anchor anchor) {
    auto hudButton = new HUDButton();
    hudButton->init();
    hudButton->setRenderPosition(renderPosition);
    hudButton->spriteNormal_ = Sprite::addSpriteChild(hudButton, filePath1, scale, anchor);
    hudButton->spriteHover_ = Sprite::addSpriteChild(hudButton, filePath2, scale, anchor);
    hudButton->spritePress_ = Sprite::addSpriteChild(hudButton, filePath3, scale, anchor);
    hudButton->spriteHover_->setActive(false);
    hudButton->spritePress_->setActive(false);
    if (parent) {
        parent->addChild(hudButton);
    }
    return hudButton;
}

bool HUDButton::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (isHover_) {
                isPress_ = true;
                Game::GetInstance().playSound("assets/sound/UI_button08.wav");
                return true;
            }
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            isPress_ = false;
            if (isHover_) {
                isTrigger_ = true;
                return true;
            }
        }
    }
    return false;
}

void HUDButton::update([[maybe_unused]] float delta) {
    checkHover();
    checkState();
}

void HUDButton::checkHover() {
    auto position = renderPosition_ + spriteNormal_->getOffset();
    auto size = spriteNormal_->getSize();
    bool newHover_ = Game::GetInstance().isMouseInRect(position, position + size);
    if (newHover_ != isHover_) {
        isHover_ = newHover_;
        if (isHover_ && !isPress_) {
            Game::GetInstance().playSound("assets/sound/UI_button12.wav");
        }
    }
}

void HUDButton::checkState() {
    if (!isPress_ && !isHover_) {
        spriteNormal_->setActive(true);
        spriteHover_->setActive(false);
        spritePress_->setActive(false);
    }
    else if (!isPress_ && isHover_) {
        spriteNormal_->setActive(false);
        spriteHover_->setActive(true);
        spritePress_->setActive(false);
    }
    else {
        spriteNormal_->setActive(false);
        spriteHover_->setActive(false);
        spritePress_->setActive(true);
    }
}

bool HUDButton::getIsTrigger() {
    if (isTrigger_) {
        isTrigger_ = false;
        isPress_ = false;
        isHover_ = false;
        return true;
    }
    return false;
}

void HUDButton::setScale(float scale) {
    spriteNormal_->setScale(scale);
    spriteHover_->setScale(scale);
    spritePress_->setScale(scale);
}
