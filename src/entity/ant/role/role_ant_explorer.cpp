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

#include "role_ant_explorer.h"
#include "entity/movement_strategy/movement_strategy_alignment.h"
#include "entity/movement_strategy/movement_strategy_all_align.h"
#include "entity/movement_strategy/movement_strategy_base.h"
#include "entity/movement_strategy/movement_strategy_cohesion.h"
#include "entity/movement_strategy/movement_strategy_separation.h"

RoleAntExplorer* RoleAntExplorer::_instance = nullptr;

RoleAntExplorer::RoleAntExplorer() : RoleAnt() {
    _role_color = Qt::yellow;
    RoleAnt::register_name("Explorer", this);
    delete _role_move_strategy;
    _role_move_strategy = new MovementStrategyAlignment( 1,
        new MovementStrategySeparation(10, 50, 2,
        new MovementStrategyCohesion( 0.01,
        new MovementStrategyBase())));
}

void
RoleAntExplorer::decide_action(Ant* context) {
    _role_move_strategy->apply_force(context);
}

RoleAnt*
RoleAntExplorer::instance() {
    if (_instance == nullptr) {
        _instance = new RoleAntExplorer();
    }
    return _instance;
}
