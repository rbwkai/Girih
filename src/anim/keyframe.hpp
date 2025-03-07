#ifndef KEYFRAME
#define KEYFRAME

#include <memory>
#include <iostream>
#include <vector>
#include <type_traits>

struct WrapKF {
    virtual ~WrapKF() = default;
    virtual void update(float t) const = 0;
    virtual std::unique_ptr<WrapKF> clone() const = 0;
};

template<typename T>
struct CoreKF : WrapKF {
    T& variable;
    T start, end;

    explicit CoreKF(T& r, T s, T e) : variable(r), start(s), end(e) {}

    void update(float t) const override {
        variable = start + (end - start) * t;
    }

    std::unique_ptr<WrapKF> clone() const override {
        return std::make_unique<CoreKF<T>>(variable, start, end);
    }
};

struct Keyframe {
    std::unique_ptr<WrapKF> ptr;

    template<typename T, typename = std::enable_if_t<!std::is_same<std::decay_t<T>, Keyframe>::value>>
    Keyframe(T& r, T s, T e) : ptr(std::make_unique<CoreKF<T>>(r, s, e)) {}

    Keyframe(const Keyframe& other) : ptr(other.ptr->clone()) {}

    Keyframe(Keyframe&& other) noexcept = default;

    Keyframe& operator=(const Keyframe& other) {
        if (this != &other) ptr = other.ptr->clone();
        return *this;
    }

    Keyframe& operator=(Keyframe&& other) noexcept = default;

    void update(float t) const {
        ptr->update(t);
    }
};

#endif // !KEYFRAME

