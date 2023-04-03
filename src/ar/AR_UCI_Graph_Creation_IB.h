#ifndef AR_UCI_GRAPH_CREATION_IB_H
#define AR_UCI_GRAPH_CREATION_IB_H
#include <string>

class AR_UCI_Graph_Creation_IB {
   public:
      virtual void create_graph(int df) = 0; 

      virtual ~AR_UCI_Graph_Creation_IB() = default;
      AR_UCI_Graph_Creation_IB() = default;
      AR_UCI_Graph_Creation_IB(const AR_UCI_Graph_Creation_IB&) = default;
      AR_UCI_Graph_Creation_IB& operator=(const AR_UCI_Graph_Creation_IB&) = default;
};

#endif /* AR_UCI_GRAPH_CREATION_IB_H */