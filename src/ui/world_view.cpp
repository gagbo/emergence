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

#include <QGraphicsScene>
#include <QtGui/QPainter>
#include <QtWidgets>
#include "world/world.h"

#include "world_view.h"

WorldView::WorldView(World& shown_world) {
    setScene(&shown_world);
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

    background = QBrush(QColor(64, 32, 64));
    setBackgroundBrush(background);

    xy_scale = 1;
    connect(get_scene(), SIGNAL(scale_change(float)), this,
            SLOT(change_scale(float)));
    connect(get_scene(), SIGNAL(scale_reset(void)), this,
            SLOT(reset_scale(void)));
    connect(get_scene(), SIGNAL(see_all_items(void)), this,
            SLOT(scale_to_see_all_items(void)));
}

WorldView::~WorldView() {}

void
WorldView::keyPressEvent(QKeyEvent* event) {
    /* TODO : A and F mappings are not perfect
     *
     * Currently the sceneRect() is undefined until the first mouse3 click. This
     * means that before the click, the sceneRect() will be the same as the
     * World::sceneRect() (which grows to fit all items and never shrinks)
     *
     * After the first mouse3 click, WorldView::setSceneRect() is called so the
     * random number generation below will always generate number within this
     * rectangle instead of random positions within the visible part of the
     * widget.
     */

    double dx = QRandomGenerator::global()->bounded(sceneRect().width());
    double dy = QRandomGenerator::global()->bounded(sceneRect().height());
    double pos_x = sceneRect().x() + dx;
    double pos_y = sceneRect().y() + dy;

    switch (event->key()) {
        case Qt::Key_A:
            emit key_handled(
                QString("Adding an Ant in (%1;%2)").arg(pos_x).arg(pos_y));
            get_scene()->add_entity("Living", "Ant", QVector2D(pos_x, pos_y));
            break;
        case Qt::Key_F:
            emit key_handled(
                QString("Adding Food in (%1;%2)").arg(pos_x).arg(pos_y));
            get_scene()->add_entity("Inert", "Food", QVector2D(pos_x, pos_y));
            break;
        case Qt::Key_V:
            emit key_handled("(V) Toggle vision drawing");
            get_scene()->toggle_all_visions();
            break;
        case Qt::Key_D:
            emit key_handled("(D) Disable vision drawing - Revert with E");
            get_scene()->disable_all_visions();
            break;
        case Qt::Key_E:
            emit key_handled("(E) Enable vision drawing - Revert with D");
            get_scene()->enable_all_visions();
            break;
        default:
            emit key_handled("User pressed " + event->text() +
                             " - NOT HANDLED");
    }
}

void
WorldView::change_scale(double scale_factor) {
    xy_scale *= scale_factor;
    scale(scale_factor, scale_factor);
    return;
}

void
WorldView::reset_scale() {
    scale(1 / xy_scale, 1 / xy_scale);
    xy_scale = 1.0;
    return;
}

void
WorldView::scale_to_see_all_items() {
    scale(1 / xy_scale, 1 / xy_scale);
    xy_scale = 1.0;
    setSceneRect(get_scene()->itemsBoundingRect());
    return;
}
