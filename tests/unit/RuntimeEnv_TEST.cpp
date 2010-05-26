/*
  This file is part of OpenFLUID-engine software
  Copyright (c) 2007-2010 INRA-Montpellier SupAgro

 == GNU General Public License Usage ==

  OpenFLUID-engine is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID-engine is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID-engine.  If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, INRA gives You the additional right
  to dynamically link the code of OpenFLUID-engine with code not covered 
  under the GNU General Public License ("Non-GPL Code") and to distribute
  linked combinations including the two, subject to the limitations in this
  paragraph. Non-GPL Code permitted under this exception must only link to
  the code of OpenFLUID-engine dynamically through the ofelib library
  interface, and only for building OpenFLUID-engine plugins. The files of
  Non-GPL Code may be link to the ofelib library without causing the
  resulting work to be covered by the GNU General Public License. You must
  obey the GNU General Public License in all respects for all of the
  OpenFLUID-engine code and other code used in conjunction with
  OpenFLUID-engine except the Non-GPL Code covered by this exception. If
  you modify this OpenFLUID-engine, you may extend this exception to your
  version of the file, but you are not obligated to do so. If you do not
  wish to provide this exception without modification, you must delete this
  exception statement from your version and license this OpenFLUID-engine
  solely under the GPL without exception.


 == Other Usage ==

  Other Usage means a use of OpenFLUID-Engine that is inconsistent with
  the GPL license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID-engine may use this file in
  accordance with the terms contained in the written agreement between
  You and INRA.
*/


/**
  \file RuntimeEnv_TEST.cpp
  \brief Implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#define BOOST_TEST_MAIN
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE unittest_runtimeenv
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <openfluid/base.hpp>

// =====================================================================
// =====================================================================


BOOST_AUTO_TEST_CASE(check_construction)
{


  BOOST_REQUIRE_NE(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir(),"");
  BOOST_REQUIRE_NE(openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir(),"");
  BOOST_REQUIRE_NE(openfluid::base::RuntimeEnvironment::getInstance()->getTempDir(),"");
  BOOST_REQUIRE_GT(openfluid::base::RuntimeEnvironment::getInstance()->getPluginsPaths().size(),0);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isClearOutputDir(),false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isVerboseRun(),false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isQuietRun(),false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isWriteResults(),true);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isWriteSimReport(),true);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isProgressiveOutput(),false);
  BOOST_REQUIRE_NE(openfluid::base::RuntimeEnvironment::getInstance()->getSimulationID(),"");

}

// =====================================================================
// =====================================================================

BOOST_AUTO_TEST_CASE(check_operations)
{

  openfluid::base::RuntimeEnvironment::getInstance()->setInputDir("/foo/bar");
  openfluid::base::RuntimeEnvironment::getInstance()->setOutputDir("/bar/foo/bar");
  openfluid::base::RuntimeEnvironment::getInstance()->setOutputDir("/bar/foo/bar");
  openfluid::base::RuntimeEnvironment::getInstance()->addExtraPluginsPaths("/bar/foo/foo/bar");
  openfluid::base::RuntimeEnvironment::getInstance()->addExtraPluginsPaths("/bar/foo/foo/bar/bar/bar");
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir(),"/foo/bar");
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir(),"/bar/foo/bar");
  BOOST_REQUIRE_NE(openfluid::base::RuntimeEnvironment::getInstance()->getTempDir(),"");
  BOOST_REQUIRE_GT(openfluid::base::RuntimeEnvironment::getInstance()->getPluginsPaths().size(),2);


  openfluid::base::RuntimeEnvironment::getInstance()->setClearOutputDir(true);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isClearOutputDir(),true);

  openfluid::base::RuntimeEnvironment::getInstance()->setVerboseRun(true);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isVerboseRun(),true);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isQuietRun(),false);

  openfluid::base::RuntimeEnvironment::getInstance()->setVerboseRun(false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isVerboseRun(),false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isQuietRun(),false);

  openfluid::base::RuntimeEnvironment::getInstance()->setVerboseRun(true);
  openfluid::base::RuntimeEnvironment::getInstance()->setQuietRun(true);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isVerboseRun(),false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isQuietRun(),true);

  openfluid::base::RuntimeEnvironment::getInstance()->setVerboseRun(false);
  openfluid::base::RuntimeEnvironment::getInstance()->setQuietRun(false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isVerboseRun(),false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isQuietRun(),false);

  openfluid::base::RuntimeEnvironment::getInstance()->setWriteResults(false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isWriteResults(),false);

  openfluid::base::RuntimeEnvironment::getInstance()->setWriteSimReport(false);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isWriteSimReport(),false);

  openfluid::base::RuntimeEnvironment::getInstance()->setProgressiveOutputKeep(23);
  openfluid::base::RuntimeEnvironment::getInstance()->setProgressiveOutputPacket(2345);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->isProgressiveOutput(),true);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->getProgressiveOutputPacket(),2345);
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->getProgressiveOutputKeep(),23);

  openfluid::base::RuntimeEnvironment::getInstance()->setSimulationID("THESIMID-2");
  BOOST_REQUIRE_EQUAL(openfluid::base::RuntimeEnvironment::getInstance()->getSimulationID(),"THESIMID-2");




  openfluid::base::FunctionEnvironment* FuncEnv;
  bool BoolValue;
  std::string StrValue;

  FuncEnv = openfluid::base::RuntimeEnvironment::getInstance()->getFunctionEnvironment();
  BOOST_REQUIRE(FuncEnv != NULL);

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("wrong.fake",&StrValue),false);
  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("fake.wrong",&BoolValue),false);

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("dir.input",&StrValue),true);
  BOOST_REQUIRE_EQUAL(StrValue,openfluid::base::RuntimeEnvironment::getInstance()->getInputDir());

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("dir.output",&StrValue),true);
  BOOST_REQUIRE_EQUAL(StrValue,openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir());

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("dir.temp",&StrValue),true);
  BOOST_REQUIRE_EQUAL(StrValue,openfluid::base::RuntimeEnvironment::getInstance()->getTempDir());

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("mode.clearoutputdir",&BoolValue),true);
  BOOST_REQUIRE_EQUAL(BoolValue,openfluid::base::RuntimeEnvironment::getInstance()->isClearOutputDir());

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("mode.quiet",&BoolValue),true);
  BOOST_REQUIRE_EQUAL(BoolValue,openfluid::base::RuntimeEnvironment::getInstance()->isQuietRun());

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("mode.verbose",&BoolValue),true);
  BOOST_REQUIRE_EQUAL(BoolValue,openfluid::base::RuntimeEnvironment::getInstance()->isVerboseRun());

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("mode.saveresults",&BoolValue),true);
  BOOST_REQUIRE_EQUAL(BoolValue,openfluid::base::RuntimeEnvironment::getInstance()->isWriteResults());

  BOOST_REQUIRE_EQUAL(FuncEnv->getValue("mode.writereport",&BoolValue),true);
  BOOST_REQUIRE_EQUAL(BoolValue,openfluid::base::RuntimeEnvironment::getInstance()->isWriteSimReport());

}

// =====================================================================
// =====================================================================
