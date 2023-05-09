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

    std::cout << csv.getLookAt()[0] << std::endl;
    std::cout << csv.getLookAt()[1] << std::endl;
    std::cout << csv.getLookAt()[2] << std::endl;

    std::cout << csv.getDistToLookAt() << std::endl;
    std::cout << csv.getCameraTheta() << std::endl;
    std::cout << csv.getCameraPhi() << std::endl;
    std::cout << csv.getCameraPsi() << std::endl;
    std::cout << csv.getOmega() << std::endl;

    std::cout << csv.getHeader().size() << std::endl;
    std::cout << csv.getData().size() << std::endl;
    std::cout << csv.getData()[0].size() << std::endl;

    std::cout << csv.getHeader().back() << std::endl;
    std::cout << csv.getData()[0].back() << std::endl;


    return 0;
}
