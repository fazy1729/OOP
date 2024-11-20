cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name

project(oop)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)
# Set the OpenSSL root directory (replace with your actual path)
set(OPENSSL_ROOT_DIR "D:/vcpkg/installed/x64-windows")

# Specify the OpenSSL include and library directories
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIBRARIES "${OPENSSL_ROOT_DIR}/lib")
set(OPENSSL_ROOT_DIR "D:/vcpkg/installed/x64-windows")
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(OPENSSL_SSL_LIBRARY "D:/vcpkg/installed/x64-windows/lib/libssl.a")
set(OPENSSL_CRYPTO_LIBRARY "D:/vcpkg/installed/x64-windows/lib/libcrypto.a")
include_directories(D:/vcpkg/installed/x64-windows/include)



# Find OpenSSL using CMake's FindPackage
find_package(OpenSSL REQUIRED)

# Alternatively, if FindOpenSSL doesn't work, you can manually set the include and library
# directories like this:
# include_directories(${OPENSSL_INCLUDE_DIR})
# target_link_libraries(your_target_name ${OPENSSL_LIBRARIES})

# If OpenSSL is found successfully, the following should work:
if (OPENSSL_FOUND)
    message(STATUS "Found OpenSSL: ${OPENSSL_VERSION}")
else()
    message(FATAL_ERROR "OpenSSL not found!")
endif()

# Your other CMake configurations go here







set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(cmake/Options.cmake)

###############################################################################

# external dependencies with FetchContent
# include(FetchContent)
#
# set(FETCHCONTENT_QUIET OFF)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#
# NOTE: Also update env vars used for caching in
#         - .github/actions/configure-cmake/action.yml
#         - .github/workflows/cmake.yml
# FetchContent_Declare(
#         SomeLib
#         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
# )
#
# FetchContent_MakeAvailable(SomeLib)

###############################################################################

# external dependencies with find_package

# find_package(Threads REQUIRED)



# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME}
        main.cpp
        generated/src/Interface.cpp
        generated/src/Level.cpp
        generated/src/Terminal.cpp
        generated/src/Hacker.cpp
        generated/src/CryptoHacker.cpp
        generated/src/GameEngine.cpp
)

target_link_libraries(oop OpenSSL::SSL OpenSSL::Crypto)
include(cmake/CompilerFlags.cmake)

###############################################################################


# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE generated/include)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${PROJECT_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
# target_link_libraries(${PROJECT_NAME} <SomeLib>)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()
include(cmake/CopyHelper.cmake)
copy_files(FILES scripts/tastatura.txt)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)
