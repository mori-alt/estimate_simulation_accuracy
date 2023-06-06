#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include "CsvData.h"
#include "BRDF.h"
#include "./spectra/spectra_data.h"


int main() {
    // set scene info
    const auto NSPECT = 16;
    const auto light_intensity = 0.25;
    const int surface_index = 0;

    // XYZ convert coefficient
    std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
    spectra2XYZ_conversion.clear();
    BRDF::set_spectra2XYZ_conversion(spectra2XYZ_conversion);

    // set scene data from csv
    const int loop_num = 1 << 15;
    Eigen::Vector3d dl(0, 1, 1);
    CsvData csv("./csv/result_3.csv");
    BRDF brdf(loop_num, dl, csv.getSurfaceGeo(surface_index)[2], csv.getSurfaceGeo(surface_index)[0], csv.getCameraPos(), csv.getRotAngle());

    brdf.show_member();

    // calc spectra
    std::vector<std::array<double, 16>> accumulation_spectras(0);
    brdf._calc_accumulate_all_angle(accumulation_spectras);

    // convert to RGB from spectra
    std::vector<Eigen::Vector3d> out_RGBs;
    for(std::array<double, 16> brdf_spectra : accumulation_spectras) {
        Eigen::Vector3d rgb = Eigen::Vector3d::Zero();
        convertSpectraData2RGB(rgb, NSPECT, spectra2XYZ_conversion, brdf_spectra, light_intensity / brdf.getLoop());
        out_RGBs.push_back(rgb);
    }

    // output csv
    csv.update_RGB(out_RGBs, surface_index);
    const std::string output_path = "./output_csv/sample_output.csv";
    csv.output_csv(output_path);


    return 0;
}
