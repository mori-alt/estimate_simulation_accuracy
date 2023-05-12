#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include "CsvData.h"
#include "BRDF.h"

Eigen::MatrixXd rotation_matrix_y(const double phi_rad) {
    // y軸が上向きのはずだからy軸中心の回転を定義しているけど問題があったら適宜修正を加えること
    Eigen::MatrixXd rotate(3, 3);
    rotate << cos(phi_rad), 0, -sin(phi_rad), 0, 1, 0, sin(phi_rad), 0, cos(phi_rad);
    return rotate;
}

int main() {
    // todo define from csv as much as possible
    const double wavelength = 375;
    const double pitch = 600; // todo ask material surface situation
    Eigen::Vector3d dl(0, 1, 1);
    CsvData csv("./csv/result_3.csv");
    BRDF brdf(wavelength, dl, csv.getSurfaceGeo(9)[2], pitch, csv.getCameraPos(), csv.getRotAngle());

    std::cout << "output test" << std::endl;
    std::vector<double> brdfs = brdf.calc_all_frame_brdf();

    std::cout << brdfs.size() << std::endl;
    for(int i = 0; i < 10; ++i){
        std::cout << brdfs[i] << std::endl;
    }


    return 0;
}
