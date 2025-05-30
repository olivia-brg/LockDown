﻿cmake_minimum_required(VERSION 3.15)
project(LockDown LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Intégration vcpkg (optionnelle, mais recommandée)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# ====== SOURCES ======
file(GLOB_RECURSE SOURCES "src/cpp/*.cpp")
file(GLOB_RECURSE HEADERS "src/headers/*.h")
file(GLOB_RECURSE TESTS "src/tests/*.cpp")

add_executable(LockDown ${SOURCES} ${HEADERS} ${TESTS})

# ====== INCLUDES ======
target_include_directories(LockDown
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ====== Crypto++ ======
find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(LockDown PRIVATE cryptopp::cryptopp)
target_include_directories(LockDown PRIVATE ${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/include)

# ====== GROUPS POUR VISUAL STUDIO ======
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})
source_group("Tests Files" FILES ${TESTS})
