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

#include "entity.h"
#include <QPainter>
#include <QtMath>

Entity::~Entity() {
    _visible_neighbours.clear();
    _neighbours.clear();
}

Entity::Entity(const QVector2D &position, const QVector2D &init_speed) {
    _pos = position;
    _vel = init_speed;
}

float
Entity::x() const {
    return _pos.x();
}
float
Entity::y() const {
    return _pos.y();
}
QVector2D
Entity::position() const {
    return _pos;
}
QVector2D
Entity::velocity() const {
    return _vel;
}
QVector2D
Entity::acceleration() const {
    return _acc;
}
int
Entity::id() const {
    return _id;
}
float
Entity::mass() const {
    return _mass;
}
float
Entity::max_force() const {
    return _max_force;
}
QColor
Entity::color() const {
    return _color;
}
float
Entity::life() const {
    return _life;
}
QVector2D
Entity::size() const {
    return _size;
}

QList<QWeakPointer<Entity>>
Entity::neigbours() const {
    return _neighbours;
}
QList<QWeakPointer<Entity>>
Entity::visible_neigbours() const {
    return _visible_neighbours;
}

void
Entity::set_time_step(float dt) {
    _dt = dt;
}

float
Entity::dt() const {
    return _dt;
}

void
Entity::decide_acceleration() {
    _acc = QVector2D(0, 0);
}

void
Entity::update() {
    _vel += _acc * _dt;
    _pos += _vel * _dt;
    update_scene_pos();
}

void
Entity::advance(int phase) {
    if (phase == 0) {
        decide_acceleration();
    }
    update();
}

void
Entity::update_scene_pos() {
    float vel_angle = 180 - qRadiansToDegrees(qAtan2(_vel.x(), _vel.y()));
    setRotation(vel_angle);
    setPos(_pos.x(), _pos.y());
}

QRectF
Entity::boundingRect() const {
    return QRectF(-_size.x() / 2, -_size.y() / 2, _size.x(), _size.y());
}

QPainterPath
Entity::shape() const {
    QPainterPath path;
    path.addRect(-_size.x() / 2, -_size.y() / 2, _size.x(), _size.y());
    return path;
}

void
Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
              QWidget *widget) {
    (void)option;  // Unused inherited param
    (void)widget;  // Unused inherited param
    // Simple ellipse
    painter->setBrush(_color);
    painter->drawEllipse(boundingRect());
    return;
}
