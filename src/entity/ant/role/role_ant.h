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

#ifndef _ENTITY_ANT_ROLE_ROLEANT_H_
#define _ENTITY_ANT_ROLE_ROLEANT_H_

#include <QDebug>
#include <QException>
#include <QHash>
#include "entity/ant/ant.h"
#include "entity/movement_strategy/movement_strategy.h"

class Ant;

//! A State for Ant responsible of setting the acceleration
class RoleAnt {
 public:
    static void register_name(QString name, RoleAnt* concrete_instance);
    //! Return a pointer to a subclassed Singleton Role
    static RoleAnt* get(QString name = "Default");

    //! Pure virtual method to get the Singleton
    static RoleAnt* instance();

    //! TODO : This computation needs to take the VelocityStrategy decorators
    //! into account
    virtual void decide_acceleration(Ant* context) = 0;

    //! Go to next role, registered by name
    void set_role(Ant* context, QString name);

    //! Return color of the current State
    const QColor color() const;

    //! Return vision of the current State
    const QPolygonF vision() const;

    virtual ~RoleAnt() {
        if (_role_move_strategy) {
            delete _role_move_strategy;
        }
    }

 protected:
    static RoleAnt* lookup(QString name);

    QColor _role_color{Qt::lightGray};
    QPolygonF _role_vision{QRectF(-30, 0, 60, -60)};
    MovementStrategy* _role_move_strategy{nullptr};

 private:
    static RoleAnt* _instance;
    static QHash<QString, RoleAnt*> _registry;
};

//! Exception thrown when the _registry is missing a Role
class RoleNotFound : public QException {
 public:
    RoleNotFound(QString missing_role) : _missing_role_name(missing_role) {}

    void
    raise() const {
        throw *this;
    }
    RoleNotFound*
    clone() const {
        return new RoleNotFound(*this);
    }
    QString
    qwhat() const {
        return "Non-existing Role : " + _missing_role_name;
    }

 protected:
    QString _missing_role_name;
};
#endif  // _ENTITY_ANT_ROLE_ROLEANT_H_
