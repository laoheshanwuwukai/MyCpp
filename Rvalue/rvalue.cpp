/**
 * @file rvalue.cpp
 * @author Tjl (1172962943@qq.com)
 * @brief Something about R-Value
 * @version 0.1
 * @date 2022-12-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

using std::cout;
using std::endl;

class A{
public:
    A(){
        cout<<"A constructor\t"<<this<<endl;
    }
    ~A(){
        cout<<"A destructor\t"<<this<<endl;
    }
    A(const A& a){
        cout<<"A copy constructor\t"<<this<<endl;
    }
    A& operator =(const A &){
        cout<<"A copy assignment constructor\t"<<this<<endl;
    }
    A(A&& ){
        cout<<"A move constructor\t"<<this<<endl;
    }
    A& operator=(A&&){
        cout<<"A move assignment constructor\t"<<this<<endl;
    }
};

A createA(){
    A a;
    return a;
}

int main(int argc , char ** argv){

    /*
A constructor   0x7ffcf3956f07
A copy constructor      0x7ffcf3956f47
A destructor    0x7ffcf3956f07
A copy constructor      0x7ffcf3956f46
A destructor    0x7ffcf3956f47
end of program.
A destructor    0x7ffcf3956f46
    */
    A a = createA();
    cout<<"end of program."<<endl;


/*both rvalue/lvalue_reference is lvalue;*/
    int && rvalue_reference = 100;
    int &  lvalue_reference = rvalue_reference;
    return 0;
}