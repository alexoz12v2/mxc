# from build directory
cmake .. -G "Ninja Multi-Config" -DCMAKE_INSTALL_PREFIX=~/.local -DCMAKE_BUILD_TYPE=Debug --preset conan-debug
cmake --build ./Debug --config Debug --clean-first --
ctest -VV -C Debug --test-dir Debug/src/math/test
cmake --install ./Debug --config Debug --strip
