#ifndef IA_GUI_Manager_I_H
#define IA_GUI_Manager_I_H
#include <vector>
#include <string>

class IA_GUI_Manager_I
{
public:
   virtual void run() = 0;
   virtual void update_view_graph_diagram(const std::vector<std::pair<double, double>> &point_list,
                                          double a_border,
                                          double c_border,
                                          double effect,
                                          double power,
                                          double beta) = 0;
   virtual void update_outputs(double power, double beta) = 0;                                         
   virtual int get_df_value() = 0;
   virtual double get_effect() = 0;
   virtual double get_alpha() = 0;
   virtual ~IA_GUI_Manager_I() = default;
   IA_GUI_Manager_I() = default;
   IA_GUI_Manager_I(const IA_GUI_Manager_I &) = default;
   IA_GUI_Manager_I &operator=(const IA_GUI_Manager_I &) = default;
};

#endif /* IA_GUI_Manager_I_H */