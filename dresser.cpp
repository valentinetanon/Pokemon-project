#include "dresser.hpp"
#include <memory>


void Dresser::addPokemon(std::unique_ptr<Pokemon> pokemon) {
    _pokemons.push_back(pokemon);
}
