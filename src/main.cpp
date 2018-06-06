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

void set_up_testing_env(World& basic_world);

int
main(int argc, char* argv[]) {
    std::cout << argv[0] << " Version " << EMERGENCE_VERSION_MAJOR << "."
              << EMERGENCE_VERSION_MINOR << std::endl;
    std::cout << "\n"
                 "*********** Usage ************\n"
                 "Hit [W] to toggle finite/infinite World (wrapping around)\n"
                 "Hit [V] to toggle the vision of Entities in the window\n"
                 "Hit [D] to disable the vision of Entities in the window\n"
                 "Hit [E] to enable the vision of Entities in the window\n"
                 "Hit [A] to add an Ant in a random position within view\n"
                 "Hit [F] to add Food in a random position within view\n";

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
    basic_world.set_time_step(1.0f / 60.0f);
    basic_world.disable_wrap_around();

    set_up_testing_env(basic_world);

    MainWindow mainWin(basic_world);
    mainWin.show();

    // Timer to trigger update, disabled for now
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), mainWin.get_view()->get_scene(),
                     SLOT(advance()));
    timer.start(static_cast<int>(1000.0f *
                                 mainWin.get_view()->get_scene()->time_step()));

    return app.exec();
}

void
set_up_testing_env(World& basic_world) {
    // Small test code of the World API. This will be moved after LivingEntities
    // are developed
    try {
        basic_world.add_entity("inert", "food");
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_prototype_entity("indsafesf");
    } catch (PrototypeNotFound& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_prototype_entity("ant_worker");
    } catch (PrototypeNotFound& e) {
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
        basic_world.add_entity("living", "ant", QVector2D(-300, 208));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("living", "ant", QVector2D(1000, 50));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("living", "ant", QVector2D(-500, -150));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("living", "ant", QVector2D(-2000, 300));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("living", "ant", QVector2D(-1, 2));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("living", "ant", QVector2D(-25, 0));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }

    try {
        basic_world.add_entity("living", "ant", QVector2D(5, -18));
    } catch (FactoryFailure& e) {
        qInfo() << e.qwhat();
    }
}
