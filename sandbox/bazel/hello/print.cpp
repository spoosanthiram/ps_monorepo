#include "hello/print.h"

#include <format>
#include <iostream>

void print(std::string_view name)
{
    std::cout << std::format("Hello {}", name) << '\n';
}
