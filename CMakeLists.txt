# CMakeList.txt : 최상위 CMake 프로젝트 파일, 전역 구성을 수행하고
# 여기에 하위 프로젝트를 포함합니다.
#
cmake_minimum_required (VERSION 3.8)

project ("redisTest")

# Find Boost
find_package(Boost REQUIRED COMPONENTS system thread)
if(Boost_FOUND)
  message(STATUS "Boost found!")
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# Find hiredis
find_path(HIREDIS_INCLUDE_DIR hiredis/hiredis.h HINTS /usr/local/include)
find_library(HIREDIS_LIBRARY NAMES hiredis HINTS /usr/local/lib)
if(HIREDIS_INCLUDE_DIR AND HIREDIS_LIBRARY)
  message(STATUS "hiredis found!")
  include_directories(${HIREDIS_INCLUDE_DIR})
endif()

# Find nlohmann_json
find_package(nlohmann_json 3.2.0 REQUIRED)
if(nlohmann_json_FOUND)
  message(STATUS "nlohmann_json found!")
endif()

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

find_path(REDIS_PLUS_PLUS_HEADER sw)

find_library(REDIS_PLUS_PLUS_LIB redis++)

# 하위 프로젝트를 포함합니다.
add_subdirectory ("redisTest")
