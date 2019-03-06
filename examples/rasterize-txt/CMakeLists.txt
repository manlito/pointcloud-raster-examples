cmake_minimum_required(VERSION 3.5)
project(rasterize_txt VERSION 1.0.0 )

# Default build to Release
set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build to default type  '${default_build_type}'.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build.")
endif ()

# Our renderer
find_package(PointcloudRaster REQUIRED)

# Our sample
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main-rasterize-txt.cpp
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PointcloudRaster::PointcloudRaster
        stdc++fs
)
target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)
