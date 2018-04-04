#include "tools_bar.h"

Tools_bar::Tools_bar(){

m_top_box.set_frame(10,10,60,300);
m_top_box.set_bg_color(JAUNECLAIR);
m_top_box.set_moveable();


m_top_box.add_child(b_quitter);
m_top_box.add_child(b_sauvgarde);

b_sauvgarde.set_dim(20,20);
b_sauvgarde.set_frame(3,3,32,16);
b_sauvgarde.set_bg_color(BLEU);
b_sauvgarde.add_child(t_sauvgarde);
t_sauvgarde.set_message("sauvgarde");

b_quitter.set_frame(3,3,32,16);



}

Tools_bar::~Tools_bar(){}

void Tools_bar::update(){
    m_top_box.update();

    if(b_sauvgarde.clicked()){
            b_sauvgarde.set_bg_color(CYAN);

    }
}
