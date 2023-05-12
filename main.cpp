#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include "CsvData.h"
#include "BRDF.h"

int main() {
    // todo define from csv as much as possible
    const double wavelength = 375;
    const double pitch = 600; // todo ask material surface situation
    Eigen::Vector3d dl(0, 1, 1);
    CsvData csv("./csv/result_3.csv");
    BRDF brdf(wavelength, dl, csv.getSurfaceGeo(9)[2], pitch, {-1, 1, 1}, csv.getRotAngle());

    std::cout << "output test" << std::endl;

    std::cout << brdf.estimate_brdf_exp_value(pow(2, 20)) << std::endl;
    brdf.show_member();

    return 0;
}
