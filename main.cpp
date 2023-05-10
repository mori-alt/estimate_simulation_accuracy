#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include "CsvData.h"
#include "BRDF.h"

Eigen::MatrixXd rotation_matrix_y(const double phi){
    Eigen::MatrixXd rotate(3, 3);
    rotate << cos(phi), 0, -sin(phi), 0, 1, 0, sin(phi), 0, cos(phi);
    return rotate;
}

int main() {
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << "Current directory: " << current_path << std::endl;
    CsvData csv("./csv/result_3.csv");

    std::vector<double> rot_angle;
    BRDF brdf(375, {1, 1, 1}, 200, 300, {-1, 1, 1}, rot_angle);



    std::string str = "[p0050nm_00deg_d074nm-theta]";
    std::vector<double> numbers = extractNumbers(csv.getHeader()[2]);

    std::cout << csv.getRotAngle()[0] << std::endl;
    std::cout << csv.getRotAngle()[1] << std::endl;
    std::cout << csv.getRotAngle()[2] << std::endl;

    std::cout << csv.read_camera_solid_angles(1)[1][0] - csv.read_camera_solid_angles(1)[1][1] << std::endl;
    std::cout << csv.read_camera_solid_angles(1)[1][1] - csv.read_camera_solid_angles(1)[1][2] << std::endl;
    std::cout << csv.read_camera_solid_angles(1)[1][2] - csv.read_camera_solid_angles(1)[1][3] << std::endl;

    // 回転行列の作成
    Eigen::Vector3d pos(2, 1, 0);
    std::cout << pos << std::endl;

    double phi = M_PI / 2;
    Eigen::MatrixXd rotate = rotation_matrix_y(phi);
    std::cout << rotate << std::endl;

    std::cout << rotate * pos << std::endl;


    return 0;
}
