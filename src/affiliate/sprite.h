#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "../core/object_affiliate.h"

struct Texture {
    SDL_Texture* texture = nullptr;
    SDL_FRect src_rect = { 0, 0, 0, 0 };
    float angle = 0.0f;
    bool is_flipped = false;
    Texture() = default;
    Texture(const std::string& file_path);
};

class Sprite : public ObjectAffiliate {
public:
    static Sprite* addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.f, Anchor anchor = Anchor::CENTER);
    virtual void render() override;
public:
    Texture getTexture() { return texture_; }
    virtual void setTexture(const Texture& texture);
    bool getFlip() const { return texture_.is_flipped; }
    void setFlip(bool flip) { texture_.is_flipped = flip; }
    float getAngle() const { return texture_.angle; }
    void setAngle(float angle) { texture_.angle = angle; }
    bool isFinished() const { return isFinished_; }
    void setFinished(bool finished) { isFinished_ = finished; }
    glm::vec2 getPercentage() const { return percentage_; }
    void setPercentage(const glm::vec2& percentage) { percentage_ = percentage; }
protected:
    Texture texture_; // Sprite texture
    bool isFinished_ = false;
    glm::vec2 percentage_ = glm::vec2(1.f);
};

#endif // SPRITE_H