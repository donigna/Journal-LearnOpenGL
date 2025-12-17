# Install script for directory: /home/donigna/Downloads/Development/assimp-6.0.2/code

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp6.0.2" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.6.0.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.6"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/donigna/Downloads/Development/assimp-6.0.2/build/bin/libassimp.so.6.0.2"
    "/home/donigna/Downloads/Development/assimp-6.0.2/build/bin/libassimp.so.6"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.6.0.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.6"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp6.0.2" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/donigna/Downloads/Development/assimp-6.0.2/build/bin/libassimp.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/anim.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/aabb.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/ai_assert.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/camera.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/color4.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/color4.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/build/code/../include/assimp/config.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/ColladaMetaData.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/commonMetaData.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/defs.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/cfileio.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/light.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/material.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/material.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/matrix3x3.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/matrix3x3.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/matrix4x4.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/matrix4x4.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/mesh.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/ObjMaterial.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/pbrmaterial.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/GltfMaterial.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/postprocess.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/quaternion.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/quaternion.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/scene.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/metadata.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/texture.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/types.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/vector2.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/vector2.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/vector3.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/vector3.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/version.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/cimport.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/AssertHandler.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/importerdesc.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Importer.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/DefaultLogger.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/ProgressHandler.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/IOStream.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/IOSystem.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Logger.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/LogStream.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/NullLogger.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/cexport.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Exporter.hpp"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/DefaultIOStream.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/DefaultIOSystem.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/ZipArchiveIOSystem.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/SceneCombiner.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/fast_atof.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/qnan.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/BaseImporter.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Hash.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/MemoryIOWrapper.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/ParsingUtils.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/StreamReader.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/StreamWriter.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/StringComparison.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/StringUtils.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/SGSpatialSort.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/GenericProperty.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/SpatialSort.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/SkeletonMeshBuilder.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/SmallVector.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/SmoothingGroups.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/SmoothingGroups.inl"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/StandardShapes.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/RemoveComments.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Subdivision.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Vertex.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/LineSplitter.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/TinyFormatter.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Profiler.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/LogAux.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Bitmap.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/XMLTools.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/IOStreamBuffer.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/CreateAnimMesh.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/XmlParser.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/BlobIOSystem.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/MathFunctions.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Exceptional.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/ByteSwapper.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Compiler/pushpack1.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Compiler/poppack1.h"
    "/home/donigna/Downloads/Development/assimp-6.0.2/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

