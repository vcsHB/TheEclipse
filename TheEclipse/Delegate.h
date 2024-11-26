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
    //_collider->OnCollisionEvent.Add(std::bind(&EnemyAI::MoveTurn, this, std::placeholders::_1));

private:
    std::vector<FuncType> functions;
};
