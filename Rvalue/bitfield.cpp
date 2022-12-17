/**
 * @brief Bit-field
 * g++ bitfield.cpp && ./a.out
 */

#include <iostream>

using std::cout;
using std::endl;

// bit_fields1.cpp
// compile with: /LD
//sizeof Date1 is 4;
struct Date1 {
   unsigned short nWeekDay  : 3;    // 0..7   (3 bits)
   unsigned short nMonthDay : 6;    // 0..31  (6 bits)
   unsigned short nMonth    : 5;    // 0..12  (5 bits)
   unsigned short nYear     : 8;    // 0..100 (8 bits)
};

//sizeof Date2 is 8;
struct Date2 {
   unsigned short nWeekDay  ;       //0..     (16bits)
   unsigned short nMonthDay ;    
   unsigned short nMonth    ;    
   unsigned short nYear     ;    
};

int main(int argc , char ** argv){
    //All starts from 1byte = 8 bits;
    cout<<"The size of unsigned short is    :"<<sizeof(unsigned short) <<endl;
    cout<<"The size of bit-field struct     :"<<sizeof(Date1)<<endl;
    cout<<"The size of non-bit-field struct :"<<sizeof(Date2)<<endl;
    
    return 0;
}