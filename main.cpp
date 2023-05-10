#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include "CsvData.h"
#include "BRDF.h"


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


    return 0;
}
