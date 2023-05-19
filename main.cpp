#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include "CsvData.h"
#include "BRDF.h"


int main() {
    // set scene info
    const auto DL = 25;
    const auto NSPECT = 16;
    const int WAVELENGTHS[NSPECT] = { 375, 400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750 };
    const auto lgith_intensity = 0.25;
    const double wavelength = 375;
    std::vector<int> wavelengths;
    std::vector<Eigen::Vector3d> spectra2XYZ_conversion;

    wavelengths.clear();
    spectra2XYZ_conversion.clear();

    // set XYZ_data
    for(auto i = 0; i < NSPECT; ++i){
        wavelengths.push_back( WAVELENGTHS[i]);
        Eigen::Vector3d XYZ_data;
        getXYZForSpectraWindow(WAVELENGTHS[i], DL, XYZ_data);
        spectra2XYZ_conversion.push_back( XYZ_data);
    }

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

    // calculate all situation calc all
    for(int i = 0; i < 74; ++i){
        // calculate brdf
        BRDF brdf2(wavelength, dl, csv.getSurfaceGeo(i)[2], pitch, csv.getCameraPos(), csv.getRotAngle());
        std::vector<double> brdfs = brdf2.calc_all_frame_brdf();

        // convert2RGB
        std::vector<Eigen::Vector3d> rgb;

        // update csv_data
        csv.update_RGB(rgb, i);
    }

    // output csv sample
    const std::string output_path = "./output_csv/sample_output.csv";
    csv.output_csv(output_path);


    return 0;
}
