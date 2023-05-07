#ifndef FD_GUI_VIEW_GRAPH_H
#define FD_GUI_VIEW_GRAPH_H
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class FD_GUI_View_Graph : public Fl_Widget
{
public:
    FD_GUI_View_Graph(int x, int y, int width, int height, const char *label);
    void draw();
    void set_point_list(const std::vector<std::pair<double, double>> &pl,
                        double a_b,
                        double c_b,
                        double ef,
                        double p,
                        double b);
    void draw_area(double left_border,
                   double right_border,
                   const std::vector<std::pair<double, double>> &point_list,
                   int x_min_gdp,
                   int x_max_gdp,
                   int y_max_gdp,
                   int x_gds,
                   int y_gds,
                   double x_aminv,
                   double x_amaxv,
                   double y_amv,
                   double x_avi,
                   double y_avi,
                   double effect);

private:
    double find_y_value_for_x(const std::vector<std::pair<double, double>> &point_list, double x);
    std::vector<std::pair<double, double>> point_list{};
    double a_border{};
    double c_border{};
    double effect{};
    double power{};
    double beta{};
    bool first_draw;
};

#endif /* FD_GUI_VIEW_GRAPH_H */