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

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

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

KnightType BaseKnight::getKnightType(){
    return this -> knightType;
}

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
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

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class PaladinKnight * * */

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
}

PaladinKnight::~PaladinKnight(){

}

/* * * END implementation of class PaladinKnight * * */

/* * * BEGIN implementation of class LancelotKnight * * */

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
}

LancelotKnight::~LancelotKnight(){

}

/* * * END implementation of class LancelotKnight * * */

/* * * BEGIN implementation of class DragonKnight * * */

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
}

DragonKnight::~DragonKnight(){

}

/* * * END implementation of class DragonKnight * * */

/* * * BEGIN implementation of class NormalKnight * * */

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this -> id = id;
    this -> maxhp = maxhp;
    this -> level = level;
    this -> gil = gil;
    this -> antidote = antidote;
    this -> phoenixdownI = phoenixdownI;
}

NormalKnight::~NormalKnight(){
    
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
    }
    cap = n;
}

ArmyKnights::~ArmyKnights(){
    KnightL1st = nullptr;
};

bool ArmyKnights::adventure(Events * events){
    int num_of_events = events -> count();
    int events_order = events -> getID();
    if (events_order == num_of_events - 1) return true;
    return false;
}

void ArmyKnights::collectArmyItem(){
    if (eventsCode == 95 && paladinShield == 0){
        hasPaladinShield();
        paladinShield = 1;
    }
    else if (eventsCode == 96 && lancelotSpear == 0){
        hasLancelotSpear();
        lancelotSpear = 1;
    }
    else if (eventsCode == 97 && guinevereHair == 0){
        hasGuinevereHair();
        guinevereHair = 1;
    }
    else if (eventsCode == 98 && excaliburSword == 0){
        hasExcaliburSword();
        excaliburSword = 1;
    }
}

bool ArmyKnights::hasPaladinShield() const{
    if (eventsCode == 95 && paladinShield == 0){
        return true;
    }
    else if (eventsCode != 95 && paladinShield == 0){
        return false;
    }
}

bool ArmyKnights::hasLancelotSpear() const{
    if (eventsCode == 96 && lancelotSpear == 0){
        return true;
    }
    else if (eventsCode != 96 && lancelotSpear == 0){
        return false;
    }
}

bool ArmyKnights::hasGuinevereHair() const{
    if (eventsCode == 97 && guinevereHair == 0){
        return true;
    }
    else if (eventsCode != 97 && guinevereHair == 0){
        return false;
    }
}

bool ArmyKnights::hasExcaliburSword() const{
    if (eventsCode == 98 && excaliburSword == 0){
        return true;
    }
    else if (eventsCode != 98 && lancelotSpear == 0){
        return false;
    }
}

BaseKnight * ArmyKnights::lastKnight() const{
    return 0;
}

int ArmyKnights::count() const{
    return cap;
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
}

KnightAdventure::~KnightAdventure(){}

void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::loadEvents(const string & file_Events){
    events = new Events(file_Events);
    for (int i = 0; i < events -> count(); i++)
        cout << events -> get(i) << " ";
    cout << endl;
}

void KnightAdventure::run(){
    int num_of_events = events -> count();
    for (int i = 0; i < num_of_events; i++){
        events -> substituteID(i); //Lấy thứ tự i của chuỗi events
        armyKnights -> adventure(events);
        armyKnights -> eventsCode = events -> get(i);
    }
    
    //delete Knight;
}


/* * * END implementation of class KnightAdventure * * */