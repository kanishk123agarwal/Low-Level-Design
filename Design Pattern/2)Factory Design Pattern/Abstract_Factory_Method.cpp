#include <iostream>

using namespace std;

// Product 1 --> Burger
class Burger {
public:
    virtual void prepare() = 0;  // Pure virtual function
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Wheat Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Wheat Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};

// Product 2 --> GarlicBread
class GarlicBread {
public:
    virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Basic Garlic Bread with butter and garlic!\n";
    }
};

class CheeseGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Cheese Garlic Bread with extra cheese and butter!\n";
    }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Basic Wheat Garlic Bread with butter and garlic!\n";
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Cheese Wheat Garlic Bread with extra cheese and butter!\n";
    }
};

// Product--->3
class Sandwich{
    public:
    virtual void prepare() = 0;
    virtual ~Sandwich() {}
};

class BasicSandWich:public Sandwich{
    public:
    void prepare(){
        cout<<"Preparing Basic SandWich with sandwich, aalo and ketchup!"<<endl;
    }
};

class StandardSandWich:public Sandwich{
    void prepare(){
        cout<<"Preparing Standard SandWich with sandwich, aalo, cheese and lettuce!"<<endl;
    }
};

class PremiumSandWich:public Sandwich{
    void prepare(){
        cout<<"Preparing Premium SandWich with gourmet sandwich, premium aalo, cheese, lettuce and secret sauce!"<<endl;
    }
};

class basicWheatSandWich:public Sandwich{
    void prepare(){
        cout<<"Preparing Basic Wheat SandWich with sandwich, aalo and ketchup!"<<endl;
    }
};

class standardWheatSandwich:public Sandwich{
    void prepare(){
        cout<<"Preparing Standard Wheat SandWich with sandwich, aalo, cheese and lettuce!"<<endl;
    }
};

class premiumWheatSandwich:public Sandwich{
    void prepare(){
        cout<<"Preparing Premium Wheat SandWich with gourmet sandwich, premium aalo, cheese, lettuce and secret sauce!"<<endl;
    }
};

// Factory and its concretions
class MealFactory {
public:
    virtual Burger* createBurger(string& type) = 0;
    virtual GarlicBread* createGarlicBread(string& type) = 0;
    virtual Sandwich* createSandwich(string type) = 0;
};

class SinghBurger : public MealFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicBurger();
        } else if (type == "standard") {
            return new StandardBurger();
        } else if (type == "premium") {
            return new PremiumBurger();
        }else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }

    Sandwich* createSandwich(string type) override{
        if(type=="basic"){
            return new BasicSandWich();
        } else if(type=="standard"){
            return new StandardSandWich();
        } else if(type=="premium"){
            return new PremiumSandWich();
        }else{
            cout<<"Invalid Sandwich type! "<<endl;
            return nullptr;
        }

    }

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "basic") {
            return new BasicGarlicBread();
        } else if (type == "cheese") {
            return new CheeseGarlicBread();
        } 
        else {
            cout << "Invalid Garlic bread type! " << endl;
            return nullptr;
        }
    }
};

class KingBurger : public MealFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicWheatBurger();
        } else if (type == "standard") {
            return new StandardWheatBurger();
        } else if (type == "premium") {
            return new PremiumWheatBurger();
        } else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }

    Sandwich* createSandwich(string type) override{
        if(type=="basic"){
            return new basicWheatSandWich();
        } else if(type=="standard"){
            return new standardWheatSandwich();
        } else if(type=="premium"){
            return new premiumWheatSandwich();
        }else{
            cout<<"Invalid Sandwich type! "<<endl;
            return nullptr;
        }

    }

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "basic") {
            return new BasicWheatGarlicBread();
        } else if (type == "cheese") {
            return new CheeseWheatGarlicBread();
        } 
        else {
            cout << "Invalid Garlic bread type! " << endl;
            return nullptr;
        }
    }
};

int main() {
    string burgerType = "basic";
    string garlicBreadType = "cheese";
    string sandwichType="premium";

    MealFactory* mealFactory = new KingBurger();

    Burger* burger = mealFactory->createBurger(burgerType);
    GarlicBread* garlicBread = mealFactory->createGarlicBread(garlicBreadType);
    Sandwich* sandwich=mealFactory->createSandwich(sandwichType);

    burger->prepare();
    garlicBread->prepare();
    sandwich->prepare();

    string bgT="premium";
    string gbT="basic";
    string sT="standard";

    MealFactory* mf=new SinghBurger();
    Burger* burger1=mf->createBurger(bgT);
    GarlicBread* garlicBread1=mf->createGarlicBread(gbT);
    Sandwich* sandwich1=mf->createSandwich("standard");

    burger1->prepare();
    garlicBread1->prepare();
    sandwich1->prepare();
    return 0;
}