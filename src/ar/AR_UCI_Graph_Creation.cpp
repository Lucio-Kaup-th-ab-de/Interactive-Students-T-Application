#include "AR_UCI_Graph_Creation.h"

AR_UCI_Graph_Creation::AR_UCI_Graph_Creation(
    AR_UCI_Graph_Creation_OB &presenter,
    AR_STAT_Util_I &s)
    : graph_presenter(presenter), stat_util(s){};

void AR_UCI_Graph_Creation::create_graph(int df, double alpha)
{
  std::vector<std::pair<double, double>> point_list{};
  double y{0};
  for (double x = -5.0; x <= 5.0; x = x + 0.1)
  {
    point_list.push_back(std::pair<double, double>{x, stat_util.students_t_pdf(x, df)});
  }
  a_border = std::round(stat_util.students_t_cdf(alpha, df) * 10.0) / 10.0;
  c_border = std::round(stat_util.students_t_cdf(1 - alpha, df) * 10.0) / 10.0;
  graph_presenter.present_graph(point_list, a_border, c_border);
};
