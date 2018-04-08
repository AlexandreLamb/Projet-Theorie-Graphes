#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "Menu.h"
#include "tools_bar.h"


int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Menu m;
    Menu m2;
    Graph g;
    bool Isclick = true ;

    m2.ecran_Aceuille();
    while(Isclick)
    {
       Isclick = m2.update2();
        grman::mettre_a_jour();

    }


    m.demarermenu();

    while (!key[KEY_SPACE])
    {
        m.update();

      switch(m.choixgraph())
        {
        case 1:
             g.make_graph_1();

             while(!key[KEY_ESC] && g.get_quitter()!=1)
             {

              g.update();
              grman::mettre_a_jour();
             }

             g.set_quitter(0);
             g.destroy_graph();


            break;

        case 2:
            g.make_graph_2();

             while(!key[KEY_ESC] && g.get_quitter()!=1)
             {
              g.update();
              grman::mettre_a_jour();
             }
             g.set_quitter(0);
             g.destroy_graph();
            break;

        case 3:

             g.make_graph_3();
             while(!key[KEY_ESC] && g.get_quitter()!=1)
             {
              g.update();
              grman::mettre_a_jour();
             }
             g.set_quitter(0);
             g.destroy_graph();
            break;



        default:
            grman::mettre_a_jour();
        }

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


