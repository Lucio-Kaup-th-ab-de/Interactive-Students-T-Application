#include "IA_Master_Controller_GUI.h"
#include <iostream>

IA_Master_Controller_GUI::IA_Master_Controller_GUI(IA_GUI_Manager_I& gui,
        IA_Graph_Creation_Controller_GUI& a_graph_controller)
            : graph_controller(a_graph_controller), gui_manager(gui) {};

void IA_Master_Controller_GUI::control_application_start(){
    graph_controller.control_graph_creation();
    gui_manager.run();
};
