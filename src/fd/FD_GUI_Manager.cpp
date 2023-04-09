#include "FD_GUI_Manager.h"

FD_GUI_Manager::FD_GUI_Manager() {
    view_window_graph = std::make_unique<FD_GUI_View_Window_Graph>(275,40,1035,520,"Distribution Graph Application", (void *)this);
    view_window_graph->show();
}

void FD_GUI_Manager::set_graph_creation_controller(IA_Graph_Creation_Controller_GUI* gc_c){
    graph_creation_controller = gc_c;
}

void FD_GUI_Manager::run() {
    Fl::run();
}

int FD_GUI_Manager::get_df_value(){
    return view_window_graph->get_df_value();
}

void FD_GUI_Manager::update_view_graph_diagram(const std::vector<std::pair<double,double>>& point_list){
    view_window_graph->update_graph(point_list);
}

void FD_GUI_Manager::gui_cb_button_up(Fl_Widget* w){
    int df = view_window_graph->get_df_value();
    if (df == df_min_value)
        view_window_graph->enable_down_button();    
    if (df < df_max_value)
        view_window_graph->set_df_value(df+1);
    if (df == (df_max_value-1))
        view_window_graph->disable_up_button();    
    graph_creation_controller->control_graph_creation();
}

void FD_GUI_Manager::gui_cb_button_down(Fl_Widget* w){
    int df = view_window_graph->get_df_value();
    if (df == df_max_value)
        view_window_graph->enable_up_button();    
    if (df > df_min_value)
        view_window_graph->set_df_value(df-1);
    if (df == df_min_value+1)
        view_window_graph->disable_down_button();
    graph_creation_controller->control_graph_creation();
}

void FD_GUI_Manager::gui_df_slider(Fl_Widget* w){
    graph_creation_controller->control_graph_creation();
    // todo Vllt fehlt hier noch was
    // evtl überprüfen ob slider Input korrekt ist
}

void FD_GUI_Manager::static_gui_cb_button_up(Fl_Widget* w, void *f){
    ((FD_GUI_Manager *)f)->gui_cb_button_up(w);
}

void FD_GUI_Manager::static_gui_cb_button_down(Fl_Widget* w, void *f){
    ((FD_GUI_Manager *)f)->gui_cb_button_down(w);
}

void FD_GUI_Manager::static_gui_df_slider(Fl_Widget*w, void* f){
    ((FD_GUI_Manager *)f)->gui_df_slider(w);
}
