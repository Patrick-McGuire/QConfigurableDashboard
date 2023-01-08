# Outstanding work
## Front end
* Right click menu editing
* Settings menu
* Re-do stylesheet stuff
* Figure out size policy/hints
## Back end
* Config Loading, and OS specific config stuff
* Connect menus to internal event structure (base menu & base action class?)
  * Kinda jank now?
* ~~Module system test~~
* Finish adding CoreObject functionality to Widget 
  * run/other method integration
* ~~App manager -> base QCD object, make members static~~
  * ~~Will have to not extend QObject to allow for multiple inheritance~~
## Docs
* Doxygen comments
* Examples
* Installing
* Look into more Doxygen features
* ~~Setup Doxygen~~
## Hard/separate
* Python and C++ libs for communicating over TCP
* Map vis
* 3D vis
* ~~Windows compatibility~~
* Mac compatibility
* ~~Figure out how to do multiple build configurations within same project~~
* Creating dynamic lib?
* Auto-assembling files to 1 header?
* Ringbuffer implementation 
## Maintenance
* Finish event based video recording architecture, add timer to recorder widget 
* Finish runUpdate rate scaling
* Add get/set methods to all widgets
* ~~Change updateThemeCallback signal to use internal event format~~
## Implementations
* Modules: (XML, ROS, FRC dash, Example)
* Port widgets: (Basic charts, annunciator, compas, nav ball, ros/dropdown)
* New widgets: (static plot)
* Interfaces: (ROS interface, TCP interface, Serial interface)
