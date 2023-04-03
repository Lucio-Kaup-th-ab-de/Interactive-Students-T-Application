#ifndef FD_GUI_VIEW_GRAPH_H
#define FD_GUI_VIEW_GRAPH_H
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class FD_GUI_View_Graph : public Fl_Widget {
    public:
        FD_GUI_View_Graph(int x, int y,int width, int height,const char* label);
        void draw();
        void set_point_list(const std::vector<std::pair<double,double>>& pl);
    private:
        std::vector<std::pair<double,double>> point_list{};
};

#endif /* FD_GUI_VIEW_GRAPH_H */