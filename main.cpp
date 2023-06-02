#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include "CsvData.h"
#include "BRDF.h"
#include "./spectra/spectra_data.h"


int main() {
    // set scene info
    const auto DL = 25;
    const auto NSPECT = 16;
    const int WAVELENGTHS[NSPECT] = { 375, 400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750 };
    const auto light_intensity = 0.25;
    const double wavelength = 375;
    const int surface_num = 3;
    std::vector<int> wavelengths;
    std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
    std::array<double, NSPECT> accumulation_spectra;

    wavelengths.clear();
    spectra2XYZ_conversion.clear();

    // set XYZ_data conversion
    for(auto i = 0; i < NSPECT; ++i){
        wavelengths.push_back( WAVELENGTHS[i]);
        Eigen::Vector3d XYZ_data;
        getXYZForSpectraWindow(WAVELENGTHS[i], DL, XYZ_data);
        spectra2XYZ_conversion.push_back( XYZ_data);
    }

    std::cout << "spectra2XYZ_conversion" << std::endl;
    std::cout << spectra2XYZ_conversion.size() << std::endl;
    for(Eigen::Vector3d d : spectra2XYZ_conversion) std::cout << d.transpose() << std::endl;

    // set scene data from csv
    const double pitch = 600;
    const int loop_num = 1 << 15;
    Eigen::Vector3d dl(0, 1, 1);
    CsvData csv("./csv/result_3.csv");
    BRDF brdf(wavelength, dl, csv.getSurfaceGeo(surface_num)[2], pitch, csv.getCameraPos(), csv.getRotAngle());

    // calc spectra
    auto _brdf = 0.0;
    std::vector<double> accumulate_spectras;
    brdf.calc_accumulate_all_angle(accumulate_spectras, loop_num);
    std::cout << "accumulate vector size : " << accumulate_spectras.size() << std::endl;

    // convert to RGB from spectra
    std::vector<Eigen::Vector3d> rgb;
    convertSpectraData2RGB(rgb, NSPECT, spectra2XYZ_conversion, accumulation_spectra, light_intensity);

    // output csv sample
    const std::string output_path = "./output_csv/sample_output.csv";
    csv.output_csv(output_path);


    return 0;
}
