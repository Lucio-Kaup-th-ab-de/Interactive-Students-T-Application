#ifndef FD_STAT_UTIL_H
#define FD_STAT_UTIL_H
#include "AR_STAT_Util_I.h"

class FD_STAT_Util : public AR_STAT_Util_I {
   public:
      double students_t_pdf(double x, int df) override;
      //*Hier evtl. CDF implementieren
      double students_t_cdf(double x, int df) override;
};

#endif /* FD_STAT_UTIL_H */