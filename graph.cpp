#include "graph.h"
#include <string>
#include <map>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{


    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 1000.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    m_top_box.add_child(m_tools_button);
    m_tools_button.add_child(m_tools_text);

    m_tools_button.set_pos(90,0);
    m_tools_text.set_pos(4,3);

    m_tools_text.set_message("Option");

    m_tools_text.set_dim(30,10);
    m_tools_button.set_dim(30,10);



}

void Vertex::Cacher_option()
{

    m_interface->m_top_box.remove_child(m_interface->m_tools_box);
    m_interface->m_top_box.set_border(2);
}

void Vertex::Afficher_option()
{

    if(grman::mouse_click && m_interface->m_tools_button.is_mouse_over())
    {
        m_interface->m_top_box.add_child(m_interface->m_tools_box);

        m_interface->m_tools_box.add_child(m_interface->m_tools_label);
        m_interface->m_tools_box.add_child(m_interface->m_button_cacher);
        m_interface-> m_tools_box.add_child(m_interface->m_label_cacher);
        m_interface->m_tools_box.add_child(m_interface->m_button_edit);
        m_interface->m_tools_box.add_child(m_interface->m_label_edit);

        m_interface->m_top_box.set_border(0);

        m_interface->m_tools_box.set_pos(-10,-10);
        m_interface->m_tools_box.set_gravity_xy(grman::GravityX::Right,grman::GravityY::Up);
        m_interface->m_tools_box.set_dim(120,120);
        m_interface->m_tools_box.set_border(1);
        m_interface->m_tools_box.set_bg_color(CYAN);

        m_interface-> m_tools_label.set_message("Option Sommet");
        m_interface-> m_label_cacher.set_message("Cacher");
        m_interface-> m_label_edit.set_message("Retour");

        m_interface-> m_tools_label.set_pos(0,0);

        m_interface->m_button_cacher.set_pos(0,20);
        m_interface->m_button_edit.set_pos(0,40);

        m_interface->m_label_cacher.set_pos(40,20);
        m_interface->m_label_edit.set_pos(40,40);

        m_interface->  m_button_cacher.set_bg_color(JAUNE);
        m_interface-> m_button_edit.set_bg_color(JAUNE);

        m_interface->m_button_cacher.set_dim(30,10);
        m_interface->m_button_edit.set_dim(30,10);

    }


}

void Vertex::Toggle_Sommet()
{

    if(grman::mouse_click && m_interface->m_button_cacher.is_mouse_over())
    {
        Vertex::IsHide = !Vertex::IsHide;

        if(IsHide==true)
        {
            //Cacher_Sommet();

        }
    }

    if(grman::mouse_click && m_interface->m_button_edit.is_mouse_over())
    {
        Cacher_option();

    }

}

void Vertex::Afficher_Somet()
{
    m_interface->m_top_box.add_child( m_interface->m_img );

    m_interface->m_top_box.add_child(m_interface->m_slider_value);

    m_interface->m_top_box.add_child(m_interface->m_label_value);




    m_interface->m_top_box.add_child(m_interface->m_tools_box);

    m_interface->m_top_box.add_child(m_interface-> m_box_label_idx );

    m_interface->m_box_label_idx.set_pos(115,90);
    m_interface->m_img.set_pos(30,0);
    m_interface->m_top_box.set_dim(130, 100);

    m_interface->m_top_box.set_border(2);

    m_interface->m_top_box.add_child(m_interface->m_tools_button);

    m_interface->m_top_box.remove_child(m_interface->m_tools_box);
    m_interface->m_tools_box.remove_child(m_interface->m_tools_label);
    m_interface-> m_tools_box.remove_child(m_interface->m_button_cacher);
    m_interface-> m_tools_box.remove_child(m_interface->m_label_cacher);
    m_interface-> m_tools_box.remove_child(m_interface->m_button_edit);
    m_interface-> m_tools_box.remove_child(m_interface->m_label_edit);


}

void Vertex::Cacher_Sommet()
{

    m_interface->m_top_box.remove_child(m_interface->m_img);
    m_interface->m_top_box.remove_child(m_interface->m_tools_box);
    m_interface->m_top_box.remove_child(m_interface->m_slider_value);
    m_interface->m_top_box.remove_child(m_interface->m_box_label_idx);
    m_interface->m_top_box.remove_child(m_interface->m_label_value);
    m_interface->m_top_box.remove_child(m_interface->m_tools_button);
    m_interface->m_top_box.set_dim(0,0);


}



/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);
    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();

    Toggle_Sommet();
    Afficher_option();

}

void Vertex::set_idx_V(int id)
{
    m_indx_V=id;
}

int Vertex::get_idx_V()
{
    return m_indx_V;
}



void Vertex::set_marque(bool x)
{
    m_ismarqued=x;
}

bool Vertex:: get_marque()
{
    return m_ismarqued;
}

void Vertex::set_connexeout(bool x)
{
    m_isin_cmpconnexeout=x;
}

bool Vertex :: get_connexeout()
{
    return m_isin_cmpconnexeout;
}

void Vertex::set_connexein(bool x)
{
    m_isin_cmpconnexein=x;
}

bool Vertex :: get_connexein()
{
    return m_isin_cmpconnexein;
}



int Vertex::get_idx()
{
    return m_idx;
}

void Vertex::set_idx(int x)
{
    m_idx=x;
}


void Vertex:: set_marque_connexeout(bool x)
{
    m_ismarqued_connexeout=x;
}
bool Vertex::get_marque_connexeout()
{
    return m_ismarqued_connexeout;
}
void Vertex:: set_marque_connexein(bool x)
{
    m_ismarqued_connexein=x;
}
bool Vertex:: get_marque_connexein()
{
    return m_ismarqued_connexein;
}






bool Vertex::islinked(Vertex x, int param)
{
    bool linked;
    /// est liée pour les sommets partant de this
    if(param==1)
    {

        for(int i=0; i<m_out.size(); i++)
        {
            for(int j=0; j<x.m_in.size(); j++)
            {
                if(m_out[i]==x.m_in[j])
                {
                    return true;
                }


                else
                    linked= false;
            }
        }
    }
    /// est liée pour les sommets arrivant sur this
    if(param==0)
    {

        for(int i=0; i<m_in.size(); i++)
        {
            for(int j=0; j<x.m_out.size(); j++)
            {
                if(m_in[i]==x.m_out[j])
                {
                    return true;

                }

                else
                    linked= false;
            }
        }
    }

    return linked;
}


int Vertex::get_value()
{
    return m_value;
}
/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );

    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...

    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}



void Edge::hide_edge_in()
{


    m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
    m_interface->m_top_edge.detach_from();


}
void Edge::hide_edge_out()
{


    m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
    m_interface->m_top_edge.detach_to();

}
void Edge::Afficher_Edges(Vertex& from, Vertex& to)
{

    m_interface->m_top_edge.attach_from(from.m_interface->m_top_box);
    m_interface->m_top_edge.attach_to(to.m_interface->m_top_box);
    m_interface-> m_top_edge.reset_arrow_with_bullet();

    m_interface->m_top_edge.add_child(m_interface->m_box_edge);

}


/// accesseurs
double Edge::get_weight()
{
    return m_weight;
}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();

    //hide_edge();
}

void Edge::set_idx_E(int id)
{
    m_indx_E=id;
}
int Edge::get_idx_E()
{
    return m_indx_E;
}




/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{

    m_top_box.set_dim(1024,760);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_top_box.set_bg_color(VERTFLUO);

    m_top_box.add_child(m_main_box);

    m_main_box.set_dim(944,750);


    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
    m_main_box.add_child(m_ordre_graph);
    m_ordre_graph.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);


    m_top_box.add_child(m_tool_box);


    m_tool_box.set_dim(80,750);

    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_tool_box.add_child(m_savebutton);

    m_tool_box.add_child(m_tool_text);
    m_tool_text.set_message("Options");
    m_tool_text.set_pos(10,20);

    m_savebutton.set_dim(45,30);
    m_savebutton.set_pos(10,40);

    m_savebutton.set_bg_color(ROUGE);
    m_savebutton.add_child(m_savebutton_text);
    m_savebutton_text.set_message("save");
    m_savebutton_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_tool_box.add_child(m_afficher_sommet);
    m_afficher_sommet.add_child(m_afficher_sommet_text);

    m_afficher_sommet.set_dim(45,30);
    m_afficher_sommet.set_bg_color(ROUGE);
    m_afficher_sommet.set_pos(10,120);

    m_afficher_sommet_text.set_message("show");
    m_afficher_sommet_text.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);

    m_tool_box.add_child(m_retour);
    m_retour.set_dim(50,50);
    m_retour.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
    m_retour.set_border(0);
    m_retour.add_child(m_retour_img);
    m_retour_img.set_pic_name("retour.bmp");
    m_retour_img.set_pic_idx(0);
    m_retour_img.set_border(0);
    m_retour_img.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);

    m_tool_box.add_child(m_button_play);
    m_button_play.set_dim(70,30);
    m_button_play.set_gravity_x(grman::GravityX::Center);
    m_button_play.set_posy(290);
    m_button_play.set_bg_color(ROUGE);
    m_button_play.add_child(m_text1_play);
    m_text1_play.set_posy(6);
    m_text1_play.set_message("Play");
    m_button_play.add_child(m_text2_play);
    m_text2_play.set_message("Mode F");
    m_text2_play.set_posy(18);


    m_tool_box.add_child(m_button_pause);
    m_button_pause.set_dim(70,30);
    m_button_pause.set_gravity_x(grman::GravityX::Center);
    m_button_pause.set_posy(322);
    m_button_pause.set_bg_color(ROUGE);
    m_button_pause.add_child(m_text1_pause);
    m_text1_pause.set_posy(6);
    m_text1_pause.set_message("Pause");
    m_button_pause.add_child(m_text2_pause);
    m_text2_pause.set_message("Mode F");
    m_text2_pause.set_posy(18);

    m_tool_box.add_child(m_button_flux);



    m_tool_box.add_child(m_cmp_fconnexe);
    m_cmp_fconnexe.set_dim(70,30);
    m_cmp_fconnexe.set_gravity_x(grman::GravityX::Center);
    m_cmp_fconnexe.set_posy(500);
    m_cmp_fconnexe.set_bg_color(ROUGE);
    m_cmp_fconnexe.add_child(m_cmp_fconnexe_text1);
    m_cmp_fconnexe.add_child(m_cmp_fconnexe_text2);
    m_cmp_fconnexe.add_child(m_cmp_fconnexe_text3);
    m_cmp_fconnexe_text1.set_message("cmp");
    m_cmp_fconnexe_text2.set_message("fortement");
    m_cmp_fconnexe_text3.set_message("connexe");
    m_cmp_fconnexe_text1.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);
    m_cmp_fconnexe_text2.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_cmp_fconnexe_text3.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);

    m_tool_box.add_child(m_button_K_co);

    m_button_K_co.set_pos(10,400);
    m_button_K_co.set_dim(45,30);
    m_button_K_co.set_bg_color(ROUGE);

    m_button_K_co.add_child(m_label_K_co);
    m_label_K_co.set_message("K-Co");
    m_label_K_co.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);

    m_tool_box.set_bg_color(BLANCBLEU);


}




void Graph::make_graph_1()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);


    Graph::charger("graph1");
    m_nomgraph ="graph1";

    m_interface->m_main_box.add_child(m_interface->m_ordre_graph);
    m_interface-> m_ordre_graph.set_gravity_xy(grman::GravityX::Left,grman::GravityY::Up );
    m_interface->m_ordre_graph.set_pos(12,3);
    m_interface-> m_ordre_graph.set_message("ordre graph: " + std::to_string(ordre));

}

void Graph::make_graph_3()
{
    std::string picname;

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    Graph::charger("graph3");
    m_nomgraph ="graph3";

    m_interface->m_main_box.add_child(m_interface->m_ordre_graph);
    m_interface-> m_ordre_graph.set_gravity_xy(grman::GravityX::Left,grman::GravityY::Up );
    m_interface->m_ordre_graph.set_pos(12,3);
    m_interface-> m_ordre_graph.set_message("ordre graph: " + std::to_string(ordre));

    for( int i = 0 ; i < m_vertices.size() ; i++ )
    {
        picname = m_vertices[i].get_name();
        picname.erase(picname.size()-4,4);
        m_vertices[i].m_interface->m_top_box.set_dim(120,90);
        m_vertices[i].m_interface->m_top_box.add_child(m_vertices[i].m_interface->m_label_name);
        m_vertices[i].m_interface->m_label_name.set_message(picname);
        m_vertices[i].m_interface->m_label_name.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);
        m_vertices[i].m_interface->m_top_box.set_bg_color(VERTCLAIR);
}
}
void Graph::make_graph_2()
{

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    Graph::charger("graph2");
    m_nomgraph ="graph2";


    m_interface->m_main_box.add_child(m_interface->m_ordre_graph);
    m_interface-> m_ordre_graph.set_gravity_xy(grman::GravityX::Left,grman::GravityY::Up );
    m_interface->m_ordre_graph.set_pos(12,3);
    m_interface-> m_ordre_graph.set_message("ordre graph: " + std::to_string(ordre));

}


long int** Graph::find_K_connex()
{

    long int* tab;
    long int** liste;

    long int i,j;
    long int n= ordre;


    int cmp = 0;
    int k =0;
    tab=(long int*)malloc(n*sizeof(long int));
    liste = (long int**)malloc((long int) pow((double)n,(double)p) * sizeof(long int*));
    for(i=0; i<(long int )pow((double)n,(double)p); i++)
    {
        liste[i] = (long int*)malloc(p*sizeof(long int));
    }
    for(i=0; i<n; i++)
    {
        tab[i]=i;
    }
    for(i=0; i<(long int )pow((double)n,(double)p); i++)
    {
        for(j=0; j<p; j++)
        {
            liste[i][j] = tab[(i/(long int)pow((double)n,(double)(p-(j+1))))%n];
        }
    }
    for(k; k<p; k++)
    {
        for(i=0; i<(long int )pow((double)n,(double)p); i++)
        {
            for(j=0; j<p; j++)
            {
                if(liste[i][k]==liste[i][j] && k!=j )
                {
                    liste[i][0]=-1;
                }
            }
        }
    }
    return liste;
}

bool Graph::IsConnex()
{



    int n = ordre;

    long int** tab ;


    std::vector<int> SomemtMarque;

    int* marque;

    int ** adja = new int* [ordre];
    int tmp1=0,tmp2=0;
    for(int i =0 ; i < ordre; i++)
    {
        adja[i] = new int [ordre];
    }

    std::cout<<"Choisir quelle k-connexité vous voulez tester ? ...";
    std::cin>>Graph::p;

    tab= find_K_connex();



    for(int i=0; i<(long int )pow((double)n,(double)p); i++)
    {
        if(tab[i][0] != -1 )
        {

            for(int j=0; j<p; j++)
            {


                m_vertices[tab[i][j]].IsMarque=true;  ///on marque toute la ligne
                m_vertices[tab[i][j]].Cacher_Sommet();
                SomemtMarque.push_back(tab[i][j]);


            }

            for(int a =0 ; a < ordre; a++)
            {
                for(int b = 0 ; b < ordre ; b ++)
                {
                    adja[a][b]=0;
                }
            }



            for(int a = 0 ; a < nbrEdge ; a++ )
            {
                if(!m_vertices[m_edges[a].m_from].IsMarque && !m_vertices[m_edges[a].m_to].IsMarque )
                {
                    adja[m_edges[a].m_from][m_edges[a].m_to] = 1;
                    adja[m_edges[a].m_to][m_edges[a].m_from] = 1;
                    tmp1=m_edges[a].m_to;
                }
            }



            marque =  marquage(adja,ordre-p,tmp1);
            tmp2=0;

            for(int x =0 ; x< ordre ; x++)
            {

                tmp2=marque[x]+tmp2; ///nbr sommet marqué
            }

            if(tmp2 == ordre-p)
            {
                std::cout<<"les sommet : "<<std::endl;
                for(int i = 0 ; i<SomemtMarque.size(); i++)
                {
                    std::cout<<"- "<<SomemtMarque[i]<<std::endl;
                }
                std::cout<<"lorsqu'il sont deconnecte ne rende pas le graph non connexe"<<std::endl;
            }
            else
            {
                std::cout<<"les sommet marque on deconnecte le graph"<<std::endl;
            }

            SomemtMarque.clear();

            for(int a=0; a<p; a++)
            {

                m_vertices[tab[i][a]].IsMarque=false;  ///on marque toute la ligne
                m_vertices[tab[i][a]].Afficher_Somet();
            }

        }


    }

}
void Graph::Temporise()
{
    bool isTemp=false;
    m_interface->m_tool_box.add_child(m_interface->m_temp);
    m_interface->m_temp.set_pos(10,400);
    m_interface->m_temp.set_dim(35,40);
    m_interface->m_temp.set_bg_color(ROUGE);


    do
    {
        if(grman::mouse_click && m_interface->m_temp.is_mouse_over())
        {

            isTemp=true;

        }

    }
    while(isTemp==false);
}

int* Graph::marquage(int** adja, int _ordre, int s )
{

    int* marques = new int[ordre];
    int x,y;
    int cmp=0;
    /*int* tab = new int[_ordre];
    for(int i = 0 ; i< ordre ; i++ ){
            std::cout<<"s = " <<s<<std::endl;
        if((s<ordre)&&(!m_vertices[s].IsMarque)){
        tab[cmp]=s;
        std::cout<<"tab de " <<cmp <<" = "<< tab[cmp]<<std::endl;
        cmp++;

        }
        if(s>=ordre) {
            s = 0;
        }
    s++;

    }*/
    for(x=0; x<ordre; x++)
    {
        marques[x]= 0;
    }
    marques[s]=1;

    for(x=0; x<ordre; x++)
    {
        if(marques[x])
        {
            for(y=0; y<ordre; y++)
            {
                if(adja[x][y]&&!marques[y])
                {
                    marques[y]=1;
                }
            }
        }
    }

    for(x=s; x>0; x--)
    {

        if(marques[x])
        {
            for(y=0; y<ordre; y++)
            {
                if(adja[x][y]&&!marques[y])
                {
                    marques[y]=1;
                }
            }
        }
    }
    return marques;
}



int Graph::KparmisN(int k,int n)
{

    int result=0;
    int nFacto=1;
    int kFacto=1;
    int kMoinNFacto=1;
    int tmp =(n-k)+1;


    if( n != 0 && k != 0 )
    {

        for(int i=1 ; i < n+1 ; i++)
        {
            nFacto=i*nFacto;
        }

        for(int i=1 ; i < k+1 ; i++)
        {
            kFacto=i*kFacto;
        }
        for(int i=1 ; i < tmp ; i++)
        {
            kMoinNFacto=i*kMoinNFacto;
        }
        result=(nFacto)/(kFacto*kMoinNFacto);

        return result;
    }

}






///zoe : sous prgramme qui gère partie fonctinnel sans affichage
void Graph::fonctionnel()
{
    /// variables

    double N=0;
    double coeff=0;



    /// condition: si l'utilisateur appuie sur play et tant qu'il n'appuie pas sur pause ou rappuie sur play

    if(play)
    {

        std::cout << " " <<std::endl;
        std::cout << " ----- TEST FLUX -----"  <<std::endl;
        std::cout << " " <<std::endl;
        /// montee en memoire des valeures sur les curseurs ou sur fichier si curseur pas modi


        /// remplit pour chaque sommet vecteur de pred
        remplirPred();

        /// remplit pour chaque sommet vecteur de pred
        remplirSucc();




        std::cout << "  ---- Boucle ---- " <<std::endl;

        /// on calcul et met à jour le K de chaque sommet
        calculK();


        for(int i=0; i<ordre; i++)
        {m_vertices[i].m_interface->m_slider_value.set_value(m_vertices[i].m_value);

            for(int j=0; j<m_vertices[i].m_succ.size(); j++)
            {
                coeff=findEdgeWeight(i,m_vertices[i].m_succ[j]);
            }
            std::cout << "K= "<< m_vertices[i].m_K<<std::endl;
        }


        /// on calcul et met à jour le N de chaque somme
        calculN();


        /// anomations du mort quand la population est morte
        for(int i=0; i<ordre; i++)
        {m_vertices[i].m_interface->m_slider_value.set_value(m_vertices[i].m_value);

            if(m_vertices[i].m_value==0)
            {
                rest(70);
                m_vertices[i].m_interface->m_img.set_pic_name("Dead.png");

            }
        }
        std::cout << " "<<std::endl;




    }

    else
    {
        for(int i=0; i<ordre; i++)
        {
            m_vertices[i].m_interface->m_img.set_pic_name(m_vertices[i].m_name);
        }

    }



}





/// methode qui calcul et remplit le N des sommets
void Graph::calculN()
{
    double N_save=0;
    double N=0;
    double N_pourc=0;
    int K=0;
    int nb;
    int id_pred;
    double Npred=0;
    double val_ref=0;
    double coeff=0;
    std::vector<double> liste_N;


    /// parcours des sommets
    for(int k=0; k<ordre; k++)
    {
         /// sauvegarde du N+1 que l'on ecrase
        N_save=m_vertices[k].m_value;

        std::cout << "N_save"<< N_save;
        /// on recupere la valeure dans le sattributs
        N=m_vertices[k].m_value;

        /// on afficeh en pourcentage sur le graphe
        m_vertices[k].m_interface->m_slider_value.set_value(N*1000/(m_vertices[k].m_val_ref ));

        /// on recupere ce qu'il y a sur le graphe au cas ou utilisateur a changer (pause)
        N= m_vertices[k].m_interface->m_slider_value.get_value();

        /// conversion de valeur à pourcentage  avec la valeure de reference
        N=N*m_vertices[k].m_val_ref/1000;

        /// on fait monter dans les attributs cette valeure pour le calcul du K
        m_vertices[k].m_value=N;
        m_vertices[k].m_interface->m_slider_value.set_value(N*1000/(m_vertices[k].m_val_ref ));




        /// recupere le K
        K=m_vertices[k].m_K;

        if(K!=0) // si K=0 pas de succ don on peut pas se reproduire et manger
        {


            std::cout << "N+1.1 = N + r * N * (1 - ( N / K )) "<<std::endl;
            std::cout<< "N+1.1 = ("<< N_save << ") + ("<<m_vertices[k].m_r << ") * (" <<N_save<<") * (1-(" <<N_save<<" / "<<K << ") = "<<std::endl;
            N= (N_save) + (m_vertices[k].m_r)*(N_save)*(1-(N_save)/K);

        }

        /// on recupere le nombre de ses predecesseurs
        nb=m_vertices[k].m_pred.size();
        //std::cout<< "N+1 = N ";


            for(int i=0; i<nb; i++)
            {
                id_pred=m_vertices[k].m_pred[i];

                coeff=findEdgeWeight(id_pred, k);

                /// N inchange encore
                Npred=m_vertices[id_pred].m_value;

                N=N-(coeff*Npred);
                // std::cout<< "- ( "<<coeff<<" * "<<Npred<< " ) " ;
                if(N<=0) /// pas de pop negative possible
                {
                    N=0;
                }
            liste_N.push_back(N);
            }

            //std::cout<< " = " << N<<std::endl;
            /// sauvegarde des valeurs de N dans des vecteurs

            //std::cout<< " " <<std::endl;



        // std::cout<< " " <<std::endl;
    }


    /// parcours des sommets pour montee en memoir les vecteurs dans les attributs
    for(int k=0; k<ordre; k++)
    {
        m_vertices[k].m_value=liste_N[k];
        std::cout << m_vertices[k].m_name<<" N = "<< m_vertices[k].m_value<<std::endl;

        /// conversion de valeur à pourcentage  avec la valeure de reference
        //val_ref=m_vertices[k].m_val_ref;
       // N_pourc= 1000*N/val_ref;

        /// afichage de cette valeur sur les curseurs
        //m_vertices[k].m_interface->m_slider_value.set_value(N_pourc);
        //rest(90);


    }

}

/// methode qui calcul et remplit le K des sommets
void Graph::calculK()
{
    int nb=0;
    int id_succ=0, id_arc=0;
    double N=0;
    double coeff=0;
    double K=0;

    /// parcours sommet
    for(int k=0; k<ordre; k++)
    {
        K=0;
        /// on recupere le nombre de ses predecesseurs = le nombre d'arc
        nb=m_vertices[k].m_succ.size();

        /// pour tous ces succ on cherche le sommet predecesseur relié a cette arete
        for(int i=0; i<nb; i++)
        {
            /// on recupere l'indice du succ
            id_succ=m_vertices[k].m_succ[i];

            /// on recupere son coeff = poids
            coeff=findEdgeWeight(k,id_succ);

            ///on recupere le nombre de pop du succ
            N=m_vertices[id_succ].m_interface->m_slider_value.get_value();


            /// on calcul K
            K=K+(coeff*N);


        }
        /// sauvegarde dans attributs
        m_vertices[k].m_K=K;
        // std::cout << "K= "<< m_vertices[k].m_K<<std::endl;
    }
}

/// methode qui remplit le vecteur des pred de tous les sommets
void Graph::remplirPred()
{
    int id_arc, id_sfrom, nb;
    /// on parcourt sommets
    for(int k=0; k<ordre; k++)
    {
        /// on recupere le nombre de ses predecesseurs = le nombre d'arc
        nb=m_vertices[k].m_out2.size();

        /// pour tous ces pred on cherche le sommet predecesseur relié a cette arete
        for(int i=0; i<nb; i++)
        {
            /// on recupere l'index d'un arc du pred
            id_arc=m_vertices[k].m_out2[i];

            /// on recupere le sommet m_to qu'elle relie au sommet [k]
            id_sfrom= m_edges[id_arc].m_from;
            ///montee en memoire
            m_vertices[k].m_pred.push_back(id_sfrom);

        }
    }
}

/// methode qui remplit le vecteur des succ de tous les sommets
void Graph::remplirSucc()
{
    int id_arc, id_sto, nb;
    /// on parcourt sommets
    for(int k=0; k<ordre; k++)
    {
        /// on recupere le nombre de ses succ = le nombre d'arc
        nb=m_vertices[k].m_in2.size();

        /// pour tous ces succ on cherche le sommet succ relié a cette arete
        for(int i=0; i<nb; i++)
        {
            /// on recupere l'index d'un arc du succ
            id_arc=m_vertices[k].m_in2[i];

            /// on recupere le sommet m_from qu'elle relie au sommet [k]
            id_sto= m_edges[id_arc].m_to;

            ///montee en memoire
            m_vertices[k].m_succ.push_back(id_sto);

        }
    }
}

/// methode qui renvoit le poids de l'arete des deux sommets en parametre
float Graph::findEdgeWeight(int sfrom, int sto)
{
    int s1=0;
    int s2=0;

    double poids=0;

    /// parcourt la map d'arete
    for(auto &elt : m_edges)
    {
        /// accede à m-from et m_to
        s1= elt.second.m_from;
        s2= elt.second.m_to;

        /// si les sommets s1 et s2 sont les meme que les sommets en parametres on retourne la valeur de l'arete (coeff)
        if(s1==sfrom && s2==sto)
        {
            poids= elt.second.m_interface->m_slider_weight.get_value();

            return poids;
        }
    }
}



void Graph::supprimerVertex()
{

    std::map<int,Vertex>::iterator it1;
    std::map<int,Edge>::iterator it2;

    for ( auto &elmt : m_vertices)
    {
        if(elmt.second.IsHide==true)
        {
            elmt.second.Cacher_Sommet();

            //std::cout<<elmt.second.m_out.size();

            for(int i =0 ; i < elmt.second.m_in.size(); i++)
            {
                m_edges[elmt.second.m_in[i]].hide_edge_in();

            }

            for(int i =0 ; i < elmt.second.m_out.size(); i++)
            {
                m_edges[elmt.second.m_out[i]].hide_edge_out();



            }
        }
    }
}





void Graph::charger(std::string graphName)
{
    std::cout<<graphName<<std::endl;
    std::ifstream fichier (graphName+".txt",std::ios::in);




    int indxVertex,posX, posY, r,indxEdge, vertexIn, vertexOut;
    double poidEdge,poidVertex, val_ref;
    std::string picName;
    bool bo=false;


    if (fichier)
    {


        fichier >> Graph::ordre;
        fichier >> Graph::nbrEdge;

        for(int i=0 ; i <ordre  ; i++)
        {
            fichier >> poidVertex;
            fichier >> posX;
            fichier >> posY;
            fichier >> r;
            fichier >> val_ref;
            fichier >> picName;


            add_interfaced_vertex(i,poidVertex,r, val_ref,posX,posY,picName+".jpg");

        }
        for(int j=0 ; j < nbrEdge ; j++)
        {

            /// montee en memoire des attributs pour interface
            fichier >> vertexIn;
            fichier >> vertexOut;
            fichier >> poidEdge;
            std::cout<< vertexIn<<" "<<vertexOut<<" "<<poidEdge<<std::endl;
            add_interfaced_edge(j,vertexIn,vertexOut,poidEdge);
        }
        fichier.close();


    }

}


void Graph::sauvgarder(std::string graphName)
{

    std::ofstream fichier(graphName+".txt",std::ios::out | std::ios::trunc);
    std::string picName;

    if(fichier)
    {
        fichier << Graph::ordre <<std::endl;
        fichier << Graph::nbrEdge<<std::endl;

        for(auto &elt : m_vertices)
        {
            fichier << elt.second.m_value<<" ";
            fichier <<elt.second.m_interface->m_top_box.get_frame_pos().x<<" ";
            fichier <<elt.second.m_interface->m_top_box.get_frame_pos().y<<" ";
            fichier <<elt.second.m_r<<" ";
            fichier <<elt.second.m_val_ref<<" ";
            picName=elt.second.m_interface->m_img.get_pic_name();
            picName.erase(picName.size()-4,4);
            fichier <<picName<<std::endl;
        }

        for(auto &elt : m_edges)
        {


            fichier << elt.second.m_from<<" ";
            fichier << elt.second.m_to<<" ";
            fichier << elt.second.m_weight<<std::endl;

        }
        fichier.close();
        std::cout<<"Sauvgarde done";
    }

}

int Graph::menugraph()
{
    int i=0;

    if(grman::mouse_click && m_interface->m_afficher_sommet.is_mouse_over())
    {

        for ( auto &elmt : m_vertices )
        {

            elmt.second.IsHide=false;
            elmt.second.Afficher_Somet();
        }
        for ( auto & elmt : m_edges )
        {

            elmt.second.Afficher_Edges(m_vertices[Sommet_suite_in[i]],m_vertices[Sommet_suite_out[i]]);
            i++;
            //std::cout<<"l'arrete "<< i <<"est composé des sommet " << Sommet_suite_in[i]<<" et "<< Sommet_suite_out[i]<<std::endl;
            if(Sommet_suite_in[i]==0 && Sommet_suite_out[i]==1)
            {
                std::cout<<i<<"t";
            }
        }

    }
    if(grman::mouse_click && m_interface->m_savebutton.is_mouse_over())
    {

        sauvgarder(m_nomgraph);

    }
    if(grman::mouse_click&1 && m_interface->m_button_flux.is_mouse_over())
    {
        fonctionnel();

        m_interface->m_tool_box.remove_child(m_interface->m_button_flux);
    }

    if(grman::mouse_click && m_interface->m_button_K_co.is_mouse_over())
    {
        IsConnex();



    }

    if(grman::mouse_click && m_interface->m_retour.is_mouse_over())
    {

        m_quitter= 1;

    }
    ///partie qui gère l'affichege des composantes fortement connexe
    if(grman::mouse_unclick&1 && m_interface->m_cmp_fconnexe.is_mouse_over())
    {

        if(m_interface->m_cmp_fconnexe.get_value())
        {

            search_all_cmpfc();
            visuelle_forte_connexite(1);


            //l'interface est initialisé ici car on veur qu'il disparaisse.

            m_interface->m_tool_box.add_child(m_interface->m_afficher_graphreduit);
            m_interface->m_afficher_graphreduit.set_dim(70,30);
            m_interface->m_afficher_graphreduit.set_gravity_x(grman::GravityX::Center);
            m_interface->m_afficher_graphreduit.set_posy(535);
            m_interface->m_afficher_graphreduit.set_bg_color(ROUGECLAIR);
            m_interface->m_afficher_graphreduit.add_child(m_interface->m_afficher_graphreduit_text1);
            m_interface->m_afficher_graphreduit.add_child(m_interface->m_afficher_graphreduit_text2);
            m_interface->m_afficher_graphreduit_text1.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Up);
            m_interface->m_afficher_graphreduit_text2.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);
            m_interface->m_afficher_graphreduit_text1.set_message("Graph");
            m_interface->m_afficher_graphreduit_text2.set_message("réduit");
            m_interface->m_afficher_graphreduit_text1.set_posy(m_interface->m_afficher_graphreduit_text1.get_posy()+4);
            m_interface->m_afficher_graphreduit_text2.set_posy(m_interface->m_afficher_graphreduit_text2.get_posy()+4);


            m_interface->m_tool_box.add_child(m_interface->m_cmp_fconnexe_off);
            m_interface-> m_cmp_fconnexe_off.set_dim(70,30);
            m_interface-> m_cmp_fconnexe_off.set_gravity_x(grman::GravityX::Center);
            m_interface-> m_cmp_fconnexe_off.set_posy(566);
            m_interface-> m_cmp_fconnexe_off.set_bg_color(ROUGECLAIR);
            m_interface-> m_cmp_fconnexe_off.add_child(m_interface->m_cmp_fconnexe_off_text1);
            m_interface-> m_cmp_fconnexe_off_text1.set_message("Off");
            m_interface->m_tool_box.add_child(m_interface->m_nb_cmpfc);
            m_interface->m_nb_cmpfc.set_dim(70,30);
            m_interface->m_nb_cmpfc.set_posy(609);
            m_interface->m_nb_cmpfc.set_message("nb cmp:" + std::to_string(m_tabcmpfc.size()));


        }





        m_interface->m_cmp_fconnexe.set_value(!m_interface->m_cmp_fconnexe.get_value());

    }




    if(grman::mouse_unclick&1 && m_interface->m_afficher_graphreduit.is_mouse_over())
    {
        if(m_interface->m_afficher_graphreduit.get_value())
        {

            Afficher_graphReduit(1);
        }
    }

    if(grman::mouse_unclick&1 && m_interface->m_cmp_fconnexe_off.is_mouse_over())
    {
        visuelle_forte_connexite(0);
        Afficher_graphReduit(0);
        m_interface->m_tool_box.remove_child(m_interface->m_cmp_fconnexe_off);
        m_interface->m_tool_box.remove_child(m_interface->m_nb_cmpfc);
        m_interface->m_tool_box.remove_child(m_interface->m_afficher_graphreduit);
    }
    if(grman::mouse_click && m_interface->m_button_play.is_mouse_over())
    {
        play=true;


    }

    if(grman::mouse_click && m_interface->m_button_pause.is_mouse_over())
    {
        play=false;



        m_interface->m_tool_box.add_child(m_interface->m_button_flux);
        m_interface->m_button_flux.set_gravity_x(grman::GravityX::Center);
        m_interface->m_button_flux.set_posy(352);
        m_interface->m_button_flux.set_dim(70,30);
        m_interface->m_button_flux.set_bg_color(ORANGESOMBRE);
        m_interface->m_button_flux.add_child(m_interface->m_text1_flux);
        m_interface->m_button_flux.add_child(m_interface->m_text2_flux);
        m_interface->m_text1_flux.set_message("ModeF");
        m_interface->m_text2_flux.set_message("OFF");
        m_interface->m_text1_flux.set_posy(6);
        m_interface->m_text2_flux.set_posy(18);


    }


    return 0;
}



void Graph::set_quitter(bool x)
{
    m_quitter=x;
}

void Graph::destroy_graph()
{

    for(std::map<int,Vertex>::iterator it= m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        m_interface->m_main_box.remove_child(it->second.m_interface->m_top_box);

    }

    m_vertices.clear();

    for(std::map<int,Edge>::iterator et= m_edges.begin(); et!=m_edges.end(); et++)
    {
        m_interface->m_main_box.remove_child(et->second.m_interface->m_top_edge);


    }
    m_edges.clear();

    m_interface.reset();
    m_interface=nullptr;

}

/// permet de démarquer tout les vertex

void Graph::Reset_marquage_vertex()
{
    for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_marque(0);
    }
}


void Graph :: Reset_marquage_marqued_connexeinout()
{
    for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_marque_connexeout(0);
        it->second.set_marque_connexein(0);
    }
}

void Graph:: Reset_marquage_isincompf_connexeinout()
{
    for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_connexein(0);
        it->second.set_connexeout(0);
    }
}

/// Recherche d'une composante fortement connexe


std::vector<Vertex*> Graph:: Cmp_fort_connexe_serach(Vertex s)
{


    std::vector<Vertex*> c ; // la composante fortement connexe

    bool add=true;


    m_vertices[s.get_idx()].set_connexeout(true);
    m_vertices[s.get_idx()].set_connexein(true);

    for(int i=0; i<m_vertices[1].m_in.size(); i++)
    {
        //std::cout << m_vertices[1].m_out[i];




    }



    while(add)
    {
        add=0;
        for(int i=0; i<ordre; i++)
        {
            if(!m_vertices[i].get_marque_connexeout() && m_vertices[i].get_connexeout())
            {
                m_vertices[i].set_marque_connexeout(true);

                for(int k=0; k<ordre; k++)
                {
                    if(m_vertices[i].islinked(m_vertices[k],1)&& !m_vertices[k].get_marque_connexeout())
                    {

                        m_vertices[k].set_connexeout(true);
                        add=1;


                    }
                }
            }
        }
    }



    add=true;
    while(add)
    {
        add=0;
        for(int i=0; i<ordre; i++)
        {
            if(!m_vertices[i].get_marque_connexein() && m_vertices[i].get_connexein() )
            {
                m_vertices[i].set_marque_connexein(true);

                for(int k=0; k<ordre; k++)
                {
                    if(m_vertices[i].islinked(m_vertices[k],0) && !m_vertices[k].get_marque_connexein())
                    {

                        m_vertices[k].set_connexein(true);
                        add=1;

                    }
                }
            }
        }
    }

    for (int z=0 ; z<ordre; z++)
    {
        if(m_vertices[z].get_connexein() && m_vertices[z].get_connexeout() && !m_vertices[z].get_marque())
        {
            c.push_back(new Vertex(m_vertices[z]));
            m_vertices[z].set_marque(true);



        }
    }
//std::cout << c.size();
    return c;
}

std::vector<std::vector<Vertex*>> Graph::search_all_cmpfc()
{
    Reset_marquage_vertex();
    Reset_marquage_marqued_connexeinout();
    Reset_marquage_isincompf_connexeinout();
    m_tabcmpfc.clear();



    bool* marquage= new bool [m_vertices.size()];
    for (int i =0; i<m_vertices.size(); i++)
    {
        marquage[i]=false;
    }

    for(int i=0; i<ordre; i++)
    {
        if(!marquage[i])
        {
            m_tabcmpfc.push_back( Cmp_fort_connexe_serach(m_vertices[i]));
            marquage[i]=true;

            for(int k=0; k<m_tabcmpfc.back().size(); k++)
            {


                marquage[m_tabcmpfc.back()[k]->get_idx()] = true;

            }
        }

    }


    for(int i=0; i<m_tabcmpfc.size(); i++)
    {
        for(int k=0; k<m_tabcmpfc[i].size(); k++)
        {
            std::cout << m_tabcmpfc[i][k]->get_idx();
        }
        std::cout << std::endl;
    }

    return m_tabcmpfc;
}






void Graph:: visuelle_forte_connexite(bool activate)
{
    int color;
    if(activate)
    {

        for(int i=0; i<m_tabcmpfc.size(); i++)
        {
            color= COULEURALEATOIRECLAIR;

            for(int k=0; k<m_tabcmpfc[i].size(); k++)
            {
                m_tabcmpfc[i][k]->m_interface->m_top_box.set_border_color(color);
                m_tabcmpfc[i][k]->m_interface->m_top_box.m_isincmpf=true;  // paramètre qui permet de sélectioner quel get_color_bg() utiliser.

                /* if(k<m_tabcmpfc[i].size()-1)
                 {
                    // if(findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx())< INFINI)
                     {
                       std::cout << findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx());
                      m_edges[findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                      m_edges[findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx())].m_interface->m_box_edge.set_bg_color(color);

                     }
                  //   else
                     {
                     // m_edges[findEdge(m_tabcmpfc[i][k+1]->get_idx(),m_tabcmpfc[i][k]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                     // m_edges[findEdge(m_tabcmpfc[i][k+1]->get_idx(),m_tabcmpfc[i][k]->get_idx())].m_interface->m_box_edge.set_bg_color(color);

                     }


                     // std::cout<< findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx());
                 }





                }
                   // on sort de la boucle pour la dernière arrete afin de ne pas faire de dépassement mémoire

                     /*if(findEdge(m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx(),m_tabcmpfc[i][0]->get_idx())!=INFINI)
                     {
                      m_edges[findEdge(m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx(),m_tabcmpfc[i][0]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                      m_edges[findEdge(m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx(),m_tabcmpfc[i][0]->get_idx())].m_interface->m_box_edge.set_bg_color(color);
                     }
                     else
                     {
                      m_edges[findEdge(m_tabcmpfc[i][0]->get_idx(),m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                      m_edges[findEdge(m_tabcmpfc[i][0]->get_idx(),m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx())].m_interface->m_box_edge.set_bg_color(color);
                     }*/
                //  std::cout<< findEdge(2,0);*/


            }






        }
    }

    else
    {
        for(int i=0; i<m_tabcmpfc.size(); i++)
        {

            for(int k=0; k<m_tabcmpfc[i].size(); k++)
            {

                m_tabcmpfc[i][k]->m_interface->m_top_box.m_isincmpf=false;

            }

        }
    }




}



void Graph::Afficher_graphReduit(bool activate)
{

    if(activate)
    {
        for(int k=0; k<m_tabcmpfc.size(); k++)
        {
            m_interface->m_tab_cmp_GraphReduit.push_back(new grman::WidgetBox);
            m_interface->m_tab_texte_GraphReduit.push_back(new grman::WidgetText);

            if(k<m_tabcmpfc.size()-1)
            {
                m_interface->m_tab_edge_GraphReduit.push_back(new grman::WidgetEdge);
            }
        }
        for(int i=0; i<m_interface->m_tab_cmp_GraphReduit.size(); i++)
        {
            m_interface->m_main_box.add_child(*m_interface->m_tab_cmp_GraphReduit[i]);
            m_interface->m_tab_cmp_GraphReduit[i]->set_pos(m_tabcmpfc[i][0]->m_interface->m_top_box.get_posx(),m_tabcmpfc[i][0]->m_interface->m_top_box.get_posy());
            m_interface->m_tab_cmp_GraphReduit[i]->set_dim(130,100);
            m_interface->m_tab_cmp_GraphReduit[i]->set_bg_color(ROUGESOMBRE);
            m_interface->m_tab_cmp_GraphReduit[i]->add_child(*m_interface->m_tab_texte_GraphReduit[i]);
            m_interface->m_tab_texte_GraphReduit[i]->set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);
            m_interface->m_tab_texte_GraphReduit[i]->set_message("cmpfconexe n°" + std::to_string(i));

            if(i< m_interface->m_tab_edge_GraphReduit.size())
            {
                m_interface->m_main_box.add_child(*m_interface->m_tab_edge_GraphReduit[i]);
                m_interface->m_tab_edge_GraphReduit[i]->attach_from(m_tabcmpfc[i][0]->m_interface->m_top_box);
                m_interface->m_tab_edge_GraphReduit[i]->attach_to(m_tabcmpfc[i+1][0]->m_interface->m_top_box);
                m_interface->m_tab_edge_GraphReduit[i]->reset_arrow_with_bullet();

            }
        }

        for(int i=0; i<m_tabcmpfc.size(); i++)
        {
            for(int k=0; k<m_tabcmpfc[i].size(); k++)
            {

                {
                    m_tabcmpfc[i][k]->Cacher_Sommet();
                    for(int z=0; z<m_tabcmpfc[i][k]->m_in.size(); z++)
                    {
                        m_edges[m_tabcmpfc[i][k]->m_in[z]].hide_edge_in();
                    }
                    for(int z=0; z<m_tabcmpfc[i][k]->m_out.size(); z++)
                    {
                        m_edges[m_tabcmpfc[i][k]->m_out[z]].hide_edge_out();
                    }
                }

            }
        }
    }


    else
    {

        for(int i=0; i<m_vertices.size(); i++)
        {
            m_vertices[i].Afficher_Somet();
        }

        for(int l=0; l<m_edges.size(); l++)
        {
            m_edges[l].Afficher_Edges(m_vertices[m_edges[l].m_from],m_vertices[m_edges[l].m_to]);
        }



        for(int k=0; k<m_interface->m_tab_cmp_GraphReduit.size(); k++)
        {

            m_interface->m_main_box.remove_child(*m_interface->m_tab_cmp_GraphReduit[k]);

            delete m_interface->m_tab_cmp_GraphReduit[k];
            delete m_interface->m_tab_texte_GraphReduit[k];

            if(k<m_interface->m_tab_cmp_GraphReduit.size()-1)
            {

                m_interface->m_main_box.remove_child(*m_interface->m_tab_edge_GraphReduit[k]);
                delete m_interface->m_tab_edge_GraphReduit[k];
            }



        }
        m_interface->m_tab_cmp_GraphReduit.clear();
        m_interface->m_tab_texte_GraphReduit.clear();
        m_interface->m_tab_edge_GraphReduit.clear();
    }

}

bool Graph::get_quitter()
{
    return m_quitter;
}



/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    menugraph();
    supprimerVertex();


    m_interface->m_top_box.update();

    if(play)
    {
        fonctionnel();
    }
    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int r, double val_ref, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :

    m_vertices[idx] = Vertex(value,r, val_ref, pic_name, vi);

    m_vertices[idx].m_r=r;


    m_vertices[idx].set_idx(idx);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{

    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;


   m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);

    Sommet_suite_in.push_back(id_vert1);
    Sommet_suite_out.push_back(id_vert2);




    if((idx!=id_vert1) ||(idx!=id_vert2))
     {
         m_vertices[id_vert1].m_in2.push_back(idx);
         m_vertices[id_vert2].m_out2.push_back(idx);

     }

}

/// methode qui renvoit indice de l'arete entre deux sommets en parametre
int Graph::findEdge(int sfrom, int sto)
{
    int s1=0;
    int s2=0;

    double idx=0;


    /// parcourt la map d'arete
    for(auto &elt : m_edges)
    {
        /// accede à m-from et m_to
        s1= elt.second.m_from;
        s2= elt.second.m_to;

        /// si les sommets s1 et s2 sont les meme que les sommets en parametres on retourne la valeur de l'arete (coeff)
        if(s1==sfrom && s2==sto)
        {
            idx= elt.first;

            return idx;
        }
    }
}
