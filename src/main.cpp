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

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QtWidgets>
#include <iostream>

#include "emergenceConfig.h"
#include "ui/mainwindow.h"
#include "world/world.h"

int
main(int argc, char* argv[]) {
    std::cout << argv[0] << " Version " << EMERGENCE_VERSION_MAJOR << "."
              << EMERGENCE_VERSION_MINOR << std::endl;

    srand(static_cast<unsigned>(time(nullptr)));

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Gerry Agbobada");
    QCoreApplication::setApplicationName(
        "emergence - Flocking Autonomous Agents");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("dummy", "Test the command line parser");
    parser.process(app);

    World basic_world;
    basic_world.set_time_step(0.1);
    basic_world.disable_wrap_around();
    
    // Small test code of the World API. This will be moved after LivingEntities
    // are developed
    try {
        basic_world.add_entity("inert", "food");
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("inert", "food", QVector2D(25, 90));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("inert", "food", QVector2D(-21, -45));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("living", "ant", QVector2D(-100, 28));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    // TODO : Move this code to the (future) test for the Factory
    try {
        basic_world.add_entity("inert", "foofdasfed");
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("oops", "food");
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    MainWindow mainWin(basic_world);
    mainWin.show();

    // Timer to trigger update, disabled for now
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), mainWin.get_view()->get_scene(),
                     SLOT(advance()));
    timer.start(mainWin.get_view()->get_scene()->time_step());

    return app.exec();
}
