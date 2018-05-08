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

#include <QPainter>
#include <QtMath>

#include "world/world.h"

#include "entity.h"

#define LOW_SPEED_THRESHOLD (1e-1)

Entity::~Entity() {
    _visible_neighbours->clear();
    _neighbours->clear();
    _vision.clear();

    delete _visible_neighbours;
    delete _neighbours;
}

Entity::Entity(const Entity &other) {
    _id = other._id;
    _pos = other._pos;
    _vel = other._vel;
    _acc = other._acc;
    _vel_angle = other._vel_angle;
    _mass = other._mass;
    _max_force = other._max_force;
    _color = other._color;
    _life = other._life;
    _size = other._size;
    _super_type = other._super_type;
    _type = other._type;
    _neighbours = new QList<const Entity *>;
    _visible_neighbours = new QList<const Entity *>;
}

Entity::Entity(const QVector2D &position, const QVector2D &init_speed) {
    _pos = position;
    _vel = init_speed;
}

QString
Entity::super_type_name() const {
    return _super_type;
}

QString
Entity::type_name() const {
    return _type;
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

QList<const Entity *> *
Entity::neighbours() const {
    return _neighbours;
}

QList<const Entity *> *
Entity::visible_neighbours() const {
    return _visible_neighbours;
}

void
Entity::decide_acceleration() {
    _acc = QVector2D(0, 0);
}

QVector2D
Entity::get_friction_force() {
    if (_vel.lengthSquared() < LOW_SPEED_THRESHOLD * LOW_SPEED_THRESHOLD) {
        return QVector2D(0, 0);
    }

    // Solid friction with World tile
    QVector2D linear_friction_force(_vel);
    linear_friction_force.normalize();
    float solid_friction = parent_world()->get_friction(_pos);
    linear_friction_force *= -1 * solid_friction;
    // If the solid friction is too strong, cancel velocity and acceleration
    if (linear_friction_force.lengthSquared() >
        _mass * _mass * _acc.lengthSquared()) {
        _vel *= 0;
        return -1 * _mass * _acc;
    }

    // Add Linear velocity friction
    linear_friction_force += -1 * _linear_vel_friction_coef * _vel;
    return linear_friction_force;
}

World *
Entity::parent_world() const {
    return dynamic_cast<World *>(scene());
}

float
Entity::time_step() const {
    return parent_world()->time_step();
}

void
Entity::update() {
    _vel += _acc * time_step();
    _pos += _vel * time_step();
    parent_world()->fix_position_for_wrap_around(_pos);
    _acc *= 0;
    update_scene_pos();
}

void
Entity::apply_friction_to_acceleration() {
    _acc += get_friction_force() / _mass;
}

void
Entity::advance(int phase) {
    if (phase == 0) {
        update_neighbourhood();
        decide_acceleration();
        apply_friction_to_acceleration();
        return;
    }
    update();
}

void
Entity::update_neighbourhood() {
    _visible_neighbours->clear();
    _neighbours->clear();

    for (auto &&item : parent_world()->items()) {
        _neighbours->append(dynamic_cast<const Entity *>(item));
    }
}

bool
Entity::is_visible(const QPointF &world_pos) const {
    if (_vision.isNull()) {
        return false;
    }

    // FIXME : Needs a fix when world wraps around
    return vision().containsPoint(mapFromScene(world_pos), Qt::OddEvenFill);
}

const QPolygonF &
Entity::vision() const {
    return *_vision.data();
}

void
Entity::update_scene_pos() {
    if (_vel.lengthSquared() > LOW_SPEED_THRESHOLD * LOW_SPEED_THRESHOLD) {
        float vel_angle = 180 - qRadiansToDegrees(qAtan2(_vel.x(), _vel.y()));
        setRotation(vel_angle);
    }
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
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect());
    return;
}

void
Entity::set_position(QVector2D new_pos) {
    _pos = new_pos;
}

void
Entity::set_velocity(QVector2D new_vel) {
    _vel = new_vel;
}

void
Entity::set_acceleration(QVector2D new_acc) {
    _acc = new_acc;
}

void
Entity::set_color(QColor new_color) {
    _color = new_color;
}

void
Entity::set_mass(float new_mass) {
    _mass = new_mass;
}

void
Entity::set_max_force(float new_max_force) {
    _max_force = new_max_force;
}

void
Entity::set_id(int new_id) {
    _id = new_id;
}

void
Entity::set_life(float new_life) {
    _life = new_life;
}

void
Entity::set_size(QVector2D new_size) {
    _size = new_size;
    _size.setX(qFabs(_size.x()));
    _size.setY(qFabs(_size.y()));
}
