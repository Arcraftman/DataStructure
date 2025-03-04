#include <iostream>
#include <queue> // 引入队列头文件
using namespace std;

int main() {
    // 创建一个队列
    queue<int> myQueue;

    // 演示 push 操作：将元素插入队列尾部
    cout << "Pushing elements into the queue..." << endl;
    myQueue.push(10);
    cout << "Pushed: 10" << endl;
    myQueue.push(20);
    cout << "Pushed: 20" << endl;
    myQueue.push(30);
    cout << "Pushed: 30" << endl;

    // 演示 front 和 back 操作
    cout << "Front element: " << myQueue.front() << endl; // 输出 10
    cout << "Back element: " << myQueue.back() << endl;   // 输出 30

    // 演示 pop 操作：移除队列的头部元素
    cout << "Popping elements from the queue..." << endl;
    myQueue.pop();
    cout << "Popped one element. New front: " << myQueue.front() << endl; // 输出 20

    // 再次 pop
    myQueue.pop();
    cout << "Popped one element. New front: " << myQueue.front() << endl; // 输出 30

    // 演示 empty 操作：判断队列是否为空
    cout << "Popping the last element..." << endl;
    myQueue.pop();
    if (myQueue.empty()) {
        cout << "Queue is now empty!" << endl;
    } else {
        cout << "Queue is not empty!" << endl;
    }

    return 0;
}
