# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("roguelike")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        GameRendererBridge.cpp
        game/time/DeltaTime.cpp
        ResourcesBridge.cpp
        assets/AssetManager.cpp
        game/GameGLConfig.cpp
        game/GameRenderer.cpp
        game/objects/entities/camera/Camera.cpp
        game/objects/entities/player/Player.cpp
        game/objects/entities/player/renderer/PlayerRenderer.cpp
        game/objects/entities/player/renderer/aim/AimRenderer.cpp
        game/objects/entities/player/renderer/line/LineRenderer.cpp
        game/objects/entities/enemy/Enemy.cpp
        game/objects/entities/enemy/EnemyRenderer.cpp
        game/objects/entities/bullets/Bullets.cpp
        game/objects/entities/bullets/BulletsRender.cpp
        game/utils/OpenglUtils.cpp
        game/utils/ShaderUtil.cpp
        game/vbo/SSBOReader.cpp
        # List C/C++ source files with relative paths to this CMakeLists.txt.
)

find_library(gles-lib GLESv3)
# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        ${gles-lib}
        android
        glm
        log
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/game
        ${CMAKE_SOURCE_DIR}/game/objects
        ${CMAKE_SOURCE_DIR}/assets
)

include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        1.0.3
)

FetchContent_MakeAvailable(glm)