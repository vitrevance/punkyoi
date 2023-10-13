cmake_minimum_required(VERSION 3.14...3.27)

project(
    Punkyoi
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

find_package(OpenGL REQUIRED)

function(bundle target assets)
    file(GLOB_RECURSE BUNDLE_ASSETS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/${assets}/*"
    )
    set(commands "")
    foreach(resource  ${BUNDLE_ASSETS})
        file(RELATIVE_PATH rel_path ${CMAKE_CURRENT_SOURCE_DIR}/${assets} ${resource})
        set(commands ${commands} COMMAND ${CMAKE_COMMAND} -E copy_if_different ${resource} $<TARGET_FILE_DIR:${target}>/${assets}/${rel_path})
    endforeach()
    add_custom_target(
        ${target}Bundle
        DEPENDS ${target}
        ${commands}
        COMMENT "Copy resources to the target directory"
    )
endfunction()

add_subdirectory(lib)

# Punkyoi

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
"src/**.cpp"
)

add_executable(punkyoi ${SRC_FILES})

target_compile_features(punkyoi PUBLIC cxx_std_20)
target_compile_definitions(punkyoi PRIVATE GLEW_STATIC)

set_target_properties(punkyoi PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(punkyoi PUBLIC src)

target_link_libraries(punkyoi PRIVATE glfw libglew_static stb_image miniaudio pegtl taocpp-json)

bundle(punkyoi assets)
