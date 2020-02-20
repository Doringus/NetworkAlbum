#pragma once

#include <memory>

class Action;

class Middleware {
public:
    virtual std::shared_ptr<Action> process(const std::shared_ptr<Action>& action) = 0;
protected:
    Middleware() = default;
};

