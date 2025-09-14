#ifndef BG_STAR_H
#define BG_STAR_H

#include "../core/object.h"

class BgStar : public Object {
public:
    static BgStar* addBgStarChild(Object* parent, int num, float scaleFar, float scaleMid, float scaleNear);
    virtual void update(float delta) override;
    virtual void render() override;
public:
    float getScaleFar() const { return scaleFar_; }
    float getScaleMid() const { return scaleMid_; }
    float getScaleNear() const { return scaleNear_; }
    void setScaleFar(float scale) { scaleFar_ = scale; }
    void setScaleMid(float scale) { scaleMid_ = scale; }
    void setScaleNear(float scale) { scaleNear_ = scale; }
protected:
    std::vector<glm::vec2> starFar_;
    std::vector<glm::vec2> starMid_;
    std::vector<glm::vec2> starNear_;
    float scaleFar_ = 0.2f;
    float scaleMid_ = 0.5f;
    float scaleNear_ = 0.7f;
    SDL_FColor colorFar_ = { 0,0,0,1 };
    SDL_FColor colorMid_ = { 0,0,0,1 };
    SDL_FColor colorNear_ = { 0,0,0,1 };
    float timer_ = 0.f;
    int num_ = 20;
};

#endif // BG_STAR_H