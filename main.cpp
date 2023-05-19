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
    const int surface_num = 3;
    std::vector<int> wavelengths;
    std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
    std::array<double, NSPECT> accumulation_spectra;

    wavelengths.clear();
    spectra2XYZ_conversion.clear();

    // set XYZ_data
    for(auto i = 0; i < NSPECT; ++i){
        wavelengths.push_back( WAVELENGTHS[i]);
        Eigen::Vector3d XYZ_data;
        getXYZForSpectraWindow(WAVELENGTHS[i], DL, XYZ_data);
        spectra2XYZ_conversion.push_back( XYZ_data);
    }

    const double pitch = 600;
    Eigen::Vector3d dl(0, 1, 1);
    CsvData csv("./csv/result_3.csv");
    BRDF brdf(wavelength, dl, csv.getSurfaceGeo(surface_num)[2], pitch, csv.getCameraPos(), csv.getRotAngle());

    const int loop_num = 1 << 15;
    std::cout << loop_num << std::endl;

    auto _brdf = 0.0;

    // calc spectra accumulation
    for(int i = 0; i < loop_num; ++i){
        Eigen::Vector2d random_st;
        random_st << randomMT(), randomMT();
        _brdf = brdf.eval_sinusoidal_brdf(random_st);
        // add normal dot calc?
        const auto f = _brdf;
        accumulation_spectra[0] += f;
    }


// save color test
//    std::vector<Eigen::Vector3d> RGB;
//    for(int i = 0; i < csv.getData().size(); ++i){
//        RGB.push_back({1, 2, 3});
//    }
//    csv.update_RGB(RGB, 4);


    // calculate brdf
    BRDF brdf2(wavelength, dl, csv.getSurfaceGeo(surface_num)[2], pitch, csv.getCameraPos(), csv.getRotAngle());
    std::vector<double> brdfs = brdf2.calc_all_frame_brdf();

    // convert2RGB
    std::vector<Eigen::Vector3d> rgb;


//    // update csv RGB data
//    csv.update_RGB(rgb, surface_num);
//    std::cout << "done" << std::endl;

    // output csv sample
    const std::string output_path = "./output_csv/sample_output.csv";
    csv.output_csv(output_path);


    return 0;
}
