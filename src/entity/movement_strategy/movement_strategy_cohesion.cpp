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

#include "movement_strategy_cohesion.h"
#include "entity/ant/ant.h"

void
MovementStrategyCohesion::compute_force(Ant* context) {
    QVector2D mean_position(0, 0);
    int entity_count = context->neighbours()->size();
    for (auto&& item : *context->neighbours()) {
        mean_position += QVector2D(item->pos());
    }
    mean_position /= entity_count;
    QVector2D target_delta_pos = mean_position - QVector2D(context->pos());
    _applied_force += target_delta_pos.normalized() *
                      _coef / context->max_force();

    // TODO : detect if context would reach objective in 1 time step, so it can slow down

    _wrappee->compute_force(context);
}
