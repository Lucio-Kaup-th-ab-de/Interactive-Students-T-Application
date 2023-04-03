#ifndef AR_UCI_GRAPH_CREATION_H
#define AR_UCI_GRAPH_CREATION_H
#include "AR_UCI_Graph_Creation_IB.h"
#include "AR_UCI_Graph_Creation_OB.h"
#include "AR_STAT_Util_I.h"

class AR_UCI_Graph_Creation : public AR_UCI_Graph_Creation_IB {
    public:
        AR_UCI_Graph_Creation(
            AR_UCI_Graph_Creation_OB& presenter,
            AR_STAT_Util_I& s);
        void create_graph(int df);
    private:
        AR_UCI_Graph_Creation_OB& graph_presenter;
        AR_STAT_Util_I& stat_util;
};
#endif /* AR_UCI_GRAPH_CREATION_H */