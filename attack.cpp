#include "attack.hpp"

Attack::Attack(const std::string& name, const std::string& type, float damage)
    : name(name), type(type), damage(damage) {}

float Attack::getDamage() const {
    return damage;
}

std::string Attack::getType() const {
    return type;
}

std::string Attack::getName() const {
    return name;
}
