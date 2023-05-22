# CMakeList.txt: redisTest에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (redisTest "main.cpp" "redisTest.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET redisTest PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(redisTest ${Boost_LIBRARIES} ${HIREDIS_LIBRARY} nlohmann_json::nlohmann_json cpp_redis ${REDIS_PLUS_PLUS_LIB})
target_include_directories(redisTest PRIVATE ${Boost_INCLUDE_DIRS} ${HIREDIS_INCLUDE_DIR} ${REDIS_PLUS_PLUS_HEADER})

# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
