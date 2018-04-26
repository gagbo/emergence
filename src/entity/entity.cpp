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

float
Entity::x() const {
    return _pos[0];
}
float
Entity::y() const {
    return _pos[1];
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

QWeakPointer<World>
Entity::parent_world() const {
    return _parent_world;
}
