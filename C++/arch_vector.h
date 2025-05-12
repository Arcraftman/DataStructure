#ifndef ARCH_VECTOR_H
#define ARCH_VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include "bits/imp_vector.h";

namespace arch {

template <typename T>
    class vector {
        public:
            vector();
            //explicit 关键字 explicit 是 C++ 中的一个关键字，用于修饰构造函数或转换运算符，目的是防止隐式转换。 作用 当构造函数被声明为 explicit 时，它不能用于隐式转换或复制初始化。 只有显式调用构造函数时才会生效。
            explicit vector(size_t size , const T& value = T());
            //const T&： 表示参数是一个常量引用。 常量引用的优点是避免拷贝（节省性能）并且不能修改原始对象。 = T()： 表示参数有一个默认值，默认为类型 T 的默认构造函数生成的对象。 } }

            vector(const vector& other);
            vector(vector&& other) noexcept;
            ~vector();
        
            // 运算符重载
            vector& operator=(const vector& other);
            vector& operator=(vector&& other) noexcept;
            T& operator[](size_t index);
            const T& operator[](size_t index) const;
        
            // 容量管理
            size_t size() const noexcept;
            size_t capacity() const noexcept;
            bool empty() const noexcept;
            void reserve(size_t new_capacity);
            void resize(size_t new_size, const T& value = T());
        
            // 修改操作
            void push_back(const T& value);
            void push_back(T&& value);
            void pop_back();
            void clear();
        
            // 元素访问
            T& at(size_t index);
            const T& at(size_t index) const;
            T& front();
            const T& front() const;
            T& back();
            const T& back() const;
        
        private:
            T* data_;           // 动态数组指针
            size_t size_;       // 当前元素个数
            size_t capacity_;   // 当前容量
        
            void reallocate(size_t new_capacity);
        };

}


#endif
