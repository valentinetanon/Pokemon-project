#include "attackFactory.hpp"

std::shared_ptr<Attack> AttackFactory::createAttack(const std::string& name, const std::string& type, float damage) {
    return std::make_shared<Attack>(name, type, damage);
}