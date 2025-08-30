#ifndef AFFILIATE_BAR_H
#define AFFILIATE_BAR_H

#include "../core/object_affiliate.h"

class AffiliateBar : public ObjectAffiliate {
public:
    static AffiliateBar* addAffiliateBarChild(ObjectScreen* parent, glm::vec2 size, Anchor anchor = Anchor::CENTER);
public:
    virtual void render() override;
public:
    float getPercentage() const { return percentage_; }
    void setPercentage(float percentage) { percentage_ = percentage; }
    SDL_FColor getColorHigh() const { return colorHigh_; }
    void setColorHigh(SDL_FColor color) { colorHigh_ = color; }
    SDL_FColor getColorMiddle() const { return colorMiddle_; }
    void setColorMiddle(SDL_FColor color) { colorMiddle_ = color; }
    SDL_FColor getColorLow() const { return colorLow_; }
    void setColorLow(SDL_FColor color) { colorLow_ = color; }
protected:
    SDL_FColor colorHigh_ = { 0, 1, 0, 1 };        // green
    SDL_FColor colorMiddle_ = { 1, 0.65, 0, 1 };   // orange
    SDL_FColor colorLow_ = { 1, 0, 0, 1 };         // red
    float percentage_ = 1.0f;
};

#endif // AFFILIATE_BAR_H