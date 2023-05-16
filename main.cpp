#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include "CsvData.h"
#include "BRDF.h"


int main() {
    const double wavelength = 375;
    const double pitch = 600; // todo ask material surface situation
    Eigen::Vector3d dl(0, 1, 1);
    CsvData csv("./csv/result_3.csv");
    BRDF brdf(wavelength, dl, csv.getSurfaceGeo(9)[2], pitch, csv.getCameraPos(), csv.getRotAngle());

    std::cout << "output test" << std::endl;
//    std::vector<double> brdfs = brdf.calc_all_frame_brdf();
//
//    std::cout << brdfs.size() << std::endl;
//    for(int i = 0; i < brdfs.size(); ++i){
//        std::cout << brdfs[i] << std::endl;
//    }

    std::cout << csv.getData().size() << std::endl;
    std::cout << csv.getData()[0].size() << std::endl;

    std::vector<Eigen::Vector3d> RGB;
    for(int i = 0; i < csv.getData().size(); ++i){
        RGB.push_back({1, 2, 3});
    }

    csv.update_RGB(RGB, 4);

    // output csv sample
    const std::string output_path = "./output_csv/sample_output.csv";
    csv.output_csv(output_path);


    return 0;
}
