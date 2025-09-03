#include "hud_text.h"

HUDText* HUDText::addHUDTextChild(Object* parent, const std::string& text, glm::vec2 renderPosition, glm::vec2 size, const std::string& fontPath, int fontSize, const std::string& bgPath, Anchor anchor) {
    auto hudText = new HUDText();
    hudText->init();
    hudText->setRenderPosition(renderPosition);
    hudText->setSpriteBg(Sprite::addSpriteChild(hudText, bgPath, 1, anchor));
    hudText->setSize(size);
    hudText->setTextLabel(TextLabel::addTextLabelChild(hudText, text, fontPath, fontSize, anchor));
    if (parent) {
        parent->addChild(hudText);
    }
    return hudText;
}

void HUDText::setSize(const glm::vec2& size) {
    size_ = size;
    spriteBg_->setSize(size);
}

void HUDText::setBackground(const std::string& filePath) {
    if (spriteBg_) {
        spriteBg_->setTexture(filePath);
    }
    else {
        spriteBg_ = Sprite::addSpriteChild(this, filePath, 1, Anchor::CENTER);
    }
}