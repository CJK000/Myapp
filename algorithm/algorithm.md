# 算法实现

本程序的算法实现主要由以下三个类实现     

​    

#### 1、Number类：

+ 成员变量：数字三部分：整数、分母、分子

  ```c++
  int integer;	//整数部分
  int numerator;	//分子
  int denominator;	//分母
  ```

+ 成员函数：

  + 构造函数

    ```C++
    Number();	//初始化全为 0
    Number(int n);	//随机生成数字不大于 n 的 Number 对象
    Number(int n, int max_de);//随机生成数值不大于 n，分母不大于 max_de 的 Number 对象
    Number(int a, int b, int c);// a 为整数部分，b 为分子，c 为分母
    Number(string str, int &i);	//将字符串 str 从第 i 位开始获取一个Number对象
    Number(string str);	//从字符串头开始获得一个数字
    ```

  + 实现运算加、减、乘、除

    ```c++
    Number operator+(Number t);
    Number operator-(Number t);
    Number operator*(Number t);
    Number operator/(Number t);
    ```

  + 实现所有比较运算 > , >= , < , <= , == , != 

    ```c++
    bool operator>(Number t);
    bool operator>=(Number t);
    bool operator<(Number t);
    bool operator<=(Number t);
    bool operator==(Number t);
    bool operator!=(Number t);
    ```

  + `string ToString();//把当前的Number对象转换成 string 对象，可用于输出或其他处理`

  + `bool CheckNumber();//检查当前 Number 对象是否为一个合法的数字，可用于判断其他运算返回的结果是否合法`

#### 2、Expression类：

+ 成员变量：

  + `Vector<Point> question //题目`

    + 其中Point类为：

    + ```C++
      class Point {
      	public:
      		int type;//标记当前结构体代表的意义， 0 表示符号, 1表示数字
      		char symbol;//运算符
      		Number num;	//数字
      		Point(Number n);// 用一个 Number 对象初始化当前 Point 对象
      		Point(char c);//用一个符号初始化当前 Point 对象
      };
      ```

  + `Number answer 答案`

    ​	当前题目的正确计算结果，如果答案小于 0，则题目有错

  + `bool valid;	//当前题目是否为一个有效的题目`

+ 成员函数：

  ```c++
  Expression() { };	//无参构造函数，初始化一个空的对象
  Expression(string str);	//用题目字符串初始化，并计算出正确答案
  string ToString();//将题目转换成字符串，不包括答案，答案可直接使用 Number 类的 ToString 函数转换
  //以下三个函数为向当前题目末尾以下各类元素
  void Add(Number n);
  void Add(char c);
  void Add(Expression exp);
  //以下三个函数分别为，按顺序向当前对象中插入内容，前三个为题目内容，最后一个为答案
  Expression(Number num, char c, Number num2, Number ans);
  Expression(Number num, char c, Expression exp,Number ans);
  Expression(Expression exp, char c, Number num, Number ans);
  void AddParenthesis(void);	//在当前题目的左右边缘添加一对括号
  void clear();	//清空对象当前内容
  bool CheckValid();	//判断当前题目是否合法
  vector<Point> Nifix2Postfix();	//中缀转后缀，后缀表达式用vector存放 
  Number Calculate();	//计算当前题目的答案
  ```

  

#### 3、Make类：

​	成员变量：`int max_number;//题目中的最大数字`

​			   `int problem_number;//要求生成题目的数量`

​	这个类实现随机生成题目的函数，分别实现生成加减乘除题目的函数，在函数中可以递归调用任意一个生成题目的函数作为本次生成题目的子部分，，根据函数接收的参数决定是否还需继续递归调用，根据另一个参数确定本次调用是否为第一次调用，如果时第一次调用则需要向用户输出内容，在返回值之前需要进行查重，如果不需要向用户输出则本次调用不需要查重，如果没有重复，则把所有题目存入到 Trie 树中。

```c++
class Make {
private:
	int max_number;	//最大数字
	int problem_number;
	bool CheckNumber();
//	set<string> stringSet;	//将生成的题目和所有等价的题目插入此，用于查重
//	bool CheckExist(Expression exp);	//检查此题目是否已生成
//	void Insert(Expression exp);	//将一个题目插入到 stringSet中
	typedef vector<Expression> (Make::*Function_ptr)(int, int, int, int);
	//函数指针数组 randMake[4] 的四个元素为随机生成题目的函数指针，方便随机调用时使用
	const Function_ptr randMake[4] = {&Make::RandPlus, &Make::RandMinus, &Make::RandMul, &Make::RandDiv };

	//以下四个函数为随机生成题目函数
	//max_n 为题目中数字整数部分的最大值，生成的数字式子的答案不能大于 max_n
	//max_de 为题目中分母的最大值
	//symbol_n 为生成题目的符号数
	//若symbol > 1，在函数中随机调用生成题目的函数，作为本次调用的子部份
	//symbol = 1，本次为最后一次调用，直接生成两个 Number 对象的基本运算，然后返回
	//output=1 表示本次调用为第一次调用，需要返回输出
	//output=0 表示本次调用为被递归调用，只需返回给上一级调用使用，无需判断生成的题目是否存在 stringSet 中
	//返回值中为一个题目和它的等价题目，可随机输出一个
	//如果返回的vector为空，则本次生成题目失败
	vector<Expression> RandPlus(int max_n, int max_de, int symbol_n, int output);
	vector<Expression> RandMinus(int max_n, int max_de, int symbol_n, int output);
	vector<Expression> RandMul(int max_n, int max_de, int symbol_n, int output);
	vector<Expression> RandDiv(int max_n, int max_de, int symbol_n, int output);

public:
	Trie trie;
	Make(int n, int m);
	Expression MakeProblem(void);	//供给主函数调用，返回一个随机生成运算符不超过3个的正确题目
};
```



#### 生成题目算法逻辑

![算法逻辑](https://img2020.cnblogs.com/blog/1814040/202004/1814040-20200412141411077-551629482.png)

### 注意

当题目中数字大于1289时可能会生成错误的题目，因为计算过程中可能会出现大于 INT_MAX 的数字导致计算错误，所以当用户输入最大数字大于1289时，生成题目后使用计算答案的函数验证题目是否正确。

证明：

设 $p_1, p_2, p_3, p_4, p_5​$ 为互不相等的素数素数。

进行除法运算时，$\frac{1}{p_2}\div p_3\frac{p_5-1}{p_5}$，即 $\frac{1}{p_2}\times\frac{p_5}{p_3\times p_5+p_4}$，此时分母最大，编写验证程序。

```c++
using namespace std;
typedef long long ll;
bool Check(ll a, ll b, ll c){
	if(a*(b*c+b-1)>INT_MAX)return false;
	if(a*(b*c+c-1)>INT_MAX)return false;
	if(b*(a*c+a-1)>INT_MAX)return false;
	if(b*(a*c+c-1)>INT_MAX)return false;
	if(c*(b*a+b-1)>INT_MAX)return false;
	if(c*(b*a+a-1)>INT_MAX)return false;
	return true;
}
void FindMax(){
	ll i,j,k;
	int j1=2,j2=3;
	int f;
	for(j=5;Check(j1,j2,j)==true;j++){
		f=1;
		for(i=2;i*i<=j;i++){
			if(j%i==0){
				f=0;
				break;
			}
		}
		if(f){
			cout << j << endl;
			j1=j2;
			j2=j;
		}
	}
}

```

经检验，当 $p_i<=1289$ 时满足条件。

