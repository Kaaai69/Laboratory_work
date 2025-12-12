cmake_minimum_required(VERSION 3.10)
project(Laba4SalesSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Подключаем pkg-config
find_package(PkgConfig REQUIRED)

# 2. Ищем libpqxx через pkg-config
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# 3. Настраиваем пути для компиляции
include_directories(${LIBPQXX_INCLUDE_DIRS})
link_directories(${LIBPQXX_LIBRARY_DIRS})

# 4. Добавляем все исходные файлы
add_executable(laba4
        src/main.cpp
        src/DatabaseManager.cpp
        src/Product.cpp
        src/Order.cpp
        src/Analytics.cpp
        src/Menu.cpp
)

# 5. Подключаем заголовочные файлы
target_include_directories(laba4 PRIVATE include)

# 6. Линкуем библиотеки (ВАЖНО: именно так, а не через PkgConfig::)
target_link_libraries(laba4 ${LIBPQXX_LIBRARIES})
# Если предыдущая строка не работает, попробуйте:
# target_link_libraries(laba4 pqxx pq)