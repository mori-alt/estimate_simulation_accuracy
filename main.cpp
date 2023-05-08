#include <iostream>
#include <filesystem>
#include "CsvData.h"

int main() {
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << "Current directory: " << current_path << std::endl;
    CsvData csv("./csv/result_3.csv");

    std::cout << csv.getEyePos()[0] << std::endl;
    std::cout << csv.getEyePos()[1] << std::endl;
    std::cout << csv.getEyePos()[2] << std::endl;

    std::cout << csv.getEyePos()[0] + csv.getEyePos()[1] << std::endl;


    return 0;
}
