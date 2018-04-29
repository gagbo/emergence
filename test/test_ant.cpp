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
#include "entity/ant/ant.h"
#include "entity/ant/role/role_ant.h"
#include "entity/ant/role/role_ant_explorer.h"
#include "entity/ant/role/role_ant_worker.h"
#include "world/world.h"

class TestAnt : public QObject {
    Q_OBJECT
 private slots:
    void change_roles(void);
};

void
TestAnt::change_roles(void) {
    // Test
    Ant first(QVector2D(23.4, -7e-8));
    QCOMPARE(first.x(), 23.4f);
    QCOMPARE(first.y(), -7e-8f);

    // Check case insensitivity
    first.set_role("Explorer");
    QCOMPARE(first.role(), RoleAntExplorer::instance());
    first.set_role("Worker");
    QCOMPARE(first.role(), RoleAntWorker::instance());
    first.set_role("explorer");
    QCOMPARE(first.role(), RoleAntExplorer::instance());
    first.set_role("worker");
    QCOMPARE(first.role(), RoleAntWorker::instance());
    first.set_role("expLorEr");
    QCOMPARE(first.role(), RoleAntExplorer::instance());
    first.set_role("woRkeR");
    QCOMPARE(first.role(), RoleAntWorker::instance());

    // Check that not found roles throw exceptions
    QVERIFY_EXCEPTION_THROWN(first.set_role("qsfse"), RoleNotFound);
}

QTEST_MAIN(TestAnt)
#include "test_ant.moc"
