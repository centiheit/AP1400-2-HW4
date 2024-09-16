#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
public:
    // 赋值构造函数
    SharedPtr(T* ptr);
    // 默认构造函数
    SharedPtr();
    // 析构函数
    ~SharedPtr();
    // 拷贝构造函数
    SharedPtr(const SharedPtr<T>& ptr);

    // 重载赋值运算符
    SharedPtr<T>& operator=(const SharedPtr<T>& ptr);
    // 引用计数器
    int use_count();

    T* get();

    // 重载解引用运算符
    T& operator*();
    // 重载指向运算符
    T* operator->();
    // 复位
    void reset();
    void reset(T* ptr);

    explicit operator bool() const;

private:
    T* _p;
    size_t* _count;
};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : _p(ptr) {
    _count = new size_t(1);
}

template <typename T>
SharedPtr<T>::SharedPtr() : _p(nullptr) {
    _count = new size_t(1);
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    // 这里我没有释放_count，因为TEST15中还需要用到_count
    *_count = *_count - 1;
    if (*_count == 0) {
        delete _p;
    }
    _p = nullptr;
}

// 这里实现的是浅拷贝
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& ptr) {
    _p = ptr._p;
    _count = ptr._count;
    *_count = *_count + 1;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& ptr) {
    if (this != &ptr) {
        reset();
        _p = ptr._p;
        _count = ptr._count;
        *_count = *_count + 1;
    }
    return *this;
}

template <typename T>
int SharedPtr<T>::use_count() {
    return *_count;
}

template <typename T>
T* SharedPtr<T>::get() {
    return _p;
}

template <typename T>
T& SharedPtr<T>::operator*() {
    return *_p;
}

template <typename T>
T* SharedPtr<T>::operator->() {
    return _p;
}

template <typename T>
void SharedPtr<T>::reset() {
    *_count = *_count - 1;
    if (*_count <= 0) {
        delete _p;
    }
    _p = nullptr;
}

template <typename T>
void SharedPtr<T>::reset(T* ptr) {
    reset();
    _p = ptr;
    _count = new size_t(1);
}

template <typename T>
SharedPtr<T>::operator bool() const {
    return _p != nullptr;
}

template <typename T>
SharedPtr<T> make_shared(T data) {
    T* ptr = new T(data);
    return SharedPtr<T>(ptr);
}

#endif //SHARED_PTR