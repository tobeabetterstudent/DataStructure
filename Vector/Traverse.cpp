// @program: 02C4 向Traverse函数传入一个函数参数 使用函数指针；函数对象；C++11 function函数对象
// @author: aslanwang
// @time: 2021-11-14

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// VST visit类 重载operator() 实现对vector求和
// 作为函数对象被void MyVector::Traverse(VST &visit) 调用
class VST
{
private:
    int sum = 0;

public:
    void operator()(int v)
    {
        sum += v;
        cout << "VST visited " << v << endl;
    }
};

// Sum方法 对vector求和并保存在全局变量
// 使用函数指针绑定到Sum 从而被void MyVector::Traverse(void (*visit)(int))调用
int sum = 0;
void Sum(int v)
{
    sum += v;
    cout << "Sum visited " << v << endl;
}

void Print(int v)
{
    cout << "Print visited " << v << endl;
}
class MyVector
{
private:
    vector<int> arr;

public:
    MyVector(vector<int> &input)
    {
        // 注意将一个vector赋值给另一个 要使用assign 不论是push/-back还是emplace_back都只能插入一个元素
        arr.assign(input.begin(), input.end());
    }
    // Traverse通过函数指针机制传入function参数 进行Traverse
    // 函数指针的声明方法为  函数返回类型 + (指针变量名)+ (形参列表) 实际上函数名可以直接作为函数指针
    void Traverse(void (*visit)(int))
    {
        for (auto &&v : this->arr)
        {
            visit(v);
        }
    }
    // Traverse通过函数对象机制 进行Traverse
    // 函数对象即定义一个类，类中重载operator()方法
    // 类模版std::function
    // 增加functional头文件
    void Traverse(VST &visit)
    {
        for (auto &&v : this->arr)
        {
            visit(v);
        }
    }
    // Traverse通过function<void(int)> Functional 进行Traverse
    // 增加functional头文件
    // 这里t = 0只是用来重载的 避免与Traverse(void (*visit)(int))冲突
    void Traverse(function<void(int)> visit, int t = 0)
    {
        for (auto &&v : this->arr)
        {
            visit(v);
        }
    }
};

int main()
{
    vector<int> data = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    MyVector arr(data);
    arr.Traverse(Sum);
    VST visit;
    arr.Traverse(visit);
    arr.Traverse(Print, 10);
}
