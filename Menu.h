#ifndef MENU_H
#define MENU_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "../grman/grman.h"



class MenuInterface
{
    friend class Menu;
public:
    MenuInterface(int x,int y,int w, int h);
    int z;

private:
    grman::WidgetBox m_main_box;

    grman::WidgetBox m_graph1;
    grman::WidgetBox m_graph2;
    grman::WidgetBox m_graph3;

    grman::WidgetImage m_imggraph1;
    grman::WidgetImage m_imggraph2;
    grman::WidgetImage m_imggraph3;

    grman::WidgetText m_graph1_text;
    grman::WidgetText m_graph2_text;
    grman::WidgetText m_graph3_text;




};


class Menu
{
    friend class MenuInterface;
    public:
        Menu(MenuInterface *interface=nullptr): m_interface(interface){  };
        void update();
        int choixgraph();
        void demarermenu();

    virtual ~Menu();

    private:
        std::shared_ptr<MenuInterface> m_interface = nullptr;

};

#endif // MENU_H
