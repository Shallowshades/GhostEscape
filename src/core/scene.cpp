#include "scene.h"

bool Scene::handleEvents(SDL_Event& event) {
    // 屏幕对象多为hud, text, button, label等必须处理的事件
    // 世界对象是为暂停对象
    for (auto& child : childrenScreen_) {
        if (child->isActive()) {
            if (child->handleEvents(event)) {
                return true;
            }
        }
    }
    if (isPause_) {
        return false;
    }
    Object::handleEvents(event);
    for (auto& child : childrenWorld_) {
        if (child->isActive()) {
            if (child->handleEvents(event)) {
                return true;
            }
        }
    }
    return false;
}

void Scene::update(float deltaTime) {
    if (!isPause_) {
        Object::update(deltaTime);
        for (auto iter = childrenWorld_.begin(); iter != childrenWorld_.end(); ) {
            if ((*iter)->isNeedRemove()) {
                (*iter)->clean();
                delete* iter;
                iter = childrenWorld_.erase(iter);
            }
            else {
                if ((*iter)->isActive()) {
                    (*iter)->update(deltaTime);
                }
                ++iter;
            }
        }
    }
    for (auto iter = childrenScreen_.begin(); iter != childrenScreen_.end(); ) {
        if ((*iter)->isNeedRemove()) {
            (*iter)->clean();
            delete* iter;
            iter = childrenScreen_.erase(iter);
        }
        else {
            if ((*iter)->isActive()) {
                (*iter)->update(deltaTime);
            }
            ++iter;
        }
    }
}

void Scene::render() {
    Object::render();
    for (auto& child : childrenWorld_) {
        if (child->isActive()) {
            child->render();
        }
    }
    for (auto& child : childrenScreen_) {
        if (child->isActive()) {
            child->render();
        }
    }
}

void Scene::clean() {
    Object::clean();
    for (auto& child : childrenWorld_) {
        child->clean();
        delete child;
        child = nullptr;
    }
    for (auto& child : childrenScreen_) {
        child->clean();
        delete child;
        child = nullptr;
    }
    childrenWorld_.clear();
    childrenScreen_.clear();
}

void Scene::addChild(Object* child) {
    switch (child->getType()) {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        childrenWorld_.push_back(static_cast<ObjectWorld*>(child));
        break;
    case ObjectType::OBJECT_SCREEN:
        childrenScreen_.push_back(static_cast<ObjectScreen*>(child));
        break;
    default:
        Object::addChild(child);
        break;
    }
}

void Scene::removeChild(Object* child) {
    switch (child->getType()) {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        childrenWorld_.erase(std::remove(childrenWorld_.begin(), childrenWorld_.end(), static_cast<ObjectWorld*>(child)), childrenWorld_.end());
        break;
    case ObjectType::OBJECT_SCREEN:
        childrenScreen_.erase(std::remove(childrenScreen_.begin(), childrenScreen_.end(), static_cast<ObjectScreen*>(child)), childrenScreen_.end());
        break;
    default:
        Object::removeChild(child);
        break;
    }
}

void Scene::pause() {
    isPause_ = true;
    Game::GetInstance().pauseSound();
    Game::GetInstance().pauseMusic();
}

void Scene::resume() {
    isPause_ = false;
    Game::GetInstance().resumeSound();
    Game::GetInstance().resumeMusic();
}

void Scene::setCameraPosition(const glm::vec2& position) {
    cameraPosition_ = position;
    cameraPosition_ = glm::clamp(cameraPosition_, glm::vec2(-30), worldSize_ - Game::GetInstance().getScreenSize() + glm::vec2(30));
}