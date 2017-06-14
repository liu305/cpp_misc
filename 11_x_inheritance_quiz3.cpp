#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


class Creature {
protected:
    std::string m_name;
    char m_symbol;
    int m_health;
    int m_dpa;
    int m_Gold;
    
public:
    Creature(std::string name, char symbol, int health, int dpa, int gold):
    m_name(name), m_symbol(symbol), m_health(health), m_dpa(dpa), m_Gold(gold)
    {
    }
    std::string getName() {return m_name;}
    char getSymbol() {return m_symbol;}
    int getHealth() {return m_health;}
    int getDPA() {return m_dpa;}
    int getGold() {return m_Gold;}
    
    void reduceHealth(int hp){m_health -= hp;}
    void addGold(int amt){m_Gold += amt;}
    bool isDead(){return m_health <=0;}
};

class Player : public Creature {
private:
    int m_level;
public:
    Player(std::string name):
    Creature(name,'@',10,1,0), m_level(1)
    {
    }
    int getLevel() {return m_level;}
    void levelup() {m_level++;m_dpa++;}
};

class Monster : public Creature {
public:
    enum Type {
        DRAGON,
        ORC,
        SLIME,
        MAX_TYPES,
    };
protected:
    struct MonsterData{
        std::string tmp_name;
        char tmp_symbol;
        int tmp_health;
        int tmp_dpa;
        int tmp_gold;
    };
    static MonsterData monsterData[MAX_TYPES];
public:
    Monster (Type type) : Creature(monsterData[type].tmp_name,
                                   monsterData[type].tmp_symbol,
                                   monsterData[type].tmp_health,
                                   monsterData[type].tmp_dpa,
                                   monsterData[type].tmp_gold)
    {
    }
    static Monster getRandomMonster();
};

Monster Monster::getRandomMonster(){
    return Monster(static_cast<Monster::Type>(getRandomNumber(0,2)));
}
Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]{
    {"dragon",'D',20,4,100},{"orc",'o',4,2,25},{"slime",'s',1,1,10}
};

void attackMonster(Player &user_name, Monster &a)
{
    std::cout << "You hit the " << a.getName() << " for " << user_name.getDPA() << " damage.\n";
    a.reduceHealth(user_name.getDPA());
    if (a.isDead()) {
        std::cout << "You killed the " << a.getName() << ".\n";
        user_name.addGold(a.getGold());
        user_name.levelup();
        std::cout << "You are now level " << user_name.getLevel() << ".\n";
        std::cout << "You found " << a.getGold() << " gold.\n";
    }
}

void attackPlayer(Player &user_name, Monster &a)
{
    user_name.reduceHealth(a.getDPA());
    std::cout << "The " << a.getName() << " hit you for " << a.getDPA() << " damage.\n";
}


void fightMonster(Player &user_name, Monster &a)
{
    char decision;
    while (!user_name.isDead() and (user_name.getLevel()<20)){
        std::cout << "(R)un or (F)ight: ";
        std::cin >> decision;
        if (decision=='r') {
            int tmp_rand = getRandomNumber(0,1);
            if (tmp_rand == 0) {std::cout << "You successfully fled.\n";return;}
            else {std::cout << "You failed to flee.\n";attackPlayer(user_name,a);}
        }
        else if (decision=='f') {
            attackMonster(user_name,a);
            if (a.isDead()) {return;}
            attackPlayer(user_name,a);
        }
        else {
            std::cout << "Invalid\n";
            continue;
        }
    }
    return;
}


int main()
{
    std::string tmp_user_name;
    std::cout << "Enter your name: ";
    std::cin >> tmp_user_name;
    std::cout << "Welcome, " << tmp_user_name << ".\n";
    Player user_name(tmp_user_name);
    srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
    rand(); // get rid of first result
    
    while (!user_name.isDead() and (user_name.getLevel()<20))
    {
        Monster a = Monster::getRandomMonster();
        std::cout << "You have encountered a " << a.getName() << " (" << a.getSymbol() << ").\n";
        fightMonster(user_name,a);
    }
    if (user_name.isDead()) {std::cout << "You died at level " <<user_name.getLevel() << " and with " <<user_name.getGold() << " gold.\nToo bad you can't take it with you.\n";}
    if (user_name.getLevel()>=20) {std::cout << "You reached level " <<user_name.getLevel() << " with " << user_name.getGold() << " gold.\nEnjoy your trophy.\n";}
    return 0;
}
