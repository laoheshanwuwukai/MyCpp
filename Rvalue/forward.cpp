/**
 * @author Tjl (1172962943@qq.com)
 * @brief 完美转发
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>

using std::cout;
using std::endl;

void func(int & n){
    cout<<"Lvalue = "<<n <<endl;
}
void func(int && n){
    cout<<"Rvalue = "<<n <<endl;
}
/*************************
template<typename T>
void revoke(T t){ // 全都是左值
    func(t);
}
template<typename T>
void revoke(T& t){ //只能处理左值
    func(t);
}
template<typename T> //const左值引用可以引用右值，但是不能改变
void revoke(const T& t){
    func(t);
}
*************************/


//完美转发：函数可以将自己的参数完美的转发给内部调用的其他函数
//        不仅仅是参数的值，还能保证被转发参数的左右值属性不变；

//实现完美转发需要使用万能引用(只有模板类型推到和auto)和std::forward<T>()

//
template<typename T>
void revoke(T && t){
    func(std::forward<T>(t));

}

int main(int argc , char ** argv){

    int i = 10;
    int & m = i;
    int && n = 100;
    revoke(m); //l
    revoke(n); //l
    revoke(static_cast<int&>(m)) ;//l
    revoke(static_cast<int&&>(n));//r

    return 0;
}