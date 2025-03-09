#ifndef KEYFRAME
#define KEYFRAME

#include <memory>
#include <iostream>
#include <vector>
#include <type_traits>

#include "constants.hpp"
#include <memory>
using namespace Constant;

struct WrapKF {
    virtual ~WrapKF() = default;
    virtual void update(float curTime) const = 0;
    virtual std::unique_ptr<WrapKF> clone() const = 0;
};

template<typename T>
struct CoreKF : WrapKF {
    T& variable;
    T start, end;
    float startTime, endTime;

    explicit CoreKF(T& r, T s, T e, float startTime, float endTime) 
        : variable(r), start(s), end(e), startTime(startTime), endTime(endTime) {}

    void update(float step) const override {
        float curTime = (step / TOTAL_STEPS) * DURATION;
        if(curTime < startTime) {
            variable = start;
        } else if(curTime > endTime) {
            variable = end;
        } else {
            variable = start + (end - start) * ((curTime - startTime) / (endTime - startTime));
        }
    }
        
    std::unique_ptr<WrapKF> clone() const override {
        return std::make_unique<CoreKF<T>>(variable, start, end, startTime, endTime);
    }
};

struct Keyframe {
    std::unique_ptr<WrapKF> ptr;
    float startTime, endTime;

    template<typename T, typename = std::enable_if_t<!std::is_same<std::decay_t<T>, Keyframe>::value>>
    Keyframe(T& r, T s, T e, float startTime = 0, float endTime = DURATION) 
        : ptr(std::make_unique<CoreKF<T>>(r, s, e, startTime, endTime)),
          startTime(startTime), endTime(endTime) {}

    Keyframe(const Keyframe& other) 
        : ptr(other.ptr->clone()), startTime(other.startTime), endTime(other.endTime) {}

    Keyframe(Keyframe&& other) noexcept = default;

    Keyframe& operator=(const Keyframe& other) {
        if (this != &other) {
            ptr = other.ptr->clone();
            startTime = other.startTime;
            endTime = other.endTime;
        }
        return *this;
    }

    Keyframe& operator=(Keyframe&& other) noexcept = default;

    void update(float t) const {
        ptr->update(t);
    }
};



#endif // !KEYFRAME

