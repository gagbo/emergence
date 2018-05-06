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

#include "mainwindow.h"

MainWindow::MainWindow(World& app_world, qint32 win_wid, qint32 win_hei)
    : _main_view(new WorldView(app_world)) {
    _main_view->setRenderHint(QPainter::Antialiasing);
    _main_view->setViewportUpdateMode(
        QGraphicsView::BoundingRectViewportUpdate);
    _main_view->setDragMode(QGraphicsView::ScrollHandDrag);

    setCentralWidget(_main_view.data());

    createActions();
    createStatusBar();
    resize(win_wid, win_hei);
    move((win_wid - width()) / 2, (win_hei - height()) / 2);

    setUnifiedTitleAndToolBarOnMac(true);

    connect(_main_view->get_scene(), SIGNAL(message(QString)), this,
            SLOT(showMessage(QString)));
    connect(_main_view.data(), SIGNAL(key_handled(QString)), this,
            SLOT(showMessage(QString)));
}

void
MainWindow::closeEvent(QCloseEvent* event) {
    event->accept();
    // event->ignore();
}

void
MainWindow::createActions() {
    menuBar()->addMenu("&File");
    menuBar()->addMenu("&Edit");
    menuBar()->addMenu("&View");
    menuBar()->addMenu("&Simulate");
    menuBar()->addMenu("&Help");
}

void
MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready"));
}

void
MainWindow::showMessage(QString msg) {
    // display message on main window status bar
    statusBar()->showMessage(msg);
}
