#ifndef FD_GUI_MANAGER_H
#define FD_GUI_MANAGER_H
#include <memory>
#include <vector>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include "FD_GUI_View_Window_Graph.h"
#include "IA_GUI_Manager_I.h"
#include "IA_Graph_Creation_Controller_GUI.h"

class FD_GUI_Manager : public IA_GUI_Manager_I
{
public:
    FD_GUI_Manager();
    void run() override;
    void update_view_graph_diagram(const std::vector<std::pair<double, double>> &point_list,
                                   double a_border,
                                   double c_border,
                                   double effect,
                                   double power,
                                   double beta,
                                   int antialias) override;
    void update_outputs(double power, double beta) override;
    int get_df_value() override;
    double get_effect() override;
    double get_alpha() override;
    int get_antialias() override;
    void set_graph_creation_controller(IA_Graph_Creation_Controller_GUI *gc_c);

    static void static_gui_cb_df_slider_callback(Fl_Widget *w, void *f);
    static void static_gui_cb_effect_slider_callback(Fl_Widget *w, void *f);
    static void static_gui_cb_alpha_slider_callback(Fl_Widget *w, void *f);
    static void static_gui_cb_antialiasing_checkbox_callback(Fl_Widget *w, void *f);

private:
    std::unique_ptr<FD_GUI_View_Window_Graph> view_window_graph;
    IA_Graph_Creation_Controller_GUI *graph_creation_controller;
    void gui_cb_df_slider_callback(Fl_Widget *w);
    void gui_cb_effect_slider_callback(Fl_Widget *w);
    void gui_cb_alpha_slider_callback(Fl_Widget *w);
    void gui_cb_antialiasing_checkbox_callback(Fl_Widget *w);
};
#endif /* FD_GUI_MANAGER_H */