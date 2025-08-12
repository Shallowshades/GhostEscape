#include "sprite.h"
#include "../core/game.h"

Texture::Texture(const std::string& file_path) {
    Game::GetInstance().getAssetStore()->loadTexture(file_path);
    texture = Game::GetInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

void Sprite::render() {
    if (texture_.texture == nullptr || parrent_ == nullptr) {
        return;
    }
    auto pos = parrent_->getRenderPosition() + offset_;
    game_.renderTexture(texture_, pos, size_);
}

void Sprite::setTexture(const Texture& texture) {
    texture_ = texture;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
