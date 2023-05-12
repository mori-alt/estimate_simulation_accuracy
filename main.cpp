#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include "CsvData.h"
#include "BRDF.h"

int main() {
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << "Current directory: " << current_path << std::endl;
    CsvData csv("./csv/result_3.csv");

    // csv データの情報だけで取得することが難しいデータはひとまず定数宣言しておく
    const double wavelength = 375;
    const double pitch = 600; // todo 物体表面の傷がどのようについているのか確認する必要がある
    Eigen::Vector3d dl(0, 1, 1);

    BRDF brdf(wavelength, dl, csv.getSurfaceGeo(9)[2], pitch, {-1, 1, 1}, csv.getRotAngle());

    std::cout << "output test" << std::endl;
    std::string str = "[p0050nm_00deg_d074nm-theta]";
    std::vector<double> numbers = extractNumbers(csv.getHeader()[2]);

    for(double d : csv.getSurfaceGeo(9)){
        std::cout << d << std::endl;
    }

    std::cout << brdf.getDl() << std::endl;
    std::cout << csv.getCameraPos() << std::endl;
    std::cout << csv.getRotAngle().size() << std::endl;
    std::cout << brdf.getRotAngle().size() << std::endl;

    std::cout << brdf.estimate_brdf_exp_value(pow(2, 20)) << std::endl;
    brdf.show_member();

    return 0;
}
