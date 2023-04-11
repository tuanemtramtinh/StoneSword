#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

struct ArmyKnightStatistic{
    int id;
    int HP;
    int level;
    int phoenixdownI;
    int gil;
    int antidote;
};

class Events;

class BaseKnight;
class PaladinKnight;
class LancelotKnight;
class DragonKnight;
class NormalKnight;

class ArmyKnights;
class BaseItem;

class BaseOpponent;
class MadBear;
class Bandit;
class LordLupin;
class Elf;
class Troll;
class Tornbey;
class QueenOfCards;
class NinaDeRing;
class DurianGarden;
class OmegaWeapon;
class Hades;

class BaseBag;
class KnightAdventure;

enum ItemType {/* TODO: */};

class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };


class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag * bag;
    KnightType knightType;

public:
    KnightType getKnightType();
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int getId(){return this -> id;} int getHP(){return this -> hp;} int getMaxhp(){return this -> maxhp;} int getLevel(){return this -> level;}
    int getGil(){return this -> gil;} int getAntidote(){return this -> antidote;} int getPhoenixdownI(){return this -> phoenixdownI;}
    string toString() const;
};

class PaladinKnight : protected BaseKnight{
public:
    PaladinKnight(BaseKnight * x);
    ~PaladinKnight();
};

class LancelotKnight : protected BaseKnight{
public:
    LancelotKnight(BaseKnight * x);
    ~LancelotKnight();
};

class DragonKnight : protected BaseKnight{
public:
    DragonKnight(BaseKnight * x);
    ~DragonKnight();
};

class NormalKnight : protected BaseKnight{
public:
    NormalKnight(BaseKnight * x);
    ~NormalKnight();
};

class ArmyKnights {
public:
    int cap;
    ArmyKnightStatistic * KnightsList;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Events {

private:
    int * events;
    int num;
    int id; //sự kiện thứ i

public:
    Events(const string& file_Events);
    ~Events();
    int count() const;
    int get(int i) const;
    void substituteID(int x); //Truyền sự kiện thứ i vào biến id
    int getID();         // Lấy sự kiện thứ i ra khỏi
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string & file_armyknights);
    void loadEvents(const string & file_Events);
    void run();
};

#endif // __KNIGHT2_H__