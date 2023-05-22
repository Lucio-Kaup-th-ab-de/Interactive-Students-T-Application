#include <string>
#include "FD_GUI_View_Window_Graph.h"
#include "FD_GUI_Manager.h"
#include <iostream>

FD_GUI_View_Window_Graph::FD_GUI_View_Window_Graph(int x, int y, int width, int height, const char *title, void *ui_pointer_for_callbacks)
    : Fl_Window(x, y, width, height, title)
{
    this->begin();
    graph_label = std::make_unique<Fl_Box>(-30, 20, 900, 40, "Interactive Visualization of Student's t-Distributions for Sample Size Planning");
    graph_label->labelfont(FL_BOLD);
    graph_label->labelsize(20);

    // DF Output
    output_degrees_of_freedom = std::make_unique<Fl_Value_Output>(730, 530, 30, 25);
    output_degrees_of_freedom->label("Degrees of Freedom");
    output_degrees_of_freedom->value(6); // Startwert
    output_degrees_of_freedom->textsize(18);
    output_degrees_of_freedom->labelsize(18);

    output_effect = std::make_unique<Fl_Value_Output>(2000, 530, 60, 40);
    output_effect->value(2.5 * 80); // Startwert
    output_alpha = std::make_unique<Fl_Value_Output>(2000, 630, 60, 40);
    output_alpha->value(0.05); // Startwert
    output_antialias = std::make_unique<Fl_Value_Output>(2000, 730, 60, 40);
    output_antialias->value(1);

    // Mean 1 Output
    output_mean_1 = std::make_unique<Fl_Value_Output>(1130, 530, 35, 25);
    output_mean_1->label("First Mean ");
    output_mean_1->labelcolor(fl_rgb_color(255, 0, 0));
    output_mean_1->textcolor(fl_rgb_color(255, 0, 0));
    output_mean_1->value(0);
    output_mean_1->textsize(18);  // Größe der Zahl
    output_mean_1->labelsize(18); // Größe des labels

    // Mean 2 Output
    output_mean_2 = std::make_unique<Fl_Value_Output>(1130, 560, 35, 25);
    output_mean_2->label("Second Mean ");
    output_mean_2->labelcolor(fl_rgb_color(0, 0, 255));
    output_mean_2->textcolor(fl_rgb_color(0, 0, 255));
    output_mean_2->value(2.5);
    output_mean_2->textsize(18);
    output_mean_2->labelsize(18);

    // Beta Niveau Output
    output_beta = std::make_unique<Fl_Value_Output>(900, 530, 75, 25);
    output_beta->label("Beta Niveau");
    output_beta->labelcolor(fl_rgb_color(153, 0, 204));
    output_beta->textcolor(fl_rgb_color(153, 0, 204));
    output_beta->value(0);
    output_beta->textsize(18);
    output_beta->labelsize(18);

    // Power Output
    output_power = std::make_unique<Fl_Value_Output>(900, 560, 75, 25);
    output_power->label("Power");
    output_power->labelcolor(fl_rgb_color(0, 139, 139));
    output_power->textcolor(fl_rgb_color(0, 139, 139));
    output_power->value(0);
    output_power->textsize(18);
    output_power->labelsize(18);

    // Degree of Freedom Slider //TODO evtl noch alle Variablennamen in SSZ umbenennen
    df_v_slider = std::make_unique<Fl_Value_Slider>(20, 530, 120, 25, "Sample Size");
    df_v_slider->type(FL_HOR_NICE_SLIDER); // Slider Typ
    df_v_slider->range(1.0, 10.0);         // Wertebereich des Sliders
    df_v_slider->step(1.0);                // Schrittweite
    df_v_slider->value(5.0);               // Startwert
    df_v_slider->textsize(16);             // Schriftgröße
    df_v_slider->callback(FD_GUI_Manager::static_gui_cb_df_slider_callback, ui_pointer_for_callbacks);

    // Effect Slider
    e_v_slider = std::make_unique<Fl_Value_Slider>(160, 530, 120, 25, "Effect Size");
    e_v_slider->type(FL_HOR_NICE_SLIDER); // Slider Typ
    e_v_slider->range(0, 5.0);            // Wertebereich des Sliders
    e_v_slider->step(0.1);                // Schrittweite
    e_v_slider->value(2.5);               // Startwert
    e_v_slider->textsize(16);             // Schriftgröße
    e_v_slider->callback(FD_GUI_Manager::static_gui_cb_effect_slider_callback, ui_pointer_for_callbacks);

    // Alpha Slider
    a_v_slider = std::make_unique<Fl_Value_Slider>(300, 530, 120, 25, "Alpha Error");
    a_v_slider->type(FL_HOR_NICE_SLIDER); // Slider Typ
    a_v_slider->range(0.01, 0.5);         // Wertebereich des Sliders
    a_v_slider->step(0.01);               // Schrittweite
    a_v_slider->value(0.05);              // Startwert
    a_v_slider->textsize(14);             // Schriftgröße
    a_v_slider->callback(FD_GUI_Manager::static_gui_cb_alpha_slider_callback, ui_pointer_for_callbacks);

    // Checkbox for Antialiasing
    antialiasing_checkbox = std::make_unique<Fl_Check_Button>(440, 530, 120, 20, "Antialiasing");
    antialiasing_checkbox->value(1); // Startwert (1 = an, 0 = aus)
    antialiasing_checkbox->callback(FD_GUI_Manager::static_gui_cb_antialiasing_checkbox_callback, ui_pointer_for_callbacks);

    graph = std::make_unique<FD_GUI_View_Graph>(5, 80, 1130, 425, "");
    this->end();
}

void FD_GUI_View_Window_Graph::set_antialias(int checked)
{
    output_antialias->value(checked);
}

void FD_GUI_View_Window_Graph::set_df_value(int df)
{
    output_degrees_of_freedom->value(df);
}

void FD_GUI_View_Window_Graph::set_effect(double effect)
{
    output_effect->value(effect);
}

void FD_GUI_View_Window_Graph::set_alpha(double alpha)
{
    output_alpha->value(alpha);
}

void FD_GUI_View_Window_Graph::set_mean_2(double m_2)
{
    output_mean_2->value(m_2);
}

void FD_GUI_View_Window_Graph::set_beta(double beta)
{
    output_beta->value(beta);
}

void FD_GUI_View_Window_Graph::set_power(double power)
{
    output_power->value(power);
}

int FD_GUI_View_Window_Graph::get_df_value()
{
    return output_degrees_of_freedom->value();
}

double FD_GUI_View_Window_Graph::get_effect()
{
    return output_effect->value();
}

double FD_GUI_View_Window_Graph::get_alpha()
{
    return output_alpha->value();
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

int FD_GUI_View_Window_Graph::get_antialias()
{
    return output_antialias->value();
}

void FD_GUI_View_Window_Graph::update_graph(const std::vector<std::pair<double, double>> &point_list,
                                            double a_border,
                                            double c_border,
                                            double effect,
                                            double power,
                                            double beta,
                                            int antialias)
{
    graph->set_point_list(point_list,
                          a_border,
                          c_border,
                          effect,
                          power,
                          beta,
                          antialias);
};
