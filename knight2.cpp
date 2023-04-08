#include "knight2.h"

/* * * BEGIN create Additional Function * * */

bool PrimeCheck(int x){
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
    if (PrimeCheck(maxHP)) return PALADIN;
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

Events::~Events(){
    delete [] events;
}

/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */

BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight * x = new BaseKnight;
    x -> id = id;
    x -> maxhp = maxhp;
    x -> level = level;
    x -> gil = gil;
    x -> antidote = antidote;
    x -> phoenixdownI = phoenixdownI;
    x -> knightType = KnightCheck(maxhp);
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

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights (const string & file_armyknights){
    ifstream infile;
    infile.open(file_armyknights);
    string str1, str2;
    getline(infile, str1);
    istringstream s1(str1);
    int n; s1 >> n;
    
    KnightsList = new ArmyKnightStatistic[n];
    for (int i = 0; i < n; i++){
        infile >> KnightsList[i].HP >> KnightsList[i].level >> KnightsList[i].phoenixdownI >> KnightsList[i].gil >> KnightsList[i].antidote;
        KnightsList[i].id = i + 1;
    }
    /*for (int i = 0; i < n; i++){
        cout << KnightsList[i].id << " " << KnightsList[i].HP << " " << KnightsList[i].phoenixdownI 
        << " " << KnightsList[i].gil << " " << KnightsList[i].antidote << endl;
    }*/
    //cout << n << endl;
    cap = n;
}

ArmyKnights::~ArmyKnights(){
    delete [] KnightsList;
};

bool ArmyKnights::hasPaladinShield() const{
    return 0;
}
bool ArmyKnights::hasLancelotSpear() const{
    return 0;
}
bool ArmyKnights::hasGuinevereHair() const{
    return 0;
}
bool ArmyKnights::hasExcaliburSword() const{
    return 0;
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
    BaseKnight * test = new BaseKnight;
    cout << test << endl;
    int n = armyKnights -> cap;
    test = test->create(armyKnights -> KnightsList[n - 1].id, armyKnights -> KnightsList[n - 1].HP, armyKnights -> KnightsList[n - 1].level,
    armyKnights -> KnightsList[n - 1].gil, armyKnights -> KnightsList[n - 1].antidote, armyKnights -> KnightsList[n - 1].phoenixdownI);

    delete test;
}


/* * * END implementation of class KnightAdventure * * */