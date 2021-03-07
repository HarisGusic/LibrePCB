/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************************
 *  Includes
 ******************************************************************************/

#include <gtest/gtest.h>
#include <librepcb/common/cam/gerbergenerator.h>
#include <librepcb/common/fileio/fileutils.h>

#include <QtCore>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {
namespace tests {

/*******************************************************************************
 *  Test Class
 ******************************************************************************/

class GerberGeneratorTest : public ::testing::Test {};

/*******************************************************************************
 *  Test Methods
 ******************************************************************************/

TEST_F(GerberGeneratorTest, testFileAttributesX1) {
  GerberGenerator gen(
      QDateTime(QDate(2000, 2, 1), QTime(1, 2, 3, 4), Qt::OffsetFromUTC, 3600),
      "Project,|Name%?!\\äöü",
      Uuid::fromString("bdf7bea5-b88e-41b2-be85-c1604e8ddfca"), "rev,5.5-%äöü",
      true);
  gen.generate();
  QString output = gen.toStr();
  QStringList lines = output.split('\n');
  EXPECT_TRUE(
      lines.contains("G04 #@! TF.GenerationSoftware,LibrePCB,LibrePCB," %
                     qApp->applicationVersion() % "*"))
      << output.toStdString();
  EXPECT_TRUE(
      lines.contains("G04 #@! TF.CreationDate,2000-02-01T01:02:03+01:00*"))
      << output.toStdString();
  EXPECT_TRUE(
      lines.contains("G04 #@! TF.ProjectId,Project|Name?!aou,"
                     "bdf7bea5-b88e-41b2-be85-c1604e8ddfca,rev5.5-aou*"))
      << output.toStdString();
  EXPECT_TRUE(lines.contains("G04 #@! TF.Part,Single*"))
      << output.toStdString();
}

TEST_F(GerberGeneratorTest, testFileAttributesX2) {
  GerberGenerator gen(
      QDateTime(QDate(2000, 2, 1), QTime(1, 2, 3, 4), Qt::OffsetFromUTC, 3600),
      "Project,|Name%?!\\äöü",
      Uuid::fromString("bdf7bea5-b88e-41b2-be85-c1604e8ddfca"), "rev,5.5-%äöü",
      false);
  gen.generate();
  QString output = gen.toStr();
  QStringList lines = output.split('\n');
  EXPECT_TRUE(lines.contains("%TF.GenerationSoftware,LibrePCB,LibrePCB," %
                             qApp->applicationVersion() % "*%"))
      << output.toStdString();
  EXPECT_TRUE(lines.contains("%TF.CreationDate,2000-02-01T01:02:03+01:00*%"))
      << output.toStdString();
  EXPECT_TRUE(
      lines.contains("%TF.ProjectId,Project|Name?!aou,"
                     "bdf7bea5-b88e-41b2-be85-c1604e8ddfca,rev5.5-aou*%"))
      << output.toStdString();
  EXPECT_TRUE(lines.contains("%TF.Part,Single*%")) << output.toStdString();
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace tests
}  // namespace librepcb
