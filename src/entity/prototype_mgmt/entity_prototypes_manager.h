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

#ifndef _ENTITY_PROTOTYPESMGMT_PROTOTYPESMANAGER_H
#define _ENTITY_PROTOTYPESMGMT_PROTOTYPESMANAGER_H

#include <QException>
#include <QString>
#include <memory>
#include <string>
#include <unordered_map>

#include "entity/entity.h"

/*! Prototypes manager for entities
 */
class EntityPrototypesManager {
 public:
    EntityPrototypesManager();
    ~EntityPrototypesManager();

    /*!
     * \brief register_name add an entry to the prototypes manager
     * \param [in] name is the name of the prototype
     * \param [in] prototype is a pointer to the prototype to register
     * Note : passing a unique_ptr by value means the function is a "sink"
     */
    void register_name(std::string name, std::unique_ptr<Entity> prototype);

    //! Return a pointer to a subclassed Singleton Role
    const std::weak_ptr<Entity> get(std::string name = "Default") const;

 protected:
 private:
    std::unordered_map<std::string, const std::shared_ptr<Entity> > _registry;
};

//! Exception thrown when the _registry is missing a prototype
class PrototypeNotFound : public QException {
 public:
    PrototypeNotFound(QString missing_prototype)
        : _missing_prototype_name(missing_prototype) {}

    void
    raise() const {
        throw *this;
    }
    PrototypeNotFound*
    clone() const {
        return new PrototypeNotFound(*this);
    }
    QString
    qwhat() const {
        return "Non-existing Prototype : " + _missing_prototype_name;
    }

 protected:
    QString _missing_prototype_name;
};

#endif  // _ENTITY_PROTOTYPESMGMT_PROTOTYPESMANAGER_H
