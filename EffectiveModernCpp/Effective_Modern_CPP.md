# 第1章：型别推到

## 条款1：理解模板型别推倒

```cpp
template<typename T>
void func(ParamType param);

//call function
func(expr)
```

​	在编译器，编译器会根据 **```expr```** 推导 **```T ```**和**``` ParamType```**这两个型别，这两个型别往往不一样，因为**```ParamType```**会包含修饰（比如说```const ```或者引用符号）；

​	T 的型别推到结果不仅仅依赖**```expr```** 的型别，还依赖**```ParamType```** 的形式，具体分三种情况

1. **```ParamType```** 具有指针或引用型别，但不是万能引用；

   若**```expr```** 具有引用型别，先将引用型别忽略，而后对**```expr```**和**```ParamType```**进行模式匹配

2. **```ParamType```**是一个万能引用；

   如果**```expr```**是个左值，T和ParamType都会被推导为左值引用；如果是个右值根据情况1 规则；

3. **```ParamType```**即非指针也非引用；

   忽略**```expr```**的引用性、const、volatile性能；

   

在C++中数组或函数型别的实参会退化成对应的指针，除非他们被用来初始化引用

```cpp
template<typename T , std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept 
{
    return N;
}
```



## 条款2：理解```auto```型别推倒

对于模板推倒过程:

```cpp
template<typename T>
void func(ParamType param);

func(expr)
```

```auto```就扮演了T这个角色，而变量的型别修饰扮演

## 条款9: 优先选用别名声明，而非typedef

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



