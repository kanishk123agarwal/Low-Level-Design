#include <iostream>
using namespace std;

// --- Strategy Interface for Walk ---
class WalkableRobot {
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {}
};

// --- Concrete Strategies for walk ---
class NormalWalk : public WalkableRobot {
public:
    void walk() override { 
        cout << "Walking normally..." << endl; 
    }
};

class NoWalk : public WalkableRobot {
public:
    void walk() override { 
        cout << "Cannot walk." << endl; 
    }
};


// --- Strategy Interface for Talk ---
class TalkableRobot {
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}
};

// --- Concrete Strategies for Talk ---
class NormalTalk : public TalkableRobot {
public:
    void talk() override { 
        cout << "Talking normally..." << endl; 
    }
};

class NoTalk : public TalkableRobot {
public:
    void talk() override { 
        cout << "Cannot talk." << endl; 
    }
};

// --- Strategy Interface for Fly ---
class FlyableRobot {
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {}
};

class NormalFly : public FlyableRobot {
public:
    void fly() override { 
        cout << "Flying normally..." << endl; 
    }
};

class NoFly : public FlyableRobot {
public:
    void fly() override { 
        cout << "Cannot fly." << endl; 
    }
};

class SpeedUp{
    public:
    virtual void speedUp() = 0;
    virtual ~SpeedUp(){}
};

class NormalSpeedUp:public SpeedUp{
    public:
    void speedUp() override{
        cout<<"Speeding Up......"<<endl;
    }
};

class NoSpeedUp:public SpeedUp{
    public:
    void speedUp() override{
        cout<<"Cannot Speed up.... "<<endl;
    }
};

// --- Robot Base Class ---
class Robot {
protected:
    WalkableRobot* walkBehavior;
    TalkableRobot* talkBehavior;
    FlyableRobot* flyBehavior;
    SpeedUp* speedUpBehavior;

public:
    Robot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f,SpeedUp* s) {
        this->walkBehavior = w;
        this->talkBehavior = t;
        this->flyBehavior = f;
        this->speedUpBehavior=s;
    }
       
    void walk() { 
        walkBehavior->walk(); 
    }
    void talk() { 
        talkBehavior->talk(); 
    }
    void fly() { 
        flyBehavior->fly(); 
    }

    void speedUp(){
        speedUpBehavior->speedUp();
    }

    virtual void projection() = 0; // Abstract method for subclasses
};

// --- Concrete Robot Types ---
class CompanionRobot : public Robot {
public:
    CompanionRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f,SpeedUp* s)
        : Robot(w, t, f,s) {}

    void projection() override {
        cout << "Displaying friendly companion features..." << endl;
    }
};

class NormalRobot:public Robot{
    public:
    NormalRobot(WalkableRobot* w,TalkableRobot* t,FlyableRobot* f,SpeedUp* s):Robot(w,t,f,s){}

    void projection() override{
        cout<<"Displaying normal robot features..."<<endl;
    }
};

class WorkerRobot : public Robot {
public:
    WorkerRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f,SpeedUp* s)
        : Robot(w, t, f,s) {}

    void projection() override {
        cout << "Displaying worker efficiency stats..." << endl;
    }
};

// --- Main Function ---
int main() {
    Robot *robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly(),new NormalSpeedUp());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->speedUp();
    robot1->projection();

    cout << "--------------------" << endl;

    Robot *robot2 = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly(),new NoSpeedUp());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->speedUp();
    robot2->projection();


    cout<<"---------------------- "<<endl;
    Robot* robot3=new NormalRobot(new NormalWalk(),new NormalTalk(),new NormalFly(),new NormalSpeedUp());
    robot3->walk();
    robot3->talk();
    robot3->fly();
    robot3->speedUp();
    robot3->projection();

    return 0;
}