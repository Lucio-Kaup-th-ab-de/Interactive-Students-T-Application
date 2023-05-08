#include "AR_UCI_Graph_Creation.h"

AR_UCI_Graph_Creation::AR_UCI_Graph_Creation(
    AR_UCI_Graph_Creation_OB &presenter,
    AR_STAT_Util_I &s)
    : graph_presenter(presenter), stat_util(s){};

void AR_UCI_Graph_Creation::create_graph(int df, double alpha, double input_effect)
{
  std::vector<std::pair<double, double>> point_list{};
  for (double x = -10.0; x <= 10.0; x += 0.1)
  {
    double y = stat_util.students_t_pdf(x, df);
    point_list.push_back(std::pair<double, double>{x, y});
  }

  // Berechne a_border und c_border mit der Quantilfunktion
  a_border = stat_util.students_t_quantile(alpha / 2, df);
  c_border = stat_util.students_t_quantile(1 - alpha / 2, df);

  // Runde a_border und c_border auf 0,1, damit die Flächen besser an die Grenzen anschließen
  a_border = round(a_border * 10) / 10.0;
  c_border = round(c_border * 10) / 10.0;

  effect = input_effect;

  // Power- und Beta-Berechnung
  double t_critical = stat_util.students_t_quantile(1 - alpha, df);
  double t_shifted = (t_critical * sqrt(df) - (effect / 80) * sqrt(df + 1)) / sqrt(df);
  power = 1 - stat_util.students_t_cdf(t_shifted, df);
  beta = 1 - power;

  graph_presenter.present_graph(point_list, a_border, c_border, effect, power, beta);
  graph_presenter.present_outputs(power, beta);
};
