#pragma once

#include <memory>

class Action;

class Store {
public:
    virtual void process(const std::shared_ptr<Action>& action) = 0;
protected:
    Store() = default;
};

