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

#ifndef _UI_MAINWINDOW_H_
#define _UI_MAINWINDOW_H_

#include <QtWidgets>
#include <memory>
#include "world/world.h"
#include "world_view.h"

#define WINDOW_DEFAULT_WIDTH 640
#define WINDOW_DEFAULT_HEIGHT 480

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    MainWindow(World& app_world, qint32 win_wid = WINDOW_DEFAULT_WIDTH,
               qint32 win_hei = WINDOW_DEFAULT_HEIGHT);

 protected:
    void closeEvent(QCloseEvent* event) override;
    QSharedPointer<WorldView> _main_view;

 public slots:
    //! Show message in status bar
    void showMessage(QString message);

 private slots:

 private:
    void createActions();
    void createStatusBar();
};
#endif  // _UI_MAINWINDOW_H_
