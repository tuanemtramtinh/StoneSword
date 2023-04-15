#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG



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
class PaladinBag;
class LancelotBag;
class DragonBag;
class NormalBag;

class KnightAdventure;

enum ItemType {PhoenixDownI = 0, PhoenixDownII, PhoenixDownIII, PhoenixDownIV, Antidote};

/********CREATE LINKED LIST********/

struct Node{
    ItemType data;
    Node * next;
};

struct LinkedList{
    Node * head;
    Node * tail;
};

typedef LinkedList ll;

/********CREATE LINKED LIST********/

class BaseBag {
public:
    ll l;
    Node * node;
    string PrintItemList;
    int num_of_item;
public:
    void CreateBagList(){
        l.head = nullptr;
        l.tail = nullptr;
    }

    Node * CreateBagNode(ItemType init_data){
        Node * node = new Node;
        node -> data = init_data;
        node -> next = nullptr;
        return node;
    }

    void preInsertFirst(){
        if (l.head == nullptr){
            l.head = node;
            l.tail = nullptr;
        }
        else{
            node -> next = l.head;
            l.head = node;
        }
    }

    void PrintBagList(){
        string typeString[5] = {"PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV", "Antidote"};
        PrintItemList = "";
        int count = 0;
        if (l.head != nullptr){
            Node * node = l.head;
            while (node != nullptr){
                if (count == num_of_item - 1){
                        PrintItemList = PrintItemList + typeString[node -> data];
                }
                else PrintItemList = PrintItemList + typeString[node -> data] + ',';
                node = node -> next;
                count++;
            }
        }
    }

    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class PaladinBag : public BaseBag{
public:
    PaladinBag(BaseKnight * x, int PhoenixDownI, int antidote);
    ~PaladinBag();
};

class LancelotBag : public BaseBag{
public:
    LancelotBag(BaseKnight * x, int PhoenixDownI, int antidote);
    ~LancelotBag();
};

class DragonBag : public BaseBag{
public:
    DragonBag(BaseKnight * x, int PhoenixDownI, int antidote);
    ~DragonBag();
};

class NormalBag : public BaseBag{
public:
    NormalBag(BaseKnight * x, int PhoenixDownI, int antidote);
    ~NormalBag();
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
    void KnightBagCreate();
    int getId(){return this -> id;} int getHP(){return this -> hp;} int getMaxhp(){return this -> maxhp;} int getLevel(){return this -> level;}
    int getGil(){return this -> gil;} int getAntidote(){return this -> antidote;} int getPhoenixdownI(){return this -> phoenixdownI;}
    string toString() const;
};

class PaladinKnight : public BaseKnight{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~PaladinKnight();
};

class LancelotKnight : public BaseKnight{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~LancelotKnight();
};

class DragonKnight : public BaseKnight{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~DragonKnight();
};

class NormalKnight : public BaseKnight{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~NormalKnight();
};

class ArmyKnights {
public:
    int cap;
    int eventsCode;
    bool paladinShield, lancelotSpear, guinevereHair, excaliburSword = false;
    BaseKnight ** KnightL1st; // Vì method Create trong class BaseKnight return về địa chỉ

public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();

    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    bool fightUltimecia();

    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void collectArmyItem();


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