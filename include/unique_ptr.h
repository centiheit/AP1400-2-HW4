#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
public:
    // 赋值构造函数
    UniquePtr(T* ptr);
    // 默认构造函数
    UniquePtr();
    // 析构函数
    ~UniquePtr();
    // 禁用拷贝构造函数
    // delete 关键字用于删除函数，使得该函数不能被调用
    UniquePtr(const UniquePtr<T>& ptr) = delete;
    // 禁用拷贝赋值运算符
    UniquePtr<T>& operator=(const UniquePtr<T>& ptr) = delete;

    T* get();

    // 解引用运算符
    T& operator*();
    // 指向运算符
    T* operator->();
    // 复位
    void reset();
    void reset(T* ptr);
    // 释放
    T* release();

    // 隐式转换（Implicit Conversion）：在不使用显式关键字的情况下，编译器可以在需要的时候自动调用转换运算符。
    // 例如，类类型对象在需要转换为布尔值或整数时，编译器会自动使用这个转换运算符进行类型转换。
    // 显式转换（Explicit Conversion）：在C++11引入的explicit关键字用于防止隐式类型转换，
    // 仅允许在明确需要的时候（如在static_cast或if语句中）使用。这样可以避免意外的类型转换导致的错误。
    explicit operator bool() const;

private:
    T* _p;
};

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr) : _p(ptr) {}

template <typename T>
UniquePtr<T>::UniquePtr() : _p(nullptr) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete _p;
}

template <typename T>
T* UniquePtr<T>::get() {
    return _p;
}

template <typename T>
T& UniquePtr<T>::operator*() {
    return *_p;
}

template <typename T>
T* UniquePtr<T>::operator->() {
    return _p;
}

template <typename T>
void UniquePtr<T>::reset() {
    delete _p;
    _p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* ptr) {
    delete _p;
    _p = ptr;
}

template <typename T>
T* UniquePtr<T>::release() {
    T* tmp = _p;
    _p = nullptr;
    return tmp;
}

template <typename T>
UniquePtr<T>::operator bool() const {
    return _p != nullptr;
}

template <typename T>
UniquePtr<T> make_unique(T data) {
    T* ptr = new T(data);
    return UniquePtr<T>(ptr);
}

#endif //UNIQUE_PTR