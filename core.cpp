#include "core.hpp"
#include "pokemon.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int getValidInput(int min, int max);

void Core::loadPokemon(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::unique_ptr<Pokemon> pokemon = std::make_unique<Pokemon>(std::move(Pokemon::deserialize(line)));
        pokemons[pokemon->getName()] = std::move(pokemon);
    }
    file.close();
    std::cout << "Pokémons chargés depuis " << filename << "." << std::endl;
}

void Core::deletePokemon(const std::string& name) {
    if (pokemons.erase(name)) {
        std::cout << "Pokémon " << name << " supprimé." << std::endl;
        savePokemon("pokemons.txt");
    } else {
        std::cout << "Pokémon " << name << " introuvable." << std::endl;
    }
}

void Core::savePokemon(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
        return;
    }
    for (const auto& pair : pokemons) {
        file << pair.second->serialize() << std::endl;
    }
    file.close();
    std::cout << "Pokémons sauvegardés dans " << filename << "." << std::endl;
}

void Core::displayAvailablePokemons() const {
    std::cout << "Pokémons disponibles : \n";
    int index = 1;
    for (const auto& pair : pokemons) {
        std::cout << index << ". " << pair.first << " (" << pair.second->getHP() << " PV)\n";
        index++;
    }
}

std::pair<std::unique_ptr<Pokemon>, std::unique_ptr<Pokemon>> Core::selectTwoPokemons() {
    displayAvailablePokemons();

    size_t firstIndex = -1;
    size_t secondIndex = -1;

    do {
        std::cout << "Choisissez le premier Pokémon : ";
        firstIndex = getValidInput(1, static_cast<int>(pokemons.size()));
    } while (firstIndex < 1 || firstIndex > pokemons.size());

    auto it1 = std::next(pokemons.begin(), firstIndex - 1);
    std::unique_ptr<Pokemon> pokemon1 = std::make_unique<Pokemon>(*it1->second);

    do {
        std::cout << "Choisissez le deuxième Pokémon : ";
        secondIndex = getValidInput(1, static_cast<int>(pokemons.size()));
        if (secondIndex == firstIndex) {
            std::cout << "Le deuxième Pokémon doit être différent du premier.\n";
        }
    } while (secondIndex == firstIndex || secondIndex < 1 || secondIndex > pokemons.size());

    auto it2 = std::next(pokemons.begin(), secondIndex - 1);
    std::unique_ptr<Pokemon> pokemon2 = std::make_unique<Pokemon>(*it2->second);

    return {std::move(pokemon1), std::move(pokemon2)};
}

void Core::executeCombat(std::unique_ptr<Pokemon>& pokemon1, std::unique_ptr<Pokemon>& pokemon2) {
    std::srand(std::time(nullptr));
    bool isPokemon1Turn = (std::rand() % 2 == 0);

    std::cout << "Le combat commence entre " << pokemon1->getName() << " et " << pokemon2->getName() << " !\n";

    while (pokemon1->isAlive() && pokemon2->isAlive()) {
        if (isPokemon1Turn) {
            handleAttackTurn(pokemon1, pokemon2);
        } else {
            handleAttackTurn(pokemon2, pokemon1);
        }
        isPokemon1Turn = !isPokemon1Turn;
    }
}

void Core::handleAttackTurn(std::unique_ptr<Pokemon>& attacker, std::unique_ptr<Pokemon>& defender) {
    std::cout << "\nC'est au tour de " << attacker->getName() << " d'attaquer !\n";
    const auto& attacks = attacker->getAttacks();
    if (attacks.empty()) {
        std::cout << attacker->getName() << " n'a pas d'attaques et passe son tour !\n";
    } else {
        std::cout << "Choisissez une attaque ou passez votre tour :\n";
        int attackIndex = 1;
        for (const auto& attack : attacks) {
            std::cout << attackIndex << ". " << attack.getName()
                      << " (" << attack.getDamage() << " dégâts, Type: " << attack.getType() << ")\n";
            attackIndex++;
        }
        std::cout << attackIndex << ". Ne rien faire\n";

        int attackChoice = getValidInput(1, attackIndex);
        if (attackChoice >= 1 && attackChoice < attackIndex) {
            const Attack& chosenAttack = attacks[attackChoice - 1];
            attacker->attack(defender, chosenAttack);
        } else {
            std::cout << attacker->getName() << " passe son tour !\n";
        }
    }
}

void Core::handleCombatOutcome(std::unique_ptr<Pokemon>& winner, std::unique_ptr<Pokemon>& loser) {
    std::string loserName = loser->getName();
    std::cout << loserName << " a été supprimé après avoir perdu le combat.\n";
    pokemons.erase(loserName);

    winner->resetToInitialHP();
    std::cout << winner->getName() << " a récupéré ses PV initiaux !\n";

    pokemons[winner->getName()] = std::move(winner);
    savePokemon("pokemons.txt");
}

void Core::processCombatOutcome(std::unique_ptr<Pokemon>& pokemon1, std::unique_ptr<Pokemon>& pokemon2) {
    std::unique_ptr<Pokemon> winner;
    std::unique_ptr<Pokemon> loser;

    if (pokemon1->isAlive()) {
        winner = std::move(pokemon1);
        loser = std::move(pokemon2);
    } else {
        winner = std::move(pokemon2);
        loser = std::move(pokemon1);
    }

    handleCombatOutcome(winner, loser);
}

void Core::startCombat() {
    if (pokemons.size() < 2) {
        std::cout << "Il faut au moins 2 Pokémons pour combattre.\n";
        return;
    }

    auto [pokemon1, pokemon2] = selectTwoPokemons();

    executeCombat(pokemon1, pokemon2);

    processCombatOutcome(pokemon1, pokemon2);
}


bool isValidName(const std::string& name) {
    return !name.empty() && std::all_of(name.begin(), name.end(), [](char c) {
        return std::isalpha(c);
    });
}

std::string getValidType() {
    int choice;
    do {
        std::cout << "Choisissez un type :\n"
                  << "1. Eau\n"
                  << "2. Feu\n"
                  << "3. Air\n"
                  << "Votre choix : ";
        choice = getValidInput(1, 3);

        switch (choice) {
            case 1:
                return "eau";
            case 2:
                return "feu";
            case 3:
                return "air";
            default:
                std::cout << "Erreur : choix invalide. Veuillez réessayer.\n";
        }
    } while (true);
}

std::string Core::getPokemonName() {
    std::string name;
    do {
        std::cout << "Nom du Pokémon : ";
        std::cin >> name;
        if (!isValidName(name)) {
            std::cout << "Erreur : le nom doit uniquement contenir des lettres.\n";
        } else if (pokemons.find(name) != pokemons.end()) {
            std::cout << "Erreur : un Pokémon avec ce nom existe déjà.\n";
        }
    } while (!isValidName(name) || pokemons.find(name) != pokemons.end());
    return name;
}

int Core::getPokemonHP() {
    int hp;
    do {
        std::cout << "Points de Vie (PV, positif) : ";
        std::cin >> hp;
        if (hp <= 0) {
            std::cout << "Erreur : les PV doivent être un nombre strictement positif.\n";
        }
    } while (hp <= 0);
    return hp;
}

void Core::addAttacksToPokemon(std::unique_ptr<Pokemon>& pokemon) {
    int numAttacks;
    do {
        std::cout << "Nombre d'attaques (1 à 4) : ";
        std::cin >> numAttacks;
        if (numAttacks < 1 || numAttacks > 4) {
            std::cout << "Erreur : choisissez entre 1 et 4 attaques.\n";
        }
    } while (numAttacks < 1 || numAttacks > 4);

    for (int i = 0; i < numAttacks; ++i) {
        std::string attackName;
        int attackDamage;

        do {
            std::cout << "Nom de l'attaque " << (i + 1) << " : ";
            std::cin >> attackName;
            if (!isValidName(attackName)) {
                std::cout << "Erreur : le nom de l'attaque doit uniquement contenir des lettres.\n";
            }
        } while (!isValidName(attackName));

        std::cout << "Type de l'attaque : \n";
        std::string attackType = getValidType();

        do {
            std::cout << "Dégâts de l'attaque (positif) : ";
            std::cin >> attackDamage;
            if (attackDamage <= 0) {
                std::cout << "Erreur : les dégâts doivent être un nombre positif.\n";
            }
        } while (attackDamage <= 0);

        pokemon->addAttack(Attack(attackName, attackType, (float)attackDamage));
    }
}

void Core::createPokemon() {
    std::string name = getPokemonName();
    int hp = getPokemonHP();
    std::string type = getValidType();

    auto pokemon = std::make_unique<Pokemon>(name, (float)hp, type);

    addAttacksToPokemon(pokemon);

    pokemons[name] = std::move(pokemon);
    std::cout << "Pokémon " << name << " créé avec succès.\n";

    savePokemon("pokemons.txt");
    std::cout << "Pokémon sauvegardé automatiquement dans le fichier.\n";
}