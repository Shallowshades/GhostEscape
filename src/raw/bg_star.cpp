#include "bg_star.h"
#include  "../core/scene.h"

BgStar* BgStar::addBgStarChild(Object* parent, int num, float scaleFar, float scaleMid, float scaleNear) {
    BgStar* bgStar = new BgStar();
    bgStar->init();
    bgStar->num_ = num;
    bgStar->scaleFar_ = scaleFar;
    bgStar->scaleMid_ = scaleMid;
    bgStar->scaleNear_ = scaleNear;
    bgStar->starFar_.reserve(num);
    bgStar->starMid_.reserve(num);
    bgStar->starNear_.reserve(num);
    auto extra = Game::GetInstance().getCurrentScene()->getWorldSize() - Game::GetInstance().getScreenSize();
    for (int i = 0; i < num; ++i) {
        bgStar->starFar_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scaleFar));
        bgStar->starMid_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scaleMid));
        bgStar->starNear_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scaleNear));
    }
    if (parent) {
        parent->addChild(bgStar);
    }
    return bgStar;
}

void BgStar::update(float delta) {
    timer_ += delta;
    colorFar_ = { 0.5f + 0.5f * sinf(timer_ * 0.9f), 0.5f + 0.5f * sinf(timer_ * 0.8f), 0.5f + 0.5f * sinf(timer_ * 0.7f), 1 };
    colorMid_ = { 0.5f + 0.5f * sinf(timer_ * 0.8f), 0.5f + 0.5f * sinf(timer_ * 0.7f), 0.5f + 0.5f * sinf(timer_ * 0.6f), 1 };
    colorNear_ = { 0.5f + 0.5f * sinf(timer_ * 0.7f), 0.5f + 0.5f * sinf(timer_ * 0.6f), 0.5f + 0.5f * sinf(timer_ * 0.5f), 1 };
}

void BgStar::render() {
    Game::GetInstance().drawPoints(starFar_, Game::GetInstance().getCurrentScene()->getCameraPosition() * scaleFar_, colorFar_);
    Game::GetInstance().drawPoints(starMid_, Game::GetInstance().getCurrentScene()->getCameraPosition() * scaleMid_, colorMid_);
    Game::GetInstance().drawPoints(starNear_, Game::GetInstance().getCurrentScene()->getCameraPosition() * scaleNear_, colorNear_);
}
