#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include <direct.h>
#include "CsvData.h"
#include "BRDF.h"
#include "./spectra/spectra_data.h"

void estimate_accuracy() {
    // set scene info
    const auto NSPECT = 16;
    const auto light_intensity = 0.25;
    Eigen::Vector3d dl(0, 1, 1);
    const int loop_num = 1 << 15;

    for(int i = 3; i < 14; ++i) {
        // set file data
        const int csv_file_num = i;
        const int surface_index = 0;
        std::string input_path = "./csv/result_" + std::to_string(csv_file_num) + ".csv";
        std::string output_path = "./output_csv/result_" + std::to_string(csv_file_num) + ".csv";

        // XYZ convert coefficient
        std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
        BRDF::set_spectra2XYZ_conversion(spectra2XYZ_conversion);

        // set scene data from csv
        CsvData csv(input_path);
        BRDF brdf(loop_num, dl, csv.getSurfaceGeo(surface_index)[2], csv.getSurfaceGeo(surface_index)[0], csv.getCameraPos(), csv.getRotAngle());

        brdf.show_member();

        // calc spectra
        std::vector<std::array<double, 16>> accumulation_spectras(0);
        brdf._calc_accumulate_all_angle(accumulation_spectras);

        // convert to RGB from spectra
        std::vector<Eigen::Vector3d> out_RGBs;
        BRDF::set_out_RGB(out_RGBs, brdf.getLoop(), spectra2XYZ_conversion, accumulation_spectras);

        for(auto& d : out_RGBs) {
            d[0] = int(d[0]);
            d[1] = int(d[1]);
            d[2] = int(d[2]);
        }

        std::cout << out_RGBs[0].transpose() << std::endl;

        // output csv
        csv.update_RGB(out_RGBs, surface_index);
        csv.output_csv(output_path);
    }
}

int main() {
    estimate_accuracy();
//    // XYZ convert coefficient
//    std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
//    spectra2XYZ_conversion.clear();
//    BRDF::set_spectra2XYZ_conversion(spectra2XYZ_conversion);
//
//    for(auto i : spectra2XYZ_conversion) {
//        std::cout << i.transpose() << std::endl;
//    }
//
//    std::vector<Eigen::Vector3d> out_RGB;
//    std::vector<std::array<double, 16>> accumulation_spectra;
//    accumulation_spectra.push_back({750});
//    BRDF::set_out_RGB(out_RGB, 1, spectra2XYZ_conversion, accumulation_spectra);
//
//    std::cout << "out_rgb" << std::endl;
//    std::cout << out_RGB[0].transpose() << std::endl;


    return 0;
}
