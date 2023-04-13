#ifndef AR_STAT_UTIL_I_H
#define AR_STAT_UTIL_I_H

class AR_STAT_Util_I {
   public:
      virtual double students_t_pdf(double x, int df) = 0;
      virtual double students_t_cdf(double x, int df) = 0;

      virtual ~AR_STAT_Util_I() = default;
      AR_STAT_Util_I() = default;
      AR_STAT_Util_I(const AR_STAT_Util_I&) = default;
      AR_STAT_Util_I& operator=(const AR_STAT_Util_I&) = default;
};

#endif /* AR_STAT_UTIL_I_H */