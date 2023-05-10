//
// Created by wd230 on 2023/05/09.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_BRDF_H
#define ESTIMATE_SIMULATION_ACCURACY_BRDF_H


#include <Eigen/Dense>
#include <cmath>
#include "CsvData.h"
#include "random/random.h"

// fixme なんかcmathの定数が呼び出せないからごり押し解決
const double M_PI = 3.141592653589793;

class Light{
private:
    double wavelength_;
    Eigen::Vector3d dl_;

public:
    Light(){

    }

    Light(double wavelength, const Eigen::Vector3d& dl){
        wavelength_ = wavelength;
        dl_ = dl.normalized();
    }

    double getWavelength() const {
        return wavelength_;
    }

    void setWavelength(double wavelength) {
        wavelength_ = wavelength;
    }

    const Eigen::Vector3d &getDl() const {
        return dl_;
    }

    void setDl(const Eigen::Vector3d &dl) {
        dl_ = dl;
    }
};

class SurfaceGeometry{
private:
    double amplitude_;  // pdf出力の一番右の値にすればいい気がする（深さなので
    double pitch_;  // 傷の付け方が直線的で，結局sinになっているらしいけど詳しいこと分からないら適当に作ること
    Eigen::Vector3d dv_; // カメラの方向にあたる

public:
    SurfaceGeometry(){

    }

    SurfaceGeometry(double amplitude, double pitch, Eigen::Vector3d dv){
        amplitude_ = amplitude;
        pitch_ = pitch;
        dv_ = dv.normalized();
    }

    double getAmplitude() const {
        return amplitude_;
    }

    void setAmplitude(double amplitude) {
        amplitude_ = amplitude;
    }

    double getPitch() const {
        return pitch_;
    }

    void setPitch(double pitch) {
        pitch_ = pitch;
    }

    const Eigen::Vector3d &getDv() const {
        return dv_;
    }

    void setDv(const Eigen::Vector3d &dv) {
        dv_ = dv;
    }
};

class BRDF{
private:
    CsvData csv_;
    Light light_;
    SurfaceGeometry geo_;


public:
    // 必要な情報はここで読むこと
    BRDF(CsvData csv){
        csv_ = csv;

        // 光源情報の作成
        Light light{375, {0, 1, 1}};
        light_ = light;


    }

    double eval_sinusoidal_brdf( const Eigen::Vector2d& in_random_st )
    {
        using namespace std::complex_literals;

        const float g_c = 50.0; //[um]  表面構造の一辺の長さ
        const auto k = 2.0 * M_PI / (light_.getWavelength() * 1.0e-9);
        const auto A = geo_.getAmplitude() * 1.0e-9;
        const auto L = geo_.getPitch() * 1.0e-9;
        const auto c = g_c * 1.0e-6;

        const Eigen::Vector3d dh_bar = 0.5 * (light_.getDl() + geo_.getDv());

        const auto factor = ( dh_bar.z() == 0.0 ) ? c : ( std::exp( k * c * dh_bar.z() * 1.0i ) - std::exp( -k * c * dh_bar.z() * 1.0i ) ) / ( 2.0i * k * dh_bar.z() );

        // 計算する点の指定　辺の長さで決めてる
        const auto _x1 = ( in_random_st.x() - 0.5 ) * c;
        const auto _x2 = ( in_random_st.y() - 0.5 ) * c;
        const auto _integral_x1_ = std::exp( -2.0i * k * ( _x1 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x1/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x1/L )*dh_bar.x()/L + dh_bar.y() );
        const auto _integral_x2_ = std::exp( -2.0i * k * ( _x2 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x2/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x2/L )*dh_bar.x()/L + dh_bar.y() );
        const auto iota_x1 = factor * _integral_x1_ * c;
        const auto iota_x2 = factor * _integral_x2_ * c;

        return k * k * ( iota_x1 * std::conj(iota_x2) ).real() / ( 4.0 * M_PI * M_PI * c * c * light_.getDl().y() * geo_.getDv().y() );
    }

//    繰り返し処理の計算
    double estimate_brdf(const int loop_freq){
        auto total_brdf_value = 0.0;
#pragma omp parallel for
        for(int i = 0; i < loop_freq; i++){
            Eigen::Vector2d brdf_st;
            brdf_st << randomMT(), randomMT();
            const auto brdf_value = eval_sinusoidal_brdf( brdf_st );
            total_brdf_value += brdf_value;
        }
        auto brdf = total_brdf_value / loop_freq;

        return brdf;
    }

    const CsvData &getCsv() const {
        return csv_;
    }

    void setCsv(const CsvData &csv) {
        csv_ = csv;
    }

    const Light &getLight() const {
        return light_;
    }

    void setLight(const Light &light) {
        light_ = light;
    }

    const SurfaceGeometry &getGeo() const {
        return geo_;
    }

    void setGeo(const SurfaceGeometry &geo) {
        geo_ = geo;
    }

};

#endif //ESTIMATE_SIMULATION_ACCURACY_BRDF_H
