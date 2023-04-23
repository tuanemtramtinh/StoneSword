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
class NinaDeRings;
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
    int bag_cap_limit = 0; //Giới hạn của túi đồ 
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

    /*void preInsertFirst(){
        if (l.head == nullptr){
            l.head = node;
            l.tail = nullptr;
        }
        else{
            node -> next = l.head;
            l.head = node;
        }
    }*/

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
    void remove_antidote_effect();

    virtual bool insertFirst(BaseItem * item);

    //Tìm vật phẩm cần dùng
    virtual BaseItem * get(ItemType itemType);
    //Tìm vật phẩm cho trường hợp HP <= 0
    BaseItem * get_death();
    virtual string toString() const;
};

class PaladinBag : public BaseBag{
public:
    PaladinBag();
    ~PaladinBag();
};

class LancelotBag : public BaseBag{
public:
    LancelotBag(){
        this -> bag_cap_limit = 16;
    }
    ~LancelotBag();
};

class DragonBag : public BaseBag{
public:
    DragonBag(){
        this -> bag_cap_limit = 14;
    }
    ~DragonBag();
};

class NormalBag : public BaseBag{
public:
    NormalBag(){
        this -> bag_cap_limit = 19;
    }
    ~NormalBag();
};

enum OpponentType {MADBEAR = 1, BANDIT, LORDLUPIN, ELF, TROLL, TORNBEY, QUEENOFCARDS, NINADERINGS, DURIANGARDEN, OMEGAWEAPON, HADES};

class BaseOpponent{
public:
    int levelO;
    int baseDamage;
    int gilValue;
    OpponentType opponentType;
public:
    void levelCalculate(int eventsID, int events_order);
    BaseOpponent * OpponentCreate(int eventsID, int events_order);
};

class MadBear : public BaseOpponent{
public:
    MadBear(){
        this -> opponentType = MADBEAR;
        this -> baseDamage = 10;
        this -> gilValue = 100;
    };
};

class Bandit : public BaseOpponent{
public:
    Bandit(){
        this -> opponentType = BANDIT;
        this -> baseDamage = 15;
        this -> gilValue = 150;
    }
};

class LordLupin : public BaseOpponent{
public:
    LordLupin(){
        this -> opponentType = LORDLUPIN;
        this -> baseDamage = 45;
        this -> gilValue = 450;
    }
};

class Elf : public BaseOpponent{
public:
    Elf(){
        this -> opponentType = ELF;
        this -> baseDamage = 75;
        this -> gilValue = 750;
    }
};

class Troll : public BaseOpponent{
public:
    Troll(){
        this -> opponentType = TROLL;
        this -> baseDamage = 95;
        this -> gilValue = 800;
    }
};

class Tornbey : public BaseOpponent{
public:
    Tornbey(){
        this -> opponentType = TORNBEY;
    }
};

class QueenOfCards : public BaseOpponent{
public:
    QueenOfCards(){
        this -> opponentType = QUEENOFCARDS;
    }
};

class NinaDeRings : public BaseOpponent{
public:
    NinaDeRings(){
        this -> opponentType = NINADERINGS;
    }
};

class DurianGarden : public BaseOpponent{
public:
    DurianGarden(){
        this -> opponentType = DURIANGARDEN;
    }
};

class OmegaWeapon : public BaseOpponent{
public:
    OmegaWeapon(){
        this -> opponentType = OMEGAWEAPON;
    }
};

class Hades : public BaseOpponent{
public:
    Hades(){
        this -> opponentType = HADES;
    }
};

/* * * BEGIN declare for class BaseKnight and its inheritance * * */

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
    double base_dame;
    int left_over_gil = 0; //Tiền bị dư ra khi mà gil đạt 999
    BaseBag * bag;
    KnightType knightType;

public:
    KnightType getKnightType();
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void KnightBagCreate();

    int getId(){return this -> id;}
    int getHP(){return this -> hp;}
    int getGil(){return this -> gil;}
    int getMaxhp(){return this -> maxhp;}
    int getLevel(){return this -> level;}
    int getAntidote(){return this -> antidote;}
    int getLeft_over_gil(){return this -> left_over_gil;}
    int getPhoenixdownI(){return this -> phoenixdownI;}
    double getBase_Dame(){return this -> base_dame;}
    BaseBag * getBag(){return this -> bag;}

    //Thay đổi máu
    void HPModify(int x){
        this -> hp = x;
    }
    //Tăng số lượng gil
    void gilInc(int x){
        this -> gil = this -> gil + x;
    }
    //Set số lượng gil
    void gilSet(int x){
        this -> gil = x;
    }
    void left_over_gil_set(int x){
        this -> left_over_gil = x;
    }

    virtual void fight(BaseOpponent * opponent) = 0;
    void fightTornbey(BaseOpponent * opponent);
    void fightQueenofCards(BaseOpponent * opponent);
    void fightNinaDeRings();
    void fightDurianGarden();
    void fightOmegaWeapon();

    void UseItemKnight();
    void GilRevive();
    void PrintBagTest();
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

/* * * END declare for class BaseKnight and its inheritance * * */

/* * * BEGIN declare for class ArmyKnights * * */

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
    void fightHades();
    int count() const;
    
    void UseItem();

    BaseKnight * lastKnight() const;
    BaseKnight ** deleteFaintedLastKnight();
    BaseKnight ** deleteKnight_Ultimecia(int index);
    BaseKnight ** set_army_knight();

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void collectPhoenix(); //Dùng để nhặt cho sự kiện từ 112 -> 114
    void collectArmyItem(); //Dùng để nhặt các báu vật
    void pass_gil_to_previous(); // Dùng để truyền gil cho hiệp sĩ trước;

    void printInfo() const;
    void printResult(bool win) const;
};

/* * * END declare for class ArmyKnights * * */

/* * * BEGIN declare for class Events * * */

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

/* * * END declare for class Events * * */

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