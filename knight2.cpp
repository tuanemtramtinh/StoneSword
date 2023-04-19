#include "knight2.h"

/* * * BEGIN create Additional Function * * */

bool PaladinCheck(int x){
    if (x == 0 || x == 1) return false;
    for (int i = 2; i <= sqrt(x); i++){
        if (i % 2 == 0) return false;
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
    return 0;
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
    if (hp < maxhp / 3 || hp <= 0) return true;
    return false;
}

void PhoenixItemIII::use(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp < maxhp / 3){
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
    if (hp < maxhp / 2 || hp <= 0) return true;
    return false;
}

void PhoenixItemIV::use(BaseKnight * knight){
    int hp = knight -> getHP();
    int maxhp = knight -> getMaxhp();
    if (hp < maxhp / 2){
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
    if (l.head == nullptr){
        l.head = this -> node;
        l.tail = nullptr;
    }
    else{
        node -> next = l.head;
        l.head = node;
    }
    return true;
}

//Tìm vật phẩm ở trong túi của Hiệp Sĩ
BaseItem* BaseBag::get(ItemType itemType){
    Node * node = l.head;
    while ((node -> data -> itemType) != (itemType) && node != nullptr){
        node = node -> next;
    }
    BaseItem * temp = node -> data;
    if (temp == nullptr) return nullptr;
    return temp;
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
}


string BaseBag::toString() const{
    string typeString[5] = {"PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV", "Antidote"};
    string s("");
    
    s = s + "Bag[count=" + to_string(num_of_item) + ";" + PrintItemList + "]";
    return s;
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation PaladinBag * * */

PaladinBag::PaladinBag(BaseKnight * x, int PhoenixDownI, int antidote){

}

/* * * END implementation PaladinBag * * */

/* * * BEGIN implementation LancelotBag * * */

LancelotBag::LancelotBag(BaseKnight * x, int PhoenixDownI, int antidote){

}

/* * * END implementation LancelotBag * * */

/* * * BEGIN implementation DragonBag * * */

DragonBag::DragonBag(BaseKnight * x, int PhoenixDownI, int antidote){

}

/* * * END implementation DragonBag * * */

/* * * BEGIN implementation NormalBag * * */

NormalBag::NormalBag(BaseKnight * x, int PhoenixDownI, int antidote){

}

/* * * END implementation NormalBag * * */

/* * * BEGIN implementation of class BaseOpponent * * */

void BaseOpponent::levelCalculate(int eventsID, int events_order){
    levelO = (events_order + eventsID) % 10 + 1;
}

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
    return x;
}

/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseKnight * * */

BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight * x = nullptr;
    if (PaladinCheck(maxhp))
    {
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
    if ((this -> knightType) == PALADIN){
        bag = new PaladinBag(this, phoenixdownI, antidote);
        bag -> CreateBagList();
        for (int i = 0; i < phoenixdownI; i++){
            temp = new PhoenixItemI();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
        for (int i = 0; i < antidote; i++){
            temp = new AntidoteItem();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
    }
    else if((this -> knightType) == LANCELOT){
        bag = new LancelotBag(this, phoenixdownI, antidote);
        bag -> CreateBagList();
        for (int i = 0; i < phoenixdownI; i++){
            temp = new PhoenixItemI();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
        for (int i = 0; i < antidote; i++){
            temp = new AntidoteItem();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
    }
    else if ((this -> knightType) == DRAGON){
        bag = new DragonBag(this, phoenixdownI, antidote);
        bag -> CreateBagList();
        for (int i = 0; i < phoenixdownI; i++){
            temp = new PhoenixItemI();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
        for (int i = 0; i < antidote; i++){
            temp = new AntidoteItem();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
    }
    else {
        bag = new NormalBag(this, phoenixdownI, antidote);
        bag -> CreateBagList();
        for (int i = 0; i < phoenixdownI; i++){
            temp = new PhoenixItemI();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
        for (int i = 0; i < antidote; i++){
            temp = new AntidoteItem();
            bag -> node = bag -> CreateBagNode(temp);
            bag -> preInsertFirst();
        }
    }
    bag -> num_of_item = phoenixdownI + antidote;
    //delete temp;
}

KnightType BaseKnight::getKnightType(){
    return this -> knightType;
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
}

PaladinKnight::~PaladinKnight(){

}

void PaladinKnight::fight(BaseOpponent * opponent){
    OpponentType MonsterType = opponent -> opponentType;
    if (MonsterType >= 1 && MonsterType <= 5){
        gil = gil + (opponent -> gilValue);
        if (gil > 999) gil = 999;
    }
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
}

LancelotKnight::~LancelotKnight(){

}

void LancelotKnight::fight(BaseOpponent * opponent){
    OpponentType MonsterType = opponent -> opponentType;
    if (MonsterType >= 1 && MonsterType <= 5){
        gil = gil + (opponent -> gilValue);
        if (gil > 999) gil = 999;
    }
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
            if (gil > 999) gil = 999;
        }
    }
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
            if (gil > 999) gil = 999;
        }
    }
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
        KnightL1st[i] = BaseKnight::create(i + 1, hp, level, gil, antidote, phoenixdownI);
        KnightL1st[i] -> KnightBagCreate();
    }
    cap = n;
}

ArmyKnights::~ArmyKnights(){
    KnightL1st = nullptr;
};

void ArmyKnights::deleteFaintedLastKnight(){
    BaseKnight ** tempKnightList = new BaseKnight* [cap - 1];
    for (int i = 0; i < cap - 1; i++){
        tempKnightList[i] = KnightL1st[i];
    }
    delete [] KnightL1st;
    KnightL1st = tempKnightList;
    cap--;
}

bool ArmyKnights::adventure(Events * events){
    //int num_of_events = events -> count();
    //int events_order = events -> getID();
    if ((this -> fightUltimecia()) == true) return true;
    return false;
}

void ArmyKnights::collectPhoenix(){
    BaseKnight * lk9 = lastKnight();
    BaseBag * tempBag = lk9 -> getBag();
    BaseItem * tempItem;
    if (eventsCode == 112){
        tempItem = new PhoenixItemII();
        tempBag -> node = tempBag -> CreateBagNode(tempItem);
        tempBag -> insertFirst(tempItem);
        tempBag -> num_of_item ++;
    }
    else if (eventsCode == 113){
        tempItem = new PhoenixItemIII();
        tempBag -> node = tempBag -> CreateBagNode(tempItem);
        tempBag -> insertFirst(tempItem);
        tempBag -> num_of_item ++;
    }
    else if (eventsCode == 114){
        tempItem = new PhoenixItemIV();
        tempBag -> node = tempBag -> CreateBagNode(tempItem);
        tempBag -> insertFirst(tempItem);
        tempBag -> num_of_item ++;
    }
    //delete tempBag;
    //delete tempItem;
}

void ArmyKnights::UseItem(){
    BaseKnight * lk9 = lastKnight();
    BaseBag * tempBag = lk9 -> getBag();
    BaseItem * tempItem;
    
    int hp = lk9 -> getHP();
    int maxhp = lk9 -> getMaxhp();
    if (lk9 -> getHP() <= 0){
        tempItem = tempBag -> get(PhoenixDownI);
        if (tempItem != nullptr){
            if (tempItem -> canUse(lk9)){
                tempItem -> use(lk9);
                tempBag -> swap_and_remove_item(PhoenixDownI);
            }
        }
    }
    else if (lk9 -> getHP() < (lk9 -> getMaxhp())/4){
        tempItem = tempBag -> get(PhoenixDownIV);
        if (tempItem != nullptr){
            if (tempItem -> canUse(lk9)){
                tempItem -> use(lk9);
                tempBag -> swap_and_remove_item(PhoenixDownIV);
            }
        }
    }
    else if (lk9 -> getHP() < (lk9 -> getMaxhp())/3){
        tempItem = tempBag -> get(PhoenixDownIII);
        if (tempItem != nullptr){
            if (tempItem -> canUse(lk9)){
                tempItem -> use(lk9);
                tempBag -> swap_and_remove_item(PhoenixDownIII);
            }
        }
    }
    else if (lk9 -> getHP() < (lk9 -> getMaxhp())/2){
        tempItem = tempBag -> get(PhoenixDownII);
        if (tempItem != nullptr){
            if (tempItem -> canUse(lk9)){
                tempItem -> use(lk9);
                tempBag -> swap_and_remove_item(PhoenixDownII);
            }
        }
    }
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
            if (KnightL1st[i] -> getHP() <= 0)
                deleteFaintedLastKnight(); //Nếu hiệp sĩ chết thì xoá hiệp sĩ đi
        }
        else break;
    }
    if (cap < 0) return false;
    return true;
}

bool ArmyKnights::fightUltimecia(){
    if (excaliburSword == true && eventsCode == 99) return true;
    return false;
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
    BaseOpponent * temp = opponent;
    for (int i = 0; i < num_of_events; i++){
        events -> substituteID(i); //Lấy thứ tự i của chuỗi events
        armyKnights -> eventsCode = events -> get(i); //Lấy mã sự kiện của sự kiện thứ i
        if (((events -> get(i)) >= 1 && (events -> get(i)) <= 7) || ((events -> get(i)) == 10) || ((events -> get(i)) == 11)){
            opponent = opponent -> OpponentCreate(events -> get(i), i);
            armyKnights -> fight(opponent);
        }
        //if ((events -> get(i)) >= 112 && (events -> get(i)) <= 114){}
        armyKnights -> collectPhoenix();
        armyKnights -> collectArmyItem();
        armyKnights -> UseItem();
        armyKnights -> printInfo();
        if (i == num_of_events - 1){
            armyKnights -> printResult(armyKnights -> adventure(events));
        }
    }
    
    
    delete temp;
}


/* * * END implementation of class KnightAdventure * * */