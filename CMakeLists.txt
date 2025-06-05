cmake_minimum_required(VERSION 3.20)
project(PROJECT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64")

enable_testing()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Test
        REQUIRED
)

add_library(volunteer_core
        Controller/Controller.cpp
        core/AddEventCommand.cpp
        core/AddVolunteerCommand.cpp
        Repository/CSV/CSVEventRepository.cpp
        Repository/CSV/CSVVolunteerRepository.cpp
        Repository/JSON/JSONEventRepository.cpp
        Repository/JSON/JSONVolunteerRepository.cpp
        core/RemoveEventCommand.cpp
        core/RemoveVolunteerCommand.cpp
        core/UpdateEventCommand.cpp
        core/UpdateVolunteerCommand.cpp
        Model/Volunteer.cpp
        Model/Event.cpp
)

target_link_libraries(volunteer_core
        Qt::Core
)

add_executable(PROJECT
        ui/main.cpp
        ui/mainwindow.cpp
)

target_link_libraries(PROJECT
        volunteer_core
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

add_executable(volunteer_tests
        tests/tests.cpp
)

target_link_libraries(volunteer_tests
        volunteer_core
        Qt::Core
        Qt::Test
)

add_test(NAME VolunteerManagementTests COMMAND volunteer_tests)

set_tests_properties(VolunteerManagementTests PROPERTIES
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}/../..")
        endif()
    endif()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll")
        add_custom_command(TARGET PROJECT POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:PROJECT>/plugins/platforms")
        add_custom_command(TARGET PROJECT POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
                "$<TARGET_FILE_DIR:PROJECT>/plugins/platforms/")
    endif()

    foreach(QT_LIB Core Gui Widgets Test)
        if (EXISTS "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll")
            add_custom_command(TARGET PROJECT POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll"
                    "$<TARGET_FILE_DIR:PROJECT>")
            add_custom_command(TARGET volunteer_tests POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll"
                    "$<TARGET_FILE_DIR:volunteer_tests>")
        endif()
    endforeach()
endif()