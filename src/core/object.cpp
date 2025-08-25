#include "object.h"

void Object::handleEvents(SDL_Event& event) {
    for (auto& child : children_) {
        if (child->isActive()) {
            child->handleEvents(event);
        }
    }
}

void Object::update(float deltaTime) {
    for (auto& child : objectToAdd_) {
        addChild(child);
        SDL_Log("Object: add child \n");
    }
    objectToAdd_.clear();
    for (auto iter = children_.begin(); iter != children_.end(); ) {
        if ((*iter)->isNeedRemove()) {
            (*iter)->clean();
            iter = children_.erase(iter);
            delete* iter;
            SDL_Log("Object: remove child \n");
        }
        else {
            if ((*iter)->isActive()) {
                (*iter)->update(deltaTime);
            }
            ++iter;
        }
    }
}

void Object::render() {
    for (auto& child : children_) {
        if (child->isActive()) {
            child->render();
        }
    }
}

void Object::clean() {
    for (auto& child : children_) {
        child->clean();
    }
    children_.clear();
}
