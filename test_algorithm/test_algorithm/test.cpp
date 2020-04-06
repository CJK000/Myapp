/***********************************************

    Filename       : test.cpp
    Author         : 岑纪鹏
    Description    : 
    Create Data    : 2018-10-21 01:05:17
    Modfiy History : 2018-10-21 01:05:17

***********************************************/
#include "pch.h"
#include "algorithm/expression.h"
#include"algorithm/make.h"
#include"algorithm/number.h"

using namespace std;

class MyTestSuite0 : public testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        cout << "TestSuite event0 : start" << endl;
    }

    static void TearDownTestSuite()
    {
        cout << "TestSuite event0 : end" << endl;
    }
};



//TEST_F(MyTestSuite0, CheckNumber)//测试checknumber函数
//{
//    int i, j, k;
//    for (i = -10; i < 11; i++) {
//        for (j = 10; j < 11; j++) {
//            for (k = -10; k < 11; k++) {
//                Number a(j, k, i);
//                EXPECT_TRUE(a.CheckNumber())<<"现在整数： "<<j<<"分数："<<i<<"分子："<<k;
//            }
//        }
//    }
//}

TEST_F(MyTestSuite0, CheckNumber_)//测试CheckNumber(int max_n, int max_de)函数
{
    int i, j;
    for (i = 1; i < 21; i++) {
        for (j = 1; j < 21; j++) {
                Number b(i,j);
                EXPECT_TRUE(b.CheckNumber(i,j))<<"i="<<i<<"   j="<<j;
        }
    }
}

TEST_F(MyTestSuite0, Rand)//测试随机生成Number(int n)和CheckNumber()
{
    int i;
    for (i = 1; i < 100; i++) {
        Number b(i);
        EXPECT_TRUE(b.CheckNumber()) << "i=" << i;
    }
}

TEST_F(MyTestSuite0, Calculate) {
    int i;
    for (i = 0; i < 30; i++) {
        Number a(i), b(i + 1);
        cout << " a=";
        a.Print();
        cout << " b=";
        b.Print();
        Number c = a + b;
        cout << endl;
        cout << " c(+)=";
        c.Print();
        cout << endl;
        c = a - b;
        cout << " c(-)=";
        c.Print();
        cout << endl;
        c = a * b;
        cout << " c(*)=";
        c.Print();
        cout << endl;
        c = a / b;
        cout << " c(/)=";
        c.Print();
        cout << endl;
        cout << endl;
    }
}

TEST_F(MyTestSuite0, str_build_num)//Number(string str)和Number(string str, int &i)
{
    char* a[5] = {
        "-26'25/26","1'189/211","  153'3/25","0'13/50","-2'14/30"
    };
    for (int i = 0; i < 5; i++)
    {
        string b = a[i];
        Number c(b);
        EXPECT_STREQ(a[i], c.ToString().c_str())<<"测试Number(string str)";
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}