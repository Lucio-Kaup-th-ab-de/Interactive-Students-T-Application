#include "FD_STAT_Util.h"
#include <boost/math/distributions/students_t.hpp>

// Berechnet die Wahrscheinlichkeit eines bestimmten Wertes
double FD_STAT_Util::students_t_pdf(double x, int df)
{
    double degrees_of_freedom = static_cast<double>(df);
    boost::math::students_t dist_stud_t{degrees_of_freedom};
    double result = boost::math::pdf(dist_stud_t, x);
    return result;
}

// Berechnet die Kumulative Wahrscheinlichkeit bis zu einem Punkt (=> Integral der Fläche)
//TODO evtl noch löschen, da nur Quantilfunktion gebraucht wird
double FD_STAT_Util::students_t_cdf(double x, int df)
{
    double degrees_of_freedom = static_cast<double>(df);
    boost::math::students_t dist_stud_t{degrees_of_freedom};
    double result = boost::math::cdf(dist_stud_t, x);
    return result;
}

// Berechnet die Quantile
double FD_STAT_Util::students_t_quantile(double alpha, int df)
{
    double degrees_of_freedom = static_cast<double>(df);
    boost::math::students_t dist_stud_t{degrees_of_freedom};
    double result = boost::math::quantile(dist_stud_t, alpha);
    return result;
}
