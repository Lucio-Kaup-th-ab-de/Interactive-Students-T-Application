#ifndef IA_GRAPH_CREATION_CONTROLLER_GUI_H
#define IA_GRAPH_CREATION_CONTROLLER_GUI_H
#include <string>
#include "AR_UCI_Graph_Creation_IB.h"
#include "IA_GUI_Manager_I.h"

class IA_Graph_Creation_Controller_GUI {
    public:
        IA_Graph_Creation_Controller_GUI(IA_GUI_Manager_I& gui, AR_UCI_Graph_Creation_IB& uci);
        void control_graph_creation();
    private:
        AR_UCI_Graph_Creation_IB& uci_graph_creation;
        IA_GUI_Manager_I& gui_manager;
};
#endif /* IA_GRAPH_CREATION_CONTROLLER_GUI_H */