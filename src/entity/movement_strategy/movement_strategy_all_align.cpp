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

#include "movement_strategy_all_align.h"
#include "entity/ant/ant.h"

void
MovementStrategyAllAlign::compute_force(Ant* context) {
    QVector2D mean_velocity(0, 0);
    QVector2D target_velocity(0, 0);
    QVector2D target_acceleration(0, 0);
    float dt = context->time_step();

    // Compute the mean position
    int entity_count = 0;
    for (auto&& item : *context->neighbours()) {
        if (item->super_type_name() == "Inert") {
            continue;
        }
        mean_velocity += QVector2D(item->velocity());
        ++entity_count;
    }
    if (entity_count == 0) {
        _wrappee->compute_force(context);
        return;
    }

    mean_velocity /= entity_count;

    // Compute the Acceleration necessary to get there in one step
    target_velocity = mean_velocity;
    target_acceleration = (target_velocity - context->velocity()) / dt;
    target_acceleration *= _coef;

    // Add the equivalent acceleration
    context->set_acceleration(context->acceleration() + target_acceleration);

    _wrappee->compute_force(context);
}
