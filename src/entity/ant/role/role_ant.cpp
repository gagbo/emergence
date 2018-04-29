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

#include "role_ant.h"

QHash<QString, RoleAnt*> RoleAnt::_registry = QHash<QString, RoleAnt*>();
RoleAnt* RoleAnt::_instance = nullptr;

RoleAnt*
RoleAnt::instance(QString name) {
    _instance = lookup(name.toLower());
    return _instance;
}

RoleAnt*
RoleAnt::lookup(QString name) {
    auto it = _registry.find(name);
    if (it == _registry.end()) {
        throw RoleNotFound(name);
    }

    return it.value();
}

void
RoleAnt::decide_acceleration(Ant* context) {
    context->_acc = QVector2D(0, 0);
}

void
RoleAnt::set_role(Ant* context, QString name) {
    try {
        RoleAnt* new_role = instance(name);
        context->set_role(new_role);
    } catch (RoleNotFound& e) {
        qInfo() << e.qwhat() << "Role unchanged";
    }
}

void
RoleAnt::register_name(QString name, RoleAnt* concrete_instance) {
    _registry.insert(name.toLower(), concrete_instance);
}
