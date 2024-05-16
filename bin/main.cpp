#include <iostream>
#include <vector>

#include <lib/lr1.h>
#include <lib/lr1.cpp>



int main() {
    std::vector<int> arr = { 0, -5, 0, -5, -5 };
    auto result = find_pairs(arr);

    std::cout << "Pairs:\n";
    int count = 0;
    for (const auto& pair : result.first) {
        count++;
        std::cout << "(index: " << pair.first << ", value: " << pair.second << ")\n";
        if (count == 2) {
            std::cout << "------------------\n";
            count = 0;
        }
    }

    std::cout << "\nErrors:\n";
    for (const auto& error : result.second) {
        std::cout << error << "\n";
    }

    return 0;
}