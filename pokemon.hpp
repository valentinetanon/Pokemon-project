#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "attack.hpp"
#include <memory>

class Pokemon {
private:
    std::string name;
    float hp;
    float initialHP;
    std::string type;
    std::vector<Attack> attacks;

public:
    Pokemon(const std::string& name, float hp, const std::string& type)
        : name(name), hp(hp), initialHP(hp), type(type) {};
    Pokemon() = default;

    void addAttack(const Attack& attack);
    void attack(std::unique_ptr<Pokemon> &target, const Attack& attack);
    void takeDamage(float damage);
    bool isAlive() const;
    std::string getName() const;
    float getHP() const;
    std::string getType() const;
    void reset();
    std::string serialize() const;
    static Pokemon deserialize(const std::string& data);
    void setType(const std::string& type) { this->type = type; }
    void resetToInitialHP();

    const std::vector<Attack>& getAttacks() const { return attacks; }
};

#endif // POKEMON_H
