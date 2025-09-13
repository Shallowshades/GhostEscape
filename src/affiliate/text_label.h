#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include <string>

#include "../core/object_affiliate.h"

class TextLabel : public ObjectAffiliate {
public:
    static TextLabel* addTextLabelChild(ObjectScreen* parent, const std::string& text, const std::string& fontPath, int fontSize, Anchor anchor = Anchor::CENTER);
    virtual void render() override;
    virtual void clean() override;
public:
    void setFont(const std::string& fontPath, int fontSize);
    void setFontPath(const std::string& fontPath);
    void setFontSize(int fontSize);
    void setText(const std::string& text);
    std::string getText() const { return ttfText_->text; }
private:
    void updateSize();
protected:
    TTF_Text* ttfText_ = nullptr;
    std::string fontPath_;
    int fontSize_ = 16;
};

#endif // TEXT_LABEL_H