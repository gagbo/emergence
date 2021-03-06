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

#include "world.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPainter>

World::World() {
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    setSceneRect(QRectF());
}

World::~World() { _agents.clear(); }

float
World::time_step() const {
    return _time_step;
}

bool
World::toggle_wrap_around() {
    return (_wraps_around = !_wraps_around);
}

bool
World::wrap_around() const {
    return _wraps_around;
}

void
World::set_size(QVector2D new_size) {
    _size = new_size;
}

QVector2D
World::size() const {
    return _size;
}

void
World::fix_position_for_wrap_around(QVector2D &old_position) const {
    if (!_wraps_around) {
        return;
    }

    while (old_position.x() < -_size.x() / 2) {
        old_position.setX(old_position.x() + _size.x());
    }
    while (old_position.x() >= _size.x() / 2) {
        old_position.setX(old_position.x() - _size.x());
    }
    while (old_position.y() < -_size.y() / 2) {
        old_position.setY(old_position.y() + _size.y());
    }
    while (old_position.y() >= _size.y() / 2) {
        old_position.setY(old_position.y() - _size.y());
    }
}

bool
World::disable_wrap_around() {
    invalidate();
    return (_wraps_around = false);
}
bool
World::enable_wrap_around() {
    return (_wraps_around = true);
}

void
World::drawForeground(QPainter *painter, const QRectF &rect) {
    if (!_wraps_around) {
        return;
    }
    (void)rect;  // We are not using the inherited parameter

    painter->setBrush(Qt::NoBrush);
    QPen pen(_border_color, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);

    float wid = _size.x();
    float hei = _size.y();
    painter->drawRect(QRectF(-wid / 2.0, -hei / 2.0, wid, hei));
}

void
World::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Qt::MouseButton pressed_button = event->button();
    if (pressed_button == Qt::LeftButton) {
        double x = event->scenePos().x();
        double y = event->scenePos().y();
        emit message(QString("Clicked at (%1,%2)").arg(x).arg(y));
    } else if (pressed_button == Qt::MiddleButton) {
        // emit scale_reset();
        emit see_all_items();
    }
    return;
}

void
World::wheelEvent(QGraphicsSceneWheelEvent *event) {
    int eighths_deg = event->delta();  // >0 means scrolling up
    int direction = eighths_deg > 0 ? 1 : -1;
    float scale_factor = 1;

    scale_factor += 0.2 * direction;

    emit scale_change(scale_factor);
}

void
World::set_time_step(float dt) {
    _time_step = dt;
}

void
World::toggle_all_visions() {
    for (auto &&item : items()) {
        auto cast_item = dynamic_cast<Entity *>(item);
        cast_item->toggle_show_vision();
    }
}

void
World::enable_all_visions() {
    for (auto &&item : items()) {
        auto cast_item = dynamic_cast<Entity *>(item);
        cast_item->enable_show_vision();
    }
}

void
World::disable_all_visions() {
    for (auto &&item : items()) {
        auto cast_item = dynamic_cast<Entity *>(item);
        cast_item->disable_show_vision();
    }
}

float
World::get_friction(QVector2D position) {
    // TODO Make a proper law one day that really depends on a map
    (void)position;
    return 2.0e-10f;
}
