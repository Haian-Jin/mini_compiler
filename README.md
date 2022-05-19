# mini_compiler

Final project for the course  “Compilers Principle” in Zhejiang University.

We build a complier named `zjucmm` ( short for ZJU C minus minus) from scratch. It follows the grammar of standard C language.

## 0.Environment

* Ubuntu 20.04
* llvm 10.0.0
* flex 2.6.4
* 3.5.1
* libjsoncpp-dev 1.7.4-3.1ubuntu2

## 1. Installation

```shell
sudo apt-get install flex bison
sudo apt-get install llvm-dev 
sudo apt-get install libjsoncpp-dev flex bison
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
  pytm-cli -i A_tree.json -o demo.html
  ```

  