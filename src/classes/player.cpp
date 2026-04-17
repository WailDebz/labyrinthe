#include "Aventurier.h"
#include "Donjon.h"
#include "Case.h"
#include "../constants.h"
#include <iostream>
#include <algorithm>

#ifdef _WIN32
    #include <cstdlib>
    #define CLEAR_SCREEN() system("cls")
#else
    #include <cstdlib>
    #define CLEAR_SCREEN() system("clear")
#endif

// ============================================================================
// Constructeur
// ============================================================================
Aventurier::Aventurier(int startX, int startY)
    : posX(startX), posY(startY),
      prevX(startX), prevY(startY),
      sante(SANTE_MAX), inventaire(0) {}

// ============================================================================
// Déplacement
// ============================================================================
void Aventurier::deplacer(int nx, int ny) {
    prevX = posX;
    prevY = posY;
    posX = nx;
    posY = ny;
}

// ============================================================================
// Résolution de case (dispatch polymorphe)
// ============================================================================
void Aventurier::resoudreCase(Case* c) {
    if (c != nullptr) {
        c->appliquerEffet(*this);
    }
}

// ============================================================================
// Gestion de l'état
// ============================================================================
bool Aventurier::estVivant() const {
    return sante > 0;
}

void Aventurier::recevoirDegats(int dmg) {
    sante = std::max(0, sante - dmg);
}

void Aventurier::ajouterTresor(int val) {
    inventaire += val;
}

// ============================================================================
// Accesseurs
// ============================================================================
std::pair<int, int> Aventurier::getPosition() const {
    return {posX, posY};
}

std::pair<int, int> Aventurier::getPositionPrecedente() const {
    return {prevX, prevY};
}

// ============================================================================
// Affichage du statut
// ============================================================================
void Aventurier::afficherStatut() const {
    std::cout << "\n  Position : (" << posX << ", " << posY << ")"
              << "   Sante : " << sante << "/" << SANTE_MAX
              << "   Inventaire : " << inventaire << " tresor(s)\n";
}

// ============================================================================
// Surcharge de l'opérateur <<
// ============================================================================
std::ostream& operator<<(std::ostream& os, const Aventurier& a) {
    os << "Aventurier[pos=(" << a.posX << "," << a.posY
       << "), HP=" << a.sante << "/" << SANTE_MAX
       << ", tresors=" << a.inventaire << "]";
    return os;
}

// ============================================================================
// Boucle de jeu principale
// ============================================================================
void Aventurier::boucleDeJeu(Donjon& d) {
    auto sortie = d.getSortie();

    while (estVivant() && getPosition() != sortie) {
        CLEAR_SCREEN();

        // Afficher le donjon avec le joueur
        d.afficher(*this);

        // Afficher le statut du joueur
        afficherStatut();

        // Lire l'entrée du joueur
        std::cout << "\n  Deplacement [z]Haut [s]Bas [q]Gauche [d]Droite [p]Chemin : ";
        char input;
        std::cin >> input;

        int nx = posX;
        int ny = posY;

        switch (input) {
            case 'z': case 'Z': ny--; break;   // Haut
            case 's': case 'S': ny++; break;   // Bas
            case 'q': case 'Q': nx--; break;   // Gauche
            case 'd': case 'D': nx++; break;   // Droite
            case 'p': case 'P': {
                // Afficher le chemin optimal via BFS
                auto chemin = d.trouverChemin(getPosition(), sortie);
                if (chemin.empty()) {
                    std::cout << "  Aucun chemin trouve vers la sortie !\n";
                } else {
                    CLEAR_SCREEN();
                    d.afficherChemin(*this, chemin);
                    std::cout << "\n  Distance a la sortie : "
                              << (chemin.size() - 1) << " cases\n";
                }
                std::cout << "  Appuyez sur une touche pour continuer...";
                std::cin >> input;  // Pause
                continue;
            }
            default:
                continue;   // Touche invalide, on recommence
        }

        // Vérifier les limites et la franchissabilité
        if (!d.estDansBornes(nx, ny)) {
            std::cout << "  Hors limites !\n";
            continue;
        }

        Case* cible = d.getCase(nx, ny);
        if (!cible->estFranchissable()) {
            std::cout << "  Un mur bloque le passage.\n";
            continue;
        }

        // Déplacement valide
        deplacer(nx, ny);

        // Résoudre l'effet de la case
        resoudreCase(cible);
    }

    // Fin de partie
    CLEAR_SCREEN();
    d.afficher(*this);
    afficherStatut();

    std::cout << "\n  ==============================\n";
    if (getPosition() == sortie) {
        std::cout << "    VICTOIRE ! Vous avez survecu au donjon !\n";
    } else {
        std::cout << "    GAME OVER. Vous etes mort dans le donjon.\n";
    }
    std::cout << "    Tresors collectes : " << inventaire << "\n";
    std::cout << "    Sante restante    : " << sante << "/" << SANTE_MAX << "\n";
    std::cout << "  ==============================\n\n";
}
