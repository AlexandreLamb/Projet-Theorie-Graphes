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
    Graph g;
    m.demarermenu();

    while (!key[KEY_SPACE])
    {
        m.update();

        switch(m.choixgraph())
        {
        case 1:
             g.make_graph_1();
             while(!key[KEY_ESC] &&    g.menugraph()!=1)
             {
              g.update();
              grman::mettre_a_jour();
             }
             g.destroy_graph();


            break;

        case 2:
            break;

        case 3:
            break;

        default:
            grman::mettre_a_jour();

        }
    }


<<<<<<< HEAD
    //Tools_bar t;
    g.make_graph_1();
    g.fonctionnel();

=======
>>>>>>> Menu/Flo
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    /*while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();
       // t.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

    }*/

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


