cmake_minimum_required(VERSION 3.15)
project(gcl VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ruta de instalación local (dentro del proyecto)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "Install path prefix" FORCE)

add_library(gcl)

include_directories(include)
include_directories(include/internal)

# Detectar plataforma
if(WIN32)
    set(GCL_PLATFORM windows)
    add_definitions(-D__GCL_WINDOWS__)
elseif(UNIX)
    set(GCL_PLATFORM linux)
    add_definitions(-D__GCL_LINUX__)
else()
    message(FATAL_ERROR "Plataforma no soportada")
endif()

# Detectar compilador
if(MSVC)
    target_compile_definitions(gcl PUBLIC __GCL_MSVC__)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(gcl PUBLIC __GCL_GCC__)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_definitions(gcl PUBLIC __GCL_CLANG__)
endif()

# Detectar arquitectura
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-D__GCL_X86_64__)
else()
    add_definitions(-D__GCL_X86__)
endif()

# Subdirectorios
add_subdirectory(src)
add_subdirectory(test)

# Instalación (opcional)
install(TARGETS gcl DESTINATION lib)
install(DIRECTORY include/gcl DESTINATION lib)