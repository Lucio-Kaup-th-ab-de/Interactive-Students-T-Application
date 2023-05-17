#include <iostream>
#include "FD_GUI_Manager.h"
#include "FD_STAT_Util.h"
#include "IA_Graph_Creation_Presenter_GUI.h"
#include "AR_UCI_Graph_Creation.h"
#include "IA_Graph_Creation_Controller_GUI.h"
#include "IA_Master_Controller_GUI.h"
using namespace std;

int main()
{
    FD_GUI_Manager gui_manager{};

    IA_Graph_Creation_Presenter_GUI graph_creation_presenter{gui_manager};
    FD_STAT_Util stat_util{};
    AR_UCI_Graph_Creation graph_creation_use_case{graph_creation_presenter, stat_util};
    IA_Graph_Creation_Controller_GUI graph_creation_controller{gui_manager, graph_creation_use_case};
    gui_manager.set_graph_creation_controller(&graph_creation_controller);

    IA_Master_Controller_GUI application_master_controller{gui_manager, graph_creation_controller};

    application_master_controller.control_application_start();
}
