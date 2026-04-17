#include "Donjon.h"
#include "Aventurier.h"
#include "CaseFactory.h"
#include "../TypeCase.h"
#include "../constants.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <queue>
#include <set>
#include <sstream>

// Moteur aléatoire global pour la génération
static std::mt19937 rng(std::random_device{}());

// ============================================================================
// Constructeur / Destructeur
// ============================================================================
Donjon::Donjon() : largeur(0), hauteur(0), entree({0, 0}), sortie({0, 0}) {}

Donjon::~Donjon() {
    for (int j = 0; j < hauteur; ++j) {
        for (int i = 0; i < largeur; ++i) {
            delete grille[j][i];
        }
    }
}

// ============================================================================
// Génération complète du donjon
// ============================================================================
void Donjon::generer(int larg, int haut) {
    // S'assurer que les dimensions sont impaires (nécessaire pour le maze)
    largeur  = (larg % 2 == 0) ? larg + 1 : larg;
    hauteur  = (haut % 2 == 0) ? haut + 1 : haut;

    // Phase 1 : Remplir la grille de murs
    grille.resize(hauteur);
    for (int j = 0; j < hauteur; ++j) {
        grille[j].resize(largeur);
        for (int i = 0; i < largeur; ++i) {
            grille[j][i] = CaseFactory::creerCase(TypeCase::MUR);
        }
    }

    // Phase 2 : Creuser le labyrinthe par Recursive Backtracking
    genererLabyrinthe(1, 1);

    // Phase 3 : Poser l'entrée et la sortie
    entree = {1, 1};
    sortie = {largeur - 2, hauteur - 2};

    // S'assurer que l'entrée et la sortie sont des passages
    if (grille[entree.second][entree.first]->getType() != TypeCase::PASSAGE) {
        delete grille[entree.second][entree.first];
        grille[entree.second][entree.first] = CaseFactory::creerCase(TypeCase::PASSAGE);
    }
    if (grille[sortie.second][sortie.first]->getType() != TypeCase::PASSAGE) {
        delete grille[sortie.second][sortie.first];
        grille[sortie.second][sortie.first] = CaseFactory::creerCase(TypeCase::PASSAGE);
    }

    // Phase 4 : Placer les éléments (trésors, monstres, pièges)
    placerElements();
}

// ============================================================================
// Recursive Backtracking — Génération du labyrinthe
// ============================================================================
void Donjon::genererLabyrinthe(int x, int y) {
    // Marquer la case courante comme passage
    delete grille[y][x];
    grille[y][x] = CaseFactory::creerCase(TypeCase::PASSAGE);

    // Directions possibles : (dx, dy) — pas de 2 cases
    int directions[4][2] = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};

    // Mélanger les directions aléatoirement
    std::shuffle(std::begin(directions), std::end(directions), rng);

    for (auto& dir : directions) {
        int nx = x + dir[0];
        int ny = y + dir[1];

        // Vérifier les bornes (on reste à l'intérieur des murs extérieurs)
        if (nx > 0 && nx < largeur - 1 && ny > 0 && ny < hauteur - 1) {
            // Vérifier que la cellule cible est encore un mur (non visitée)
            if (grille[ny][nx]->getType() == TypeCase::MUR) {
                // Casser le mur entre la cellule courante et la voisine
                int wallX = (x + nx) / 2;
                int wallY = (y + ny) / 2;
                delete grille[wallY][wallX];
                grille[wallY][wallX] = CaseFactory::creerCase(TypeCase::PASSAGE);

                // Récursion
                genererLabyrinthe(nx, ny);
            }
        }
    }
}

// ============================================================================
// Placement aléatoire des éléments
// ============================================================================
void Donjon::placerElements() {
    std::uniform_int_distribution<int> dist(0, 99);

    for (int j = 0; j < hauteur; ++j) {
        for (int i = 0; i < largeur; ++i) {
            // Ne pas toucher à l'entrée ni à la sortie
            if ((i == entree.first && j == entree.second) ||
                (i == sortie.first && j == sortie.second)) {
                continue;
            }

            // Ne remplacer que les passages
            if (grille[j][i]->getType() == TypeCase::PASSAGE) {
                int r = dist(rng);

                TypeCase nouveau;
                if (r < PROB_TRESOR) {
                    nouveau = TypeCase::TRESOR;
                } else if (r < PROB_MONSTRE) {
                    nouveau = TypeCase::MONSTRE;
                } else if (r < PROB_PIEGE) {
                    nouveau = TypeCase::PIEGE;
                } else {
                    continue;  // Reste un passage
                }

                delete grille[j][i];
                grille[j][i] = CaseFactory::creerCase(nouveau);
            }
        }
    }
}

// ============================================================================
// Affichage du donjon (sans joueur)
// ============================================================================
void Donjon::afficher() const {
    // Bordure supérieure
    std::cout << "  +";
    for (int i = 0; i < largeur; ++i) std::cout << "-";
    std::cout << "+\n";

    for (int j = 0; j < hauteur; ++j) {
        std::cout << "  |";
        for (int i = 0; i < largeur; ++i) {
            std::cout << grille[j][i]->afficher();
        }
        std::cout << "|\n";
    }

    // Bordure inférieure
    std::cout << "  +";
    for (int i = 0; i < largeur; ++i) std::cout << "-";
    std::cout << "+\n";
}

// ============================================================================
// Affichage du donjon avec le joueur (@) et la sortie (E)
// ============================================================================
void Donjon::afficher(const Aventurier& joueur) const {
    auto pos = joueur.getPosition();

    std::ostringstream buffer;

    // Bordure supérieure
    buffer << "  +";
    for (int i = 0; i < largeur; ++i) buffer << "-";
    buffer << "+\n";

    for (int j = 0; j < hauteur; ++j) {
        buffer << "  |";
        for (int i = 0; i < largeur; ++i) {
            if (i == pos.first && j == pos.second) {
                buffer << '@';  // Position du joueur
            } else if (i == sortie.first && j == sortie.second) {
                buffer << 'E';  // Sortie
            } else {
                buffer << grille[j][i]->afficher();
            }
        }
        buffer << "|\n";
    }

    // Bordure inférieure
    buffer << "  +";
    for (int i = 0; i < largeur; ++i) buffer << "-";
    buffer << "+\n";

    std::cout << buffer.str();
}

// ============================================================================
// Affichage du donjon avec le chemin BFS marqué par '.'
// ============================================================================
void Donjon::afficherChemin(const Aventurier& joueur,
                            const std::vector<std::pair<int, int>>& chemin) const {
    auto pos = joueur.getPosition();

    // Convertir le chemin en set pour recherche rapide
    std::set<std::pair<int, int>> cheminSet(chemin.begin(), chemin.end());

    std::ostringstream buffer;

    buffer << "  +";
    for (int i = 0; i < largeur; ++i) buffer << "-";
    buffer << "+\n";

    for (int j = 0; j < hauteur; ++j) {
        buffer << "  |";
        for (int i = 0; i < largeur; ++i) {
            if (i == pos.first && j == pos.second) {
                buffer << '@';
            } else if (i == sortie.first && j == sortie.second) {
                buffer << 'E';
            } else if (cheminSet.count({i, j}) > 0) {
                buffer << '.';   // Case faisant partie du chemin
            } else {
                buffer << grille[j][i]->afficher();
            }
        }
        buffer << "|\n";
    }

    buffer << "  +";
    for (int i = 0; i < largeur; ++i) buffer << "-";
    buffer << "+\n";

    std::cout << buffer.str();
}

// ============================================================================
// Pathfinding — BFS (Breadth-First Search)
// ============================================================================
std::vector<std::pair<int, int>> Donjon::trouverChemin(
    std::pair<int, int> depart,
    std::pair<int, int> arrivee) const {

    // Tableaux de visite et de parents
    std::vector<std::vector<bool>> visite(hauteur, std::vector<bool>(largeur, false));
    std::vector<std::vector<std::pair<int, int>>> parent(
        hauteur, std::vector<std::pair<int, int>>(largeur, {-1, -1}));

    // File FIFO pour le BFS
    std::queue<std::pair<int, int>> file;

    file.push(depart);
    visite[depart.second][depart.first] = true;

    // Vecteurs de direction : droite, gauche, bas, haut
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (!file.empty()) {
        auto courant = file.front();
        file.pop();

        // Arrivée trouvée — reconstruire le chemin
        if (courant == arrivee) {
            std::vector<std::pair<int, int>> chemin;
            auto c = arrivee;
            while (c != depart) {
                chemin.push_back(c);
                c = parent[c.second][c.first];
            }
            chemin.push_back(depart);
            std::reverse(chemin.begin(), chemin.end());
            return chemin;
        }

        // Explorer les 4 voisins
        for (int d = 0; d < 4; ++d) {
            int nx = courant.first  + dx[d];
            int ny = courant.second + dy[d];

            if (estDansBornes(nx, ny) && !visite[ny][nx] &&
                grille[ny][nx]->estFranchissable()) {
                visite[ny][nx] = true;
                parent[ny][nx] = courant;
                file.push({nx, ny});
            }
        }
    }

    // Aucun chemin trouvé (ne devrait pas arriver dans un labyrinthe parfait)
    return {};
}

// ============================================================================
// Accesseurs
// ============================================================================
Case* Donjon::getCase(int x, int y) const {
    if (estDansBornes(x, y)) {
        return grille[y][x];
    }
    return nullptr;
}

void Donjon::setCase(int x, int y, Case* c) {
    if (estDansBornes(x, y)) {
        delete grille[y][x];   // Libérer l'ancienne case
        grille[y][x] = c;
    }
}

bool Donjon::estDansBornes(int x, int y) const {
    return x >= 0 && x < largeur && y >= 0 && y < hauteur;
}
