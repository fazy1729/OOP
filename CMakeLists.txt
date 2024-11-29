cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name

project(oop)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configurează toolchain-ul pentru vcpkg (util dacă rulezi pe Windows/CI)
if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

find_package(OpenSSL REQUIRED)

if (NOT OPENSSL_FOUND AND WIN32 AND MINGW)
    set(OPENSSL_ROOT_DIR "D:/vcpkg/installed/x64-windows")  # Asigură-te că e corectă calea ta!
    set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
    set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libcrypto.a")
    set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libssl.a")

    # Verifică dacă fișierele există
    if (EXISTS "${OPENSSL_INCLUDE_DIR}" AND EXISTS "${OPENSSL_SSL_LIBRARY}" AND EXISTS "${OPENSSL_CRYPTO_LIBRARY}")
        message(STATUS "OpenSSL paths set manually for MinGW:")
        message(STATUS "OPENSSL_INCLUDE_DIR=${OPENSSL_INCLUDE_DIR}")
        message(STATUS "OPENSSL_SSL_LIBRARY=${OPENSSL_SSL_LIBRARY}")
        message(STATUS "OPENSSL_CRYPTO_LIBRARY=${OPENSSL_CRYPTO_LIBRARY}")
        set(OPENSSL_FOUND TRUE)
    else()
        message(FATAL_ERROR "OpenSSL libraries or include directories are missing!")
    endif()
endif()

# Debug: Afișare informații despre OpenSSL
if (OPENSSL_FOUND)
    message(STATUS "OpenSSL found!")
    message(STATUS "OpenSSL Version: ${OPENSSL_VERSION}")
    message(STATUS "OpenSSL Include Dir: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenSSL not found!")
endif()

# Setăm manual locațiile pentru OpenSSL dacă nu au fost setate automat
set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
set(OPENSSL_INCLUDE_DIR $ENV{OPENSSL_INCLUDE_DIR})
set(OPENSSL_LIBRARIES $ENV{OPENSSL_LIBRARIES})
set(OPENSSL_CRYPTO_LIBRARY $ENV{OPENSSL_CRYPTO_LIBRARY})
set(OPENSSL_SSL_LIBRARY $ENV{OPENSSL_SSL_LIBRARY})

include(cmake/Options.cmake)





add_executable(${PROJECT_NAME}
        main.cpp
        generated/src/Interface.cpp
        generated/src/Level.cpp
        generated/src/Terminal.cpp
        generated/src/Hacker.cpp
        generated/src/CryptoHacker.cpp
        generated/src/GameEngine.cpp
        generated/include/ForensicsHacker.h
        generated/src/ForensicsHacker.cpp
)

target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
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
copy_files(FILES tastatura.txt)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)

