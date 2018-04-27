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

class World;

class Entity : public QGraphicsItem {
 public:
    /////////////// Constructors

    //! Construct a new Entity
    Entity() = default;

    //! Copy Constructor
    // TODO : decide what to do with _neighbours and _visible_neighbours
    Entity(const Entity& other);

    //! Default move Constructor
    Entity(Entity&& other) = default;

    //! Construct a new Ant at position with inital velocity
    Entity(const QVector2D &position,
           const QVector2D &init_speed = QVector2D(0, 0));

    /////////////// Destructor
    virtual ~Entity();

    /////////////// Misc. Methods

    //! Give an approximate bounding rectangle for the Ant
    QRectF boundingRect() const override;

    //! Give the shape of the Entity for collision detection
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

    //! Override called by World to update the entity
    void advance(int phase) override;

    //! Set the acceleration according to the surrounding of the Entity
    virtual void decide_acceleration();

    //! Update the position of the Entity according to acceleration, _dt
    //! and set the position in World
    virtual void update();

    //! Set the position and rotation in the parent World
    void update_scene_pos();

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
    float dt() const;
    QString type_name() const;
    QString super_type_name() const;

    QList<QWeakPointer<Entity>> neigbours() const;
    QList<QWeakPointer<Entity>> visible_neigbours() const;

    void set_time_step(float dt);

    //! Arbitrarily set position of entity
    void set_position(QVector2D new_pos);

    //! Arbitrarily set velocity of entity
    void set_velocity(QVector2D new_vel);

    //! Arbitrarily set position of entity
    void set_acceleration(QVector2D new_acc);

    //! Arbitrarily set color of entity
    void set_color(QColor new_color);

    //! Arbitrarily set mass of entity
    void set_mass(float new_mass);

    //! Arbitrarily set max_force of entity
    void set_max_force(float new_max_force);

    //! Arbitrarily set id of entity
    void set_id(int new_id);

    //! Arbitrarily set life of entity
    void set_life(float new_life);

    //! Arbitrarily set size of entity
    void set_size(QVector2D new_size);

 protected:

    int _id{-1};                    //!< Global Entity Id
    QVector2D _pos{0, 0};           //!< Position
    QVector2D _vel{0, 0};           //!< Velocity
    QVector2D _acc{0, 0};           //!< Acceleration
    float _vel_angle{0};            //!< Current angle of the velocity
    float _mass{1};                 //!< Mass of the Entity
    float _max_force{1e-2};         //!< Maximum force the
                                    //!< Entity can apply to move itself
    QColor _color{200, 0, 0, 255};  //!< Color
    float _life{100};
    QVector2D _size{20, 20};
    QList<QWeakPointer<Entity>> _neighbours{};
    QList<QWeakPointer<Entity>> _visible_neighbours{};

    float _dt{1};  //<! Time-step given by World

    QString _super_type{""};
    QString _type{""};
};
#endif  // _ENTITY_ENTITY_H_
