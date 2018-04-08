#ifndef MENU_H
#define MENU_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "grman/grman.h"



class MenuInterface
{
    friend class Menu;
public:
    MenuInterface(int x,int y,int w, int h);
    MenuInterface(int w, int h);
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


    grman::WidgetImage m_demarer_img;


    grman::WidgetImage m_titre_img;
    grman::WidgetButton m_button_demarrer;

};


class Menu
{
    friend class MenuInterface;
    public:
        Menu(MenuInterface *interface=nullptr): m_interface(interface){  };
        void update();
        bool update2();
        int choixgraph();
        void demarermenu();
        void ecran_Aceuille();

    virtual ~Menu();

    private:
        std::shared_ptr<MenuInterface> m_interface = nullptr;


};

#endif // MENU_H
