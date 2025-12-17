IF(NOT EXISTS "/home/donigna/OpenGL/LearnOpenGL/LearnOpGL-13-Rendering Mesh/build/external/assimp/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/home/donigna/OpenGL/LearnOpenGL/LearnOpGL-13-Rendering Mesh/build/external/assimp/install_manifest.txt\"")
ENDIF(NOT EXISTS "/home/donigna/OpenGL/LearnOpenGL/LearnOpGL-13-Rendering Mesh/build/external/assimp/install_manifest.txt")

FILE(READ "/home/donigna/OpenGL/LearnOpenGL/LearnOpGL-13-Rendering Mesh/build/external/assimp/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  EXEC_PROGRAM(
    "/home/donigna/Downloads/Development/CLion-2025.2.3/clion-2025.2.3/bin/cmake/linux/x64/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
    OUTPUT_VARIABLE rm_out
    RETURN_VALUE rm_retval
    )
  IF(NOT "${rm_retval}" STREQUAL 0)
    MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
  ENDIF(NOT "${rm_retval}" STREQUAL 0)
ENDFOREACH(file)
