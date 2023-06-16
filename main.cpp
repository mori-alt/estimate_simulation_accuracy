#include <iostream>
#include <filesystem>
#include <Eigen/Dense>
#include <random>
#include <direct.h>
#include "CsvData.h"
#include "BRDF.h"
#include "./spectra/spectra_data.h"


void calc_one_surface(CsvData& csv, const int surface_index) {
    const int loop_num = 1 << 10;
    const Eigen::Vector3d dl(0, 1, 1);

    BRDF brdf(loop_num, dl, csv.getSurfaceGeo(surface_index)[2], csv.getSurfaceGeo(surface_index)[0], csv.getCameraPos(), csv.getRotAngle());

    // XYZ convert coefficient
    std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
    BRDF::set_spectra2XYZ_conversion(spectra2XYZ_conversion);

    // calc spectra
    std::vector<std::array<double, 16>> accumulation_spectras(0);
    brdf.calc_accumulate_all_angle(accumulation_spectras);

    // convert to RGB from spectra
    std::vector<Eigen::Vector3d> out_RGBs;
    BRDF::set_out_RGB(out_RGBs, brdf.getLoop(), spectra2XYZ_conversion, accumulation_spectras);

    // output csv
    csv.update_RGB(out_RGBs, surface_index);
    csv.output_csv();
}

void calc_one_csv(const int csv_file_num){
    std::string input  = "./csv/result_" + std::to_string(csv_file_num) + ".csv";
    std::string output = "./output_csv/result_" + std::to_string(csv_file_num) + ".csv";

    CsvData csv(input, output);

    for(int surface_idx = 0; surface_idx < 48; surface_idx++){
        calc_one_surface(csv, surface_idx);
    }
}

// calc all geometry
void estimate_accuracy_single_surface(){
    for(int csv_idx = 3; csv_idx < 14; ++csv_idx){
        calc_one_csv(csv_idx);
    }
}

// calc one geometry (one circle
void estimate_accuracy_one_surface(const int surface_index) {
    // set scene info
    Eigen::Vector3d dl(0, 1, 1);
    const int loop_num = 1 << 10;

    // csv file 3 - 13
    for(int i = 3; i < 14; ++i) {
        // set file data
        const int csv_file_num = i;
        std::string input_path = "./csv/result_" + std::to_string(csv_file_num) + ".csv";
        std::string output_path = "./output_csv/result_" + std::to_string(csv_file_num) + ".csv";

        // set scene data from csv
        CsvData csv(input_path, output_path);
        BRDF brdf(loop_num, dl, csv.getSurfaceGeo(surface_index)[2], csv.getSurfaceGeo(surface_index)[0], csv.getCameraPos(), csv.getRotAngle());

        // matrix spectra to XYZ
        std::vector<Eigen::Vector3d> spectra2XYZ_conversion;
        BRDF::set_spectra2XYZ_conversion(spectra2XYZ_conversion);

        // calc spectra
        std::vector<std::array<double, 16>> accumulation_spectras(0);
        brdf.calc_accumulate_all_angle(accumulation_spectras);

        // convert to RGB ( spectra -> XYZ -> RGB )
        std::vector<Eigen::Vector3d> out_RGBs;
        BRDF::set_out_RGB(out_RGBs, brdf.getLoop(), spectra2XYZ_conversion, accumulation_spectras);

        // output csv
        csv.update_RGB(out_RGBs, surface_index);
        csv.output_csv();
    }
}


int main() {
//    estimate_accuracy_one_surface(0);
//    estimate_accuracy_each_surface();
    estimate_accuracy_single_surface();


    return 0;
}
