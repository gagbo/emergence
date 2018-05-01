/* Copyright (c) 2018 Gerry Agbobada
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "living_entity.h"

const static QString super_type_value = "Living";

LivingEntity::LivingEntity() : Entity() {
    _super_type = super_type_value;
}

LivingEntity::LivingEntity(const QVector2D &position,
                           const QVector2D &init_speed)
    : Entity(position, init_speed) {
    _super_type = super_type_value;
}

void
LivingEntity::decide_acceleration() {
    _acc = QVector2D(0.0f, 0.0f);
}

void
LivingEntity::update_neighbourhood() {
    Entity::update_neighbourhood();

    for (auto &&item : *_neighbours) {
        if (is_visible(item->pos())) {
            _visible_neighbours->append(item);
        }
    }
}

bool
LivingEntity::is_visible(const QPointF &world_pos) const {
    if (_vision.isNull()) {
        return false;
    }

    return vision().containsPoint(mapFromScene(world_pos), Qt::OddEvenFill);
}

QRectF
LivingEntity::boundingRect() const {
    if (_show_vision && !vision().isEmpty()) {
        // We add margins to the bounding Rect of Vision so it extends behind
        // itself, theoretically covering the back of the Ant
        return _vision->boundingRect().marginsAdded(
            QMarginsF(0, 0, 0, _vision->boundingRect().height()));
    }
    return Entity::boundingRect();
}

const QPolygonF& LivingEntity::vision() const {
    return *_vision.data();
}
