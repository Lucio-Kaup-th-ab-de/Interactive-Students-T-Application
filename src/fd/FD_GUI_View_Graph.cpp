#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "FD_GUI_View_Graph.h"
#include <iostream>

FD_GUI_View_Graph::FD_GUI_View_Graph(int x, int y, int width, int height, const char *label)
    : Fl_Widget(x, y, width, height, label), first_draw(true)
{
}

void FD_GUI_View_Graph::set_point_list(const std::vector<std::pair<double, double>> &pl, double a_b, double c_b, double ef)
{
    point_list = pl;
    a_border = a_b;
    c_border = c_b;
    effect = ef;
    redraw();
}

void FD_GUI_View_Graph::draw()
{
    const int axis_space{60};
    const int x_left = x(), y_up = y();
    const int x_right = x() + w() - 1, y_down = y() + h() - 1;
    const int x_min_graph_draw_pos = x_left + axis_space;
    int x_max_graph_draw_pos = x_right - axis_space + effect;
    const int y_min_graph_draw_pos = y_up + axis_space;
    const int y_max_graph_draw_pos = y_down - axis_space;
    const int x_graph_draw_size = x_max_graph_draw_pos - x_min_graph_draw_pos;
    const int y_graph_draw_size = y_max_graph_draw_pos - y_min_graph_draw_pos;
    const double x_axis_min_value{-5.0};
    const double x_axis_max_value{5.0};
    const double y_axis_min_value{0.0};
    const double y_axis_max_value{0.4};
    const double x_axis_value_interval{x_axis_max_value - x_axis_min_value};
    const double y_axis_value_interval{y_axis_max_value - y_axis_min_value};

    // draw Scale
    if (first_draw) // Zeichnet die Skala nur beim ersten Zeichnen
    {

        // draw graph background area
        fl_color(FL_WHITE);
        fl_rectf(x(), y(), w() + 290, h());

        // *draw axes
        fl_color(FL_BLACK);
        // graph y axis
        fl_line(x_min_graph_draw_pos, y_min_graph_draw_pos, x_min_graph_draw_pos, y_max_graph_draw_pos);
        // graph x axis
        fl_line(x_min_graph_draw_pos, y_max_graph_draw_pos, x_max_graph_draw_pos, y_max_graph_draw_pos);
        const int scale_fontsize = 12;
        fl_font(FL_HELVETICA, scale_fontsize);
        // x-Scale
        const double x_scale_interval{x_axis_value_interval / 20};
        for (double value = x_axis_min_value; value <= x_axis_max_value; value += x_scale_interval)
        {
            double x_position = x_min_graph_draw_pos + ((value - x_axis_min_value) * x_graph_draw_size) / x_axis_value_interval;
            fl_line(x_position, y_max_graph_draw_pos - 5, x_position, y_max_graph_draw_pos + 5);
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << value;
            std::string value_str = ss.str();
            fl_draw(value_str.c_str(), x_position - 8, y_max_graph_draw_pos + scale_fontsize + 5);
        }
        // x-axis label
        fl_draw("X-Achse", x_max_graph_draw_pos, y_max_graph_draw_pos + 30);
        // y-Scale
        const double y_scale_interval{y_axis_value_interval / 10};
        for (double value = y_axis_min_value; value <= y_axis_max_value + 0.01; value += y_scale_interval)
        {
            double y_position = y_max_graph_draw_pos - ((value - y_axis_min_value) * y_graph_draw_size) / y_axis_value_interval;
            fl_line(x_min_graph_draw_pos - 5, y_position, x_min_graph_draw_pos + 5, y_position);
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << value;
            std::string value_str = ss.str();
            fl_draw(value_str.c_str(), x_min_graph_draw_pos - 20 - scale_fontsize, y_position + 5);
        }
        // y-axis label
        fl_draw("Y-Achse", x_min_graph_draw_pos - 50, y_min_graph_draw_pos - 20);
        // first_draw = false; //*Steuert, ob das blanke Koordiantensystem nur einmal oder immer aufs neue gezeichnet wird
    }

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
            if (x_start >= x_min_graph_draw_pos && x_end <= x_max_graph_draw_pos)
            {
                fl_line(x_start, y_start, x_end, y_end);
            }
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
            if (x_start >= x_min_graph_draw_pos - effect && x_end <= x_max_graph_draw_pos - effect)
            {
                fl_line(x_start + effect, y_start, x_end + effect, y_end);
            }
        }
    }

    // *Fehlergrenzen
    fl_color(180, 180, 180);
    // a Grenze
    fl_yxline(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((a_border - x_axis_min_value) / x_axis_value_interval)), y_min_graph_draw_pos, y_max_graph_draw_pos);
    //  c Grenze
    fl_yxline(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((c_border - x_axis_min_value) / x_axis_value_interval)), y_min_graph_draw_pos, y_max_graph_draw_pos);
}