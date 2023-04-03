#include "IA_Graph_Creation_Presenter_GUI.h"

IA_Graph_Creation_Presenter_GUI::IA_Graph_Creation_Presenter_GUI(IA_GUI_Manager_I& gui)
            : gui_manager(gui) {};
void IA_Graph_Creation_Presenter_GUI::present_graph(const std::vector<std::pair<double,double>>& point_list) {
    gui_manager.update_view_graph_diagram(point_list);
};
