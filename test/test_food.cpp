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
#include "entity/food/food.h"
#include "world/world.h"

Q_DECLARE_METATYPE(Food);

class TestFood : public QObject {
    Q_OBJECT
 private slots:
    void access(void);
    void entity_setters_getters(void);
    void update_doesnt_accelerate(void);
    void update_doesnt_accelerate_data(void);
};

void
TestFood::access(void) {
    // Data
    float coord1(1.25);
    float coord2(-3.1);
    float v1(2.1);
    float v2(-0.243);

    // Test
    Food first(QVector2D(coord1, coord2));
    Food second = Food(QVector2D(coord1, coord2));
    Food third(QVector2D(coord2, coord1), QVector2D(v1, v2));
    QCOMPARE(first.x(), coord1);
    QCOMPARE(first.y(), coord2);
    QCOMPARE(second.x(), coord1);
    QCOMPARE(second.y(), coord2);
    QCOMPARE(third.x(), coord2);
    QCOMPARE(third.y(), coord1);
    QCOMPARE(third.velocity().x(), v1);
    QCOMPARE(third.velocity().y(), v2);
}

void
TestFood::entity_setters_getters(void) {
    Food tested(QVector2D(23, 23));

    tested.set_position(QVector2D(-41.1, 0.211));
    QCOMPARE(tested.x(), -41.1f);
    QCOMPARE(tested.y(), 0.211f);

    tested.set_velocity(QVector2D(1e-10, 2e1));
    QCOMPARE(tested.velocity(), QVector2D(1e-10, 2e1));

    tested.set_acceleration(QVector2D(1, 2));
    QCOMPARE(tested.acceleration(), QVector2D(1.0, 2.0));

    tested.set_color(QColor("red"));
    QCOMPARE(tested.color(), QColor("red"));

    tested.set_mass(1.4562);
    QCOMPARE(tested.mass(), 1.4562f);

    tested.set_max_force(1e-5);
    QCOMPARE(tested.max_force(), 1e-5f);

    tested.set_id(2);
    QCOMPARE(tested.id(), 2);

    tested.set_life(253);
    QCOMPARE(tested.life(), 253);

    tested.set_size(QVector2D(24, 32));
    QCOMPARE(tested.size(), QVector2D(24, 32));

    tested.set_size(QVector2D(-2, 98));
    QCOMPARE(tested.size(), QVector2D(2, 98));
}

void
TestFood::update_doesnt_accelerate_data(void) {
    QTest::addColumn<QVector2D>("position");
    QTest::addColumn<QVector2D>("velocity");
    QTest::addColumn<float>("time_step");
    QTest::addColumn<QVector2D>("expected_position");

    QTest::newRow("No initial speed") << QVector2D(23, -1.43) << QVector2D(0, 0)
                                      << 1.2f << QVector2D(23, -1.43);
}

void
TestFood::update_doesnt_accelerate(void) {
    // Data
    QFETCH(QVector2D, position);
    QFETCH(QVector2D, velocity);
    QFETCH(float, time_step);
    QFETCH(QVector2D, expected_position);

    // Test
    World test_world;
    test_world.set_time_step(time_step);
    Food tested(position, velocity);
    test_world.addItem(&tested);
    tested.advance(0);
    QCOMPARE(tested.position(), position);
    QCOMPARE(tested.velocity(), velocity);
    QCOMPARE(tested.acceleration().x() + 1.0f, 1.0f);
    QCOMPARE(tested.acceleration().y() + 1.0f, 1.0f);

    tested.advance(1);
    QCOMPARE(tested.position(), expected_position);
    QCOMPARE(tested.velocity(), velocity);
    QCOMPARE(tested.acceleration().x() + 1.0f, 1.0f);
    QCOMPARE(tested.acceleration().y() + 1.0f, 1.0f);
}

QTEST_MAIN(TestFood)
#include "test_food.moc"
