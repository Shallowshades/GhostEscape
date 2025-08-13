#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate : public ObjectScreen {
public:
    ObjectAffiliate() = default;
    virtual ~ObjectAffiliate() = default;
public:
    ObjectScreen* getParent() const { return parrent_; }
    void setParent(ObjectScreen* parent) { parrent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2& offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2& size) { size_ = size; }
protected:
    ObjectScreen* parrent_ = nullptr;
    glm::vec2 offset_ = glm::vec2(0, 0);
    glm::vec2 size_ = glm::vec2(0, 0);
};

#endif // OBJECT_AFFILIATE_H