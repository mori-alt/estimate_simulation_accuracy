#include <iostream>
#include <filesystem>
#include "CsvData.h"

int main() {
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << "Current directory: " << current_path << std::endl;
    CsvData csv("./csv/result_3.csv");
    std::cout  << csv.getFilePath() << std::endl;


    return 0;
}
