# Generated by opp_cmake
add_library(veins SHARED IMPORTED GLOBAL)
set_target_properties(veins PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/veins/src/artery/extern/veins/out/clang-release/src/${CMAKE_SHARED_LIBRARY_PREFIX}veins${CMAKE_SHARED_LIBRARY_SUFFIX}"
  IMPORTED_NO_SONAME TRUE
  INTERFACE_INCLUDE_DIRECTORIES "/home/veins/src/artery/extern/veins/src"
  NED_FOLDERS "/home/veins/src/artery/extern/veins/examples/veins;/home/veins/src/artery/extern/veins/src/veins"
  OMNETPP_LIBRARY TRUE
)
set_property(TARGET veins PROPERTY IMPORTED_CONFIGURATIONS RELEASE)