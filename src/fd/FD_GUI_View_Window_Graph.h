#ifndef FD_GUI_VIEW_WINDOW_GRAPH_H
#define FD_GUI_VIEW_WINDOW_GRAPH_H
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
// #include <FL/Fl_PNG_Image.H>
#include <Fl/Fl_Value_Slider.H>
#include <FL/Fl_Value_Output.H>
#include "FD_GUI_View_Graph.h"

class FD_GUI_View_Window_Graph : public Fl_Window
{
public:
    FD_GUI_View_Window_Graph(int x, int y, int width, int height, const char *title, void *ui_pointer_for_callbacks);
    void update_graph(const std::vector<std::pair<double, double>> &point_list,
                      double a_border,
                      double c_border,
                      double effect,
                      double power,
                      double beta);

    // slider
    void set_df_value(int df);
    int get_df_value();

    void set_effect(double effect);
    double get_effect();

    void set_alpha(double alpha);
    double get_alpha();

    // Value Outputs
    void set_mean_2(double m_2);
    void set_beta(double b);
    void set_power(double p);

    double get_mean_2();
    double get_beta();
    double get_power();

private:
    std::unique_ptr<FD_GUI_View_Graph> graph;
    std::unique_ptr<Fl_Box> graph_label;
    std::unique_ptr<Fl_Value_Output> output_degrees_of_freedom;
    std::unique_ptr<Fl_Value_Output> output_effect;
    std::unique_ptr<Fl_Value_Output> output_alpha;
    std::unique_ptr<Fl_Value_Output> output_mean_1;
    std::unique_ptr<Fl_Value_Output> output_mean_2;
    std::unique_ptr<Fl_Value_Output> output_beta;
    std::unique_ptr<Fl_Value_Output> output_power;
    // std::unique_ptr<Fl_Button> up_button;
    // std::unique_ptr<Fl_Button> down_button;
    std::unique_ptr<Fl_Value_Slider> df_v_slider;
    std::unique_ptr<Fl_Value_Slider> e_v_slider;
    std::unique_ptr<Fl_Value_Slider> a_v_slider;
};
#endif /* FD_GUI_VIEW_WINDOW_GRAPH_H */