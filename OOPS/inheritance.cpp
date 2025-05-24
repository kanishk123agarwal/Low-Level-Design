#include<iostream>
#include<string>
using namespace std;
class Car{
  protected:
  string brand;
  string model;
  bool isEngineOn;
  int currentSpeed;
  public:
  Car(string b,string m){
    this->brand=b;
    this->model=m;
    isEngineOn=false;
    currentSpeed=0;
  }

  // common method for all car object
  void startEngine(){
    isEngineOn=true;
    cout<<brand<<" "<<model<<"Engine started"<<endl;
  }

  void stopEngine(){
    isEngineOn=false;
    currentSpeed=0;
    cout<<brand<<" "<<model<<"Engine stopped"<<endl;
  }
  void accelerate(){
    if(isEngineOn){
      currentSpeed+=10;
      cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
    }
    else{
      cout<<brand<<" "<<model<<"Please start the engine first"<<endl;
    }
  }

  void brake(){
    currentSpeed-=10;
    if(currentSpeed<0){
      currentSpeed=0;
    }
    cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
  }
  virtual ~Car(){};
};

class ManualCar: public Car{
  private:
  int currentGear;  //specific to manual car
  public:
  ManualCar(string b,string m):Car(b,m){
    currentGear=0;
  }
  void shiftGear(int gear){
    currentGear=gear;
    cout<<brand<<" "<<model<<"Current gear: "<<currentGear<<endl;
  }
};

class ElectricCar: public Car{
  private:
  int battery; //specific to the electric car
  public:
  ElectricCar(string b,string m):Car(b,m){
    battery=100;
  }
  void chargeBattery(int amount){
    battery+=amount;
    cout<<brand<<" "<<model<<"Battery charge: "<<battery<<endl;
  }
  
};

int main(){
  ManualCar* myCar=new ManualCar("Ford","Mustang");
  myCar->startEngine();
  myCar->accelerate();
  myCar->shiftGear(3);
  myCar->brake();
  myCar->stopEngine();
  delete myCar;

  cout<<"--------------------- "<<endl;
  ElectricCar *myCar2=new ElectricCar("Tesla","Model S");
  myCar2->startEngine();
  myCar2->accelerate();
  myCar2->chargeBattery(50);
  myCar2->brake();
  myCar2->stopEngine();
  delete myCar2;
  return 0;
}