#include <iostream>
#include <filesystem>
#include "CsvData.h"

int main() {
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << "Current directory: " << current_path << std::endl;
    try {
        CsvData csv("./csv/result_3.csv");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
