#ifndef __SPECTRUM_DATA_H__
#define __SPECTRUM_DATA_H__

#include <Eigen/Dense>
#include <vector>

void getXYZForSpectraWindow( const unsigned long in_Lambda, const unsigned long in_DeltaLambda, Eigen::Vector3d& out_XYZ );
void convertSpectraData2RGB( Eigen::Vector3d& out_RGB, const int in_NumSpect, const std::vector<Eigen::Vector3d>& in_Spectra2XYZ, const std::vector<double>& in_SpectraData, const double in_Ratio );

#endif
