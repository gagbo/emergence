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

#ifndef _ENTITY_FACTORY_ENTITYFACTORY_H_
#define _ENTITY_FACTORY_ENTITYFACTORY_H_
#include "entity/food/food.h"

#include "entity/inert_entity.h"
#include "entity/living_entity.h"

#include "entity/entity.h"

#include <QSharedPointer>
#include <QString>

class InertEntityFactory {
 public:
    template <typename... Ts>
    static InertEntity*
    make_entity(QString type, Ts&&... params) {
        if (QString::compare(type, Food::type_string, Qt::CaseInsensitive) == 0) {
            return new Food(std::forward<Ts>(params)...);
        } else {
            // TODO Throw TypeUnknown
            return nullptr;
        }
    }
};

class LivingEntityFactory {
 public:
    template <typename... Ts>
    static LivingEntity*
    make_entity(QString type, Ts&&... params) {
        if (QString::compare(type, "ant", Qt::CaseInsensitive) == 0) {
            // TODO Throw TypeUnsupported
            return nullptr;
        } else if (QString::compare(type, "predator", Qt::CaseInsensitive) ==
                   0) {
            // TODO Throw TypeUnsupported
            return nullptr;
        } else {
            // TODO Throw TypeUnknown
            return nullptr;
        }
    }
};

class EntityFactory {
 public:
    template <typename... Ts>
    static Entity*
    make_entity(QString super_type, QString type, Ts&&... params) {
        if (QString::compare(super_type, LivingEntity::super_type_string,
                             Qt::CaseInsensitive) == 0) {
            // TODO Catch TypeUnknown
            return LivingEntityFactory::make_entity(
                type, std::forward<Ts>(params)...);
        } else if (QString::compare(super_type, InertEntity::super_type_string,
                                    Qt::CaseInsensitive) == 0) {
            // TODO Catch TypeUnknown
            return InertEntityFactory::make_entity(type,
                                                   std::forward<Ts>(params)...);
        } else {
            // TODO Throw SupertypeUnknown
            return nullptr;
        }
    }
};
#endif  // _ENTITY_FACTORY_ENTITYFACTORY_H_
