#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <memory>
#include "FD_GUI_View_Graph.h"
#include <iostream>

FD_GUI_View_Graph::FD_GUI_View_Graph(int x, int y, int width, int height, const char *label)
    : Fl_Widget(x, y, width, height, label), first_draw(true)
{
}

void FD_GUI_View_Graph::set_point_list(const std::vector<std::pair<double, double>> &pl,
                                       double a_b,
                                       double c_b,
                                       double ef,
                                       double p,
                                       double b)
{
    point_list = pl;
    a_border = a_b;
    c_border = c_b;
    effect = ef;
    power = p;
    beta = b;
    redraw();
}

void FD_GUI_View_Graph::draw_area(double left_border,
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
                                  double effect)
{
    const double x_min_graph_draw_pos = static_cast<double>(x_min_gdp);
    const double x_max_graph_draw_pos = static_cast<double>(x_max_gdp);
    const double y_max_graph_draw_pos = static_cast<double>(y_max_gdp);
    const double x_graph_draw_size = static_cast<double>(x_gds);
    const double y_graph_draw_size = static_cast<double>(y_gds);
    const double x_axis_min_value = x_aminv;
    const double x_axis_max_value = x_amaxv;
    const double y_axis_min_value = y_amv;
    const double x_axis_value_interval = x_avi;
    const double y_axis_value_interval = y_avi;

    fl_begin_polygon();
    // Begrenzungen, falls die Grenzen außerhalb des Graphen liegen
    //links
    if (left_border <= -5.0)
    {
        left_border = -5.0;
    }
    if (right_border <= -5.0)
    {
        right_border = -5.0;
    }
    //rechts
    if (left_border >= 7.5)
    {
        left_border = 7.5;
    }
    if (right_border >= 7.5)
    {
        right_border = 7.5;
    }
    fl_vertex(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((left_border - x_axis_min_value) / x_axis_value_interval)), y_max_graph_draw_pos); // Linke Untere Ecke der Fläche
    double left_border_y_val = find_y_value_for_x(point_list, left_border - effect);
    double left_border_y = y_max_graph_draw_pos - std::round(y_graph_draw_size * ((left_border_y_val - y_axis_min_value) / y_axis_value_interval));
    fl_vertex(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((left_border - x_axis_min_value) / x_axis_value_interval)), left_border_y); // Linke Obere Ecke der Fläche

    for (size_t i = 0; i < point_list.size(); i++)
    {
        if (point_list.at(i).first <= 7.5)
        {
            double x_val = point_list.at(i).first;
            if (effect != 0)
            {
                x_val += effect / 80;
            }
            double y_val = point_list.at(i).second;

            if (x_val >= left_border && x_val <= right_border && x_val <= x_axis_max_value)
            {
                double x = x_min_graph_draw_pos + std::round(x_graph_draw_size * ((x_val - x_axis_min_value) / x_axis_value_interval));
                double y = y_max_graph_draw_pos - std::round(y_graph_draw_size * ((y_val - y_axis_min_value) / y_axis_value_interval));
                fl_vertex(x, y);
            }
        }
    }
    fl_vertex(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((right_border - x_axis_min_value) / x_axis_value_interval)), y_max_graph_draw_pos);
    fl_end_polygon();
}

void FD_GUI_View_Graph::draw()
{
    // TODO Reihenfolge der Zeichnung noch final so anpassen, dass alles übersichtlich ist
    // TODO Startwert vom Effekt noch anpassen
    // TODO Farben der Flächen verbessern
    // Einstellungen
    fl_antialias(1); //* Kann optional zur Kantenglättung verwendet werden (1) verringert allerdings die Performance des Programms
    int graph_line_width = 3;
    int axis_line_width = 2;

    // Zeichenwerte
    const int axis_space{60};
    const int x_left = x(), y_up = y();
    const int x_right = x() + w() - 0, y_down = y() + h() - 1;
    const int x_min_graph_draw_pos = x_left + axis_space;
    const int x_max_graph_draw_pos = x_right - axis_space; // ! vllt macht const hier noch Probleme
    const int y_min_graph_draw_pos = y_up + axis_space;
    const int y_max_graph_draw_pos = y_down - axis_space;
    const int x_graph_draw_size = x_max_graph_draw_pos - x_min_graph_draw_pos;
    const int y_graph_draw_size = y_max_graph_draw_pos - y_min_graph_draw_pos;
    const double x_axis_min_value{-5.0};
    const double x_axis_max_value{7.5};
    const double y_axis_min_value{0.0};
    const double y_axis_max_value{0.4};
    const double x_axis_value_interval{x_axis_max_value - x_axis_min_value};
    const double y_axis_value_interval{y_axis_max_value - y_axis_min_value};

    // draw graph background area
    fl_color(FL_WHITE);
    fl_rectf(x(), y(), w() + axis_space, h());

    // *Flächenzeichnungen
    // Power Fläche
    fl_color(0, 139, 139);
    draw_area(c_border - 0.2,
              x_axis_max_value,
              point_list,
              x_min_graph_draw_pos,
              x_max_graph_draw_pos,
              y_max_graph_draw_pos,
              x_graph_draw_size,
              y_graph_draw_size,
              x_axis_min_value,
              x_axis_max_value,
              y_axis_min_value,
              x_axis_value_interval,
              y_axis_value_interval,
              effect);

    // Linke Alpha Fläche
    fl_color(231, 84, 128);
    draw_area(-5.0,
              a_border,
              point_list,
              x_min_graph_draw_pos,
              x_max_graph_draw_pos,
              y_max_graph_draw_pos,
              x_graph_draw_size,
              y_graph_draw_size,
              x_axis_min_value,
              x_axis_max_value,
              y_axis_min_value,
              x_axis_value_interval,
              y_axis_value_interval,
              0);

    // Rechte Alpha Fläche
    // TODO Kleines Artefakt an der Grenze entfernen
    fl_color(231, 84, 128);
    draw_area(c_border,
              x_axis_max_value,
              point_list,
              x_min_graph_draw_pos,
              x_max_graph_draw_pos,
              y_max_graph_draw_pos,
              x_graph_draw_size,
              y_graph_draw_size,
              x_axis_min_value,
              x_axis_max_value,
              y_axis_min_value,
              x_axis_value_interval,
              y_axis_value_interval,
              0);

    // Beta Fläche
    fl_color(153, 0, 204);
    draw_area(-5.0,
              c_border + 0.01,
              point_list,
              x_min_graph_draw_pos,
              x_max_graph_draw_pos,
              y_max_graph_draw_pos,
              x_graph_draw_size,
              y_graph_draw_size,
              x_axis_min_value,
              x_axis_max_value,
              y_axis_min_value,
              x_axis_value_interval,
              y_axis_value_interval,
              effect);

    // *Verteilung eins
    fl_line_style(FL_SOLID, graph_line_width);
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
                fl_line(x_start + effect + 3, y_start, x_end + effect + 3, y_end);
            }
        }
    }

    // *Fehlergrenzen
    fl_color(100, 100, 100);

    // a Grenze
    fl_yxline(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((a_border - x_axis_min_value) / x_axis_value_interval)), y_min_graph_draw_pos, y_max_graph_draw_pos);
    //   c Grenze
    fl_yxline(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((c_border - x_axis_min_value) / x_axis_value_interval)), y_min_graph_draw_pos, y_max_graph_draw_pos);

    // *Weitere Achsenbeschriftungen:
    // Power und Beta
    fl_color(200, 200, 200);
    fl_yxline(x_min_graph_draw_pos + std::round(x_graph_draw_size * ((c_border - x_axis_min_value) / x_axis_value_interval)), y_max_graph_draw_pos, y_max_graph_draw_pos + 50);
    fl_color(153, 0, 204);
    fl_draw("Beta",x_min_graph_draw_pos + std::round(x_graph_draw_size * ((c_border - x_axis_min_value) / x_axis_value_interval)) - 40, y_max_graph_draw_pos + 50);
    fl_color(0, 139, 139);
    fl_draw("Power",x_min_graph_draw_pos + std::round(x_graph_draw_size * ((c_border - x_axis_min_value) / x_axis_value_interval)) + 10, y_max_graph_draw_pos + 50);

    // *draw axes
    fl_line_style(FL_SOLID, axis_line_width); 
    // draw Scale
    fl_color(FL_BLACK);
    // graph y axis
    fl_line(x_min_graph_draw_pos, y_min_graph_draw_pos, x_min_graph_draw_pos, y_max_graph_draw_pos);
    // graph x axis
    fl_line(x_min_graph_draw_pos, y_max_graph_draw_pos, x_max_graph_draw_pos, y_max_graph_draw_pos);
    const int scale_fontsize = 14;
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
        fl_draw(value_str.c_str(), x_position - 8, y_max_graph_draw_pos + scale_fontsize + 7);
    }
    // x-axis label
    fl_draw("X-Achse", x_max_graph_draw_pos, y_max_graph_draw_pos + 40);
    // y-Scale
    const double y_scale_interval{y_axis_value_interval / 10};
    for (double value = y_axis_min_value; value <= y_axis_max_value + 0.01; value += y_scale_interval)
    {
        double y_position = y_max_graph_draw_pos - ((value - y_axis_min_value) * y_graph_draw_size) / y_axis_value_interval;
        fl_line(x_min_graph_draw_pos - 5, y_position, x_min_graph_draw_pos + 5, y_position);
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << value;
        std::string value_str = ss.str();
        fl_draw(value_str.c_str(), x_min_graph_draw_pos - 24 - scale_fontsize, y_position + 5);
    }
    // y-axis label
    fl_draw("Y-Achse", x_min_graph_draw_pos - 50, y_min_graph_draw_pos - 20);
}

// private
double FD_GUI_View_Graph::find_y_value_for_x(const std::vector<std::pair<double, double>> &point_list, double x)
{
    for (size_t i = 1; i < point_list.size(); i++)
    {
        if (point_list[i].first >= x)
        {
            size_t nearest_index;

            if (point_list[i].first - x < x - point_list[i - 1].first)
            {
                nearest_index = i;
            }
            else
            {
                nearest_index = i - 1;
            }

            if (nearest_index > 0)
            {
                return point_list[nearest_index - 1].second;
            }
            else
            {
                return point_list[0].second;
            }
        }
    }
    return 0;
}
