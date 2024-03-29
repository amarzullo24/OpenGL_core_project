# Install script for directory: /home/alessandro/Desktop/bullet-2.82-r2704/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Library/Frameworks")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Library/Frameworks/include/bullet/btBulletCollisionCommon.h;/Library/Frameworks/include/bullet/btBulletDynamicsCommon.h;/Library/Frameworks/include/bullet/Bullet-C-Api.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Library/Frameworks/include/bullet" TYPE FILE FILES
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/btBulletCollisionCommon.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/btBulletDynamicsCommon.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/Bullet-C-Api.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Library/Frameworks/include/bullet/vectormath/vmInclude.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Library/Frameworks/include/bullet/vectormath" TYPE FILE FILES "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/vmInclude.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Library/Frameworks/include/bullet/vectormath/scalar/boolInVec.h;/Library/Frameworks/include/bullet/vectormath/scalar/floatInVec.h;/Library/Frameworks/include/bullet/vectormath/scalar/mat_aos.h;/Library/Frameworks/include/bullet/vectormath/scalar/quat_aos.h;/Library/Frameworks/include/bullet/vectormath/scalar/vec_aos.h;/Library/Frameworks/include/bullet/vectormath/scalar/vectormath_aos.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Library/Frameworks/include/bullet/vectormath/scalar" TYPE FILE FILES
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/scalar/boolInVec.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/scalar/floatInVec.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/scalar/mat_aos.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/scalar/quat_aos.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/scalar/vec_aos.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/scalar/vectormath_aos.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Library/Frameworks/include/bullet/vectormath/sse/boolInVec.h;/Library/Frameworks/include/bullet/vectormath/sse/floatInVec.h;/Library/Frameworks/include/bullet/vectormath/sse/mat_aos.h;/Library/Frameworks/include/bullet/vectormath/sse/quat_aos.h;/Library/Frameworks/include/bullet/vectormath/sse/vec_aos.h;/Library/Frameworks/include/bullet/vectormath/sse/vecidx_aos.h;/Library/Frameworks/include/bullet/vectormath/sse/vectormath_aos.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Library/Frameworks/include/bullet/vectormath/sse" TYPE FILE FILES
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/sse/boolInVec.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/sse/floatInVec.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/sse/mat_aos.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/sse/quat_aos.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/sse/vec_aos.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/sse/vecidx_aos.h"
    "/home/alessandro/Desktop/bullet-2.82-r2704/src/vectormath/sse/vectormath_aos.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/alessandro/Desktop/bullet-2.82-r2704/src/BulletSoftBody/cmake_install.cmake")
  include("/home/alessandro/Desktop/bullet-2.82-r2704/src/BulletCollision/cmake_install.cmake")
  include("/home/alessandro/Desktop/bullet-2.82-r2704/src/BulletDynamics/cmake_install.cmake")
  include("/home/alessandro/Desktop/bullet-2.82-r2704/src/LinearMath/cmake_install.cmake")

endif()

