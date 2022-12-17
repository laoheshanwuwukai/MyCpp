## Part 3 : Resource Management-资源管理

 	所谓资源就是，一旦使用了它，将来必须还给系统。C++ 程序中最常使用的资源就是动态分配内存（如果使用了，但是没有还给系统，就会造成内存泄露），除了动态分配内存，常见的资源还包括文件描述器（file descriptors）、互斥锁（mutex lock）、图形界面中的字型和笔刷、数据库的链接以及网络Socket；



### 条款13：以对象管理资源 -Use objects to manage resources

```cpp
Investment*  createInvestment(); //动态分配了内存
void f(){
      Investment* pInv = createInvestment();
        .......
       delete pInv;
        //（这个f 中加入了过早的return 或者抛出了异常，delete不会被执行，就会导致内存泄露）
 }


//改进：
void f(){
    std::auto_ptr<Investment> pInv(createInvestment() );
    ......
        
}
```

为了保证资源能够被正确的释放，我们将资源放进对象内，当控制流离开 f  时，该对象可以通过析构函数释放资源 。

以资源管理对象具备两个关键想法：

1. 获得资源后立即放进管理对象内（RAII 思想，Resource Acquisition Is Initialization;）

2. 管理对象析构时自动释放了管理的对象；

   ---

   auto_ptr 被销毁时会自动删除所指之物，所以不可使多个auto_ptr 指向同一个对象；为了防止上述问题，auto_ptr 的copy constructor && copy assignment 操作复制他们会导致原指针变为null;

   

   STL 容器要求其元素发挥正常的复制行为，因此不能搭配auto_ptr; 因此一个方法是使用引用计数型智能指针（reference-counting smart pointer , RCSP）shared_ptr;

​		auto_ptr 和shared_ptr 两者都在析构函数内做delete操作而不是delete [] , 意味着不能使用在动态分配得到的数组上;

​	

### 条款14：在资源管理类中小心copying 行为

​		在使用资源管理类时要注意考虑copying行为的不同情况；

	1. 禁止复制：比如将copy函数放入到private中或者 = delete；
	1. 使用引用计数，比如对于mutex 可以使用shared_ptr并指定delete,作为第二个参数；
	1. 复制底部资源；
	1. 转移底部资源的所有权；



### 条款15：在资源管理类中提供对原始资源的访问

​		资源管理类可以有效避免内存泄露，但是如果有API 的接口是原始资源，那么资源管理类需要开放一个接口，书中介绍了两种方法：

		1. 提供get()方法，返回原生资源；
		1. 提供隐式转换的接口； ``` operator FontHandle() const {return f;}``` 

​		

### 条款16：成对使用new 和 delete时需要采用相同的形式

```cpp
std:: string * stringArray = new std::string[100] ;

...
    
delete stringArray; //只是删除了第一个，剩下的99个没有被删除；
```

---

```cpp
typedef	 std::string	 AddressLines[4];
//AddressLines是一个数组，有4个string
```



### 条款17：以独立语句将new 对象置入智能指针

```cpp
//有两个接口
int prority();
void processWidget(std::shared_ptr<Widget> pw , int priority);


//processWidget(new Widget , priority() )     错误的调用，普通指针不能隐式转换成智能指针
processWidget(std::shared_ptr<Widget>(new Widget) , priority() ) ; //可以调用，但是存在隐藏的风险
    /*
    已知：
    先执行new Widget ,然后在执行explict的shared_ptr的构造函数，但是priority()函数在什么时候执行有两种情况
    情况1：
    1. priority()
    2. new Widget
    3.shared_ptr<Widget>
    情况2：
    1.new Widget;
    2.priority();
    3.shared_ptr<Widget>
    
    如果是情况2，那么如果在priority()的时候出现了异常，那么分配出来的内存没有被资源管理类接手；
    */
 
//最好的办法就是 以独立的语句将new对象存储于智能指针内
std::shared_ptr<Widget> pw(new Widget);
processWidget(pw , priority() );
```



## Part 4 : 设计与声明-- Designs and Declarations

​	针对良好的的C++接口设计和声明；

### 条款18：让接口容易被正确使用，不易被误用





## Part 7 模板与泛型编程 -- Templates and Generic Programming

​	泛型编程(generic programming) 使代码与其所处理的对象类型彼此独立；

​	模板元编程(template mateprogramming)，创造出了“在C++ 编译器内执行并于编译完成时停止执行”的程序；

#### 条款41：了解隐式接口和编译期多态

​		C++  = C  + Object Oriented C++  + Template + STL ;

​		其中面向对象编程总是以显示接口(Explicit interface) 和运行期多态(runtime polymorphism)解决问题，**以函数签名为中心的接口及virtual pointer为中心；**

​		Template则更加注重隐式接口(implicit interface)和编译期多态(compile-time pllymorphism)，**隐式接口不基于函数的签名，而是基于有效表达式，编译期多态则基于template具现化和函数重载解析；**

```cpp
template<typename T>
void doProcessing(T &w){
    	if(w.size()>10 && w!= someNastyWidge){
            .......
        }
}
/*
T的类型看起来需要提供以下两个接口：
	1.名为size()的成员函数，且返回一个整数值；
	2.支持 operator != 函数；
但事实上并不需要：
	1.T必须支持size()函数，然而这个函数可能从base class继承而来，这个成员函数不需要返回一个int，甚至不需要返回一个数值类型，它唯一要做的是返回一个类型为X的对象，而X对象加上一个int()类型转换必须能调用operator> ，这个operator> 不需要非得取一个类型为X的参数，因为他也可以取得类型Y的参数，只要存在一个隐式转换能够将类型X的对象转换为类型Y的对象；
	2.同样道理，T不一定需要支持operator!= 因为以下这样也是可以的：operator!= 接受一个类型为X的对象和一个类型为Y的对象，T可被转换为X ,someNastyWidge的类型可以被转换成Y;
*/
```

#### 条款42：了解typename的双重意义

​		typename作为模板中template<typename T> 和 template<class T> 时和class没有什么区别，但在template内指涉到嵌套类型名称时候起到说明作用；

```cpp
template<typename C>
void print2nd(const C& container){
    	if(container.size()>2){
            	//C::const_iterator iter(container.begin());	//错误，无法通过编译；
                typename C::const_iterator inter(container.begin());
            	++iter;
            	int value = *iter;
            	std::cout<<value<<endl;
        }
}
```

​		注：iter的类型是C::const_iterator，实际是什么必须取决于template的参数C，他有可能是个变量名字，也有可能是个类型名称，**当编译器开始解析template print2nd时，尚未确知C是什么，如果解析器在template中遭遇一个嵌套从属名称，他便假设这个名称不是个类型，除非前面加上typename明确告诉编译器它是类型. 特殊情况是在base class list 和member initialization list 中不可以出现**
