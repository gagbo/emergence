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

#ifndef _ENTITY_MOVEMENT_STRATEGY_MOVEMENT_STRATEGY_BASE_H_
#define _ENTITY_MOVEMENT_STRATEGY_MOVEMENT_STRATEGY_BASE_H_
#include "entity/ant/ant.h"
#include "movement_strategy.h"

//! Only "standalone" base class of the Decorator
/*! This class is meant to be the only concrete subclass of MovementStrategy
 * This way, code should not compile if a Strategy is defined where this Base strategy is not effectively the last layer
 * As the forced last layer, we can give it more responsibilities :
 *    - It is (optionnally) responsible to cancel out too small forces
 *    - It also can cap the force so it doesn't go beyond context->max_force()
 *
 * The optionnal responsibility of cancelling out small forces probably mean
 * there should be another MovementStrategyBase that does the cancel
 */
class MovementStrategyBase : public MovementStrategy {
 public:
    MovementStrategyBase() : MovementStrategy() {}
    ~MovementStrategyBase() {}
    void compute_force(Ant* context) override;
};
#endif  // _ENTITY_MOVEMENT_STRATEGY_MOVEMENT_STRATEGY_BASE_H_
