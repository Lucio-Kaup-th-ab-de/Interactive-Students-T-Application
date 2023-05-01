#ifndef AR_UCI_GRAPH_CREATION_OB_H
#define AR_UCI_GRAPH_CREATION_OB_H
#include <vector>
#include <map>
#include <string>

class AR_UCI_Graph_Creation_OB
{
public:
   virtual void present_graph(const std::vector<std::pair<double, double>> &point_list,
                              double a_border,
                              double c_border,
                              double effect,
                              double power,
                              double beta) = 0;

   virtual ~AR_UCI_Graph_Creation_OB() = default;
   AR_UCI_Graph_Creation_OB() = default;
   AR_UCI_Graph_Creation_OB(const AR_UCI_Graph_Creation_OB &) = default;
   AR_UCI_Graph_Creation_OB &operator=(const AR_UCI_Graph_Creation_OB &) = default;
};

#endif /* AR_UCI_GRAPH_CREATION_OB_H */