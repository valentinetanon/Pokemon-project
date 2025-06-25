/*
** EPITECH PROJECT, 2024
** Pokemon-project
** File description:
** attackFactory.hpp
*/

#pragma once

#include <string>
#include <memory>
#include "attack.hpp"

class AttackFactory {
public:
    static std::shared_ptr<Attack> createAttack(const std::string& name, const std::string& type, float damage);
};