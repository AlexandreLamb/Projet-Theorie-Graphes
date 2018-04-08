#include "Menu.h"

MenuInterface::MenuInterface(int x,int y,int w, int h)
{
    m_main_box.set_dim(w,h);
    m_main_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_main_box.set_bg_color(MARRONCLAIR);

    m_main_box.add_child(m_graph1);
    m_graph1.set_dim(275,183);
    m_graph1.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);
    m_graph1.add_child(m_imggraph1);

    m_graph1.add_child(m_graph1_text);
    m_graph1_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);


    m_imggraph1.set_pic_name("m_graph1.jpg");
    m_imggraph1.set_pic_idx(0);
    m_imggraph1.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);


    m_main_box.add_child(m_graph2);
     m_graph2.set_dim(275,183);
     m_graph2.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
     m_graph2.add_child(m_imggraph2);
     m_imggraph2.set_pic_name("m_graph2.jpg");
     m_imggraph2.set_pic_idx(0);
     m_imggraph2.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_main_box.add_child(m_graph3);
     m_graph3.set_dim(275,183);
     m_graph3.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
     m_graph3.add_child(m_imggraph3);
     m_imggraph3.set_pic_name("m_graph3.jpg");
     m_imggraph3.set_pic_idx(0);
     m_imggraph2.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
}



MenuInterface::MenuInterface(int w, int h)
{
    m_main_box.set_dim(w,h);
    m_main_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_main_box.set_bg_color(MARRONCLAIR);

     m_main_box.add_child(m_button_demarrer);
    m_button_demarrer.set_dim(800,759);
    m_button_demarrer.set_pos(0,0);

    m_main_box.add_child(m_titre_img);
    m_titre_img.set_pic_name("titre.jpg");
    m_titre_img.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Up );
    m_titre_img.set_pic_idx(0);

    m_main_box.add_child(m_demarer_img);
    m_demarer_img.set_pic_name("Demarrer.jpg");
     m_demarer_img.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Down );
    m_demarer_img.set_pic_idx(0);
}


 int Menu::choixgraph()
 {

     if(grman::mouse_click&1 && m_interface->m_graph1.is_mouse_over())
     {
         return 1;
     }

      if(grman::mouse_click&1 && m_interface->m_graph2.is_mouse_over())
     {
         return 2;
     }

      if(grman::mouse_click&1 && m_interface->m_graph3.is_mouse_over())
     {
         return 3;
     }

 }





void Menu::demarermenu()
{


         m_interface= std::make_shared<MenuInterface>(0,0,1000,740);


}

void Menu::ecran_Aceuille()
{
    m_interface= std::make_shared<MenuInterface>(1000,740);
}

bool Menu::update2()
{
    if (!m_interface)
        return true;


     m_interface->m_main_box.update();

     if(grman::mouse_click&1 && m_interface->m_button_demarrer.is_mouse_over())
     {
         m_interface->m_main_box.remove_child(m_interface->m_button_demarrer);
         m_interface->m_main_box.remove_child(m_interface->m_titre_img);
         m_interface->m_main_box.remove_child(m_interface->m_demarer_img);

         return false;
     }

     else return true;
}

 void Menu::update()
 {
     if (!m_interface)
        return;


     m_interface->m_main_box.update();

     choixgraph();


 }
Menu::~Menu()
{
    //dtor
}
