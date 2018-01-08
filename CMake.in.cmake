#
# Configuration file for CMakeLists.txt files
#
# Author : Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
#
# This file is included by the main CMakeLists.txt file, and defines variables
# to configure the build and install
#
# The variables in this file can also be overriden through the
# CMake.in.local.config file
#


################### general ###################

SET(OPENFLUID_MAIN_NAME "openfluid")


################### versions ###################

SET(OFBUILD_CUSTOM_CMAKE_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")

SET(OPENFLUID_VERSION_MAJOR 2)
SET(OPENFLUID_VERSION_MINOR 1)
SET(OPENFLUID_VERSION_PATCH 5)
SET(OPENFLUID_VERSION_STATUS "alpha10") # example: SET(OPENFLUID_VERSION_STATUS "rc1")

SET(OPENFLUID_VERSION_FULL "${OPENFLUID_VERSION_MAJOR}.${OPENFLUID_VERSION_MINOR}.${OPENFLUID_VERSION_PATCH}")

IF(OPENFLUID_VERSION_STATUS)
  SET(OPENFLUID_VERSION_FULL "${OPENFLUID_VERSION_FULL}~${OPENFLUID_VERSION_STATUS}")
ENDIF()

# Compute version as numeric
MATH(EXPR OPENFLUID_VERSION_NUMERIC "${OPENFLUID_VERSION_MAJOR} * 10000 + ${OPENFLUID_VERSION_MINOR} * 100 + ${OPENFLUID_VERSION_PATCH}")


################### paths and files ###################

SET(OPENFLUID_RELATIVE_PATH "${OPENFLUID_MAIN_NAME}")

SET(OPENFLUID_DEFAULT_INPUT_PATH "OPENFLUID.IN")
SET(OPENFLUID_DEFAULT_OUTPUT_PATH "OPENFLUID.OUT")
SET(OPENFLUID_WORKSPACE_PATH "workspace")
SET(OPENFLUID_WARESBIN_PATH "wares")
SET(OPENFLUID_WARESDEV_PATH "wares-dev")
SET(OPENFLUID_SIMULATORS_PATH "simulators")
SET(OPENFLUID_OBSERVERS_PATH "observers")
SET(OPENFLUID_BUILDEREXTS_PATH "builderexts")
SET(OPENFLUID_EXAMPLES_PATH "examples")
SET(OPENFLUID_PROJECTS_PATH "projects")

SET(OPENFLUID_PROJECT_INPUT_PATH "IN")
SET(OPENFLUID_PROJECT_OUTPUT_PATHPREFIX "OUT")

SET(OFBUILD_BIN_INSTALL_PATH "bin")
SET(OFBUILD_LIB_INSTALL_PATH "lib${OFBUILD_LIBDIR_SUFFIX}")
SET(OFBUILD_INCLUDE_INSTALL_PATH "include")
SET(OFBUILD_SHARE_INSTALL_PATH "share")
SET(OPENFLUID_INCLUDE_INSTALL_PATH "${OFBUILD_INCLUDE_INSTALL_PATH}/${OPENFLUID_RELATIVE_PATH}")
SET(OPENFLUID_SHARE_INSTALL_PATH "${OFBUILD_SHARE_INSTALL_PATH}/${OPENFLUID_RELATIVE_PATH}")

SET(OPENFLUID_DESKTOPENTRY_INSTALL_PATH "${OFBUILD_SHARE_INSTALL_PATH}/applications")

SET(OPENFLUID_SHARE_COMMON_INSTALL_PATH "${OPENFLUID_SHARE_INSTALL_PATH}/common")
SET(OPENFLUID_SHARE_TRANSLATIONS_INSTALL_PATH "${OFBUILD_SHARE_INSTALL_PATH}/locale")
SET(OPENFLUID_SHARE_APPS_INSTALL_PATH "${OPENFLUID_SHARE_INSTALL_PATH}/apps")
SET(OPENFLUID_SHARE_WARESDEV_INSTALL_PATH "${OPENFLUID_SHARE_INSTALL_PATH}/waresdev")

SET(OPENFLUID_SIMULATORS_INSTALL_PATH "${OFBUILD_LIB_INSTALL_PATH}/${OPENFLUID_RELATIVE_PATH}/${OPENFLUID_SIMULATORS_PATH}")
SET(OPENFLUID_OBSERVERS_INSTALL_PATH "${OFBUILD_LIB_INSTALL_PATH}/${OPENFLUID_RELATIVE_PATH}/${OPENFLUID_OBSERVERS_PATH}")
SET(OPENFLUID_BUILDEREXTS_INSTALL_PATH "${OFBUILD_LIB_INSTALL_PATH}/${OPENFLUID_RELATIVE_PATH}/${OPENFLUID_BUILDEREXTS_PATH}")

IF (WIN32)
  SET(OPENFLUID_CMAKE_MODULES_INSTALL_PATH "${OFBUILD_LIB_INSTALL_PATH}/cmake")
  SET(OPENFLUID_CMAKE_HELPERSMODULES_INSTALL_PATH "${OFBUILD_LIB_INSTALL_PATH}/cmake")
ELSE()
  SET(OPENFLUID_CMAKE_MODULES_INSTALL_PATH "${OFBUILD_LIB_INSTALL_PATH}/${OPENFLUID_RELATIVE_PATH}/cmake")
  SET(OPENFLUID_CMAKE_HELPERSMODULES_INSTALL_PATH "${OFBUILD_LIB_INSTALL_PATH}/${OPENFLUID_RELATIVE_PATH}helpers/cmake")
ENDIF()

SET(OPENFLUID_DOC_INSTALL_PATH "${OFBUILD_SHARE_INSTALL_PATH}/doc/${OPENFLUID_RELATIVE_PATH}")
SET(OPENFLUID_MAIN_DOC_INSTALL_PATH "${OPENFLUID_DOC_INSTALL_PATH}/main")
SET(OPENFLUID_SIMULATORS_DOC_INSTALL_PATH "${OPENFLUID_DOC_INSTALL_PATH}/${OPENFLUID_SIMULATORS_PATH}")
SET(OPENFLUID_OBSERVERS_DOC_INSTALL_PATH "${OPENFLUID_DOC_INSTALL_PATH}/${OPENFLUID_OBSERVERS_PATH}")

SET(OPENFLUID_EXAMPLES_INSTALL_PATH "${OPENFLUID_DOC_INSTALL_PATH}/${OPENFLUID_EXAMPLES_PATH}")
SET(OPENFLUID_EXAMPLES_PROJECTS_INSTALL_PATH "${OPENFLUID_EXAMPLES_INSTALL_PATH}/${OPENFLUID_PROJECTS_PATH}")
SET(OPENFLUID_EXAMPLES_SRC_INSTALL_PATH "${OPENFLUID_EXAMPLES_INSTALL_PATH}/src")
SET(OPENFLUID_EXAMPLES_DATA_INSTALL_PATH "${OPENFLUID_EXAMPLES_INSTALL_PATH}/datasets")
SET(OPENFLUID_EXAMPLES_DOCPDF_INSTALL_PATH "${OPENFLUID_EXAMPLES_INSTALL_PATH}")


SET(OPENFLUID_DEFAULT_CONFIGFILE "${OPENFLUID_MAIN_NAME}.conf")
SET(OPENFLUID_PROJECT_FILE "${OPENFLUID_MAIN_NAME}-project.conf")


################### source and output directories ###################

SET(OFBUILD_SOURCE_EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/${OPENFLUID_EXAMPLES_PATH}")
SET(OFBUILD_SOURCE_EXAMPLES_PROJECTS_DIR "${OFBUILD_SOURCE_EXAMPLES_DIR}/projects")

SET(OFBUILD_DOC_LAYOUT_DIR "${CMAKE_SOURCE_DIR}/doc/layout")
SET(OFBUILD_DOC_CONTENTS_DIR "${CMAKE_SOURCE_DIR}/doc/contents")
SET(OFBUILD_DOC_SRCTOPARSE_DIR "${CMAKE_SOURCE_DIR}/src/openfluid")


SET(OFBUILD_DIST_DIR "${CMAKE_BINARY_DIR}/dist")
SET(OFBUILD_DIST_LIB_DIR "${OFBUILD_DIST_DIR}/${OFBUILD_LIB_INSTALL_PATH}")
SET(OFBUILD_DIST_BIN_DIR "${OFBUILD_DIST_DIR}/${OFBUILD_BIN_INSTALL_PATH}")

SET(OFBUILD_DIST_SIMULATORS_DIR "${OFBUILD_DIST_DIR}/${OPENFLUID_SIMULATORS_INSTALL_PATH}")
SET(OFBUILD_DIST_OBSERVERS_DIR "${OFBUILD_DIST_DIR}/${OPENFLUID_OBSERVERS_INSTALL_PATH}")
SET(OFBUILD_DIST_BUILDEREXTS_DIR "${OFBUILD_DIST_DIR}/${OPENFLUID_BUILDEREXTS_INSTALL_PATH}")

SET(OFBUILD_DIST_CMAKE_MODULES_DIR "${OFBUILD_DIST_DIR}/${OPENFLUID_CMAKE_MODULES_INSTALL_PATH}")

SET(OFBUILD_DIST_MAIN_DOC_DIR "${OFBUILD_DIST_DIR}/${OPENFLUID_MAIN_DOC_INSTALL_PATH}")
SET(OFBUILD_DIST_SIMULATORS_DOC_DIR "${OFBUILD_DIST_DIR}/${OPENFLUID_SIMULATORS_DOC_INSTALL_PATH}")

SET(OFBUILD_DIST_TRANSLATIONS_DIR "${OFBUILD_DIST_DIR}/${OPENFLUID_SHARE_TRANSLATIONS_INSTALL_PATH}")

SET(OFBUILD_DOCBUILD_DIR "${CMAKE_BINARY_DIR}/docbuild")

SET(OFBUILD_TESTS_BINARY_DIR "${CMAKE_BINARY_DIR}/tests-bin")
SET(OFBUILD_TESTS_USERDATA_DIR "${CMAKE_BINARY_DIR}/tests-userdata")
SET(OFBUILD_TESTS_TEMP_DIR "${CMAKE_BINARY_DIR}/tests-temp")
SET(OFBUILD_TESTS_INPUT_DATASETS_DIR "${CMAKE_SOURCE_DIR}/resources/tests/datasets")
SET(OFBUILD_TESTS_INPUT_MISCDATA_DIR "${CMAKE_SOURCE_DIR}/resources/tests/miscdata")
SET(OFBUILD_TESTS_OUTPUT_DATA_DIR "${CMAKE_BINARY_DIR}/tests-output")
SET(OPENFLUID_TESTS_TEMP_PATH ${OFBUILD_TESTS_TEMP_DIR}) # for usage in OPENFLUID_ADD_TEST macro
SET(OPENFLUID_TESTS_USERDATA_PATH ${OFBUILD_TESTS_USERDATA_DIR}) # for usage in OPENFLUID_ADD_TEST macro


################### applications ###################

SET(OPENFLUID_CMD_APP "openfluid")
SET(OPENFLUID_BUILDER_APP "openfluid-builder")
SET(OPENFLUID_DEVSTUDIO_APP "openfluid-devstudio")
SET(OPENFLUID_LOGEXPLORER_APP "openfluid-logexplorer")

IF(APPLE)
  SET(OPENFLUID_BUILDER_APP "OpenFLUID-Builder")
  SET(OPENFLUID_DEVSTUDIO_APP "OpenFLUID-Devstudio")
  SET(OPENFLUID_LOGEXPLORER_APP "OpenFLUID-Logexplorer")
ENDIF()


################### compilation and build ###################

IF(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
  SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wextra")
  SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra")
ENDIF()

SET(OFBUILD_AGGREGATE_HEADER_NAMESPACES base buddies core machine fluidx tools ware scientific)

IF(APPLE)
  SET(CMAKE_FIND_FRAMEWORK LAST)
ENDIF()

SET(OPENFLUID_PLUGINS_BINARY_EXTENSION "${CMAKE_SHARED_LIBRARY_SUFFIX}")
SET(OPENFLUID_PLUGINS_GHOST_EXTENSION ".xml")

SET(OPENFLUID_SIMULATORS_SUFFIX "_ofware${OPENFLUID_VERSION_NUMERIC}-sim")
SET(OPENFLUID_OBSERVERS_SUFFIX "_ofware${OPENFLUID_VERSION_NUMERIC}-obs")
SET(OPENFLUID_BUILDEREXTS_SUFFIX "_ofware${OPENFLUID_VERSION_NUMERIC}-bext")

SET(OPENFLUID_GHOSTSIMULATORS_SUFFIX "_ofghost-sim")

SET(OPENFLUID_DEBUG_PREFIX "[OpenFLUID debug]")


################### 3rd party headers and libraries ###################

SET(RapidJSON_GIT_URL "https://github.com/miloyip/rapidjson.git")


################### parts and libraries build ###################

SET(OFBUILD_ENABLE_GUI 1)

SET(OFBUILD_ENABLE_LANDR 1)

SET(OFBUILD_ENABLE_MARKET 0)


################### applications build ###################

# set this to 1 to build openfluid command line program
SET(OFBUILD_ENABLE_APP_CMD 1)

# set this to 1 to build openfluid-minimal
SET(OFBUILD_ENABLE_APP_MINIMAL 1)

# set this to 1 to build openfluid-builder
SET(OFBUILD_ENABLE_APP_BUILDER 1)

# set this to 1 to build openfluid-devstudio
SET(OFBUILD_ENABLE_APP_DEVSTUDIO 1)

# set this to 1 enable waresdev integration in openfluid-builder
SET(ENABLE_WARESDEV_BUILDER_INTEGRATION 1)

# set this to 1 to build openfluid-market-client
SET(OFBUILD_ENABLE_APP_MARKETCLIENT 0)

# set this to 1 enable market integration in openfluid-builder
SET(OFBUILD_ENABLE_MARKET_BUILDER_INTEGRATION 0)

# set this to 1 to build openfluid-logexplorer
SET(OFBUILD_ENABLE_APP_LOGEXPLORER 1)


################### doc build ###################

# uncomment this to build latex docs
SET(BUILD_DOCS 1)


################### logfiles ###################

SET(OPENFLUID_MESSAGES_LOG_FILE "openfluid-messages.log")

SET(OPENFLUID_CUMULATIVE_PROFILE_FILE "openfluid-profile-cumulative.log")
SET(OPENFLUID_SCHEDULE_PROFILE_FILE "openfluid-profile-schedule.log")
SET(OPENFLUID_TIMEINDEX_PROFILE_FILE "openfluid-profile-timeindex.log")


################### waresdev ###################

SET(OPENFLUID_WARESDEV_CMAKE_USERFILE "CMake.in.config")
SET(OPENFLUID_WARESDEV_CMAKE_SIMCPPVAR "SIM_CPP")
SET(OPENFLUID_WARESDEV_CMAKE_OBSCPPVAR "OBS_CPP")
SET(OPENFLUID_WARESDEV_CMAKE_BEXTCPPVAR "BEXT_CPP")


################### market ###################

SET(OPENFLUID_MARKETBAGDIR "market-bag")
SET(OPENFLUID_MARKETPLACE_SITEFILE "OpenFLUID-Marketplace")
SET(OPENFLUID_MARKETPLACE_CATALOGFILE "Catalog")

SET(OPENFLUID_MARKET_COMMONBUILDOPTS "-DSIM_SIM2DOC_DISABLED=1")

IF(WIN32)
  SET(OPENFLUID_MARKET_COMMONBUILDOPTS "-G \\\"${CMAKE_GENERATOR}\\\" ${OPENFLUID_MARKET_COMMONBUILDOPTS}")
ENDIF()


################### i18n ###################

SET(OFBUILD_TRANSLATIONS_TSDIR "${CMAKE_SOURCE_DIR}/resources/translations")
SET(OFBUILD_TRANSLATIONS_DIRSTOSCAN "${CMAKE_SOURCE_DIR}/src/openfluid/ui"
                                    "${CMAKE_SOURCE_DIR}/src/openfluid/ui/config.hpp.in"
                                    "${CMAKE_SOURCE_DIR}/src/openfluid/waresdev"
                                    "${CMAKE_SOURCE_DIR}/src/apps/openfluid-builder"
                                    "${CMAKE_SOURCE_DIR}/src/apps/openfluid-devstudio")
SET(OPENFLUID_TRANSLATIONS_FILEROOT openfluid)
SET(OPENFLUID_TRANSLATIONS_LANGS fr_FR)


################### tests configuration ###################

# uncomment this to build simulators mixing C++ and fortran source codes (in this source tree)
#SET(OFBUILD_TESTS_ENABLE_FORTRAN 1)

# set options passed to unit tests programs. ex: "--log_level=all"
SET(OFBUILD_UNITTESTS_RUN_OPTIONS "")

SET(OFBUILD_TESTS_RESTSERVICE_URL_HTTP "http://jsonplaceholder.typicode.com")
SET(OFBUILD_TESTS_RESTSERVICE_URL_HTTPS "https://jsonplaceholder.typicode.com")
SET(OFBUILD_TESTS_FLUIDHUB_URL_HTTP "http://www.openfluid-project.org/resources/fluidhub-api/testing")
SET(OFBUILD_TESTS_FLUIDHUB_URL_HTTPS "https://www.openfluid-project.org/resources/fluidhub-api/testing")
SET(OFBUILD_TESTS_WARESHUB_URL_HTTP ${OFBUILD_TESTS_FLUIDHUB_URL_HTTP})
SET(OFBUILD_TESTS_WARESHUB_URL_HTTPS ${OFBUILD_TESTS_FLUIDHUB_URL_HTTPS})
SET(OFBUILD_TESTS_WARESHUB_USERNAME "")
SET(OFBUILD_TESTS_WARESHUB_PASSWORD "")
SET(OFBUILD_TESTS_GITHELPER_URL "https://github.com/libgit2/TestGitRepository")
SET(OFBUILD_TESTS_GITHELPER_EMPTYREPOS_URL "https://github.com/libgit2/TestEmptyRepository")
SET(OFBUILD_TESTS_GITHELPER_AUTH_URL "https://bitbucket.org/libgit2/testgitrepository.git")
SET(OFBUILD_TESTS_GITHELPER_AUTH_USERNAME "libgit2")
SET(OFBUILD_TESTS_GITHELPER_AUTH_PASSWORD "libgit2")


################### cppcheck ###################

SET(OFBUILD_CPPCHECK_EXTRA_OPTIONS "-q"
                           "--enable=style,information,performance,portability,missingInclude"
                           "--suppress=variableScope"
                           "--force")
