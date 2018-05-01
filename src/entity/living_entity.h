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

#ifndef _ENTITY_LIVING_ENTITY_H_
#define _ENTITY_LIVING_ENTITY_H_

#include "entity.h"

class LivingEntity : public Entity {
 public:
    static QString super_type_string;

    LivingEntity();
    //! Construct a new Entity at position with initial velocity
    LivingEntity(const QVector2D &position,
                 const QVector2D &init_speed = QVector2D(0, 0));

    //! Override necessary because of _vision
    void update_neighbourhood() override;

    //! Override necessary because of _vision
    virtual QRectF boundingRect() const override;

    inline void
    set_vision(QSharedPointer<QPolygonF> new_vision) {
        // operator= handles the decrement of older reference count
        _vision = new_vision;
    }
    inline void
    set_vision(QWeakPointer<QPolygonF> new_vision) {
        set_vision(new_vision.toStrongRef());
    }

    //! Return a constant reference to the vision of LivingEntity
    /*! _vision should be non-null when we call this (although it
     * can point to an empty QPolygonF)
     */
    const QPolygonF &vision() const;
    //! Return true if this world_pos is visible by LivingEntity
    virtual bool is_visible(const QPointF &world_pos) const;

    virtual void decide_acceleration();

    inline void
    toggle_show_vision() {
        _show_vision = !_show_vision;
    }
    inline void
    disable_show_vision() {
        _show_vision = false;
    }
    inline void
    enable_show_vision() {
        _show_vision = true;
    }

    virtual ~LivingEntity() { _vision.clear(); }

 protected:
    //! Vision polygon in Item coord
    /*! We look forward in the -y direction
     * all Entities must be centered on (0,0) for _vision to work
     *
     * _vision should not be left null, it WILL break when we use the
     * vision() getter in other functionnalities
     *
     * TODO : consider a defaut construction of _vision.
     * Currently we prefer keeping returning a const reference to QPolygonF
     * in vision(), to avoid copies. However we are not able to simply return
     * an empty QPolygonF built on stack with this signature.
     */
    QSharedPointer<QPolygonF> _vision{};

    bool _show_vision{true};
};

#endif  // _ENTITY_LIVING_ENTITY_H_
