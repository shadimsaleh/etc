#ifndef __DIST_UTIL_H__
#define __DIST_UTIL_H__

#include <hrpUtil/Eigen3d.h>

double pointLineSegmentDistance(const hrp::Vector3 &p,
                                const hrp::Vector3 &p1,
                                const hrp::Vector3 &p2);

double SegSegDist(const hrp::Vector3& u0, const hrp::Vector3& u1,
                  const hrp::Vector3& v0, const hrp::Vector3& v1);

#endif
