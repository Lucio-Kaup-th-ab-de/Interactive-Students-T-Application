#include "doctest.h"
#include "FD_STAT_Util.h"


TEST_SUITE_BEGIN("FD_STAT_Util");
TEST_CASE("get pdf value for 1.976, df = 2") 
{
    FD_STAT_Util stat_util{};
    CHECK(stat_util.students_t_pdf(1.976, 2) == doctest::Approx(0.0696975));
}
TEST_CASE("get pdf value for 1.976, df = 8") 
{
    FD_STAT_Util stat_util{};
    CHECK(stat_util.students_t_pdf(1.976, 8) == doctest::Approx(0.0646495));
}

TEST_SUITE_END();