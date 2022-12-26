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
        src/Util/VideoRecorder.cpp include/VideoRecorder.h
        include/UtilFunctions.h
        )
set(widgetFiles
        src/Widgets/Widget.cpp include/Widget.h
        src/Widgets/CustomWidgets/ButtonWidget.cpp include/ButtonWidget.h
        src/Widgets/CustomWidgets/LineDisplayWidget.cpp include/LineDisplayWidget.h
        src/Widgets/CustomWidgets/TextListWidget.cpp include/TextListWidget.h
        src/Widgets/CustomWidgets/VideoDisplayWidget.cpp include/VideoDisplayWidget.h
        src/Widgets/CustomWidgets/GraphWidget.cpp include/GraphWidget.h
        src/Widgets/CustomWidgets/VideoRecorderWidget.cpp include/VideoRecorderWidget.h
        )
set(widgetContainerFiles
        src/Widgets/WidgetContainers/Container.cpp include/Container.h
        src/Widgets/WidgetContainers/PanelContainer.cpp include/PanelContainer.h
        src/Widgets/WidgetContainers/GridContainer.cpp include/GridContainer.h
        src/Widgets/WidgetContainers/VBoxContainer.cpp include/VBoxContainer.h
        src/Widgets/WidgetContainers/HBoxContainer.cpp include/HBoxContainer.h
        src/Widgets/WidgetContainers/TabContainer.cpp include/TabContainer.h
        )
set(interfaceFiles
        src/Modules/Module.cpp include/Module.h
        src/Modules/ThreadedModule.cpp include/ThreadedModule.h
        src/Modules/TimerModule.cpp include/TimerModule.h
        src/Modules/DataExamples/RandomDataModule.cpp include/RandomDataModule.h
        src/Modules/DataExamples/WebCamModule.cpp include/WebCamModule.h
        src/Modules/DataExamples/TRandomDataModule.cpp include/TRandomDataModule.h
        src/Modules/DataExamples/TWebCamModule.cpp include/TWebCamModule.h
        )
set(coreFiles
        src/Core/QConfigurableDashboard.cpp include/QConfigurableDashboard.h
        src/Core/AppManager.cpp include/AppManager.h
        src/Core/CallbackDispatcher.cpp include/CallbackDispatcher.h
        src/Core/ConfigLoader.cpp include/ConfigLoader.h
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

## Configure all source files as a library
set(allExecutablesNames QcdExample Playground XmlTcp)
set(allExecutables examples/QcdExample.cpp examples/Playground.cpp examples/XmlTcp.cpp)
foreach(exe exeName IN ZIP_LISTS allExecutables allExecutablesNames)
    add_executable(${exeName} ${exe} ${allFiles})
    target_link_libraries(${exeName} ${allLibs})
    target_include_directories(${exeName} PRIVATE include)
endforeach(exe ${allExecutables})


