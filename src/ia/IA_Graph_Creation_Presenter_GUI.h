#ifndef IA_GRAPH_CREATION_PRESENTER_GUI_H
#define IA_GRAPH_CREATION_PRESENTER_GUI_H
#include "IA_GUI_Manager_I.h"
#include "AR_UCI_Graph_Creation_OB.h"
#include <vector>
#include <map>
#include <string>

class IA_Graph_Creation_Presenter_GUI : public AR_UCI_Graph_Creation_OB
{
public:
    IA_Graph_Creation_Presenter_GUI(IA_GUI_Manager_I &gui);
    void present_graph(const std::vector<std::pair<double, double>> &point_list,
                       double a_border,
                       double c_border,
                       double effect,
                       double power,
                       double beta,
                       int antialias);
    void present_outputs(double power, double beta);

private:
    IA_GUI_Manager_I &gui_manager;
};
#endif /* IA_GRAPH_CREATION_PRESENTER_GUI_H */