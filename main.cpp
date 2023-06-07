#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include <direct.h>
#include "CsvData.h"
#include "BRDF.h"
#include "./spectra/spectra_data.h"

void estimate_accuracy_one_surface(const int surface_index) {
    // set scene info
    Eigen::Vector3d dl(0, 1, 1);
    const int loop_num = 1 << 15;

    // csv file 3 - 13
    for(int i = 3; i < 14; ++i) {
        // set file data
        const int csv_file_num = i;
        std::string input_path = "./csv/result_" + std::to_string(csv_file_num) + ".csv";
        std::string output_path = "./output_csv/result_" + std::to_string(csv_file_num) + ".csv";

        // XYZ convert coefficient
        std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
        BRDF::set_spectra2XYZ_conversion(spectra2XYZ_conversion);

        // set scene data from csv
        CsvData csv(input_path);
        BRDF brdf(loop_num, dl, csv.getSurfaceGeo(surface_index)[2], csv.getSurfaceGeo(surface_index)[0], csv.getCameraPos(), csv.getRotAngle());

        // calc spectra
        std::vector<std::array<double, 16>> accumulation_spectras(0);
        brdf._calc_accumulate_all_angle(accumulation_spectras);

        // convert to RGB from spectra
        std::vector<Eigen::Vector3d> out_RGBs;
        BRDF::set_out_RGB(out_RGBs, brdf.getLoop(), spectra2XYZ_conversion, accumulation_spectras);

        // output csv
        csv.update_RGB(out_RGBs, surface_index);
        csv.output_csv(output_path);
    }
}

// todo : replacing the order of loops
void estimate_accuracy_each_surface() {
    // single surface index 3 - 47
    for(int i = 0; i < 47; ++i) {
        estimate_accuracy_one_surface(i);
    }
}


int main() {
//    estimate_accuracy_one_surface(9);
    estimate_accuracy_each_surface();

    return 0;
}
