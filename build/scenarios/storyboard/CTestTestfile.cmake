# CMake generated Testfile for 
# Source directory: /home/veins/src/artery/scenarios/storyboard
# Build directory: /home/veins/src/artery/build/scenarios/storyboard
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(storyboard-inet "/home/veins/src/omnetpp/bin/opp_run_release" "-n" "/home/veins/src/artery/src/artery:/home/veins/src/artery/src/traci:/home/veins/src/artery/extern/veins/examples/veins:/home/veins/src/artery/extern/veins/src/veins:/home/veins/src/artery/extern/inet/src:/home/veins/src/artery/extern/inet/examples:/home/veins/src/artery/extern/inet/tutorials:/home/veins/src/artery/extern/inet/showcases" "-l" "/home/veins/src/artery/build/src/artery/envmod/libartery_envmod.so" "-l" "/home/veins/src/artery/build/scenarios/highway-police/libartery_police.so" "-l" "/home/veins/src/artery/build/src/artery/envmod/libartery_envmod.so" "-l" "/home/veins/src/artery/build/src/artery/storyboard/libartery_storyboard.so" "-l" "/home/veins/src/artery/extern/inet/out/clang-release/src/libINET.so" "-l" "/home/veins/src/artery/extern/veins/out/clang-release/src/libveins.so" "-l" "/home/veins/src/artery/build/src/artery/libartery_core.so" "omnetpp.ini" "-uCmdenv" "--sim-time-limit=60s")
set_tests_properties(storyboard-inet PROPERTIES  WORKING_DIRECTORY "/home/veins/src/artery/scenarios/storyboard")
add_test(storyboard-veins "/home/veins/src/omnetpp/bin/opp_run_release" "-n" "/home/veins/src/artery/src/artery:/home/veins/src/artery/src/traci:/home/veins/src/artery/extern/veins/examples/veins:/home/veins/src/artery/extern/veins/src/veins:/home/veins/src/artery/extern/inet/src:/home/veins/src/artery/extern/inet/examples:/home/veins/src/artery/extern/inet/tutorials:/home/veins/src/artery/extern/inet/showcases" "-l" "/home/veins/src/artery/build/src/artery/envmod/libartery_envmod.so" "-l" "/home/veins/src/artery/build/scenarios/highway-police/libartery_police.so" "-l" "/home/veins/src/artery/build/src/artery/envmod/libartery_envmod.so" "-l" "/home/veins/src/artery/build/src/artery/storyboard/libartery_storyboard.so" "-l" "/home/veins/src/artery/extern/inet/out/clang-release/src/libINET.so" "-l" "/home/veins/src/artery/extern/veins/out/clang-release/src/libveins.so" "-l" "/home/veins/src/artery/build/src/artery/libartery_core.so" "omnetpp.ini" "-uCmdenv" "-cveins" "--sim-time-limit=60s")
set_tests_properties(storyboard-veins PROPERTIES  WORKING_DIRECTORY "/home/veins/src/artery/scenarios/storyboard")
