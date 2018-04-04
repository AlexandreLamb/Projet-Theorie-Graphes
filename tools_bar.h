#ifndef TOOLS_BAR_H_INCLUDED
#define TOOLS_BAR_H_INCLUDED

#include "grman/grman.h"
#include <iostream>
#include "graph.h"
class Tools_bar{
    friend class Graph;

private:

        grman::WidgetBox m_top_box;

        grman::WidgetImage i_sauvgarde;
        grman::WidgetImage i_quitter;
        grman::WidgetText t_sauvgarde;
        grman::WidgetText t_quitter;

        grman::WidgetButton b_sauvgarde;
        grman::WidgetButton b_quitter;

        public:
        Tools_bar();
        void update();

        ~Tools_bar();




};

#endif // TOOLS_BAR_H_INCLUDED
