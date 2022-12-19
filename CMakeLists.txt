cmake_minimum_required(VERSION 3.22)
project(QConfigurableDashboard)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Run bash script to finish setup tasks
execute_process(
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND scripts/compile_helper.bash ${CMAKE_SOURCE_DIR}
)

add_executable(QConfigurableDashboard main.cpp src/QConfigurableDashboard.cpp src/QConfigurableDashboard.h src/Widgets/BaseWidget.cpp src/Widgets/BaseWidget.h src/QCD.h src/Util/FlagVariable.h src/GuiManager.cpp src/GuiManager.h src/Widgets/WidgetContainers/PanelContainer.cpp src/Widgets/WidgetContainers/PanelContainer.h src/Widgets/CustomWidgets/ButtonWidget.cpp src/Widgets/CustomWidgets/ButtonWidget.h src/Widgets/CustomWidgets/LineDisplayWidget.cpp src/Widgets/CustomWidgets/LineDisplayWidget.h src/Widgets/WidgetContainers/BaseContainer.cpp src/Widgets/WidgetContainers/BaseContainer.h src/Interfaces/BaseInterface.cpp src/Interfaces/BaseInterface.h src/Interfaces/BaseTimerInterface.cpp src/Interfaces/BaseTimerInterface.h src/Interfaces/Examples/RandomDataInterface.cpp src/Interfaces/Examples/RandomDataInterface.h src/Util/UtilFuntions.h src/Config/AppConfig.cpp src/Config/AppConfig.h)
set(SOURCE_FILES main.cpp)
include_directories(/usr/include/)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(OpenCV REQUIRED)

target_link_libraries(QConfigurableDashboard Qt5::Core Qt5::Widgets Qt5::Network Qt5::Charts)
target_link_libraries(QConfigurableDashboard stdc++fs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


message(STATUS ${OpenCV_INCLUDE_DIRS})
message(STATUS ${OpenCV_LIBS})


include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

