#include "./runner.hpp"
using namespace std;

int Runner::run(){
    push(-1);
    data = vector<int>(10000000,0);
    pc = getLineNumberByLabel("main");
    if(pc==-1){
        cout<<"main not found.\n";
        exit(0);
    }

    while(pc!=-1){
        //std::cout<<"pc: "<<pc<<"\n";
        Tuple inst = ram[pc];
        int result;
        if(inst.op.compare("ADD")==0){
            result = getValue(inst.s1) + getValue(inst.s2);
        }else if(inst.op.compare("SUB")==0){
            result = getValue(inst.s1) - getValue(inst.s2);
        }else if(inst.op.compare("MUL")==0){
            result = getValue(inst.s1) * getValue(inst.s2);
        }else if(inst.op.compare("DIV")==0){
            result = getValue(inst.s1) / getValue(inst.s2);
        }else if(inst.op.compare("REM")==0){
            result = getValue(inst.s1) % getValue(inst.s2);
        }else if(inst.op.compare("SLT")==0){
            //std::cout<<getValue(inst.s1)<<" < "<<getValue(inst.s2);
            result = (getValue(inst.s1) < getValue(inst.s2));
        }else if(inst.op.compare("BNE")==0){
            if(getValue(inst.s1)!=getValue(inst.s2)){
                if(inst.d[0]>='0'&&inst.d[0]<='9'){
                    int offset;
                    sscanf(inst.d.c_str(),"%d",&offset);
                    pc = pc+1+offset;
                }else{
                    pc = getLineNumberByLabel(inst.d);
                }
            }else{
                pc++;
            }
            continue;
        }else if(inst.op.compare("BEQ")==0){
            if(getValue(inst.s1)==getValue(inst.s2)){
                if(inst.d[0]>='0'&&inst.d[0]<='9'){
                    int offset;
                    sscanf(inst.d.c_str(),"%d",&offset);
                    pc = pc+1+offset;
                }else{
                    pc = getLineNumberByLabel(inst.d);
                }
            }else{
                pc++;
            }
            continue;
        }else if(inst.op.compare("CALL")==0){
            push(pc+1);
            pc = getLineNumberByLabel(inst.s1);
            continue;
        }else if(inst.op.compare("RET")==0){
            pop(pc);

            continue;
        }else if(inst.op.compare("READ")==0){
            inst.d = inst.s1;
            //cout<<"input: ";
            cin>>result;
            //pc++;
            //continue;
        }else if(inst.op.compare("WRITE")==0){
            //cout<<"output: ";
            if(inst.s1[0]=='['||inst.s1[0]=='`'){
                cout<<getValue(inst.s1);
            }else{
                for(int i=1;i<inst.s1.length()-1;i++){
                    if(inst.s1[i]=='\\'){
                        if(inst.s1[i+1]=='n'){
                            i++;
                            cout<<endl;
                        }
                    }else{
                        cout<<inst.s1[i];
                    }
                }
            }
            pc++;
            continue;
        }else if(inst.op.compare("PUSH")==0){
            push(getValue(inst.s1));
            pc++;
            continue;
        }else if(inst.op.compare("POP")==0){
            pop(result);
            inst.d = inst.s1;
        }

        store(inst.d, result);
        pc++;
    }
}