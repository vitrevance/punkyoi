include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()
# GLEW
FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        origin/master
)
FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_Populate(glew)

    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# std_image
FetchContent_Declare(
    stb_image_src
    GIT_REPOSITORY https://github.com/nothings/stb.git
)
FetchContent_GetProperties(stb_image_src)
if(NOT stb_image_src_POPULATED)
    FetchContent_Populate(stb_image_src)
endif()
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_image_src_SOURCE_DIR})
# taojson
FetchContent_Declare(
  taojson
  GIT_REPOSITORY https://github.com/taocpp/json.git
  GIT_TAG        main
)
FetchContent_GetProperties(taojson)
if(NOT taojson_POPULATED)
    FetchContent_Populate(taojson)

    set(TAOCPP_JSON_BUILD_TESTS OFF CACHE INTERNAL "")
    set(TAOCPP_JSON_BUILD_EXAMPLES OFF CACHE INTERNAL "")
    set(TAOCPP_JSON_INSTALL OFF CACHE INTERNAL "")

    add_subdirectory(${taojson_SOURCE_DIR} ${taojson_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# miniaudio
FetchContent_Declare(
    miniaudio_src
    GIT_REPOSITORY https://github.com/mackron/miniaudio.git
)
FetchContent_GetProperties(miniaudio_src)
if(NOT miniaudio_src_POPULATED)
    FetchContent_Populate(miniaudio_src)
endif()
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE ${miniaudio_src_SOURCE_DIR})
