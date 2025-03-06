/*
C++ 中的 std::set 是一个常用的关联容器，提供了自动排序和快速查找功能。以下是 std::set 的重要特点、方法和使用场景的详细列举。

1. std::set 的特点
有序性：std::set 是一个有序容器，所有元素会根据键值自动排序（默认按升序）。
唯一性：std::set 中的元素是唯一的，不能有重复值。
底层实现：基于平衡二叉搜索树（通常是红黑树）。
时间复杂度：
插入、删除、查找：O(log n)。
2. 重要的成员函数
以下列出了 std::set 中常用的成员函数及其作用：

*/



#include <iostream>
#include <set>

int main(){
    std::set<int> s;
    s.insert(5);
    s.insert(10);
    s.insert(15);
    s.insert(20);
    s.insert(25);
    s.insert(30);
    s.insert(35);
    s.insert(40);

    for (const auto& ele : s){
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    if (s.find(15) != s.end()){
        std::cout << "15 exists !" << std::endl;
    }

    s.erase(10);

    // 注释1
    auto it = s.lower_bound(24);
    if ( it != s.end() ){
        std::cout << "Lower bound of 24 : " << *it << std::endl;
    }
    
    std::cout << "Set elements and their addresses:" << std::endl;
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << "Value: " << *it
                  << ", Address: " << reinterpret_cast<const void*>(&(*it))
                  << std::endl;
    }


    return 0;
}




//注释1
/*
这段代码的作用是通过 std::set 的 lower_bound 方法查找集合中**第一个大于或等于指定值（这里是 15）**的元素，并对其进行处理。

代码逐步解析
1. auto it = s.lower_bound(15);

s.lower_bound(15) 是 std::set 的一个成员函数。
功能：返回一个迭代器，指向集合中第一个大于或等于 15 的元素。

如果集合中存在等于 15 的元素，则返回指向该元素的迭代器。
如果集合中没有大于或等于 15 的元素，则返回 s.end()（即集合的尾后迭代器）。


auto 的作用：自动推导迭代器的类型（std::set<int>::iterator）。

2. if (it != s.end())

检查 lower_bound 返回的迭代器是否等于 s.end()。
为什么要检查：

如果 lower_bound 返回 s.end()，说明集合中不存在大于或等于 15 的元素。
如果不检查，直接解引用 *it 会导致未定义行为（因为 s.end() 不指向有效元素）。



3. std::cout << "Lower bound of 15: " << *it << std::endl;

如果 it 不等于 s.end()，说明找到了大于或等于 15 的元素。
使用 *it 解引用迭代器，输出该元素的值。


运行逻辑示例
假设集合 s 的内容如下：
std::set<int> s = {10, 15, 20, 25};

第一种情况：集合中存在等于 15 的元素

调用 s.lower_bound(15)。

lower_bound 返回指向值为 15 的迭代器。
it != s.end() 成立。
输出：Lower bound of 15: 15



第二种情况：集合中不存在等于 15 的元素，但有大于 15 的元素

假设集合为：
std::set<int> s = {10, 18, 20, 25};


调用 s.lower_bound(15)。

lower_bound 返回指向值为 18 的迭代器（第一个大于 15 的元素）。
it != s.end() 成立。
输出：Lower bound of 15: 18



第三种情况：集合中不存在大于或等于 15 的元素

假设集合为：
std::set<int> s = {1, 5, 10};


调用 s.lower_bound(15)。

lower_bound 返回 s.end()。
it != s.end() 不成立。
不会输出任何内容（因为 std::cout 的代码块不会执行）。




总结

lower_bound 用于查找集合中第一个大于或等于指定值的元素。
如果找不到符合条件的元素，返回 s.end()。
在使用 lower_bound 返回的迭代器前，必须检查它是否等于 s.end()，以避免解引用无效迭代器导致的未定义行为。
*/


