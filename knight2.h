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


class AntidoteItem;
class PhoenixItemI;
class PhoenixItemII;
class PhoenixItemIII;
class PhoenixItemIV;

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

class BaseItem {
public:
    ItemType itemType;
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class AntidoteItem : public BaseItem{
public:
    AntidoteItem(){
        this -> itemType = Antidote;
    }
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

class PhoenixItemI : public BaseItem{
public:
    PhoenixItemI(){
        this -> itemType = PhoenixDownI;
    }
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

class PhoenixItemII : public BaseItem{
public:
    PhoenixItemII(){
        this -> itemType = PhoenixDownII;
    }
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

class PhoenixItemIII : public BaseItem{
public:
    PhoenixItemIII(){
        this -> itemType = PhoenixDownIII;
    }
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

class PhoenixItemIV : public BaseItem{
public:
    PhoenixItemIV(){
        this -> itemType = PhoenixDownIV;
    }
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

/********CREATE LINKED LIST********/

struct Node{
    BaseItem * data;
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

    Node * CreateBagNode(BaseItem * init_data){
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

    Node * FindItem(BaseItem * item);

    void PrintBagList(){
        string typeString[5] = {"PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV", "Antidote"};
        PrintItemList = "";
        int count = 0;
        if (l.head != nullptr){
            Node * node = l.head;
            while (node != nullptr){
                if (count == num_of_item - 1){
                        PrintItemList = PrintItemList + typeString[node -> data -> itemType];
                }
                else PrintItemList = PrintItemList + typeString[node -> data -> itemType] + ',';
                node = node -> next;
                count++;
            }
        }
    }

    void PrintBagListTemp(){
        if (l.head != nullptr){
            Node * node = l.head;
            while (node != nullptr){
                cout << node -> data -> itemType;
                node = node -> next;
            }
        }
    }

    void swap_and_remove_item(ItemType itemType);

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

class BaseOpponent{
public:
    int levelO;
    int baseDamage;
    int gilValue;
public:
    void levelCalculate(int eventsID, int events_order);
    BaseOpponent * OpponentCreate(int eventsID, int events_order);
};

class MadBear : public BaseOpponent{
public:
    MadBear(){
        this -> baseDamage = 10;
        this -> gilValue = 100;
    };
};

class Bandit : public BaseOpponent{
public:
    Bandit(){
        this -> baseDamage = 15;
        this -> gilValue = 150;
    }
};

class LordLupin : public BaseOpponent{
public:
    LordLupin(){
        this -> baseDamage = 45;
        this -> gilValue = 450;
    }
};

class Elf : public BaseOpponent{
public:
    Elf(){
        this -> baseDamage = 75;
        this -> gilValue = 750;
    }
};

class Troll : public BaseOpponent{
public:
    Troll(){
        this -> baseDamage = 95;
        this -> gilValue = 800;
    }
};

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
    BaseBag * getBag(){return this -> bag;}
    void HPModify(int x){
        this -> hp = x;
    }
    void PrintBagTest();
    virtual void fight(BaseOpponent * opponent) = 0;
    string toString() const;
};

class PaladinKnight : public BaseKnight{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~PaladinKnight();
    void fight(BaseOpponent * opponent);

};

class LancelotKnight : public BaseKnight{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~LancelotKnight();
    void fight(BaseOpponent * opponent);
};

class DragonKnight : public BaseKnight{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~DragonKnight();
    void fight(BaseOpponent * opponent);
};

class NormalKnight : public BaseKnight{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~NormalKnight();
    void fight(BaseOpponent * opponent);
};

class ArmyKnights {
public:
    int cap;
    int eventsCode;
    bool paladinShield = false, lancelotSpear = false, guinevereHair = false, excaliburSword = false;
    BaseKnight ** KnightL1st; // Vì method Create trong class BaseKnight return về địa chỉ

public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();

    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    bool fightUltimecia();
    int count() const;
    
    void UseItem();

    BaseKnight * lastKnight() const;
    void deleteFaintedLastKnight();

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void collectPhoenix(); //Dùng để nhặt cho sự kiện từ 112 -> 114
    void collectArmyItem(); //Dùng để nhặt các báu vật


    void printInfo() const;
    void printResult(bool win) const;
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
    BaseOpponent * opponent;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string & file_armyknights);
    void loadEvents(const string & file_Events);
    void run();
};

#endif //__KNIGHT2_H__