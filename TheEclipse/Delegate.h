#pragma once 
#include <vector>
#include <functional>
#include <iostream>

template<typename... Args>
class Delegate {
public:
    using FuncType = std::function<void(Args...)>;

    void Add(FuncType func) {
        functions.push_back(func);
    }

    void Invoke(Args... args) {
        for (auto& func : functions) {
            func(args...);
        }
    }
    // 이런식으로 추가함.
    //델리게이트.Add(std::bind(&클래스::메서드, this, std::placeholders::_1));


private:
    std::vector<FuncType> functions;
};
