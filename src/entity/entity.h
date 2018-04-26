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

#ifndef _ENTITY_ENTITY_H_
#define _ENTITY_ENTITY_H_

#include <QGraphicsItem>
#include <QVector2D>
#include <iostream>
#include "world/world.h"

class World;

class Entity : public QGraphicsItem {
 public:
    /////////////// Constructors

    //! Construct a new Ant to move in d dimensions (default 2)
    Entity() = default;

    //! Construct a new Ant at position
    Entity(const QVector2D &position);

    //! Construct a new Ant at position with inital velocity
    Entity(const QVector2D &position,
           const QVector2D &init_speed = QVector2D(0, 0));

    /////////////// Destructor
    ~Entity();

    /////////////// Misc. Methods

    //! Give an approximate bounding rectangle for the Ant
    QRectF boundingRect() const override;

    //! Give the shape of the Entity for collision detection
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

    //! Set the acceleration according to the surrounding of the Entity
    virtual void tick() = 0;

    //! Update the position of the Entity according to acceleration and
    //! World time step
    virtual void tock();

    /////////////// Accessors and output

    float x() const;
    float y() const;
    QVector2D position() const;
    QVector2D velocity() const;
    QVector2D acceleration() const;
    int id() const;
    float mass() const;
    float max_force() const;
    QColor color() const;
    float life() const;
    QVector2D size() const;

    QList<QWeakPointer<Entity>> neigbours() const;
    QList<QWeakPointer<Entity>> visible_neigbours() const;

    QWeakPointer<World> parent_world() const;

 protected:
    void advance(int phase) override;

    int _id{-1};                      //!< Global Entity Id
    QVector2D _pos{0, 0};             //!< Position
    QVector2D _vel{0, 0};             //!< Velocity
    QVector2D _acc{0, 0};             //!< Acceleration
    float _vel_angle{0};              //!< Current angle of the velocity
    float _mass{1};                   //!< Mass of the Entity
    float _max_force{1e-2};           //!< Maximum force the
                                      //!< Entity can apply to move itself
    QColor _color{200, 80, 25, 255};  //!< Color
    float _life{100};
    QVector2D _size{3, 3};
    QList<QWeakPointer<Entity>> _neighbours{};
    QList<QWeakPointer<Entity>> _visible_neighbours{};

    QWeakPointer<World> _parent_world{nullptr};
};
#endif  // _ENTITY_ENTITY_H_
