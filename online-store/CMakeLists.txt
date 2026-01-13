cmake_minimum_required(VERSION 3.16)
project(online_store CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(online_store
        src/main.cpp
        src/Users.cpp
        src/Menu.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

set(PostgreSQL_INCLUDE_DIR "/opt/homebrew/opt/libpq/include")
set(PostgreSQL_LIBRARY "/opt/homebrew/opt/libpq/lib/libpq.dylib")

target_include_directories(online_store PRIVATE ${PostgreSQL_INCLUDE_DIR})
target_link_libraries(online_store PRIVATE PkgConfig::PQXX ${PostgreSQL_LIBRARY})
