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

#include "inert_entity.h"

const static QString super_type_value = "Inert";

InertEntity::InertEntity() : Entity() { _super_type = super_type_value; }

InertEntity::InertEntity(const QVector2D &position, const QVector2D &init_speed)
    : Entity(position, init_speed) {
    _super_type = super_type_value;
}

void
InertEntity::decide_action() {
    _acc = QVector2D(0, 0);
    return;
}

Entity *
InertEntity::clone() {
    /* FIXME : Entity::clone is not enough
     * if we return only Entity::clone then all the InertEntity properties are
     * wrong
     */
    return Entity::clone();
}
