#ifndef ATTACK_H
#define ATTACK_H

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

#endif // ATTACK_H
