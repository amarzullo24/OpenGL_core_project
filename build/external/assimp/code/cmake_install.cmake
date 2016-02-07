# Install script for directory: /Users/aldo/Downloads/LearnOpenGL/external/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/aldo/Downloads/LearnOpenGL/build/external/assimp/code/libassimp.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/anim.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/ai_assert.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/camera.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/color4.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/color4.inl"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/config.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/defs.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/cfileio.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/light.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/material.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/material.inl"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/matrix3x3.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/matrix3x3.inl"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/matrix4x4.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/matrix4x4.inl"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/mesh.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/postprocess.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/quaternion.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/quaternion.inl"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/scene.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/metadata.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/texture.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/types.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/vector2.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/vector2.inl"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/vector3.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/vector3.inl"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/version.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/cimport.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/importerdesc.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/Importer.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/IOStream.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/IOSystem.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/Logger.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/LogStream.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/NullLogger.hpp"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/cexport.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/Exporter.hpp"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/Users/aldo/Downloads/LearnOpenGL/external/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

