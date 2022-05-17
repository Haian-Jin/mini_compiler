if [ ! -d "./build" ]; then
    mkdir build
fi

cd build
cmake ..
make && echo "Build Successful, file in ./build/zjucmm"
cd ..