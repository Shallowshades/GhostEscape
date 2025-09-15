#include "sprite.h"
#include "../core/game.h"

Texture::Texture(const std::string& file_path) {
    Game::GetInstance().getAssetStore()->loadTexture(file_path);
    texture = Game::GetInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite* Sprite::addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale, [[maybe_unused]] Anchor anchor) {
    auto sprite = new Sprite();
    sprite->init();
    sprite->setAnchor(anchor);
    sprite->setTexture(Texture(file_path));
    sprite->setScale(scale);
    sprite->setParent(parent);
    if (parent) {
        parent->addChild(sprite);
    }
    return sprite;
}

void Sprite::render() {
    if (texture_.texture == nullptr || parent_ == nullptr || isFinished_) {
        return;
    }
    auto pos = parent_->getRenderPosition() + offset_;
    Game::GetInstance().renderTexture(texture_, pos, size_, percentage_);
}

void Sprite::setTexture(const Texture& texture) {
    texture_ = texture;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
