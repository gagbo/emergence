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

#ifndef _ENTITY_MOVEMENT_STRATEGY_MOVEMENT_STRATEGY_DECORATOR_H_
#define _ENTITY_MOVEMENT_STRATEGY_MOVEMENT_STRATEGY_DECORATOR_H_
#include "movement_strategy.h"

class MovementStrategyDecorator : public MovementStrategy {
 public:
    virtual ~MovementStrategyDecorator() {
        if (_wrappee) {
            delete _wrappee;
        }
    }

    MovementStrategyDecorator(MovementStrategy* wrappee) : _wrappee(wrappee) {}

    virtual void compute_force(Ant* context) override;

 protected:
    MovementStrategy* _wrappee{nullptr};
};
#endif  // _ENTITY_MOVEMENT_STRATEGY_MOVEMENT_STRATEGY_DECORATOR_H_
