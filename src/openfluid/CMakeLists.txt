

INCLUDE_DIRECTORIES(${GDAL_INCLUDE_DIRS})

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(base)
ADD_SUBDIRECTORY(machine)
ADD_SUBDIRECTORY(fluidx)
ADD_SUBDIRECTORY(ware)
ADD_SUBDIRECTORY(tools)
ADD_SUBDIRECTORY(scientific)
ADD_SUBDIRECTORY(utils)
ADD_SUBDIRECTORY(buddies)
ADD_SUBDIRECTORY(waresdev)

IF(OFBUILD_ENABLE_GUI)
  ADD_SUBDIRECTORY(ui)
  IF (OFBUILD_ENABLE_APP_BUILDER)
    ADD_SUBDIRECTORY(builderext)
  ENDIF()
ENDIF()

IF(OFBUILD_ENABLE_LANDR)
  ADD_SUBDIRECTORY(landr)
ENDIF()  

IF(OFBUILD_ENABLE_MARKET)
  ADD_SUBDIRECTORY(market)
ENDIF()  

OFBUILD_CREATE_01_VAR(OFBUILD_ENABLE_GUI)
OFBUILD_CREATE_01_VAR(OFBUILD_ENABLE_LANDR)
OFBUILD_CREATE_01_VAR(OFBUILD_ENABLE_MARKET)
OFBUILD_CREATE_01_VAR(OFBUILD_ENABLE_SIM2DOC)

CONFIGURE_FILE(global.hpp.in global.hpp @ONLY)
CONFIGURE_FILE(config.hpp.in config.hpp @ONLY)
CONFIGURE_FILE(buildinfo.hpp.in buildinfo.hpp @ONLY)

FOREACH(AGGREGATE_NS ${OFBUILD_AGGREGATE_HEADER_NAMESPACES})
  string(TOUPPER ${AGGREGATE_NS} AGGREGATE_NS_UP)
  CONFIGURE_FILE(aggregate_namespace_header.tpl ${AGGREGATE_NS}.hpp @ONLY)
ENDFOREACH()


INSTALL(FILES dllexport.hpp debug.hpp
        DESTINATION ${OPENFLUID_INCLUDE_INSTALL_PATH})

FOREACH(AGGREGATE_NS ${OFBUILD_AGGREGATE_HEADER_NAMESPACES})
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${AGGREGATE_NS}.hpp
          DESTINATION ${OPENFLUID_INCLUDE_INSTALL_PATH})
ENDFOREACH()


INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/config.hpp" 
              "${CMAKE_CURRENT_BINARY_DIR}/global.hpp"
              "${CMAKE_CURRENT_BINARY_DIR}/buildinfo.hpp"
        DESTINATION ${OPENFLUID_INCLUDE_INSTALL_PATH})
                       