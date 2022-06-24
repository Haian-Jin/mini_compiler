# mini_compiler

Final project for the course  “Compilers Principle” in Zhejiang University.

We build a complier named `zjucmm` ( short for ZJU C minus minus) from scratch based on `flex`, `yacc` and `LLVM`. It follows the grammar of standard C language and supports struct, multi-dimensional array, string and so on.

There is also another compiler implemented with "Three Address Code" by our teammate. The link is: https://github.com/zqd-SE7EN/-c---

## -1. Notice

For ZJU students who are suffering from this project, do not refer to this repository as you have many better choices. Because we didn't devote too much time on this, it has many aspects to improve and the implementations from other "Convolution Kings" may be better.

## 0.Environment

* Ubuntu 20.04
* llvm 10.0.0
* flex 2.6.4
* bison 3.5.1
* libjsoncpp-dev 1.7.4-3.1ubuntu2
* pkg-config

## 1. Installation

```shell
sudo apt-get install flex bison
sudo apt-get install llvm-dev 
sudo apt-get install libjsoncpp-dev
sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json
sudo apt-get install clang

```

## 2. How to Build the ZJUCMM Compiler

```shell
mkdir build
cd build
cmake ..
make
```

You can also run the script `./build.sh` to build the compiler.  

## 3. How to Use：

* write your C code in ${code_path}, assume 

* compile your code and generate json file for AST

  assume ${code_path} is ./test/ast/test1.c 

  ```
  ./build/zjucmm < ./test/ast/test1.c 
  ```

* visualization the AST in a HTML file

  ```shell
  pytm-cli -i ast_tree.json -o demo.html
  ```

* generate executable file

  ```shell
    OjectFile=output
    clang++ objtest.cpp output.o -o ${OjectFile}
  ```

  