﻿#include "../UI/Image.h"

namespace Falltergeist
{
    namespace UI
    {
        Image::Image(const Graphics::Sprite &sprite) : Falltergeist::UI::Base(), _sprite(sprite)
        {
        }

        Image::Image(Format::Frm::File *frm, unsigned int direction) : Falltergeist::UI::Base(), _sprite(frm)
        {
            if (direction >= frm->directions().size()) {
                //throw Exception("Image::Image(frm, direction) - direction not found: " + std::to_string(direction));
                direction = 0;
            }
            auto& dir = frm->directions().at(direction);
            setOffset(
                frm->offsetX(direction) + dir.shiftX(),
                frm->offsetY(direction) + dir.shiftY()
            );
        }

        void Image::render(bool eggTransparency)
        {
            _sprite.trans(_trans);
            _sprite.render(position().x(),position().y(), eggTransparency, light(), _outline, _lightLevel);
        }

        Size Image::size() const
        {
            return _sprite.size();
        }

        bool Image::opaque(unsigned int x, unsigned int y)
        {
            return _sprite.opaque(x, y);
        }

        bool Image::opaque(const Point &pos)
        {
            if (pos.x() < 0 || pos.y() < 0) {
                return false;
            }
            return opaque((unsigned)pos.x(), (unsigned)pos.y());
        }

        void Image::render(const Size &size, bool eggTransparency)
        {
            _sprite.renderScaled(position().x(), position().y(), size.width(), size.height(), eggTransparency, light(), _outline);
        }
    }
}
