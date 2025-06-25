/*
** EPITECH PROJECT, 2024
** Pokemon-project
** File description:
** dresser.hpp
*/

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
    std::string getName() const;

    const std::list<std::unique_ptr<Pokemon>>& getPokemons() const {
        return _pokemons;
    }

private:
    std::string _name;
    std::list<std::unique_ptr<Pokemon>> _pokemons = {};
};
