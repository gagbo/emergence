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

#ifndef _WORLD_WORLD_H_
#define _WORLD_WORLD_H_

#include <QGraphicsScene>
#include <QVector2D>
#include "entity/factory/entity_factory.h"

#define DEFAULT_TIMESTEP 0.5
#define DEFAULT_BORDER_COLOR "limegreen"
#define DEFAULT_WORLD_WIDTH 640
#define DEFAULT_WORLD_HEIGHT 480

class QGraphicsSceneMouseEvent;

class Entity;

class World : public QGraphicsScene {
    Q_OBJECT

 public:
    //! Default Constructor
    World();

    //! Destructor
    ~World() override;

    //! Render the World for QGraphicsView
    void render();

    //! Add an entity to the World
    /** TODO : Manage ownership of return pointer
     * How can we manage ownership ? The method should return a WeakPointer
     */
    template <typename... Ts>
    Entity *
    add_entity(QString super_type, QString type, Ts &&... params) {
        Entity *p_entity = EntityFactory::make_entity(
            super_type, type, std::forward<Ts>(params)...);
        addItem(p_entity);
        p_entity->set_id(_next_id);
        _next_id++;
        p_entity->update();
        return p_entity;
    }

    //! Get the friction coefficient for a position in the world
    float get_friction(QVector2D position);

    //! update the world state, advancing _time_step in _time
    void update();

    //! Enable wraps_around and return the new current value
    bool enable_wrap_around();

    //! Disable wraps_around and return the new current value
    bool disable_wrap_around();

    //! Toggle wraps_around and return the new current value
    bool toggle_wrap_around();

    //! Return the current status for wrap_around
    inline bool wrap_around() const;

    //! Sets arbitrarily the size of the World (useful only with _wraps_around)
    void set_size(QVector2D new_size);

    //! Return the current size of the World (useful only with _wraps_around)
    QVector2D size() const;

    /*!
     * @brief fix_position_for_wrap_around Ensure that old_position is within
     * the rectangle centered in (0;0) and with dimensions _size, ONLY if
     * _wraps_around is set
     * @param [in,out] old_position is the position to be modified in order to
     * fit the requirement
     */
    void fix_position_for_wrap_around(QVector2D &old_position) const;

    float time_step() const;
    void set_time_step(float dt);

    //! Toggle the _show_visions of all LivingEntity contained
    void toggle_all_visions();
    //! Enable the _show_visions of all LivingEntity contained
    void enable_all_visions();
    //! Disable the _show_visions of all LivingEntity contained
    void disable_all_visions();

 signals:
    //! Emit a message to be read and/or printed by MainWindow
    void message(QString);

    //! Emit a signal to multiply the scale of the view by given factor
    void scale_change(float);

    //! Emit a signal to reset the scale of the view to 1:1
    void scale_reset(void);

    //! Emit a signal to ask a view to see all its items
    void see_all_items(void);

 protected:
    float _time_step{DEFAULT_TIMESTEP};  //!< Time step of the physics engine
    QColor _border_color{DEFAULT_BORDER_COLOR};  //!< Color of the border to
                                                 //!< draw where the scene wraps
                                                 //!< around

    bool _wraps_around{false};
    QVector2D _size{DEFAULT_WORLD_WIDTH, DEFAULT_WORLD_HEIGHT};
    float _time{0};
    QVector<QSharedPointer<Entity>> _agents{};
    int _next_id{0};  //!< Next id to assign to Entity

    //! Draw a border around the World rectangle if the world wraps around
    /*! This is an overloaded method, the second parameter is not used.
     */
    void drawForeground(QPainter *, const QRectF &) override;

    //! Handle mouse button events to emit signals upwards
    /*! The Left button emits a message to tell where we clicked
     *  The middle button resets the scaling of the representation of the scene
     *  The right button pops a menu
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;

    //! Handle mouse scroll events to emit zoom signals to the containing view
    void wheelEvent(QGraphicsSceneWheelEvent *) override;

    //! Tick the world state
    /*! Here ticking means
     *   - Update the neighbourhoods for each Entity
     *   - Uptate the decision for each Entity (acceleration decided)
     */
    void tick();

    //! Tock the world state
    /*! Here tocking means
     *   - Update the position of each Entity with their decided acceleration
     *   - Wrap around if applicable the positions of each Entity
     */
    void tock();
};
#endif  // _WORLD_WORLD_H_
