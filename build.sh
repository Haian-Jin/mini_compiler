if [ ! -d "./build" ]; then
    mkdir build
fi

cd build
rm -rf ./*
cmake ..
make && echo "Build Successful, file in ./build/zjucmm"
cd ..