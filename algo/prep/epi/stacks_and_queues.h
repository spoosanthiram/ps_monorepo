#pragma once

#include <string_view>
#include <vector>

namespace ps::algo {

/// EPI 9.1: Implement Stack with Max API
class StackWithMax
{
public:
    void push(int value);
    int pop();
    int max() const;

private:
    struct StackElement
    {
        int value;
        int current_max;
    };
    std::vector<StackElement> stack_;
};

/// EPI 9.3: Test a string over "{,}, (, ), [, ]" for well-formedness
bool is_well_formed(const std::string_view str);

} // namespace ps::algo
