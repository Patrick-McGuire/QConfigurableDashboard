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

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(CreateDoxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs/
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

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

# Define all the files needed to build
set(libFiles
        lib/QCustomPlot/qcustomplot.cpp
        )
set(utilFiles
        src/util/VideoRecorder.cpp include/VideoRecorder.h
        include/UtilFunctions.h
        )
set(widgetFiles
        src/widgets/Widget.cpp include/Widget.h
        src/widgets/CustomWidgets/ButtonWidget.cpp include/ButtonWidget.h
        src/widgets/CustomWidgets/LineDisplayWidget.cpp include/LineDisplayWidget.h
        src/widgets/CustomWidgets/TextListWidget.cpp include/TextListWidget.h
        src/widgets/CustomWidgets/VideoDisplayWidget.cpp include/VideoDisplayWidget.h
        src/widgets/CustomWidgets/GraphWidget.cpp include/GraphWidget.h
        src/widgets/CustomWidgets/VideoRecorderWidget.cpp include/VideoRecorderWidget.h
        )
set(widgetContainerFiles
        src/widgets/WidgetContainers/Container.cpp include/Container.h
        src/widgets/WidgetContainers/PanelContainer.cpp include/PanelContainer.h
        src/widgets/WidgetContainers/GridContainer.cpp include/GridContainer.h
        src/widgets/WidgetContainers/VBoxContainer.cpp include/VBoxContainer.h
        src/widgets/WidgetContainers/HBoxContainer.cpp include/HBoxContainer.h
        src/widgets/WidgetContainers/TabContainer.cpp include/TabContainer.h
        )
set(moduleFiles
        src/modules/Module.cpp include/Module.h
        src/modules/ThreadedModule.cpp include/ThreadedModule.h
        src/modules/TimerModule.cpp include/TimerModule.h
        src/modules/DataExamples/RandomDataModule.cpp include/RandomDataModule.h
        src/modules/DataExamples/WebCamModule.cpp include/WebCamModule.h
        src/modules/DataExamples/TRandomDataModule.cpp include/TRandomDataModule.h
        src/modules/DataExamples/TWebCamModule.cpp include/TWebCamModule.h
        )
set(coreFiles
        src/core/QConfigurableDashboard.cpp include/QConfigurableDashboard.h
        src/core/CallbackDispatcher.cpp include/CallbackDispatcher.h
        src/core/ConfigLoader.cpp include/ConfigLoader.h
        src/core/CoreObject.cpp include/CoreObject.h
        include/CallbackDispatcherInterface.h
        )
set(allFiles
        ${libFiles}
        ${utilFiles}
        ${widgetFiles}
        ${widgetContainerFiles}
        ${moduleFiles}
        ${coreFiles}
        )

## Configure all source files as a library
set(allExecutablesNames QcdExample Playground XmlTcp)
set(allExecutables examples/QcdExample.cpp examples/Playground.cpp examples/XmlTcp.cpp)
foreach (exe exeName IN ZIP_LISTS allExecutables allExecutablesNames)
    add_executable(${exeName} ${exe} ${allFiles})
    target_link_libraries(${exeName} ${allLibs})
    target_include_directories(${exeName} PRIVATE include)
endforeach (exe ${allExecutables})
