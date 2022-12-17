#### 条款9: 优先选用别名声明，而非typedef

​		在C++中简化一个类型的声明可以使用如下两种方式：

```cpp
//智能指针指向键值对类型都为std::string 的map    别名：UPtrMapSS
typedef		std::unique_ptr<std::unordered_map<std::string , std::string> >	 UPtrMapSS;
using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string , std::string> > ;

//函数指针 FP
typedef void (*FP)(int , const std::string&);
using FP = void(*)(int , const std::string&);
```

​		就起别名的简便形式上两者不分上下，但是对于具有模板性质的代码来说，using可以和template结合，而typedef只能使用名称空间来操作：

```cpp
template<typename T>
using MyAllocList = std::list<T , MyAlloc<T> > ;

MyAllocList<Widget> lw;


template<typename T>
struct MyAllocList{
    	typedef std::list<T , MyAlloc<T> > type;
}
MyAllocList<Widget> ::type lw;
```



