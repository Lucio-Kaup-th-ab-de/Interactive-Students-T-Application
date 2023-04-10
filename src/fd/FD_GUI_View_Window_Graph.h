#ifndef FD_GUI_VIEW_WINDOW_GRAPH_H
#define FD_GUI_VIEW_WINDOW_GRAPH_H
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <Fl/Fl_Value_Slider.H>
#include <FL/Fl_Value_Output.H>
#include "FD_GUI_View_Graph.h"

class FD_GUI_View_Window_Graph : public Fl_Window
{
public:
    FD_GUI_View_Window_Graph(int x, int y, int width, int height, const char *title, void *ui_pointer_for_callbacks);
    void update_graph(const std::vector<std::pair<double, double>> &point_list);
    double get_df_slider_value();
    void set_df_value(int df);
    int get_df_value();
    void enable_up_button();
    void disable_up_button();
    void enable_down_button();
    void disable_down_button();

private:
    std::unique_ptr<FD_GUI_View_Graph> graph;
    std::unique_ptr<Fl_Box> graph_label;
    std::unique_ptr<Fl_Value_Output> output_degrees_of_freedom;
    std::unique_ptr<Fl_Button> up_button;
    std::unique_ptr<Fl_Button> down_button;
    std::unique_ptr<Fl_Value_Slider> df_v_slider;
};
#endif /* FD_GUI_VIEW_WINDOW_GRAPH_H */