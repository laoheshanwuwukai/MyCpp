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

    A a = createA();
    cout<<"end of program."<<endl;

    return 0;
}