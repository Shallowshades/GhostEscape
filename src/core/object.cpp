#include "object.h"

bool Object::handleEvents(SDL_Event& event) {
    for (auto& child : children_) {
        if (child->isActive()) {
            if (child->handleEvents(event)) {
                return true;
            }
        }
    }
    return false;
}

void Object::update(float deltaTime) {
    for (auto& child : objectToAdd_) {
        addChild(child);
    }
    objectToAdd_.clear();
    for (auto iter = children_.begin(); iter != children_.end(); ) {
        if ((*iter)->isNeedRemove()) {
            (*iter)->clean();
            iter = children_.erase(iter);
            delete* iter;
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
        delete child;
        child = nullptr;
    }
    children_.clear();
}
