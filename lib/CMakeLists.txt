include(FetchContent)

set(FETCHCONTENT_QUIET off)
set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/fetch CACHE PATH "Dependency location" FORCE)

message("Fetching dependencies to: ${FETCHCONTENT_BASE_DIR}")

FetchContent_Declare(
        glad_fetch
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        glad2
        GIT_SHALLOW    TRUE
        SOURCE_SUBDIR  cmake
)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE

        SOURCE_DIR    ${PROJECT_SOURCE_DIR}/lib/glfw
)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/icaven/glm.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE

        SOURCE_DIR    ${PROJECT_SOURCE_DIR}/lib/glm
)
FetchContent_Declare(
        boo
        GIT_REPOSITORY https://github.com/imtofuu/boo.git
        GIT_TAG        main
        GIT_SHALLOW    TRUE
        
        SOURCE_DIR    ${PROJECT_SOURCE_DIR}/lib/boo
)

FetchContent_MakeAvailable(glad_fetch glfw glm boo)

glad_add_library(glad STATIC API gl:core=4.1 LOCATION ${PROJECT_SOURCE_DIR}/lib/glad)