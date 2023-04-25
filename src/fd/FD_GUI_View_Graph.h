#ifndef FD_GUI_VIEW_GRAPH_H
#define FD_GUI_VIEW_GRAPH_H
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class FD_GUI_View_Graph : public Fl_Widget
{
public:
    FD_GUI_View_Graph(int x, int y, int width, int height, const char *label);
    void draw();
    void set_point_list(const std::vector<std::pair<double, double>> &pl, double a_border, double c_border, double ef);

private:
    std::vector<std::pair<double, double>> point_list{};
    double a_border{5}; //! Anfangswerte noch anpassen
    double c_border{10};
    double effect{};
    double alpha{5};
};

#endif /* FD_GUI_VIEW_GRAPH_H */