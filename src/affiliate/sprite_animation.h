#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "sprite.h"

class SpriteAnimation : public Sprite {
public:
    static SpriteAnimation* addSpriteAnimationChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.f, Anchor anchor = Anchor::CENTER);
    virtual void update(float delta_time) override;

    virtual void setTexture(const Texture& texture) override;

    int getCurrentFrame() const { return currentFrame_; }
    void setCurrentFrame(int frame) { currentFrame_ = frame; }
    int getTotalFrames() const { return totalFrames_; }
    void setTotalFrames(int frames) { totalFrames_ = frames; }
    int getFPS() const { return fps_; }
    void setFPS(int fps) { fps_ = fps; }
    float getFrameTimer() const { return frameTimer; }
    void setFrameTimer(float timer) { frameTimer = timer; }
    bool isLoop() const { return isLoop_; }
    void setLoop(bool loop) { isLoop_ = loop; }
private:
    int currentFrame_;
    int totalFrames_;
    int fps_ = 10;
    float frameTimer = 0.f;
    bool isLoop_ = true;
};

#endif // SPRITE_ANIMATION_H