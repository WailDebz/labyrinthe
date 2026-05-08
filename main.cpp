#include <iostream>
#include <cstdlib>
#include <ctime>
#include "src/classes/Donjon.h"
#include "src/classes/Aventurier.h"
#include "src/constants.h"
int main(int argc, char* argv[]) {
    int largeur = LARGEUR_DEFAULT;
    int hauteur = HAUTEUR_DEFAULT;
    if (argc >= 3) {
        largeur = std::atoi(argv[1]);
        hauteur = std::atoi(argv[2]);
        if (largeur < 5) largeur = 5;
        if (hauteur < 5) hauteur = 5;
    }
    std::cout << "\n";
    std::cout << "  DONJON & LABYRINTHE\n";
    std::cout << "  Dimensions : " << largeur << " x " << hauteur << "\n";
    std::cout << "  Controles  : z/q/s/d = deplacements, p = chemin\n";
    std::cout << "  Appuyez sur Entree pour commencer...";
    std::cin.get();
    Donjon donjon;
    donjon.generer(largeur, hauteur);
    auto entree = donjon.getEntree();
    Aventurier joueur(entree.first, entree.second);
    joueur.boucleDeJeu(donjon);
    return 0;
}
