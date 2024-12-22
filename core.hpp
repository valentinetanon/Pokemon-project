#ifndef CORE_HPP
#define CORE_HPP

#include "pokemon.hpp"
#include <map>
#include <string>
#include <memory>

class Core {
private:
    std::map<std::string, std::unique_ptr<Pokemon>> pokemons;

public:
    void loadPokemon(const std::string& filename);
    void savePokemon(const std::string& filename);
    void deletePokemon(const std::string& name);
    void createPokemon();
    void startCombat();
    void displayAvailablePokemons() const;
    std::pair<std::unique_ptr<Pokemon>, std::unique_ptr<Pokemon>> selectTwoPokemons();
    void handleAttackTurn(std::unique_ptr<Pokemon>& attacker, std::unique_ptr<Pokemon>& defender);
    std::string getPokemonName();
    int getPokemonHP();
    void addAttacksToPokemon(std::unique_ptr<Pokemon>& pokemon);
    void executeCombat(std::unique_ptr<Pokemon>& pokemon1, std::unique_ptr<Pokemon>& pokemon2);
    void processCombatOutcome(std::unique_ptr<Pokemon>& pokemon1, std::unique_ptr<Pokemon>& pokemon2);
    void handleCombatOutcome(std::unique_ptr<Pokemon>& winner, std::unique_ptr<Pokemon>& loser);

};

#endif // CORE_HPP
