#include "FD_STAT_Util.h"
#include <boost/math/distributions/students_t.hpp>
double FD_STAT_Util::students_t_pdf(double x, int df){
    double degrees_of_freedom = static_cast<double>(df);    
    boost::math::students_t dist_stud_t{degrees_of_freedom};
    double result = boost::math::pdf(dist_stud_t, x);
    return result;
}
