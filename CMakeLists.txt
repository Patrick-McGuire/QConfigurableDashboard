##########################
# QConfigurableDashboard #
##########################

# Configure project
cmake_minimum_required(VERSION 3.22)
project(QConfigurableDashboard)
set(CMAKE_CXX_STANDARD 11)
# We need this for some reason
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Define all the files needed to build
set(libFiles
        lib/QCustomPlot/qcustomplot.cpp
        )
set(utilFiles
        src/Util/VideoRecorder.cpp src/Util/VideoRecorder.h
        src/Util/UtilFunctions.h
        )
set(widgetFiles
        src/Widgets/BaseWidget.cpp src/Widgets/BaseWidget.h
        src/Widgets/CustomWidgets/ButtonWidget.cpp src/Widgets/CustomWidgets/ButtonWidget.h
        src/Widgets/CustomWidgets/LineDisplayWidget.cpp src/Widgets/CustomWidgets/LineDisplayWidget.h
        src/Widgets/CustomWidgets/TextListWidget.cpp src/Widgets/CustomWidgets/TextListWidget.h
        src/Widgets/CustomWidgets/VideoDisplayWidget.cpp src/Widgets/CustomWidgets/VideoDisplayWidget.h
        src/Widgets/CustomWidgets/GraphWidget.cpp src/Widgets/CustomWidgets/GraphWidget.h
        src/Widgets/CustomWidgets/VideoRecorderWidget.cpp src/Widgets/CustomWidgets/VideoRecorderWidget.h
        )
set(widgetContainerFiles
        src/Widgets/WidgetContainers/BaseContainer.cpp src/Widgets/WidgetContainers/BaseContainer.h
        src/Widgets/WidgetContainers/PanelContainer.cpp src/Widgets/WidgetContainers/PanelContainer.h
        src/Widgets/WidgetContainers/GridContainer.cpp src/Widgets/WidgetContainers/GridContainer.h
        src/Widgets/WidgetContainers/VBoxContainer.cpp src/Widgets/WidgetContainers/VBoxContainer.h
        src/Widgets/WidgetContainers/HBoxContainer.cpp src/Widgets/WidgetContainers/HBoxContainer.h
        src/Widgets/WidgetContainers/TabContainer.cpp src/Widgets/WidgetContainers/TabContainer.h
        )
set(interfaceFiles
        src/Interfaces/BaseInterface.cpp src/Interfaces/BaseInterface.h
        src/Interfaces/BaseThreadedInterface.cpp src/Interfaces/BaseThreadedInterface.h
        src/Interfaces/BaseTimerInterface.cpp src/Interfaces/BaseTimerInterface.h
        src/Interfaces/Examples/RandomDataInterface.cpp src/Interfaces/Examples/RandomDataInterface.h
        src/Interfaces/Examples/WebCamStreamInterface.cpp src/Interfaces/Examples/WebCamStreamInterface.h
        src/Interfaces/Examples/ThreadedRandomDataInterface.cpp src/Interfaces/Examples/ThreadedRandomDataInterface.h
        src/Interfaces/Examples/ThreadedWebCamInterface.cpp src/Interfaces/Examples/ThreadedWebCamInterface.h
        )
set(coreFiles
        src/QConfigurableDashboard.cpp src/QConfigurableDashboard.h
        src/Core/AppManager.cpp src/Core/AppManager.h
        src/Core/CallbackDispatcher.cpp src/Core/CallbackDispatcher.h
        src/Core/ConfigLoader.cpp src/Core/ConfigLoader.h
        src/Modules/BaseModule.cpp src/Modules/BaseModule.h
        )
set(allFiles
        ${libFiles}
        ${utilFiles}
        ${widgetFiles}
        ${widgetContainerFiles}
        ${interfaceFiles}
        ${coreFiles}
        )

# Set up everything to find libs/include
include_directories(/usr/include/)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Gui)
set(allLibs Qt5::Core Qt5::Widgets Qt5::Network Qt5::Charts Qt5::Multimedia Qt5::PrintSupport Qt5::Gui stdc++fs ${OpenCV_LIBS})

# Configure all source files as a library
set(allExecutables QcdExample.cpp Playground.cpp XmlTcp.cpp)
foreach(exe ${allExecutables})
    add_executable(${exe} ${exe} ${allFiles})
    target_link_libraries(${exe} ${allLibs})
endforeach(exe ${allExecutables})


