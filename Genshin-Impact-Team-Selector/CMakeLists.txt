# CMake Configuration

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(GenshinImpactTeamSelector)

# Inclusion des Headers

include_directories(${PROJECT_SOURCE_DIR}/INCLUDE)

# Ajout des liens vers les autres répertoires
add_subdirectory(${PROJECT_SOURCE_DIR}/TOOLS_LIBRARY)
add_subdirectory(${PROJECT_SOURCE_DIR}/CODE_LIBRARY)
add_subdirectory(${PROJECT_SOURCE_DIR}/EXECUTABLE)
