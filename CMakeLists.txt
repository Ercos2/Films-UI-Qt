cmake_minimum_required(VERSION 3.5)

project(Films_UI_Qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set (MY_MAINWINDOW_DIR ${CMAKE_SOURCE_DIR}/mainwindow)
set (MY_DIALOD_ADD_DIR ${CMAKE_SOURCE_DIR}/dialog_add)
set (MY_DIALOG_CHANGE_DIR ${CMAKE_SOURCE_DIR}/dialog_change)
set (MY_DIALOG_SELECT_DIR ${CMAKE_SOURCE_DIR}/dialog_select)
set (MY_FILMS_DIR ${CMAKE_SOURCE_DIR}/Films)

set(PROJECT_SOURCES
        main.cpp
        ${MY_MAINWINDOW_DIR}/mainwindow.cpp
        ${MY_MAINWINDOW_DIR}/mainwindow.h
        ${MY_MAINWINDOW_DIR}/mainwindow.ui
        ${MY_DIALOD_ADD_DIR}/dialog_add.cpp
        ${MY_DIALOD_ADD_DIR}/dialog_add.h
        ${MY_DIALOD_ADD_DIR}/dialog_add.ui
        ${MY_DIALOG_CHANGE_DIR}/dialog_change.cpp
        ${MY_DIALOG_CHANGE_DIR}/dialog_change.h
        ${MY_DIALOG_CHANGE_DIR}/dialog_change.ui
        ${MY_DIALOG_SELECT_DIR}/dialog_select.cpp
        ${MY_DIALOG_SELECT_DIR}/dialog_select.h
        ${MY_DIALOG_SELECT_DIR}/dialog_select.ui
        ${MY_FILMS_DIR}/Films.cpp
        ${MY_FILMS_DIR}/Films.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Films_UI_Qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Films_UI_Qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Films_UI_Qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Films_UI_Qt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(Films_UI_Qt PUBLIC ${MY_MAINWINDOW_DIR} ${MY_DIALOD_ADD_DIR} ${MY_DIALOG_CHANGE_DIR} ${MY_DIALOG_SELECT_DIR} ${MY_FILMS_DIR})
target_link_libraries(Films_UI_Qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Films_UI_Qt)
endif()
set_target_properties(Films_UI_Qt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Films_UI_Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Films_UI_Qt)
endif()
