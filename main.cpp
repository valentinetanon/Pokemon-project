#include <iostream>
#include <limits>
#include "core.hpp"

int getValidInput(int min, int max) {
    int input;
    while (true) {
        std::cout << "Votre choix : ";
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide. Veuillez entrer un nombre entre " << min << " et " << max << ".\n";
        } else if (input < min || input > max) {
            std::cout << "Choix hors limites. Veuillez entrer un nombre entre " << min << " et " << max << ".\n";
        } else {
            return input;
        }
    }
}

int main() {
    Core core;
    std::string filename = "pokemons.txt";

    core.loadPokemon(filename);

    int choix;
    do {
        std::cout << "1. Créer un Pokémon\n2. Supprimer un Pokémon\n3. Commencer un combat\n4. Quitter\n";
        choix = getValidInput(1, 4);

        switch (choix) {
        case 1:
            core.createPokemon();
            break;
        case 2: {
            std::string name;
            std::cout << "Nom du Pokémon à supprimer: ";
            std::cin >> name;
            core.deletePokemon(name);
            break;
        }
        case 3:
            core.startCombat();
            break;
        case 4:
            std::cout << "Au revoir !\n";
            break;
        default:
            std::cout << "Choix invalide. Veuillez réessayer.\n";
        }
    } while (choix != 4);

    return 0;
}
