#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include "CsvData.h"
#include "BRDF.h"

int main() {
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << "Current directory: " << current_path << std::endl;
    CsvData csv("./csv/result_3.csv");
    BRDF brdf(csv);


    return 0;
}
