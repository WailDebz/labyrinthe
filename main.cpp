#include <iostream>
#include <cstdlib>
#include <ctime>
#include "src/classes/Donjon.h"
#include "src/classes/Aventurier.h"
#include "src/constants.h"

int main(int argc, char* argv[]) {
    // Déterminer les dimensions du donjon (par défaut ou via arguments)
    int largeur = LARGEUR_DEFAULT;
    int hauteur = HAUTEUR_DEFAULT;

    if (argc >= 3) {
        largeur = std::atoi(argv[1]);
        hauteur = std::atoi(argv[2]);

        // Validation minimale
        if (largeur < 5) largeur = 5;
        if (hauteur < 5) hauteur = 5;
    }

    // --- Affichage du titre ---
    std::cout << "\n";
    std::cout << "  ============================================\n";
    std::cout << "       DONJON & LABYRINTHE — Exploration\n";
    std::cout << "  ============================================\n";
    std::cout << "  Dimensions : " << largeur << " x " << hauteur << "\n";
    std::cout << "  Controles  : z/q/s/d = deplacements, p = chemin\n";
    std::cout << "  ============================================\n\n";
    std::cout << "  Appuyez sur Entree pour commencer...";
    std::cin.get();

    // --- Génération du donjon ---
    Donjon donjon;
    donjon.generer(largeur, hauteur);

    // --- Création de l'aventurier à l'entrée ---
    auto entree = donjon.getEntree();
    Aventurier joueur(entree.first, entree.second);

    // --- Lancement de la boucle de jeu ---
    joueur.boucleDeJeu(donjon);

    return 0;
}
