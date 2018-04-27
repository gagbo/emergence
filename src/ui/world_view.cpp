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
}

WorldView::~WorldView() {}

void
WorldView::change_scale(float scale_factor) {
    xy_scale *= scale_factor;
    scale(scale_factor, scale_factor);
    return;
}
