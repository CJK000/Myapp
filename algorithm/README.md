# 结对项目

### 思路

三个类：

+ Number类（已实现）：
  + 成员变量：数字三部分：整数、分母、分子

    ```c++
    int integer;	//整数部分
    int numerator;	//分子
    int denominator;	//分母
    ```

  + 成员函数：

    + 实现运算加、减、乘、除
    + 实现所有比较运算 > , >= , < , <= , == , != 
    + `void ClarifyNu();	//假分数化成带分数，调用前整数部分为正确数字`
    + `bool CheckNumber();	//检查当前 Number 对象是否为一个合法的数字，可用于判断其他运算返回的结果是否合法`
+ Expression类（已实现）：

  + 成员变量：

    + `Vector<Point> question //题目`

      + 其中Point类为：

      + ```C++
        class Point {
        	public:
        		int type;	// 1 表示数字，2 表示符号
        		char symbol;	//运算符
        		Number num;		//数字
        		Point(Number n);
        		Point(char c);
        };
        ```

    + `Number answer 答案`

      ​	当前题目的正确计算结果

    + `bool valid;	//当前题目是否为一个有效的题目`

  + 成员函数：

    ```c++
    Expression() { };	//无参构造函数，初始化一个空的对象
    Expression(string str);	//用题目字符串初始化，并计算出正确答案
    string ToString();
    //向当前表达式末尾以下各类元素
    void Add(Number n);
    void Add(char c);
    void Add(Expression exp);
    void AddParenthesis(void);	//添加一对括号
    void clear();	//清空对象当前内容
    bool CheckValid();	//判断当前题目是否合法
    vector<Point> Nifix2Postfix();	//中缀转后缀，后缀表达式用vector存放 
    Number Calculate();	//计算当前题目的答案
    ```

    

+ Make类（未实现）：
  + 成员变量：最大数字，生成题目数量
  + 成员函数
    + 生成加法算式
    + 生成减法算式
    + 生成乘法算式
    + 生成除法算式
    + 生成多个运算符的算式

