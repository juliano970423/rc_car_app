cmake_minimum_required(VERSION 3.16)

project(rc_car VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick Qml Bluetooth)

qt_standard_project_setup()

qt_add_executable(apprc_car
    main.cpp
)

qt_add_qml_module(apprc_car
    URI rc_car
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES
    SOURCES
    SOURCES
    SOURCES remotecar.h remotecar.cpp
    SOURCES
    SOURCES
    SOURCES bledevicescanner.h bledevicescanner.cpp
    SOURCES
    SOURCES
    SOURCES bleconnector.h bleconnector.cpp


)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apprc_car PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apprc_car
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

target_link_libraries(apprc_car
    PRIVATE Qt6::Quick Qt6::Qml Qt6::Bluetooth
)

include(GNUInstallDirs)
install(TARGETS apprc_car
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
