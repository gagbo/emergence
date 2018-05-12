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

#include "ant.h"
#include <QPainter>
#include <QtMath>

const static QString type_string_value = "Ant";

Ant::Ant() : LivingEntity() {
    _type = type_string_value;
    set_role("Worker");
    _color = Qt::darkBlue;
}

Ant::Ant(const QVector2D& position, const QVector2D& init_speed)
    : LivingEntity(position, init_speed) {
    _type = type_string_value;
    set_role("Worker");
    _color = Qt::darkBlue;
}

void
Ant::decide_action() {
    _current_role->decide_action(this);
}

void
Ant::set_role(QString role_name) {
    _current_role = RoleAnt::get(role_name);
    set_vision(_current_role->vision());
}

const RoleAnt*
Ant::role() const {
    return _current_role;
}

void
Ant::paint(QPainter* painter, const QStyleOptionGraphicsItem* style_opt,
           QWidget* widget) {
    (void)style_opt;
    (void)widget;
    // Body
    painter->setBrush(_current_role->color());
    painter->setPen(Qt::NoPen);
    QPointF triangle_body[3] = {QPointF(-_size.x() / 2, _size.y() / 2),
                                QPointF(_size.x() / 2, _size.y() / 2),
                                QPointF(0, -_size.y() / 2)};
    painter->drawPolygon(triangle_body, 3);

    // Eyes
    int eyes_size = 3;
    int pos_left_x = qFloor(-_size.x() / 5);
    int pos_eyes_y = qFloor(-_size.y() + 2 * eyes_size);
    painter->setBrush(Qt::white);
    painter->drawEllipse(-pos_left_x, pos_eyes_y, eyes_size, eyes_size);
    painter->drawEllipse(pos_left_x, pos_eyes_y, eyes_size, eyes_size);

    // Vision
    if (_show_vision && !vision().isEmpty()) {
        painter->setPen(Qt::lightGray);
        painter->setBrush(Qt::NoBrush);
        painter->drawPolygon(vision());
    }
}
