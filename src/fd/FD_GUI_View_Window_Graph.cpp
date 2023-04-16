#include <string>
#include "FD_GUI_View_Window_Graph.h"
#include "FD_GUI_Manager.h"
#include <iostream>

FD_GUI_View_Window_Graph::FD_GUI_View_Window_Graph(int x, int y, int width, int height, const char *title, void *ui_pointer_for_callbacks)
    : Fl_Window(x, y, width, height, title)
{
    this->begin();
    graph_label = std::make_unique<Fl_Box>(150, 35, 900, 40, "Student's t probability density function");
    graph_label->labelfont(FL_BOLD);
    graph_label->labelsize(20);

    // DF Output
    output_degrees_of_freedom = std::make_unique<Fl_Value_Output>(700, 530, 60, 40);
    output_degrees_of_freedom->label("df");
    // output_degrees_of_freedom->labelcolor(fl_rgb_color(255, 20, 147));
    // output_degrees_of_freedom->textcolor(fl_rgb_color(255, 20, 147));
    output_degrees_of_freedom->value(5); // Startwert

    // Mean 1 Output
    output_mean_1 = std::make_unique<Fl_Value_Output>(1100, 530, 30, 20);
    output_mean_1->label("Mean one");
    output_mean_1->labelcolor(fl_rgb_color(255, 0, 0));
    output_mean_1->textcolor(fl_rgb_color(255, 0, 0));
    output_mean_1->value(0);

    // Mean 2 Output
    output_mean_2 = std::make_unique<Fl_Value_Output>(1100, 560, 30, 20);
    output_mean_2->label("Mean two ");
    output_mean_2->labelcolor(fl_rgb_color(0, 0, 255));
    output_mean_2->textcolor(fl_rgb_color(0, 0, 255));
    output_mean_2->value(0);

    // Beta Niveau Output
    output_beta = std::make_unique<Fl_Value_Output>(980, 530, 30, 20);
    output_beta->label("Beta Niveau");
    // output_beta->labelcolor(fl_rgb_color(0, 0, 255));
    // output_beta->textcolor(fl_rgb_color(0, 0, 255));
    output_beta->value(0);

    // Mean 2 Output
    output_power = std::make_unique<Fl_Value_Output>(980, 560, 30, 20);
    output_power->label("Power");
    // output_power->labelcolor(fl_rgb_color(0, 0, 255));
    // output_power->textcolor(fl_rgb_color(0, 0, 255));
    output_power->value(0);

    // DF Buttons //!noch löschen
    // up_button = std::make_unique<Fl_Button>(20, 525, 120, 40, "Increase df");
    // down_button = std::make_unique<Fl_Button>(910, 130, 120, 40, "Decrease df");
    // up_button->callback(FD_GUI_Manager::static_gui_cb_button_up, ui_pointer_for_callbacks);
    // down_button->callback(FD_GUI_Manager::static_gui_cb_button_down, ui_pointer_for_callbacks);

    // Degree of Freedom Slider
    df_v_slider = std::make_unique<Fl_Value_Slider>(20, 530, 120, 25, "Degrees of Freedom");
    df_v_slider->type(FL_HOR_NICE_SLIDER); // Slider Typ
    df_v_slider->range(1.0, 10.0);         // Wertebereich des Sliders
    df_v_slider->step(1.0);                // Schrittweite
    df_v_slider->value(5.0);               // Startwert
    df_v_slider->callback(FD_GUI_Manager::static_gui_cb_df_slider_callback, ui_pointer_for_callbacks);

    // Effect Slider
    e_v_slider = std::make_unique<Fl_Value_Slider>(160, 530, 120, 25, "Effect size");
    e_v_slider->type(FL_HOR_NICE_SLIDER); // Slider Typ
    e_v_slider->range(0, 100.0);          // Wertebereich des Sliders
    e_v_slider->step(0.1);                // Schrittweite
    e_v_slider->value(50.0);              // Startwert
    // e_v_slider->callback(FD_GUI_Manager::static_gui_cb_e_slider_callback, ui_pointer_for_callbacks);

    // Alpha Slider
    a_v_slider = std::make_unique<Fl_Value_Slider>(300, 530, 120, 25, "Alpha Error");
    a_v_slider->type(FL_HOR_NICE_SLIDER); // Slider Typ
    a_v_slider->range(0, 20.0);           // Wertebereich des Sliders
    a_v_slider->step(0.1);                // Schrittweite
    a_v_slider->value(5.0);               // Startwert
    // e_v_slider->callback(FD_GUI_Manager::static_gui_cb_e_slider_callback, ui_pointer_for_callbacks);

    graph = std::make_unique<FD_GUI_View_Graph>(5, 80, 900, 425, "");
    this->end();
}
/* //! Brauch ich evtl nicht mehr
double FD_GUI_View_Window_Graph::get_df_slider_value()
{
    double slider_value = static_cast<double>(df_v_slider->value());
    return slider_value;
}*/

void FD_GUI_View_Window_Graph::set_df_value(int df)
{
    output_degrees_of_freedom->value(df);
}

void FD_GUI_View_Window_Graph::set_mean_2(double m_2)
{
    output_mean_2->value(m_2);
}

void FD_GUI_View_Window_Graph::set_beta(double b)
{
    output_beta->value(b);
}

void FD_GUI_View_Window_Graph::set_power(double p)
{
    output_power->value(p);
}

int FD_GUI_View_Window_Graph::get_df_value()
{
    return output_degrees_of_freedom->value();
}

double FD_GUI_View_Window_Graph::get_mean_2()
{
    return output_mean_2->value();
}

double FD_GUI_View_Window_Graph::get_beta()
{
    return output_beta->value();
}

double FD_GUI_View_Window_Graph::get_power()
{
    return output_power->value();
}

int FD_GUI_View_Window_Graph::get_df_value()
{
    return output_degrees_of_freedom->value();
}

/*
void FD_GUI_View_Window_Graph::enable_up_button()
{
    up_button->activate();
}

void FD_GUI_View_Window_Graph::disable_up_button()
{
    up_button->deactivate();
}

void FD_GUI_View_Window_Graph::enable_down_button()
{
    down_button->activate();
}

void FD_GUI_View_Window_Graph::disable_down_button()
{
    down_button->deactivate();
}*/

void FD_GUI_View_Window_Graph::update_graph(const std::vector<std::pair<double, double>> &point_list, double a_border)
{
    graph->set_point_list(point_list, a_border);
};
