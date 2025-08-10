#ifndef ASSET_STORE_H
#define ASSET_STORE_H

#include <string>
#include <unordered_map>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

class AssetStore {
public:
    AssetStore(SDL_Renderer* renderer) : renderer_(renderer) {}
    ~AssetStore() = default;
    void clean();

    // load functions
    void loadImage(const std::string& filePath);
    void loadSound(const std::string& filePath);
    void loadMusic(const std::string& filePath);
    void loadFont(const std::string& filePath, int fontSize);

    // read functions
    SDL_Texture* getImage(const std::string& filePath);
    Mix_Chunk* getSound(const std::string& filePath);
    Mix_Music* getMusic(const std::string& filePath);
    TTF_Font* getFont(const std::string& filePath, int fontSize);

protected:

private:
    SDL_Renderer* renderer_ = nullptr;
    std::unordered_map<std::string, SDL_Texture*> textures_;
    std::unordered_map<std::string, Mix_Chunk*> sounds_;
    std::unordered_map<std::string, Mix_Music*> musics_;
    std::unordered_map<std::string, TTF_Font*> fonts_;
};

#endif // ASSET_STORE_H