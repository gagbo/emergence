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

#include <QTest>
#include "world/world.h"

class TestWorld : public QObject {
    Q_OBJECT
 private slots:
    void add_food(void);
    void add_ant(void);
};

void
TestWorld::add_food(void) {
    // Data
    World test_instance;

    // Test case insensitivity and passing arguments
    QCOMPARE(test_instance.add_entity("Inert", "Food"), true);
    QCOMPARE(test_instance.add_entity("Inert", "Food", QVector2D(22, 35)), true);
    QCOMPARE(test_instance.add_entity("Inert", "Food", QVector2D(-3.2, 21), QVector2D(24.1, 1e-2)), true);
    QCOMPARE(test_instance.add_entity("inert", "food"), true);
    QCOMPARE(test_instance.add_entity("inert", "food", QVector2D(22, 35)), true);
    QCOMPARE(test_instance.add_entity("inert", "food", QVector2D(-3.2, 21), QVector2D(24.1, 1e-2)), true);
    QCOMPARE(test_instance.add_entity("InErt", "FooD"), true);
    QCOMPARE(test_instance.add_entity("InErt", "FooD", QVector2D(22, 35)), true);
    QCOMPARE(test_instance.add_entity("InErt", "FooD", QVector2D(-3.2, 21), QVector2D(24.1, 1e-2)), true);


    // Test exception in case of bad type and super type
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("fdasdfas", "food"), FactoryFailure);
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("inert", "fdsafe"), FactoryFailure);
}

void
TestWorld::add_ant(void) {
    // Data
    World test_instance;

    // Test case insensitivity and passing arguments
    QCOMPARE(test_instance.add_entity("Living", "Ant"), true);
    QCOMPARE(test_instance.add_entity("Living", "Ant", QVector2D(22, 35)), true);
    QCOMPARE(test_instance.add_entity("Living", "Ant", QVector2D(-3.2, 21), QVector2D(24.1, 1e-2)), true);
    QCOMPARE(test_instance.add_entity("living", "ant"), true);
    QCOMPARE(test_instance.add_entity("living", "ant", QVector2D(22, 35)), true);
    QCOMPARE(test_instance.add_entity("living", "ant", QVector2D(-3.2, 21), QVector2D(24.1, 1e-2)), true);
    QCOMPARE(test_instance.add_entity("liVinG", "aNt"), true);
    QCOMPARE(test_instance.add_entity("liVinG", "aNt", QVector2D(22, 35)), true);
    QCOMPARE(test_instance.add_entity("liVinG", "aNt", QVector2D(-3.2, 21), QVector2D(24.1, 1e-2)), true);


    // Test exception in case of bad type and super type
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("fdasdfas", "ant"), FactoryFailure);
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("living", "fdsafe"), FactoryFailure);
}

QTEST_MAIN(TestWorld)
#include "test_world.moc"
