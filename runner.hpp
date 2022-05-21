#include<vector>
#include<iostream>
#include<stack>
#include<map>
#include<fstream>
#include<string>
#include"./cCompilerCommon.hpp"
using namespace std;
class ProgramRam{
public:
    struct Tuple{
        std::string op,s1,s2,d;
    };
public:
    ProgramRam(){}
    ProgramRam(std::string name):mProgramPieceName(name){}

    void push(std::string op,std::string s1,std::string s2,std::string d){
        ram.push_back({op,s1,s2,d});
    }
    void push(ProgramRam::Tuple comm){
        ram.push_back(comm);
    }
    void push(ProgramRam piece){
        for(auto c : piece.ram){
            this->ram.push_back(c);
        }
    }

    void makeLineLable(int lineNumber, std::string lable){
        lineLable.insert({lable,lineNumber});
    }
    void makeLineLable(std::string lable, int lineNumber){
        lineLable.insert({lable,lineNumber});
    }
    void labelNextLine(std::string label){
        lineLable.insert({label, ram.size()});
    }

    int getLineNumberByLabel(std::string label){
        if(lineLable.find(label)==lineLable.end()){
            return -1;
        }else{
            return lineLable[label];
        }
    }

    void print(){
        std::cout<<"ProgramName: "<<mProgramPieceName<<"\n";
        int i=0;
        for(auto c : ram){
            std::cout<<(i++)<<": "<<c.op<<' '<<c.s1<<' '<<c.s2<<' '<<c.d<<"\n";
            //std::cout<<(i++)<<": "<<c.op<<'|'<<c.s1<<'|'<<c.s2<<'|'<<c.d<<"\n";
        }
        std::cout<<"\nThe Labeled Lines Are:\n";
        for(auto c:lineLable){
            std::cout<<c.first<<" : "<<c.second<<"\n";
        }
    }
    void print(ofstream fout){
        fout<<"ProgramName: "<<mProgramPieceName<<"\n";
        int i=0;
        for(auto c : ram){
            fout<<(i++)<<": "<<c.op<<' '<<c.s1<<' '<<c.s2<<' '<<c.d<<"\n";
            //std::cout<<(i++)<<": "<<c.op<<'|'<<c.s1<<'|'<<c.s2<<'|'<<c.d<<"\n";
        }
        fout<<"\nThe Labeled Lines Are:\n";
        for(auto c:lineLable){
            fout<<c.first<<" : "<<c.second<<"\n";
        }
        fout.flush();
        fout.close();
    }

    void readCode(std::string fileName="./midcode.m"){
        //cout<<"reading\n";
        std::fstream fin(fileName);
        //istream &fin=cin;
        //cout<<"opend\n";
        std::string name;
        //cout<<"nameready\n";
        fin>>name;
        //cout<<"nameread\n";
        //cout<<name;
        while(!fin.eof()){
            std::string op,s1,s2,d;
            fin>>op;
            if(op[0]>='0'&&op[0]<='9'){/* is instruction */
                fin>>op;

                if(op.compare("ADD")==0||op.compare("SUB")==0||op.compare("MUL")==0||op.compare("DIV")==0||op.compare("REM")==0){
                    fin>>s1>>s2>>d;
                }else if(op.compare("SLT")==0||op.compare("BEQ")==0||op.compare("BNE")==0){
                    fin>>s1>>s2>>d;
                }else if(op.compare("CALL")==0){
                    fin>>s1>>s2>>d;
                }else if(op.compare("RET")==0||op.compare("NULL")==0){
                    
                }else if(op.compare("READ")==0||op.compare("WRITE")==0||op.compare("PUSH")==0||op.compare("POP")==0){
                    
                    getline(fin,s1);
                    int lb=0, rb=s1.length()-1;
                    while(lb<rb && s1[lb]==' ')lb++;
                    while(rb>lb && s1[rb]==' ')rb--;
                    s1=s1.substr(lb,rb-lb+1);
                }
                this->ram.push_back({op,s1,s2,d});
            }else break;
        }
        std::string trash;
        fin>>trash>>trash>>trash;
        while(!fin.eof()){
            std::string label;
            int number;
            fin>>label;
            fin>>trash;
            fin>>number;
            this->lineLable[label]=number;
        }
        //cout<<"read finish.\n";
    }
    
protected:
    std::string mProgramPieceName;
    std::vector<ProgramRam::Tuple> ram;
    std::map<std::string, int> lineLable;
};

class Runner : public ProgramRam{
public:
    Runner(ProgramRam p):ProgramRam(p){};
    int run();
protected:
    int pc;
    std::stack<int> stack;
    std::vector<int> data;
    std::map<std::string, int> tempPool;
    void push(int x){
        stack.push(x);
    }
    void pop(){
        stack.pop();
    }
    void pop(int &x){
        x=stack.top();
        stack.pop();
    }
    int top(){
        stack.top();
    }
    int getValue(std::string name){
        if(name[0]=='['){ /* cong [address] li qu zhi*/
            int addr;
            std::string trueName = name.substr(1,name.length()-2);
            if(trueName[0]=='`'){
                addr = tempPool[trueName];
            }else{
                sscanf(trueName.c_str(),"%d",&addr);
            }
            return data[addr];
        }else{ /* li ji shu */
            if(name[0]=='`'){ 
                return tempPool[name];
            }else{
                int in;
                sscanf(name.c_str(),"%d",&in);
                //std::cout<<"immediate "<<in<<"\n";
                return in;
            }
        }
    }
    void store(std::string name, int value){
        if(name[0]=='`'){
            tempPool[name] = value;
        }else if(name[0]=='[' && name.substr(1,name.length()-2).c_str()[0]=='`'){
            data[tempPool[name.substr(1,name.length()-2)]] = value;
        }else {
            int addr;
            sscanf(name.substr(1,name.length()-2).c_str(),"%d",&addr);
            data[addr] = value;
        }
    }
};