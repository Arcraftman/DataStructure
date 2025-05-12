#ifndef ARCH_VECTOR_IMPL_H
#define ARCH_VECTOR_IMPL_H

namespace arch {

// 默认构造函数
template <typename T>
my_vector<T>::my_vector() : data_(nullptr), size_(0), capacity_(0) {}

// 指定大小的构造函数
template <typename T>
my_vector<T>::my_vector(size_t size, const T& value) 
    : data_(new T[size]), size_(size), capacity_(size) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

// 初始化列表构造函数
template <typename T>
my_vector<T>::my_vector(std::initializer_list<T> init_list) 
    : data_(new T[init_list.size()]), size_(init_list.size()), capacity_(init_list.size()) {
    size_t i = 0;
    for (const T& elem : init_list) {
        data_[i++] = elem;
    }
}

// 拷贝构造函数
template <typename T>
my_vector<T>::my_vector(const my_vector& other) 
    : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

// 移动构造函数
template <typename T>
my_vector<T>::my_vector(my_vector&& other) noexcept 
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

// 析构函数
template <typename T>
my_vector<T>::~my_vector() {
    delete[] data_;
}

// 运算符重载：拷贝赋值
template <typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector& other) {
    if (this != &other) {
        delete[] data_;
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

// 运算符重载：移动赋值
template <typename T>
my_vector<T>& my_vector<T>::operator=(my_vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

// 元素访问
template <typename T>
T& my_vector<T>::operator[](size_t index) {
    return data_[index];
}

template <typename T>
const T& my_vector<T>::operator[](size_t index) const {
    return data_[index];
}

template <typename T>
T& my_vector<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
const T& my_vector<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

// 容量管理
template <typename T>
size_t my_vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t my_vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
bool my_vector<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
void my_vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        reallocate(new_capacity);
    }
}

template <typename T>
void my_vector<T>::resize(size_t new_size, const T& value) {
    if (new_size > capacity_) {
        reallocate(new_size);
    }
    for (size_t i = size_; i < new_size; ++i) {
        data_[i] = value;
    }
    size_ = new_size;
}

// 修改操作
template <typename T>
void my_vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}

template <typename T>
void my_vector<T>::push_back(T&& value) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
}

template <typename T>
void my_vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template <typename T>
void my_vector<T>::clear() {
    size_ = 0;
}

// 内部工具函数
template <typename T>
void my_vector<T>::reallocate(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

} // namespace my_namespace

#endif 

