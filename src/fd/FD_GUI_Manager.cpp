#include "FD_GUI_Manager.h"

FD_GUI_Manager::FD_GUI_Manager()
{
    view_window_graph = std::make_unique<FD_GUI_View_Window_Graph>(275, 40, 1200, 600, "Distribution Graph Application", (void *)this); //* Main Window
    // Fl_PNG_Image app_icon("resources/icon.png");
    // view_window_graph->icon(&app_icon);
    view_window_graph->show();
}

void FD_GUI_Manager::set_graph_creation_controller(IA_Graph_Creation_Controller_GUI *gc_c)
{
    graph_creation_controller = gc_c;
}

void FD_GUI_Manager::run()
{
    Fl::run();
}

int FD_GUI_Manager::get_df_value()
{
    return view_window_graph->get_df_value();
}

void FD_GUI_Manager::update_view_graph_diagram(const std::vector<std::pair<double, double>> &point_list, double a_border, double c_border)
{
    view_window_graph->update_graph(point_list, a_border, c_border);
}

void FD_GUI_Manager::gui_cb_df_slider_callback(Fl_Widget *w)
{
    Fl_Value_Slider *slider_value = (Fl_Value_Slider *)w;
    int value = slider_value->value();
    view_window_graph->set_df_value(value);
    graph_creation_controller->control_graph_creation();
}

void FD_GUI_Manager::static_gui_cb_df_slider_callback(Fl_Widget *w, void *f)
{
    ((FD_GUI_Manager *)f)->gui_cb_df_slider_callback(w);
}
