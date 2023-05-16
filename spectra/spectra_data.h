#ifndef __SPECTRUM_DATA_H__
#define __SPECTRUM_DATA_H__

#include <Eigen/Dense>
#include <vector>

void getXYZForSpectraWindow( const unsigned long in_Lambda, const unsigned long in_DeltaLambda, Eigen::Vector3d& out_XYZ );
Eigen::Vector3d convertSpectraData2RGB( const int in_NumSpect, const std::vector<Eigen::Vector3d>& in_Spectra2XYZ, const double* in_SpectraData, const double in_Ratio );

#endif
