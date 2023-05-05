#include "knight2.h"

/* * * BEGIN create Additional Function * * */

bool PaladinCheck(int x){
    if (x == 0 || x == 1) return false;
    for (int i = 2; i <= sqrt(x); i++){
        if (x % i == 0) return false;
    }
    return true;
}

bool LancelotCheck(int maxHP){
    if (maxHP == 888) return true;
    else return false;
}

bool DragonCheck(int maxHP){
    string s = to_string(maxHP);
    if (s.size() < 3) return false;
    int a, b, c;
    a = s[0] - '0';
    b = s[1] - '0';
    c = s[2] - '0';
    if (a != 0 && b != 0 && c != 0)
        if ((pow(a, 2) + pow(b, 2)) == pow(c, 2) || (pow(a, 2) + pow(c, 2)) == pow(b,2) || (pow(b, 2) + pow(c, 2)) == pow(a, 2)) return true;
    return false;
}

KnightType KnightCheck(int maxHP){
    if (PaladinCheck(maxHP)) return PALADIN;
    if (LancelotCheck(maxHP)) return LANCELOT;
    if (DragonCheck(maxHP)) return DRAGON;
    return NORMAL;
}

/* * * END create Additional Function * * */

/* * * BEGIN implementation of class Events * * */
Events::Events(const string& file_Events){
    ifstream infile;
    infile.open(file_Events);
    string str1, str2;
    getline(infile, str1);
    istringstream s1(str1); s1 >> this -> num;
    getline(infile, str2);
    this -> events = new int[this -> num];
    getline(infile, str2);
    istringstream s2(str2);
    for (int  i = 0; i < num; i++){
        s2 >> events[i];
    }
}

int Events::count() const{
    return this -> num;
}

int Events::get(int i) const{
    return events[i];
}

void Events::substituteID(int x){
    this -> id = x;
}

int Events::getID(){
    return this -> id;
}

Events::~Events(){
    delete [] events;
}

/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class BaseItem * * */

/* * * END implementation of class BaseItem * * */

/*BEGIN implementation of derived class Antidote*/

bool AntidoteItem::canUse(BaseKnight * knight){
    return true;
}

void AntidoteItem::use(BaseKnight * knight){

}

/*END implementation of derived class Antidote*/

/*BEGIN implementation of derived class PhoenixItemI*/

bool PhoenixItemI::canUse(BaseKnight * knight){
    if (knight -> getHP() <= 0) return true;
    return false;
}

void PhoenixItemI::use(BaseKnight * knight){
    int maxhp = knight -> getMaxhp();
    knight -> HPModify(maxhp);
}

/*END implementation of derived class PhoenixItemI*/

/*BEGIN implementation of derived class PhoenixItemII*/

bool PhoenixItemII::canUse(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp < maxhp / 4) return true;
    return false;
}

void PhoenixItemII::use(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp < maxhp / 4) knight -> HPModify(maxhp);
}

/*END implementation of derived class PhoenixItem II*/

/*BEGIN implementation of derived class PhoenixItemIII*/

bool PhoenixItemIII::canUse(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp < maxhp / 3 && hp > 0 || hp <= 0) return true;
    return false;
}

void PhoenixItemIII::use(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp > 0 && hp < maxhp / 3){
        int hpInc = hp + (maxhp / 4);
        knight -> HPModify(hpInc);
    }
    else if (hp <= 0){
        knight -> HPModify(maxhp / 3);
    }
}

/*END implementation of derived class PhoenixItem III*/

/*BEGIN implementation of derived class PhoenixItemIV*/

bool PhoenixItemIV::canUse(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp < maxhp / 2 && hp > 0 || hp <= 0) return true;
    return false;
}

void PhoenixItemIV::use(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp > 0 && hp < maxhp / 2){
        int hpInc = hp + (maxhp / 5);
        knight -> HPModify(hpInc);
    }
    else if (hp <= 0){
        knight -> HPModify(maxhp / 2);
    }
}

/*END implementation of derived class PhoenixItemIV*/

/* * * BEGIN implementation of class BaseBag * * */

//Thêm vật phẩm vào đầu của túi
bool BaseBag::insertFirst(BaseItem * item){
    Node * newNode = new Node;
    newNode -> data = item;
    newNode -> next = nullptr;
    this -> node = newNode;
    if ((num_of_item < bag_cap_limit && bag_cap_limit != 0) || bag_cap_limit == 0){
        if (l.head == nullptr){
            l.head = this -> node;
            l.tail = nullptr;
        }
        else{
            node -> next = l.head;
            l.head = node;
        }
        num_of_item++;
        return true;
    }   
    else return false;
}

//Tìm vật phẩm ở trong túi của Hiệp Sĩ
BaseItem* BaseBag::get(ItemType itemType){
    Node * node = l.head;
    while (node != nullptr){
        if (node -> data -> itemType == itemType){
            return node -> data;
        }
        node = node -> next;
    }
    return nullptr;
}

BaseItem* BaseBag::get_death(){
    Node * node = l.head;
    while (node != nullptr){
        if (node -> data -> itemType == PhoenixDownI || node -> data -> itemType == PhoenixDownII || node -> data -> itemType == PhoenixDownIII || node -> data -> itemType == PhoenixDownIV){
            return node -> data;
        }
        node = node -> next;
    }
    return nullptr;
}

//Đổi chỗ vật cần sử dụng và xóa nó khỏi danh sách
void BaseBag::swap_and_remove_item(ItemType itemType){
    BaseItem * tempItem;
    Node * node = l.head;
    while ((node -> data -> itemType) != (itemType) && node != nullptr){
        node = node -> next;
    }
    //Đổi chỗ vật cần sử dụng
    tempItem = l.head -> data;
    l.head -> data = node -> data;
    node -> data = tempItem;
    //Xóa vật
    Node * temp = l.head;
    l.head = l.head -> next;
    num_of_item--;
    delete temp;
    temp = nullptr;
}

//Xoá vật phẩm khi bị dính độc của Tornbey (MSK: 6)
void BaseBag::remove_antidote_effect(){
    Node * node = l.head;
    Node * temp = new Node;
    if (num_of_item > 3){
        for (int i = 0; i < 3; i++){
            temp = l.head;
            node = node -> next;
            l.head = node;
            num_of_item--;
            delete temp;
        }
    }
    else {
        temp = l.head;
        l.head = nullptr;
        int count = num_of_item;
        for (int i = 0; i < count; i++){
            temp = l.head;
            node = node -> next;
            l.head = node;
            num_of_item--;
            delete temp;
        }   
    }
    

}


string BaseBag::toString() const{
    string typeString[5] = {"PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV", "Antidote"};
    string s("");
    
    s = s + "Bag[count=" + to_string(num_of_item) + ";" + PrintItemList + "]";
    return s;
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation PaladinBag * * */

PaladinBag::PaladinBag(){

}

/* * * END implementation PaladinBag * * */

/* * * BEGIN implementation LancelotBag * * */

LancelotBag::LancelotBag(){
    this -> bag_cap_limit = 16;
}

/* * * END implementation LancelotBag * * */

/* * * BEGIN implementation DragonBag * * */

DragonBag::DragonBag(){
    this -> bag_cap_limit = 14;
}

/* * * END implementation DragonBag * * */

/* * * BEGIN implementation NormalBag * * */

NormalBag::NormalBag(){
    this -> bag_cap_limit = 19;
}

/* * * END implementation NormalBag * * */

/* * * BEGIN implementation of class BaseOpponent * * */

BaseOpponent * BaseOpponent::OpponentCreate(int eventsID, int events_order){
    BaseOpponent * x = nullptr;
    this -> levelO = (events_order + eventsID) % 10 + 1;
    if (eventsID == 1){
        x = new MadBear();
        x -> levelO = this -> levelO;
    }
    else if (eventsID == 2){
        x = new Bandit();
        x -> levelO = this -> levelO;
    }
    else if (eventsID == 3){
        x = new LordLupin();
        x -> levelO = this -> levelO;
    }
    else if (eventsID == 4){
        x = new Elf();
        x -> levelO = this -> levelO;
    }
    else if (eventsID == 5){
        x = new Troll();
        x -> levelO = this -> levelO;
    }
    else if (eventsID == 6){
        x = new Tornbey();
        x -> levelO = this -> levelO;
    }
    else if (eventsID == 7){
        x = new QueenOfCards();
        x -> levelO = this -> levelO;
    }
    else if (eventsID == 8){
        x = new NinaDeRings();  
    }
    else if (eventsID == 9){
        x = new DurianGarden();
    }
    else if (eventsID == 10){
        x = new OmegaWeapon();
    }
    else if (eventsID == 11){
        x = new Hades();
    }
    return x;
}

/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseKnight * * */

BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight * x = nullptr;
    if (PaladinCheck(maxhp)){
        x = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        x -> knightType = KnightCheck(x -> maxhp);
    }
    else if (LancelotCheck(maxhp)){
        x = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        x -> knightType = KnightCheck(x -> maxhp);
    }
    else if (DragonCheck(maxhp)){
        x = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        x -> knightType = KnightCheck(x -> maxhp);
    }
    else{
        x = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        x -> knightType = KnightCheck(x -> maxhp);
    }
    return x;
}

void BaseKnight::KnightBagCreate(){
    BaseItem * temp;
    int num_of_phoenixdownI = 0;
    int num_of_antidote = 0;
    if (phoenixdownI > 5) num_of_phoenixdownI = 5;
    else num_of_phoenixdownI = phoenixdownI;
    if (antidote > 5) num_of_antidote = 5;
    else num_of_antidote = antidote;
    if ((this -> knightType) == PALADIN){
        bag = new PaladinBag();
        bag -> CreateBagList();
        for (int i = 0; i < num_of_phoenixdownI; i++){
            temp = new PhoenixItemI();
            bag -> insertFirst(temp);
        }
        for (int i = 0; i < num_of_antidote; i++){
            temp = new AntidoteItem();
            bag -> insertFirst(temp);
        }
    }
    else if((this -> knightType) == LANCELOT){
        bag = new LancelotBag();
        bag -> CreateBagList();
        for (int i = 0; i < num_of_phoenixdownI; i++){
            temp = new PhoenixItemI();
            if (bag -> num_of_item < bag -> bag_cap_limit){
                bag -> insertFirst(temp);
            }
        }
        for (int i = 0; i < num_of_antidote; i++){
            temp = new AntidoteItem();
            if (bag -> num_of_item < bag -> bag_cap_limit){
                bag -> insertFirst(temp);
            }
        }
    }
    else if ((this -> knightType) == DRAGON){
        bag = new DragonBag();
        bag -> CreateBagList();
        for (int i = 0; i < num_of_phoenixdownI; i++){
            temp = new PhoenixItemI();
            if (bag -> num_of_item < bag -> bag_cap_limit){
                bag -> insertFirst(temp);
            }
        }
        //Do DRAGON không cần lấy Antidote
    }
    else {
        bag = new NormalBag();
        bag -> CreateBagList();
        for (int i = 0; i < num_of_phoenixdownI; i++){
            temp = new PhoenixItemI();
            if (bag -> num_of_item < bag -> bag_cap_limit){
                bag -> insertFirst(temp);
            }
        }
        for (int i = 0; i < num_of_antidote; i++){
            temp = new AntidoteItem();
            if (bag -> num_of_item < bag -> bag_cap_limit){
                bag -> insertFirst(temp);
            }
        }
    }
    //bag -> num_of_item = phoenixdownI + antidote;
    //delete temp;
}

KnightType BaseKnight::getKnightType(){
    return this -> knightType;
}

//Tăng máu và hồi sinh bằng thuốc
void BaseKnight::UseItemKnight(){
    BaseItem * tempItem = nullptr;
    //Khi HP <= 0 tìm kiếm phoenix gần nhất và sử dụng
    if (hp <= 0){
        tempItem = bag -> get_death();
        //cout << tempItem -> itemType;
        if (tempItem != nullptr && tempItem -> canUse(this)){
            tempItem -> use(this);
            bag -> swap_and_remove_item(tempItem -> itemType);
        }
    }
    else{
        tempItem = bag -> get(PhoenixDownII);
        if (tempItem != nullptr && tempItem -> canUse(this)){
            tempItem -> use(this);
            bag -> swap_and_remove_item(tempItem -> itemType);
        }
        else{
            tempItem = bag -> get(PhoenixDownIII);
            if (tempItem != nullptr && tempItem -> canUse(this)){
                tempItem -> use(this);
                bag -> swap_and_remove_item(tempItem -> itemType);
            }
            else{
                tempItem = bag -> get(PhoenixDownIV);
                if (tempItem != nullptr && tempItem -> canUse(this)){
                    tempItem -> use(this);
                    bag -> swap_and_remove_item(tempItem -> itemType);
                }
            }
        }
    }
}

//Hồi sinh bằng Gil
void BaseKnight::GilRevive(){
    if (hp <= 0){
        if (gil >= 100){
            gil -= 100;
            HPModify(maxhp / 2);
        }
    }
}

//Đánh với quái Tornbey (MSK: 6)
void BaseKnight::fightTornbey(BaseOpponent * opponent){
    bool PoisonAffected = false;
    if (level >= opponent -> levelO){
        level++;
        if (level > 10)
            this -> level = 10;
    }
    else if (knightType != DRAGON){
        PoisonAffected = true;
        BaseItem * tempAntidote = nullptr;
        if (PoisonAffected){
            tempAntidote = bag -> get(Antidote);
            if (tempAntidote != nullptr){
                if (tempAntidote -> canUse(this)){
                    bag -> swap_and_remove_item(Antidote);
                }
            }
            else{
                //cout << "hello";
                bag -> remove_antidote_effect();
                this -> hp = this -> hp - 10;
            }
        }
    }
}

//Đánh với QueenOfCards (MSK: 7)
void BaseKnight::fightQueenofCards(BaseOpponent * opponent){
    if (level < opponent -> levelO && knightType != PALADIN){
        gil /= 2;
    }
    else if (level >= opponent -> levelO){
        gil *= 2;
        if (gil > 999){
            left_over_gil = gil - 999;
        }
        else left_over_gil = 0;
    }
}

//Trao đổi với NinaDeRings (MSK: 8)
void BaseKnight::fightNinaDeRings(){
    int HPinc = 0;
    if ((gil >= 50 && hp < maxhp / 3) || (knightType != PALADIN && hp < maxhp / 3)){
        if (knightType != PALADIN)
            gil -= 50;
        HPinc = hp + maxhp/5;
        HPModify(HPinc);
    }
}

//Đớp Vườn Sầu Riêng (MSK: 9)
void BaseKnight::fightDurianGarden(){
    this -> HPModify(maxhp);
}

//Đánh với OmegaWeapon (MSK: 10)
void BaseKnight::fightOmegaWeapon(){
    if ((level == 10 && hp == maxhp) || knightType == DRAGON){
        level = 10;
        gil = 999;
    }
    else hp = 0;
}

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    bag -> PrintBagList();
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

void BaseKnight::PrintBagTest(){
    bag -> PrintBagListTemp();
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class PaladinKnight * * */

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> hp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
    this -> knightType = PALADIN;
    this -> bag = nullptr;
    this -> base_dame = 0.06;
}

PaladinKnight::~PaladinKnight(){

}

void PaladinKnight::fight(BaseOpponent * opponent){
    OpponentType MonsterType = opponent -> opponentType;
    if (MonsterType >= 1 && MonsterType <= 5){
        gil = gil + (opponent -> gilValue);
        if (gil > 999){
            left_over_gil = gil - 999;
        }
        else left_over_gil = 0;
    }
    else if (MonsterType == 6) fightTornbey(opponent);
    else if (MonsterType == 7) fightQueenofCards(opponent);
    else if (MonsterType == NINADERINGS) fightNinaDeRings();
    else if (MonsterType == DURIANGARDEN) fightDurianGarden();
}

/* * * END implementation of class PaladinKnight * * */

/* * * BEGIN implementation of class LancelotKnight * * */

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> hp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
    this -> knightType = LANCELOT;
    this -> bag = nullptr;
    this -> base_dame = 0.05;
}

LancelotKnight::~LancelotKnight(){

}

void LancelotKnight::fight(BaseOpponent * opponent){
    OpponentType MonsterType = opponent -> opponentType;
    if (MonsterType >= 1 && MonsterType <= 5){
        gil = gil + (opponent -> gilValue);
        if (gil > 999){
            left_over_gil = gil - 999;
        }
        else left_over_gil = 0;
    }
    else if (MonsterType == 6) fightTornbey(opponent);
    else if (MonsterType == 7) fightQueenofCards(opponent);
    else if (MonsterType == NINADERINGS) fightNinaDeRings();
    else if (MonsterType == DURIANGARDEN) fightDurianGarden();
}

/* * * END implementation of class LancelotKnight * * */

/* * * BEGIN implementation of class DragonKnight * * */

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> hp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
    this -> knightType = DRAGON;
    this -> bag = nullptr;
    this -> base_dame = 0.075;
}

DragonKnight::~DragonKnight(){

}

void DragonKnight::fight(BaseOpponent * opponent){
    OpponentType MonsterType = opponent -> opponentType;
    if (MonsterType >= 1 && MonsterType <= 5){
        if (level < (opponent -> levelO)){
        hp = hp - (opponent -> baseDamage) * ((opponent -> levelO) - level);
        }
        else{
            gil = gil + (opponent -> gilValue);
            if (gil > 999){
                left_over_gil = gil - 999;
            }
            else left_over_gil = 0;
        }
    }
    else if (MonsterType == 6) fightTornbey(opponent);
    else if (MonsterType == 7) fightQueenofCards(opponent);
    else if (MonsterType == NINADERINGS) fightNinaDeRings();
    else if (MonsterType == DURIANGARDEN) fightDurianGarden();
}

/* * * END implementation of class DragonKnight * * */

/* * * BEGIN implementation of class NormalKnight * * */

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> hp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
    this -> knightType = NORMAL;
    this -> bag = nullptr;
}

NormalKnight::~NormalKnight(){
}

void NormalKnight::fight(BaseOpponent * opponent){
    OpponentType MonsterType = opponent -> opponentType;
    if (MonsterType >= 1 && MonsterType <= 5){
        if (level < (opponent -> levelO)){
        hp = hp - (opponent -> baseDamage) * ((opponent -> levelO) - level);
        }
        else{
            gil = gil + (opponent -> gilValue);
            if (gil > 999){
                left_over_gil = gil - 999;
            }
            else left_over_gil = 0;
        }
    }
    else if (MonsterType == 6) fightTornbey(opponent);
    else if (MonsterType == 7) fightQueenofCards(opponent);
    else if (MonsterType == NINADERINGS) fightNinaDeRings();
    else if (MonsterType == DURIANGARDEN) fightDurianGarden();
}

/* * * END implementation of class NormalKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights (const string & file_armyknights){
    ifstream infile;
    infile.open(file_armyknights);
    string str1, str2;
    getline(infile, str1);
    istringstream s1(str1);
    int n; s1 >> n;
    KnightL1st = new BaseKnight * [n];
    int hp, level, phoenixdownI, gil, antidote;
    for (int i = 0; i < n; i++){
        infile >> hp >> level >> phoenixdownI >> gil >> antidote;
        //cout << hp << " " << level << " " << phoenixdownI << " " << gil << " " << antidote;
        KnightL1st[i] = BaseKnight::create(i + 1, hp, level, gil, antidote, phoenixdownI);
        KnightL1st[i] -> KnightBagCreate();
    }
    cap = n;

}

ArmyKnights::~ArmyKnights(){
    KnightL1st = nullptr;
};

void ArmyKnights::deleteKnight(int index){
    if (cap > 0){
        BaseKnight ** tempKnightList = new BaseKnight* [cap - 1];
            for (int i = index; i < cap - 1; i++){
                KnightL1st[i] = KnightL1st[i + 1];
            }
            for (int i = 0; i < cap - 1; i++){
                tempKnightList[i] = KnightL1st[i];
            }
        /*else{
            for (int i = 0; i < cap - 1; i++){
                tempKnightList[i] = KnightL1st[i];
            }
        }*/
        delete [] KnightL1st;
        KnightL1st = tempKnightList;
        //tempKnightList = nullptr;
        cap--;
    }
}

void ArmyKnights::deleteKnightTemp(int index){
    cout << cap;
    /*if (cap > 0){
        BaseKnight ** tempKnightList = new BaseKnight* [cap - 1];
            for (int i = index; i < cap - 1; i++){
                KnightL1st[i] = KnightL1st[i + 1];
            }
            for (int i = 0; i < cap - 1; i++){
                tempKnightList[i] = KnightL1st[i];
            }
        else{
            for (int i = 0; i < cap - 1; i++){
                tempKnightList[i] = KnightL1st[i];
            }
        }
        //delete [] KnightL1st;
        //KnightL1st = tempKnightList;
        //tempKnightList = nullptr;
        //cap--;
    }*/
}

//----------------------------------------

BaseKnight ** ArmyKnights::set_army_knight(){
    BaseKnight ** tempKnightList = new BaseKnight * [0];
    delete [] KnightL1st;
    KnightL1st = tempKnightList;
    cap = 0;
    return KnightL1st;
}

bool ArmyKnights::adventure(Events * events){
    if ((this -> fightUltimecia()) == true) return true;
    if (cap < 0) return false;
    return false;
}

void ArmyKnights::collectPhoenix(){
    BaseItem * tempItem;
    for (int i = cap - 1; i >= 0; i--){
        if (eventsCode == 112){
            tempItem = new PhoenixItemII();
            if (((KnightL1st[i] -> getBag() -> num_of_item < KnightL1st[i] -> getBag() -> bag_cap_limit) && KnightL1st[i] -> getBag() -> bag_cap_limit != 0)
                || KnightL1st[i] -> getKnightType() == PALADIN){
                KnightL1st[i] -> getBag() -> insertFirst(tempItem);
                break;
            }
        }
        else if (eventsCode == 113){
            tempItem = new PhoenixItemIII();
            if (((KnightL1st[i] -> getBag() -> num_of_item < KnightL1st[i] -> getBag() -> bag_cap_limit) && KnightL1st[i] -> getBag() -> bag_cap_limit != 0)
                || KnightL1st[i] -> getKnightType() == PALADIN){
                KnightL1st[i] -> getBag() -> insertFirst(tempItem);
                break;
            }
        }
        else if (eventsCode == 114){
            tempItem = new PhoenixItemIV();
            if (((KnightL1st[i] -> getBag() -> num_of_item < KnightL1st[i] -> getBag() -> bag_cap_limit) && KnightL1st[i] -> getBag() -> bag_cap_limit != 0)
                || KnightL1st[i] -> getKnightType() == PALADIN){
                KnightL1st[i] -> getBag() -> insertFirst(tempItem);
                break;
            }
        }
    }
}

void ArmyKnights::UseItem(){
    BaseKnight * lk9 = lastKnight();
    lk9 -> UseItemKnight();
    lk9 -> GilRevive();
}

void ArmyKnights::collectArmyItem(){
    if (eventsCode == 95 && paladinShield == 0){
        paladinShield = 1;
    }
    else if (eventsCode == 96 && lancelotSpear == 0){
        lancelotSpear = 1;
    }
    else if (eventsCode == 97 && guinevereHair == 0){
        guinevereHair = 1;
    }
    else if (eventsCode == 98 && excaliburSword == 0){
        if (paladinShield == true && lancelotSpear == true && guinevereHair == true)
            excaliburSword = 1;
    }
}

//Truyền gil cho hiệp sĩ trước và giới hạn lại gil
void ArmyKnights::pass_gil_to_previous(){
    int army_left_over_gil = 0;
    for (int i = cap - 1; i >= 0; i--){
        if (i == 0){
            if (KnightL1st[i] -> getGil() > 999){
                KnightL1st[i] -> gilSet(999);
            }
        }
        else if (KnightL1st[i] -> getGil() > 999){
            army_left_over_gil = KnightL1st[i] -> getGil() - 999;
            KnightL1st[i] -> gilSet(999);
            KnightL1st[i - 1] -> gilInc(army_left_over_gil);
        }
    }
}

bool ArmyKnights::hasPaladinShield() const{
    if (paladinShield == true) return paladinShield;
    return false;
}

bool ArmyKnights::hasLancelotSpear() const{
    if (lancelotSpear == true) return lancelotSpear;
    return false;
}

bool ArmyKnights::hasGuinevereHair() const{
    if (guinevereHair == true) return guinevereHair;
    return false;
}

bool ArmyKnights::hasExcaliburSword() const{
    if (excaliburSword == true) return excaliburSword;
    return false;
}

BaseKnight * ArmyKnights::lastKnight() const{
    return KnightL1st[cap - 1];
}

int ArmyKnights::count() const{
    return cap;
}

bool ArmyKnights::fight(BaseOpponent * opponent){
    for (int i = cap - 1; i >= 0; i--){
        KnightL1st[i] -> fight(opponent);
        //Cho hiệp sĩ cuối đánh với quái trước
        if (KnightL1st[i] -> getHP() <= 0){ 
            UseItem();
            if (KnightL1st[i] -> getHP() > 0){
                //Thêm một biến kiểm tra hồi sinh nếu hồi sinh thì biến thành true
                reviveCheck = true;
                break;
            }
            else if (KnightL1st[i] -> getHP() <= 0)
                deleteKnight(i); //Nếu hiệp sĩ chết thì xoá hiệp sĩ đi
        }
        else break;
    }
    if (cap == 0) return false;
    return true;
}

void ArmyKnights::fightHades(){
    
    if (hades_meet == false){
        for (int i = cap - 1; i >= 0; i--){
            if ((KnightL1st[i] -> getLevel() == 10) || ((KnightL1st[i] -> getLevel()) == 8 && (KnightL1st[i] -> getKnightType()) == PALADIN)){
                //cout << "Hello";
                if (paladinShield == false) paladinShield = true;
                hades_meet = true;
            }
            else {
                KnightL1st[i] -> HPModify(0);
                //cout << KnightL1st[i] -> getKnightType();
            }
            if (KnightL1st[i] -> getHP() <= 0){
                UseItem();
                if (KnightL1st[i] -> getHP() > 0){
                    reviveCheck = true;
                    break;
                }
                else if (KnightL1st[i] -> getHP() <= 0)
                    deleteKnight(i); //Nếu hiệp sĩ chết thì xoá hiệp sĩ đi 
            }
            else break;
        }
    }
}

void ArmyKnights::fightOmega(){
    if (omega_meet == false){
        for (int i = cap - 1; i >= 0; i--){
            if (((KnightL1st[i] -> getLevel() == 10) && (KnightL1st[i] -> getHP() == KnightL1st[i] -> getMaxhp())) || KnightL1st[i] -> getKnightType() == DRAGON){
                KnightL1st[i] -> levelSet(10);
                KnightL1st[i] -> gilSet(999);
                omega_meet = true;
            }
            else KnightL1st[i] -> HPModify(0);
            if (KnightL1st[i] -> getHP() <= 0){
                UseItem();
                if (KnightL1st[i] -> getHP() > 0){
                    reviveCheck = true;
                    break;
                }
                else if (KnightL1st[i] -> getHP() <= 0){
                    deleteKnight(i); //Nếu hiệp sĩ chết thì xoá hiệp sĩ đi 
                }
            }
            else break;
        }
    }
}

bool ArmyKnights::fightUltimecia(){
    static int UltimeciaHP = 5000;
    int damage = 0;
    if (excaliburSword == true && eventsCode == 99) return true;
    else{
        if (paladinShield == true && lancelotSpear == true && guinevereHair == true && eventsCode == 99){
            //Đếm số lượng hiệp sĩ đánh với Ultimecia (Chủ yếu để xem rằng trong đội quân có còn ai Paladin, Dragon, Lancelot)
            int Normal_Knight_count = 0;
            for (int i = 0; i < cap; i++){
                if (KnightL1st[i] -> getKnightType() == NORMAL) Normal_Knight_count++;
            }
            for (int i = cap - 1; i >= 0; i--){
                if ((KnightL1st[i] -> getKnightType()) == PALADIN || (KnightL1st[i] -> getKnightType()) == LANCELOT || (KnightL1st[i] -> getKnightType()) == DRAGON){
                    damage = (KnightL1st[i] -> getHP()) * (KnightL1st[i] -> getLevel()) * (KnightL1st[i] -> getBase_Dame());
                    UltimeciaHP -= damage;
                    if (UltimeciaHP > 0){
                        deleteKnight(i);
                    }
                }
            }
            if (UltimeciaHP > 0 && cap == Normal_Knight_count){
                KnightL1st = set_army_knight();
                return false;
            }
            else return true;
        }
        else {
            KnightL1st = set_army_knight();
            return false;
        }
    }
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
    opponent = nullptr;
}

KnightAdventure::~KnightAdventure(){}

void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);

}

void KnightAdventure::loadEvents(const string & file_Events){
    events = new Events(file_Events);
}

void KnightAdventure::run(){
    int num_of_events = events -> count();
    opponent = new BaseOpponent;
    for (int i = 0; i < num_of_events; i++){
        events -> substituteID(i); //Lấy thứ tự i của chuỗi events
        armyKnights -> eventsCode = events -> get(i); //Lấy mã sự kiện của sự kiện thứ i
        if ((events -> get(i)) >= 1 && (events -> get(i)) <= 11){
            if ((events -> get(i)) == 11){
                armyKnights -> fightHades();
            }
            else{
                if ((events -> get(i)) == 10){
                    //cout << armyKnights -> omega_meet;
                    armyKnights -> fightOmega();
                }
                else {
                    opponent = opponent -> OpponentCreate(events -> get(i), i);
                    armyKnights -> fight(opponent);
                }
            }
        }
        if (armyKnights -> cap == 0){
            armyKnights -> printInfo();
            armyKnights -> printResult(armyKnights -> adventure(events));
            break;
        }
        if (i == num_of_events - 1){
            armyKnights -> fightUltimecia();
            armyKnights -> printInfo();
            armyKnights -> printResult(armyKnights -> adventure(events));
            break;
        }
        armyKnights -> pass_gil_to_previous(); //Truyền gil cho hiệp sĩ trước và đồng thời set lại gil
        armyKnights -> collectPhoenix(); //Nhặt sự kiện từ mã 112 -> 114
        armyKnights -> collectArmyItem(); //Nhặt báu vật 95 -> 98
        if ((events -> get(i) != 112 && events -> get(i) != 113 && events -> get(i) != 114) || armyKnights -> reviveCheck == false){
            armyKnights -> UseItem(); //Sử dụng vật phẩm
        }
        if (armyKnights -> reviveCheck == true) armyKnights -> reviveCheck = false;
        armyKnights -> printInfo();
    }
}


/* * * END implementation of class KnightAdventure * * */   