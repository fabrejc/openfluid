
SET(CPACK_SOURCE_GENERATOR "TGZ")
  
  
IF(OFBUILD_DISTRO_IS_DEBIAN)  
  SET(CPACK_GENERATOR "DEB")      
  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-test${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, qt5-default, qtbase5-dev-tools, qttools5-dev-tools, libqt5svg5-dev, libgdal-dev, gcc, g++, cmake (>= 2.8.9), gnuplot (>= 4.2), p7zip-full, graphviz, git")    
  IF(OFBUILD_ENABLE_LANDR)
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libgeos++-dev (>= 3.3.0)")
  ENDIF()  
  SET(CPACK_DEBIAN_PACKAGE_RECOMMENDS "gnuplot (>= 4.2), p7zip-full, graphviz") 
  SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${OFBUILD_DISTRO_ARCH}")
  SET(CPACK_DEBIAN_PACKAGE_SECTION "science")
  SET(CPACK_DEBIAN_PACKAGE_PRIORITY "extra")
  SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${OFBUILD_DISTRO_CODE}_${OFBUILD_DISTRO_ARCH}")
ENDIF()
  
  
IF(OFBUILD_DISTRO_IS_UBUNTU)  
  SET(CPACK_GENERATOR "DEB")      
  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-test${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, qt5-default, qtbase5-dev-tools, qttools5-dev-tools, libqt5svg5-dev, libgdal-dev, gcc, g++, cmake (>= 2.8.9), gnuplot (>= 4.2), p7zip-full, graphviz, git")    
  IF(OFBUILD_ENABLE_LANDR)
    IF(${OFBUILD_DISTRO_VERSION} VERSION_GREATER "12.04")
      SET(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libgeos++-dev (>= 3.3.0)")
    ELSE()
      SET(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libgeos-dev (>= 3.3.0)")    
    ENDIF()
  ENDIF()  
  SET(CPACK_DEBIAN_PACKAGE_RECOMMENDS "gnuplot (>= 4.2), p7zip-full, graphviz") 
  SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${OFBUILD_DISTRO_ARCH}")
  SET(CPACK_DEBIAN_PACKAGE_SECTION "science")
  SET(CPACK_DEBIAN_PACKAGE_PRIORITY "extra")
  SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${OFBUILD_DISTRO_CODE}_${OFBUILD_DISTRO_ARCH}")
ENDIF()
  

IF(OFBUILD_DISTRO_IS_CENTOS)
  SET(CPACK_GENERATOR "RPM") 
  SET(CPACK_RPM_PACKAGE_REQUIRES "gcc-c++, boost-devel >= 1.40, gdal-devel, qt5-qttools-devel, qt5-qtbase-devel, qt5-qtsvg-devel, qt5-qtwebkit-devel, qt5-qtsvg-devel, git")
  IF(OFBUILD_ENABLE_LANDR)
    SET(CPACK_RPM_PACKAGE_REQUIRES "${CPACK_RPM_PACKAGE_REQUIRES}, libgeos-devel >= 3.3.0")
  ENDIF()  
  SET(CPACK_RPM_PACKAGE_ARCHITECTURE "${OF_DISRO_ARCH}")
  SET(CPACK_PACKAGE_DESCRIPTION "This package contains the OpenFLUID software environment for modelling landscapes functionning, mainly oriented on spatial fluxes modelling. It also includes API and tools for development.")
  SET(CPACK_RPM_PACKAGE_DESCRIPTION "${OPENFLUID_PACKAGE_DESCRIPTION}")
  SET(CPACK_RPM_PACKAGE_SUMMARY "${OPENFLUID_PACKAGE_SUMMARY}")
  SET(CPACK_RPM_PACKAGE_GROUP "science")
  SET(CPACK_RPM_PACKAGE_LICENSE "${OPENFLUID_PACKAGE_LICENSE}")
  SET(CPACK_RPM_PACKAGE_VERSION "${OPENFLUID_VERSION_MAJOR}.${OPENFLUID_VERSION_MINOR}.${OPENFLUID_VERSION_PATCH}")
  STRING(SUBSTRING ${OFBUILD_DISTRO_VERSION} 0 1 CENTOS_EL_VERSION)
  SET(CPACK_RPM_PACKAGE_RELEASE "1.el${CENTOS_EL_VERSION}")
  IF(OPENFLUID_VERSION_STATUS)
    SET(CPACK_RPM_PACKAGE_RELEASE "0.${OPENFLUID_VERSION_STATUS}.el${CENTOS_EL_VERSION}")
  ENDIF()    
  SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_RPM_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.${OFBUILD_DISTRO_ARCH}")
ENDIF()


IF(OFBUILD_DISTRO_IS_FEDORA)
  SET(CPACK_GENERATOR "RPM") 
  SET(CPACK_RPM_PACKAGE_REQUIRES "make, gcc-c++, gcc-gfortran, cmake, boost-devel >= 1.54, gdal-devel, qt5-qttools-devel, qt5-qtbase-devel, qt5-qtsvg-devel, qt5-qtwebkit-devel, qt5-qtsvg-devel, p7zip, gnuplot, graphviz, doxygen, git")
  IF(OFBUILD_ENABLE_LANDR)
    SET(CPACK_RPM_PACKAGE_REQUIRES "${CPACK_RPM_PACKAGE_REQUIRES}, geos-devel >= 3.3.2")
  ENDIF()  
  SET(CPACK_RPM_PACKAGE_ARCHITECTURE "${OF_DISRO_ARCH}")
  SET(CPACK_PACKAGE_DESCRIPTION "This package contains the OpenFLUID software environment for modelling landscapes functionning, mainly oriented on spatial fluxes modelling. It also includes API and tools for development.")
  SET(CPACK_RPM_PACKAGE_DESCRIPTION "${OPENFLUID_PACKAGE_DESCRIPTION}")
  SET(CPACK_RPM_PACKAGE_SUMMARY "${OPENFLUID_PACKAGE_SUMMARY}")
  SET(CPACK_RPM_PACKAGE_GROUP "science")
  SET(CPACK_RPM_PACKAGE_LICENSE "${OPENFLUID_PACKAGE_LICENSE}")
  SET(CPACK_RPM_PACKAGE_VERSION "${OPENFLUID_VERSION_MAJOR}.${OPENFLUID_VERSION_MINOR}.${OPENFLUID_VERSION_PATCH}")
  STRING(SUBSTRING ${OFBUILD_DISTRO_VERSION} 0 2 FEDORA_FC_VERSION)
  SET(CPACK_RPM_PACKAGE_RELEASE "1.fc${FEDORA_FC_VERSION}")
  IF(OPENFLUID_VERSION_STATUS)
    SET(CPACK_RPM_PACKAGE_RELEASE "0.${OPENFLUID_VERSION_STATUS}.fc${FEDORA_FC_VERSION}")
  ENDIF()
  SET(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_PREFIX}/${OFBUILD_BIN_INSTALL_PATH}" 
                                           "${CMAKE_INSTALL_PREFIX}/${OFBUILD_LIB_INSTALL_PATH}" "${CMAKE_INSTALL_PREFIX}/${OFBUILD_INCLUDE_INSTALL_PATH}"  
                                           "${CMAKE_INSTALL_PREFIX}/${OFBUILD_SHARE_INSTALL_PATH}"
                                           "${CMAKE_INSTALL_PREFIX}/${OPENFLUID_DESKTOPENTRY_INSTALL_PATH}" 
                                           "${CMAKE_INSTALL_PREFIX}/${OPENFLUID_SHARE_TRANSLATIONS_INSTALL_PATH}" "${CMAKE_INSTALL_PREFIX}/${OFBUILD_SHARE_INSTALL_PATH}/doc")
  SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_RPM_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.${OFBUILD_DISTRO_ARCH}")
ENDIF()

