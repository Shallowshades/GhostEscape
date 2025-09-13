#include "text_label.h"

TextLabel* TextLabel::addTextLabelChild(ObjectScreen* parent, const std::string& text, const std::string& fontPath, int fontSize, Anchor anchor) {
    auto textLabel = new TextLabel();
    textLabel->init();
    textLabel->setFont(fontPath, fontSize);
    textLabel->setText(text);
    textLabel->setAnchor(anchor);
    textLabel->updateSize();
    if (parent) {
        parent->addChild(textLabel);
        textLabel->setParent(parent);
    }
    return textLabel;
}

void TextLabel::render() {
    ObjectAffiliate::render();
    auto position = parent_->getRenderPosition() + offset_;
    TTF_DrawRendererText(ttfText_, position.x, position.y);
}

void TextLabel::clean() {
    if (!ttfText_) {
        return;
    }
    TTF_DestroyText(ttfText_);
}

void TextLabel::setFont(const std::string& fontPath, int fontSize) {
    fontPath_ = fontPath;
    fontSize_ = fontSize;
    auto font = game_.getAssetStore()->getFont(fontPath_, fontSize_);
    if (!ttfText_) {
        ttfText_ = game_.createTTFText("", fontPath_, fontSize_);
    }
    TTF_SetTextFont(ttfText_, font);
}

void TextLabel::setFontPath(const std::string& fontPath) {
    fontPath_ = fontPath;
    auto font = game_.getAssetStore()->getFont(fontPath_, fontSize_);
    TTF_SetTextFont(ttfText_, font);
    updateSize();
}

void TextLabel::setFontSize(int fontSize) {
    fontSize_ = fontSize;
    auto font = game_.getAssetStore()->getFont(fontPath_, fontSize_);
    TTF_SetTextFont(ttfText_, font);
    updateSize();
}

void TextLabel::setText(const std::string& text) {
    TTF_SetTextString(ttfText_, text.c_str(), text.length());
    updateSize();
}

void TextLabel::updateSize() {
    int w, h;
    TTF_GetTextSize(ttfText_, &w, &h);
    setSize(glm::vec2(w, h));
}
