#include "hud_stats.h"
#include "../core/actor.h"
#include "../raw/stats.h"
#include "../affiliate/sprite.h"

HUDStats* HUDStats::addHUDStatsChild(Object* parent, Actor* target, glm::vec2 renderPosition) {
    HUDStats* hudStats = new HUDStats();
    hudStats->init();
    hudStats->setRenderPosition(renderPosition);
    hudStats->setTarget(target);
    if (parent) {
        parent->addChild(hudStats);
    }
    return hudStats;
}

void HUDStats::init() {
    ObjectScreen::init();
    healthBarBg_ = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", 3.f, Anchor::CENTER_LEFT);
    healthBarBg_->setOffset(healthBarBg_->getOffset() + glm::vec2(30.f, 0));
    healthBar_ = Sprite::addSpriteChild(this, "assets/UI/bar_red.png", 3.f, Anchor::CENTER_LEFT);
    healthBar_->setOffset(healthBar_->getOffset() + glm::vec2(30.f, 0));
    healthIcon_ = Sprite::addSpriteChild(this, "assets/UI/Red Potion.png", 0.5f, Anchor::CENTER_LEFT);

    manaBarBg_ = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", 3.f, Anchor::CENTER_LEFT);
    manaBarBg_->setOffset(manaBarBg_->getOffset() + glm::vec2(300.f, 0));
    manaBar_ = Sprite::addSpriteChild(this, "assets/UI/bar_blue.png", 3.f, Anchor::CENTER_LEFT);
    manaBar_->setOffset(manaBar_->getOffset() + glm::vec2(300.f, 0));
    manaIcon_ = Sprite::addSpriteChild(this, "assets/UI/Blue Potion.png", 0.5f, Anchor::CENTER_LEFT);
    manaIcon_->setOffset(manaIcon_->getOffset() + glm::vec2(270.f, 0));
}

void HUDStats::update(float delta) {
    ObjectScreen::update(delta);
    updateHealthBar();
    updateManaBar();
}

void HUDStats::updateHealthBar() {
    if (!target_ || !healthBar_ || !target_->getStats()) {
        return;
    }
    healthBar_->setPercentage(glm::vec2(target_->getStats()->getHealth() / target_->getStats()->getMaxHealth(), 1.f));
}

void HUDStats::updateManaBar() {
    if (!target_ || !manaBar_ || !target_->getStats()) {
        return;
    }
    manaBar_->setPercentage(glm::vec2(target_->getStats()->getMana() / target_->getStats()->getMaxMana(), 1.f));
}
