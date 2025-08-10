#include "asset_store.h"

void AssetStore::clean() {
    for (auto& texture : textures_) {
        SDL_DestroyTexture(texture.second);
    }
    textures_.clear();

    for (auto& sound : sounds_) {
        Mix_FreeChunk(sound.second);
    }
    sounds_.clear();

    for (auto& music : musics_) {
        Mix_FreeMusic(music.second);
    }
    musics_.clear();

    for (auto& font : fonts_) {
        TTF_CloseFont(font.second);
    }
    fonts_.clear();
}

void AssetStore::loadImage(const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer_, filePath.c_str());
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s, %s", filePath.c_str(), SDL_GetError());
        return;
    }
    // textures_[filePath] = texture;       // Store if already present
    textures_.emplace(filePath, texture);   // Store if not already present
}

void AssetStore::loadSound(const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound: %s, %s", filePath.c_str(), SDL_GetError());
        return;
    }
    // sounds_[filePath] = sound;           // Store if already present
    sounds_.emplace(filePath, sound);       // Store if not already present
}

void AssetStore::loadMusic(const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s, %s", filePath.c_str(), SDL_GetError());
        return;
    }
    // musics_[filePath] = music;           // Store if already present
    musics_.emplace(filePath, music);       // Store if not already present
}

void AssetStore::loadFont(const std::string& filePath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), static_cast<float>(fontSize));
    if (font == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s, %s", filePath.c_str(), SDL_GetError());
        return;
    }
    // fonts_[filePath] = font;             // Store if already present
    fonts_.emplace(filePath + std::to_string(fontSize), font);         // Store if not already present
}

SDL_Texture* AssetStore::getImage(const std::string& filePath) {
    auto iter = textures_.find(filePath);
    if (iter != textures_.end()) {
        loadImage(filePath); // Ensure the image is loaded
        iter = textures_.find(filePath);
    }
    if (iter == textures_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Image not found: %s", filePath.c_str());
        return nullptr;
    }
    return iter->second;
}

Mix_Chunk* AssetStore::getSound(const std::string& filePath) {
    auto iter = sounds_.find(filePath);
    if (iter != sounds_.end()) {
        loadSound(filePath); // Ensure the sound is loaded
        iter = sounds_.find(filePath);
    }
    if (iter == sounds_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Sound not found: %s", filePath.c_str());
        return nullptr;
    }
    return iter->second;
}

Mix_Music* AssetStore::getMusic(const std::string& filePath) {
    auto iter = musics_.find(filePath);
    if (iter != musics_.end()) {
        loadMusic(filePath); // Ensure the music is loaded
        iter = musics_.find(filePath);
    }
    if (iter == musics_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Music not found: %s", filePath.c_str());
        return nullptr;
    }
    return iter->second;
}

TTF_Font* AssetStore::getFont(const std::string& filePath, int fontSize)
{
    auto iter = fonts_.find(filePath + std::to_string(fontSize));
    if (iter != fonts_.end()) {
        loadFont(filePath, fontSize); // Ensure the font is loaded
        iter = fonts_.find(filePath + std::to_string(fontSize));
    }
    if (iter == fonts_.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font not found: %s", filePath.c_str());
        return nullptr;
    }
    return iter->second;
}
