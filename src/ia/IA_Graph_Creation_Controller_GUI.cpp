#include "IA_Graph_Creation_Controller_GUI.h"
#include <iostream>
#include <string>

IA_Graph_Creation_Controller_GUI::IA_Graph_Creation_Controller_GUI(IA_GUI_Manager_I &gui, AR_UCI_Graph_Creation_IB &uci)
    : uci_graph_creation(uci), gui_manager(gui){};
void IA_Graph_Creation_Controller_GUI::control_graph_creation()
{
    int df = gui_manager.get_df_value();
    uci_graph_creation.create_graph(df, 5); //! Nur als Beispiel Alpha
};
