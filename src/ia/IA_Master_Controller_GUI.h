#ifndef IA_MASTER_CONTROLLER_GUI
#define IA_MASTER_CONTROLLER_GUI
#include "IA_Graph_Creation_Controller_GUI.h"
#include "IA_GUI_Manager_I.h"

class IA_Master_Controller_GUI {
    public:
        IA_Master_Controller_GUI(
            IA_GUI_Manager_I& gui,
            IA_Graph_Creation_Controller_GUI& a_graph_controller);
        void control_application_start();
    private:
        IA_Graph_Creation_Controller_GUI& graph_controller;
        IA_GUI_Manager_I& gui_manager;      
};
#endif /* IA_MASTER_CONTROLLER_GUI */