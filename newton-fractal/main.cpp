#include "AppWindow.hpp"
#include <iostream>

auto main() -> int {
    std::cout << "Drawing a Newton fractal for the equation z^n - 1 = 0\n"
                 "Please enter the value of n (must be a positive integer):";

    auto input = 3; // default value
    std::cin >> input;
    auto n = input;

    drawWindow(n, 800, 800);
}
