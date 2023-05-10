//
// Created by wd230 on 2023/05/09.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_BRDF_H
#define ESTIMATE_SIMULATION_ACCURACY_BRDF_H
#define _USE_MATH_DEFINES

#include <Eigen/Dense>
#include <cmath>
#include "CsvData.h"
#include "random/random.h"

struct Light{ // 光源情報はまだ仮でおくだけだから適当に定義すること
    double wavelength;
    Eigen::Vector3d dl;
};

struct SurfaceGeometry{
    double amplitude;  // pdf出力の一番右の値にすればいい気がする（深さなので
    double pitch;  // 傷の付け方が直線的で，結局sinになっているけど詳しいこと分からないら適当に作ること
    Eigen::Vector3d dv;
};

struct Scene{
    SurfaceGeometry geo;
    Light light;
};

class BRDF{
private:
    CsvData csv_;


public:
    BRDF(CsvData csv){
        csv_ = csv;
    }

    double eval_sinusoidal_brdf( const double in_wave_length, const Eigen::Vector2d& in_random_st, const Eigen::Vector3d& in_dl, const Eigen::Vector3d& in_dv, const double amplitude, const double pitch )
    {
        using namespace std::complex_literals;

        const float g_c = 50.0; //[um]  表面構造の一辺の長さ
        const auto k = 2.0 * M_PI / (in_wave_length * 1.0e-9);
        const auto A = amplitude * 1.0e-9;
        const auto L = pitch * 1.0e-9;
        const auto c = g_c * 1.0e-6;

        const Eigen::Vector3d dh_bar = 0.5 * (in_dl + in_dv);

        const auto factor = ( dh_bar.z() == 0.0 ) ? c : ( std::exp( k * c * dh_bar.z() * 1.0i ) - std::exp( -k * c * dh_bar.z() * 1.0i ) ) / ( 2.0i * k * dh_bar.z() );

        // 計算する点の指定　辺の長さで決めてる
        const auto _x1 = ( in_random_st.x() - 0.5 ) * c;
        const auto _x2 = ( in_random_st.y() - 0.5 ) * c;
        const auto _integral_x1_ = std::exp( -2.0i * k * ( _x1 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x1/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x1/L )*dh_bar.x()/L + dh_bar.y() );
        const auto _integral_x2_ = std::exp( -2.0i * k * ( _x2 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x2/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x2/L )*dh_bar.x()/L + dh_bar.y() );
        const auto iota_x1 = factor * _integral_x1_ * c;
        const auto iota_x2 = factor * _integral_x2_ * c;

        return k * k * ( iota_x1 * std::conj(iota_x2) ).real() / ( 4.0 * M_PI * M_PI * c * c * in_dl.y() * in_dv.y() );
    }

//    繰り返し処理の計算
    double estimate_brdf(const int loop_freq, const double in_wavelength, const Eigen::Vector2d& in_random_st, const Eigen::Vector3d& dl, const Eigen::Vector3d& dv, const double amplitude, const double pitch){
        auto total_brdf_value = 0.0;
#pragma omp parallel for
        for(int i = 0; i < loop_freq; i++){
            Eigen::Vector2d brdf_st;
            brdf_st << randomMT(), randomMT();
            const auto brdf_value = eval_sinusoidal_brdf(in_wavelength, brdf_st, dl, dv, amplitude, pitch);
            total_brdf_value += brdf_value;
        }
        auto brdf = total_brdf_value / loop_freq;

        return brdf;
    }

    const CsvData &getCsvData() const {
        return csv_;
    }

    void setCsvData(CsvData csv){
        csv_ = csv;
    }

};

#endif //ESTIMATE_SIMULATION_ACCURACY_BRDF_H
