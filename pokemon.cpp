#include "pokemon.hpp"
#include "attackFactory.hpp"
#include <sstream>
#include <iostream>
#include <memory>

void Pokemon::addAttack(std::shared_ptr<Attack> attack) {
    if (attacks.size() < 4) {
        attacks.push_back(attack);
    } else {
        std::cout << "Un Pokémon ne peut avoir que 4 attaques maximum.\n";
    }
}

void Pokemon::attack(std::unique_ptr<Pokemon> &target, std::shared_ptr<Attack> attack) {
    const std::string targetType = target->getType();
    const std::string attackType = attack->getType();
    float finalDamages = attack->getDamage();

    if (attackType == "eau" && targetType == "eau ") {
        finalDamages *= 0.5;
    }
    else if (attackType == "eau" && targetType == "feu") {
        finalDamages *= 2;
    }
    else if (attackType == "feu" && targetType == "eau") {
        finalDamages *= 0.5;
    }
    else if (attackType == "feu" && targetType == "feu") {
        finalDamages *= 0.5;
    }

    std::cout << name << " attaque " << target->getName() << " avec " << attack->getName()
              << " pour " << attack->getDamage() << " dégâts !\n";
    target->takeDamage(finalDamages);
}

void Pokemon::takeDamage(float damage) {
    hp -= damage;
    if (hp < 0.0) hp = 0.0;
}

void Pokemon::resetToInitialHP() {
    hp = initialHP;
}

bool Pokemon::isAlive() const {
    return hp > 0.0;
}

std::string Pokemon::getName() const {
    return name;
}

float Pokemon::getHP() const {
    return hp;
}

std::string Pokemon::getType() const {
    return type;
}

void Pokemon::reset() {
    hp = 100.0;
}

std::string Pokemon::serialize() const {
    std::ostringstream oss;
    oss << name << "," << hp << "," << type << ",";
    for (const auto& attack : attacks) {
        oss << attack->getName() << ":" << attack->getDamage() << ":" << attack->getType() << ";";
    }
    return oss.str();
}

Pokemon Pokemon::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string name, type;
    int hp;

    std::getline(iss, name, ',');
    iss >> hp;
    iss.ignore();
    std::getline(iss, type, ',');

    Pokemon pokemon(name, hp, type);

    std::string attacksData;
    std::getline(iss, attacksData);
    std::istringstream attacksStream(attacksData);
    std::string attack;
    while (std::getline(attacksStream, attack, ';')) {
        if (attack.empty()) continue;

        std::string attackName, attackType;
        float attackDamage;
        std::istringstream attackStream(attack);
        std::getline(attackStream, attackName, ':');
        attackStream >> attackDamage;
        attackStream.ignore();
        std::getline(attackStream, attackType, ':');

        pokemon.addAttack(AttackFactory::createAttack(attackName, attackType, attackDamage));
    }
    return pokemon;
}
