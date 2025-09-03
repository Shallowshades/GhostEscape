#include "affiliate_bar.h"

AffiliateBar* AffiliateBar::addAffiliateBarChild(ObjectScreen* parent, glm::vec2 size, Anchor anchor) {
    auto bar = new AffiliateBar();
    bar->init();
    bar->setAnchor(anchor);
    bar->setSize(size);
    if (parent) {
        bar->setParent(parent);
        parent->addChild(bar);
    }
    return bar;
}

void AffiliateBar::render() {
    auto position = parent_->getRenderPosition() + offset_;
    if (percentage_ > 0.7f) {
        game_.renderHealthBar(position, size_, percentage_, colorHigh_);
    }
    else if (percentage_ > 0.3f) {
        game_.renderHealthBar(position, size_, percentage_, colorMiddle_);
    }
    else {
        game_.renderHealthBar(position, size_, percentage_, colorLow_);
    }
}
