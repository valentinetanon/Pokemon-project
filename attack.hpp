#pragma once

#include <string>

class Attack {
private:
    std::string name;
    std::string type;
    float damage;

public:
    Attack(const std::string& name, const std::string& type, float damage);
    float getDamage() const;
    std::string getType() const;
    std::string getName() const; 
};
