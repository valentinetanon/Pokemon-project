/*
** EPITECH PROJECT, 2024
** Pokemon-project
** File description:
** dresser.cpp
*/

#include "dresser.hpp"
#include <memory>


void Dresser::addPokemon(std::unique_ptr<Pokemon> pokemon) {
    _pokemons.push_back(pokemon);
}

std::string Pokemon::getName() const {
    return name;
}

const std::list<std::unique_ptr<Pokemon>>& Dresser::getPokemons() const {
    return _pokemons;
}
