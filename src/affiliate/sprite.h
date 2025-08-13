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
    static Sprite* addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.f);
    virtual void render() override;

    void setScale(float scale) { size_ *= scale; }

    Texture getTexture() { return texture_; }
    virtual void setTexture(const Texture& texture);
    bool getFlip() const { return texture_.is_flipped; }
    void setFlip(bool flip) { texture_.is_flipped = flip; }
    float getAngle() const { return texture_.angle; }
    void setAngle(float angle) { texture_.angle = angle; }
protected:
    Texture texture_; // Sprite texture
};

#endif // SPRITE_H