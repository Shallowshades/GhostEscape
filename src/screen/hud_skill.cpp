#include "hud_skill.h"
#include "../affiliate/sprite.h"

HUDSkill* HUDSkill::addHUDSkillChild(Object* parent, const std::string& filePath, glm::vec2& position, float scale, Anchor anchor) {
    auto hudSkill = new HUDSkill();
    hudSkill->init();
    hudSkill->icon_ = Sprite::addSpriteChild(hudSkill, filePath, scale, anchor);
    hudSkill->setRenderPosition(position);
    if (parent) {
        parent->addChild(hudSkill);
    }
    return hudSkill;
}

void HUDSkill::render() {
    SDL_SetTextureColorModFloat(icon_->getTexture().texture, 0.3, 0.3, 0.3);
    auto position = getRenderPosition() + icon_->getOffset();
    game_.renderTexture(icon_->getTexture(), position, icon_->getSize());
    SDL_SetTextureColorModFloat(icon_->getTexture().texture, 1.0, 1.0, 1.0);
    ObjectScreen::render();
}

void HUDSkill::setPercentage(float percentage) {
    percentage_ = glm::clamp(percentage, 0.0f, 1.0f);
    if (icon_) {
        icon_->setPercentage(glm::vec2(1.0f, percentage_));
    }
}
