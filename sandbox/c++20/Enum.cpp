#include <iostream>
#include <string_view>

enum class Color
{
    Red,
    Green,
    Blue
};

enum class TrafficLight
{
    Red,
    Green,
    Orange
};

std::string_view to_string(Color c)
{
    std::string_view str{"?"};
    switch (c) {
        case Color::Red:
            str = "Red";
            break;
        case Color::Green:
            str = "Green";
            break;
        case Color::Blue:
            str = "Blue";
            break;
    }
    return str;
}

int main()
{
    Color c = Color::Blue;
    Color c2{6};

    std::cout << "c2: " << to_string(c2) << '\n';

    return 0;
}
