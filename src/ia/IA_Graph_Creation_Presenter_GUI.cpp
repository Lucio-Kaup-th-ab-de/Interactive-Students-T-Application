#include "IA_Graph_Creation_Presenter_GUI.h"

IA_Graph_Creation_Presenter_GUI::IA_Graph_Creation_Presenter_GUI(IA_GUI_Manager_I &gui)
    : gui_manager(gui){};
void IA_Graph_Creation_Presenter_GUI::present_graph(const std::vector<std::pair<double, double>> &point_list,
                                                    double a_border,
                                                    double c_border,
                                                    double effect,
                                                    double power,
                                                    double beta)
{
    gui_manager.update_view_graph_diagram(point_list,
                                          a_border,
                                          c_border,
                                          effect,
                                          power,
                                          beta);
};
