/**
@file
@brief Helper functions

Use of this source code is governed by a BSD-style license that can be found in
the LICENSE file.
*/

#ifndef TINYNURBS_UTIL
#define TINYNURBS_UTIL

#include <glm/glm.hpp>
#include <vector>

namespace tinynurbs {
namespace util {

/**
Convert an nd point in homogenous coordinates to an (n-1)d point in cartesian
coordinates by perspective division
@param[in] pt Point in homogenous coordinates
@return Input point in cartesian coordinates
*/
template<int nd, typename T>
inline glm::vec<nd - 1, T> homogenousToCartesian(const glm::vec<nd, T> &pt) {
    return glm::vec<nd - 1, T>(pt / pt[pt.length() - 1]);
}

/**
Convert an nd point in cartesian coordinates to an (n+1)d point in homogenous
coordinates
@param[in] pt Point in cartesian coordinates
@param[in] w Weight
@return Input point in homogenous coordinates
*/
template<int nd, typename T>
inline glm::vec<nd + 1, T> cartesianToHomogenous(const glm::vec<nd, T> &pt, T w) {
    return glm::vec<nd + 1, T>(pt * w, w);
}

/**
Convert an (n+1)d point to an nd point without perspective division
by truncating the last dimension
@param[in] pt Point in homogenous coordinates
@return Input point in cartesian coordinates
*/
template<int nd, typename T>
inline glm::vec<nd - 1, T> truncateHomogenous(const glm::vec<nd, T> &pt) {
    return glm::vec<nd - 1, T>(pt);
}

/**
Compute the binomial coefficient (nCk) using the formula
\product_{i=0}^k (n + 1 - i) / i
*/
inline unsigned int binomial(unsigned int n, unsigned int k) {
    unsigned int result = 1;
    if (k > n) {
        return 0;
    }
    for (unsigned int i = 1; i <= k; ++i) {
        result *= (n + 1 - i);
        result /= i;
    }
    return result;
}

/**
Check if two numbers are close enough within eps
*/
template <typename T>
inline bool close(T a, T b, double eps = std::numeric_limits<T>::epsilon()) {
    return (std::abs(a - b) < eps) ? true : false;
}

/**
Map numbers from one interval to another
*/
template <typename T>
inline T mapToRange(T val, T old_min, T old_max, T new_min, T new_max) {
    T old_range = old_max - old_min;
    T new_range = new_max - new_min;
    return (((val - old_min) * new_range) / old_range) + new_min;
}

} // namespace util

} // namespace tinynurbs

#endif // TINYNURBS_UTIL
