cmake_minimum_required(VERSION 3.19)

project("QtShellIntegration"
    VERSION "0.0.0"
    DESCRIPTION "Integrate Wayland shells with Qt applications"
    LANGUAGES CXX C
)

## Only build on the appropriate platforms.
if(NOT (UNIX OR NOT CMAKE_SYSTEM_NAME MATCHES "Android"))
    message(NOTICE "Skipping the build as the condition \"UNIX OR NOT Android\" is not met.")
    return()
endif()

## ECM:
find_package(ECM 5.245.0 REQUIRED NO_MODULE)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

## Installation directories:
include(KDEInstallDirs)

## Compiler settings:
set(KDE_SKIP_NULLPTR_WARNINGS_SETTINGS TRUE)
include(KDECompilerSettings NO_POLICY_SCOPE)

## Enable keywords such as emit:
# TODO: Replace keywords such as emit with Q_EMIT
remove_definitions(-DQT_NO_KEYWORDS)

## CMake settings:
include(KDECMakeSettings)

## QML module:
include(ECMQmlModule)

## ECM:
include(ECMQtDeclareLoggingCategory)

## Disable use of C++ API deprecated in Qt 5.15
add_compile_definitions(QT_DISABLE_DEPRECATED_UP_TO=0x050F00)

## Shared macros and functions:
if(NOT LIRI_LOCAL_ECM)
    find_package(LiriCMakeShared "2.0.99" REQUIRED NO_MODULE)
    list(APPEND CMAKE_MODULE_PATH "${LCS_MODULE_PATH}")
endif()

## Liri specific setup common for all modules:
include(LiriSetup)

## Features:
include(features.cmake)

## QML import path:
if(NOT QML_IMPORT_PATH)
    set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/bin CACHE STRING "" FORCE)
endif()

## Add subdirectories:
add_subdirectory(src/interfaces)
add_subdirectory(src/interfaces/declarative)
add_subdirectory(src/shell-integrations/ext-session-lock)
add_subdirectory(src/shell-integrations/layer-shell)
