#include <iostream>
#include <stack>
/*
 *std::stack 的底层实现：
 *
 *默认基于 std::deque，也可以使用 std::vector 或 std::list。
 *它是一个容器适配器，而不是基于两个队列实现。
 *两个队列实现栈：
 *
 *这是一个经典的数据结构问题。
 *可以通过两种方法实现：
 *push 操作代价低：直接插入队列，pop 时转移元素。
 *pop 操作代价低：push 时转移元素，pop 时直接弹出。
 *实际开发中：
 *
 *如果需要栈，直接使用 std::stack，它的效率和易用性都更高。
 *用两个队列实现栈主要用于学习和面试场景。
 */


using namespace std;

int main(){
    stack<int> stk;
    
    cout << "Pushing elements onto the stack..." << endl;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);
    stk.push(60);
    stk.push(70);
    stk.push(80);

    // 演示 top 操作：获取栈顶元素
    cout << "Top element: " << stk.top() << endl; 
    // 演示 pop 操作：移除栈顶元素
    cout << "Popping elements from the stack..." << endl;
    stk.pop();
    cout << "Popped one element. New top: " << stk.top() << endl;

    while (!stk.empty()){
        stk.pop();
    }

    if (stk.empty()){
        cout << "stk is empty " << endl;
    } else {
        cout << "stk is not empty" << endl;
    }

    return 0;
}
