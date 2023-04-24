#include <vector>
#include <cmath>
#include "FD_GUI_View_Graph.h"
#include <iostream>

FD_GUI_View_Graph::FD_GUI_View_Graph(int x, int y, int width, int height, const char *label)
    : Fl_Widget(x, y, width, height, label)
{
}

void FD_GUI_View_Graph::set_point_list(const std::vector<std::pair<double, double>> &pl, double a_b, double c_b)
{
    point_list = pl;
    a_border = a_b;
    c_border = c_b;
    redraw();
}

void FD_GUI_View_Graph::draw()
{
    const int axis_space{100};
    const int x_left = x(), y_up = y();
    const int x_right = x() + w() - 1, y_down = y() + h() - 1;
    const int x_min_graph_draw_pos = x_left + axis_space;
    const int x_max_graph_draw_pos = x_right - axis_space;
    const int y_min_graph_draw_pos = y_up + axis_space;
    const int y_max_graph_draw_pos = y_down - axis_space;
    const int x_graph_draw_size = x_max_graph_draw_pos - x_min_graph_draw_pos;
    const int y_graph_draw_size = y_max_graph_draw_pos - y_min_graph_draw_pos;
    // draw graph background area
    fl_color(FL_WHITE);
    fl_rectf(x(), y(), w() + 290, h());
    // draw axes
    fl_color(FL_BLACK);
    // graph y axis
    fl_line(x_min_graph_draw_pos, y_min_graph_draw_pos, x_min_graph_draw_pos, y_max_graph_draw_pos);
    // graph x axis
    fl_line(x_min_graph_draw_pos, y_max_graph_draw_pos, x_max_graph_draw_pos + effect, y_max_graph_draw_pos);
    const double x_axis_min_value{-5.0};
    const double x_axis_max_value{5.0};
    const double y_axis_min_value{0.0};
    const double y_axis_max_value{0.4};
    const double x_axis_value_interval{x_axis_max_value - x_axis_min_value};
    const double y_axis_value_interval{y_axis_max_value - y_axis_min_value};

    // *Verteilung eins

    if ((point_list.size() > 0) && ((point_list.size() % 2) == 1))
    {

        for (size_t i = 0; i < (point_list.size() - 1); i++)
        {
            fl_color(255, 0, 0);
            int x_start = x_min_graph_draw_pos + std::round(x_graph_draw_size * ((point_list.at(i).first - x_axis_min_value) / x_axis_value_interval));
            int x_end = x_min_graph_draw_pos + std::round(x_graph_draw_size * ((point_list.at(i + 1).first - x_axis_min_value) / x_axis_value_interval));
            int y_start = y_max_graph_draw_pos - std::round(y_graph_draw_size * ((point_list.at(i).second - y_axis_min_value) / y_axis_value_interval));
            int y_end = y_max_graph_draw_pos - std::round(y_graph_draw_size * ((point_list.at(i + 1).second - y_axis_min_value) / y_axis_value_interval));
            fl_line(x_start, y_start, x_end, y_end);
        }
    }

    // *Verteilung zwei
    fl_color(0, 0, 255);
    if ((point_list.size() > 0) && ((point_list.size() % 2) == 1))
    {
        for (size_t i = 0; i < (point_list.size() - 1); i++)
        {
            int x_start = x_min_graph_draw_pos + std::round(x_graph_draw_size * ((point_list.at(i).first - x_axis_min_value) / x_axis_value_interval));
            int x_end = x_min_graph_draw_pos + std::round(x_graph_draw_size * ((point_list.at(i + 1).first - x_axis_min_value) / x_axis_value_interval));
            int y_start = y_max_graph_draw_pos - std::round(y_graph_draw_size * ((point_list.at(i).second - y_axis_min_value) / y_axis_value_interval));
            int y_end = y_max_graph_draw_pos - std::round(y_graph_draw_size * ((point_list.at(i + 1).second - y_axis_min_value) / y_axis_value_interval));
            fl_line(x_start + effect, y_start, x_end + effect, y_end);
        }
    }

    // *Fehlergrenzen
    fl_color(180, 180, 180);
    // a Grenze
    fl_yxline(250, y_min_graph_draw_pos, y_max_graph_draw_pos);
    //  c Grenze

    fl_yxline(c_border, y_min_graph_draw_pos, y_max_graph_draw_pos);
}