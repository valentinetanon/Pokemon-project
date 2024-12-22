#pragma once

#include "pokemon.hpp"
#include <list>
#include <string>
#include <memory>

class Dresser {
public:
    ~Dresser() = default;
    Dresser(std::string name) : _name(name) {};
    void addPokemon(std::unique_ptr<Pokemon> pokemon);
private:
    std::string _name;
    std::list<std::unique_ptr<Pokemon>> _pokemons = {};
};