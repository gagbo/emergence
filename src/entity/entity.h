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
    static QString super_type_string;
    static QString type_string;
    /////////////// Constructors

    //! Construct a new Entity
    Entity() = default;

    //! Copy Constructor
    Entity(const Entity &other);

    //! Default move Constructor
    Entity(Entity &&other) = default;

    //! Construct a new Ant at position with inital velocity
    Entity(const QVector2D &position,
           const QVector2D &init_speed = QVector2D(0, 0));

    /////////////// Destructor
    virtual ~Entity();

    /////////////// Misc. Methods

    //! Give an approximate bounding rectangle for the Ant
    virtual QRectF boundingRect() const override;

    //! Give the shape of the Entity for collision detection
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

    //! Get a pointer to parent World
    World *parent_world() const;

    //! Obtain the time step from World
    float time_step() const;

    //! Override called by World to update the entity
    void advance(int phase) override;

    //! Update the _neighbours and _visible_neighbours members
    /*! For LivingEntity we use _vision to make the update
     *  For InertEntity, no override necessary :
     *     - _neighbours will have all Entities
     *     - _visible_neighbours will be empty
     */
    virtual void update_neighbourhood();

    //! Set the acceleration according to the surrounding of the Entity
    virtual void decide_acceleration();

    //! Computes the friction force the Entity undergoes given position,
    //! velocity.
    /*! Side effect : set _friction_force to the relevant value considering
     * velocity of the Entity
     */
    virtual QVector2D get_friction_force();

    //! Apply the Friction force to the decided acceleration
    void apply_friction_to_acceleration();

    //! Update the position of the Entity according to acceleration, dt
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
    float friction_coefficient() const;
    float max_force() const;
    QColor color() const;
    float life() const;
    QVector2D size() const;
    QString type_name() const;
    QString super_type_name() const;

    QList<const Entity*> *neighbours() const;
    QList<const Entity*> *visible_neighbours() const;

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

    //! Arbitrarily set friction coefficient of entity
    void set_friction_coefficient(float new_friction_coef);

    //! Arbitrarily set max_force of entity
    void set_max_force(float new_max_force);

    //! Arbitrarily set id of entity
    void set_id(int new_id);

    //! Arbitrarily set life of entity
    void set_life(float new_life);

    //! Arbitrarily set size of entity
    void set_size(QVector2D new_size);

 protected:
    int _id{-1};                         //!< Global Entity Id
    QVector2D _pos{0, 0};                //!< Position
    QVector2D _vel{0, 0};                //!< Velocity
    QVector2D _acc{0, 0};                //!< Acceleration
    float _vel_angle{0};                 //!< Current angle of the velocity
    float _mass{1};                      //!< Mass of the Entity
    float _max_force{4};                 //!< Maximum force the
                                         //!< Entity can apply to move itself
    float _linear_vel_friction_coef{10};  //!< friction coefficient
                                         //!< for linear velocity
    QColor _color{200, 0, 0, 255};       //!< Color
    float _life{100};
    QVector2D _size{20, 20};
    QList<const Entity*> *_neighbours{new QList<const Entity*>};
    QList<const Entity*> *_visible_neighbours{
        new QList<const Entity*>};

    // TODO : check if still necessary with the static
    QString _super_type{""};
    QString _type{""};
};
#endif  // _ENTITY_ENTITY_H_
