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
    void test_toggle_vision(void);
    void test_wrap_around(void);
    void test_wrap_around_data(void);
};

void
TestWorld::add_food(void) {
    // Data
    World test_instance;

    // Test case insensitivity and passing arguments
    QVERIFY(test_instance.add_entity("Inert", "Food") != nullptr);
    QVERIFY(test_instance.add_entity("Inert", "Food", QVector2D(22, 35)) !=
            nullptr);
    QVERIFY(test_instance.add_entity("Inert", "Food", QVector2D(-3.2f, 21),
                                     QVector2D(24.1f, 1e-2f)) != nullptr);
    QVERIFY(test_instance.add_entity("inert", "food") != nullptr);
    QVERIFY(test_instance.add_entity("inert", "food", QVector2D(22, 35)) !=
            nullptr);
    QVERIFY(test_instance.add_entity("inert", "food", QVector2D(-3.2f, 21),
                                     QVector2D(24.1f, 1e-2f)) != nullptr);
    QVERIFY(test_instance.add_entity("InErt", "FooD") != nullptr);
    QVERIFY(test_instance.add_entity("InErt", "FooD", QVector2D(22, 35)) !=
            nullptr);
    QVERIFY(test_instance.add_entity("InErt", "FooD", QVector2D(-3.2f, 21),
                                     QVector2D(24.1f, 1e-2f)) != nullptr);

    // Test exception in case of bad type and super type
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("fdasdfas", "food"),
                             FactoryFailure);
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("inert", "fdsafe"),
                             FactoryFailure);
}

void
TestWorld::add_ant(void) {
    // Data
    World test_instance;

    // Test case insensitivity and passing arguments
    QVERIFY(test_instance.add_entity("Living", "Ant") != nullptr);
    QVERIFY(test_instance.add_entity("Living", "Ant", QVector2D(22, 35)) !=
            nullptr);
    QVERIFY(test_instance.add_entity("Living", "Ant", QVector2D(-3.2f, 21),
                                     QVector2D(24.1f, 1e-2f)) != nullptr);
    QVERIFY(test_instance.add_entity("living", "ant") != nullptr);
    QVERIFY(test_instance.add_entity("living", "ant", QVector2D(22, 35)) !=
            nullptr);
    QVERIFY(test_instance.add_entity("living", "ant", QVector2D(-3.2f, 21),
                                     QVector2D(24.1f, 1e-2f)) != nullptr);
    QVERIFY(test_instance.add_entity("liVinG", "aNt") != nullptr);
    QVERIFY(test_instance.add_entity("liVinG", "aNt", QVector2D(22, 35)) !=
            nullptr);
    QVERIFY(test_instance.add_entity("liVinG", "aNt", QVector2D(-3.2f, 21),
                                     QVector2D(24.1f, 1e-2f)) != nullptr);

    // Test exception in case of bad type and super type
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("fdasdfas", "ant"),
                             FactoryFailure);
    QVERIFY_EXCEPTION_THROWN(test_instance.add_entity("living", "fdsafe"),
                             FactoryFailure);
}

void
TestWorld::test_toggle_vision(void) {
    // Data
    World test_instance;
    const Entity* ant = test_instance.add_entity("Living", "Ant");

    test_instance.enable_all_visions();
    QVERIFY(ant->show_vision() == true);
    test_instance.disable_all_visions();
    QVERIFY(ant->show_vision() == false);
    test_instance.toggle_all_visions();
    QVERIFY(ant->show_vision() == true);
    test_instance.toggle_all_visions();
    QVERIFY(ant->show_vision() == false);
}

void TestWorld::test_wrap_around_data(void) {
    QTest::addColumn<QVector2D>("world_size");
    QTest::addColumn<QVector2D>("initial_pos");
    QTest::addColumn<QVector2D>("expected_pos");

    QTest::newRow("Integer  size -- No work")
            << QVector2D(640, 480)
            << QVector2D(-25, 200.3f)
            << QVector2D(-25, 200.3f);
    QTest::newRow("Integer  size -- 1 pass x+")
            << QVector2D(640, 480)
            << QVector2D(345.2f, 200.3f)
            << QVector2D(-294.8f, 200.3f);
    QTest::newRow("Integer  size -- multiple passes x+")
            << QVector2D(640, 480)
            << QVector2D(1049.2f, 200.3f)
            << QVector2D(-230.8f, 200.3f);
    QTest::newRow("Integer  size -- 1 pass x-")
            << QVector2D(640, 480)
            << QVector2D(-600.0f, 200.3f)
            << QVector2D(40.0f, 200.3f);
    QTest::newRow("Integer  size -- multiple passes x-")
            << QVector2D(640, 480)
            << QVector2D(-1240.0f, 200.3f)
            << QVector2D(40.0f, 200.3f);
    QTest::newRow("Integer  size -- 1 pass y+")
            << QVector2D(640, 480)
            << QVector2D(-25.0f, 250.3f)
            << QVector2D(-25.0f, -229.7f);
    QTest::newRow("Integer  size -- multiple passes y+")
            << QVector2D(640, 480)
            << QVector2D(-25.0f, 899.0f)
            << QVector2D(-25.0f, -61.0f);
    QTest::newRow("Integer  size -- 1 pass y-")
            << QVector2D(640, 480)
            << QVector2D(-25.0f, -490.3f)
            << QVector2D(-25.0f, -10.3f);
    QTest::newRow("Integer  size -- multiple passes y-")
            << QVector2D(640, 480)
            << QVector2D(-25.0f, -899.0f)
            << QVector2D(-25.0f, 61.0f);
    QTest::newRow("Integer  size -- 1 pass x+, y-")
            << QVector2D(640, 480)
            << QVector2D(345.2f, -490.3f)
            << QVector2D(-294.8f, -10.3f);
    QTest::newRow("Integer  size -- 1 pass x-, y+")
            << QVector2D(640, 480)
            << QVector2D(-600.0f, 250.3f)
            << QVector2D(40.0f, -229.7f);
    QTest::newRow("Integer  size -- multiple passes x-, 1 pass y+")
            << QVector2D(640, 480)
            << QVector2D(-1240.0f, 250.3f)
            << QVector2D(40.0f, -229.7f);
    QTest::newRow("Integer  size -- 1 pass x-, multiple passes y+")
            << QVector2D(640, 480)
            << QVector2D(-600.0f, 899.0f)
            << QVector2D(40.0f, -61.0f);
    QTest::newRow("Integer  size -- multiple passes x+, multiple passes y-")
            << QVector2D(640, 480)
            << QVector2D(1049.2f, -899.0f)
            << QVector2D(-230.8f, 61.0f);

    QTest::newRow("Floating size -- No work")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-25, 200.3f)
            << QVector2D(-25, 200.3f);
    QTest::newRow("Floating size -- 1 pass x+")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(345.2f, 200.3f)
            << QVector2D(-294.8f - 0.5f, 200.3f);
    QTest::newRow("Floating size -- multiple passes x+")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(1049.2f, 200.3f)
            << QVector2D(-230.8f - 1.0f, 200.3f);
    QTest::newRow("Floating size -- 1 pass x-")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-600.0f, 200.3f)
            << QVector2D(40.0f+0.5f, 200.3f);
    QTest::newRow("Floating size -- multiple passes x-")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-1240.0f, 200.3f)
            << QVector2D(40.0f+1.0f, 200.3f);
    QTest::newRow("Floating size -- 1 pass y+")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-25.0f, 250.3f)
            << QVector2D(-25.0f, -229.7f -0.5f);
    QTest::newRow("Floating size -- multiple passes y+")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-25.0f, 899.0f)
            << QVector2D(-25.0f, -61.0f - 1.0f);
    QTest::newRow("Floating size -- 1 pass y-")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-25.0f, -490.3f)
            << QVector2D(-25.0f, -10.3f + 0.5f);
    QTest::newRow("Floating size -- multiple passes y-")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-25.0f, -899.0f)
            << QVector2D(-25.0f, 61.0f + 1.0f);
    QTest::newRow("Floating size -- 1 pass x+, y-")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(345.2f, -490.3f)
            << QVector2D(-294.8f -0.5f, -10.3f + 0.5f);
    QTest::newRow("Floating size -- 1 pass x-, y+")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-600.0f, 250.3f)
            << QVector2D(40.0f + 0.5f, -229.7f -0.5f);
    QTest::newRow("Floating size -- multiple passes x-, 1 pass y+")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-1240.0f, 250.3f)
            << QVector2D(40.0f + 1.0f, -229.7f -0.5f);
    QTest::newRow("Floating size -- 1 pass x-, multiple passes y+")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(-600.0f, 899.0f)
            << QVector2D(40.0f + 0.5f, -61.0f - 1.0f);
    QTest::newRow("Floating size -- multiple passes x+, multiple passes y-")
            << QVector2D(640.5f, 480.5f)
            << QVector2D(1049.2f, -899.0f)
            << QVector2D(-230.8f -1.0f, 61.0f + 1.0f);
}

void TestWorld::test_wrap_around(void) {
    // Data
    World test_instance;
    QFETCH(QVector2D, world_size);
    QFETCH(QVector2D, initial_pos);
    QFETCH(QVector2D, expected_pos);


    // Test
    test_instance.set_size(world_size);
    test_instance.enable_wrap_around();
    test_instance.fix_position_for_wrap_around(initial_pos);
    QVERIFY(qFuzzyCompare(initial_pos, expected_pos));
}

QTEST_MAIN(TestWorld)
#include "test_world.moc"
