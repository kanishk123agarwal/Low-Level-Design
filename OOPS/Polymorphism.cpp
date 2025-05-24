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

  void startEngine(){
    isEngineOn=true;
    cout<<brand<<" "<<model<<"Engine started"<<endl;
  }

  void stopEngine(){
    isEngineOn=false;
    currentSpeed=0;
    cout<<brand<<" "<<model<<"Engine stopped"<<endl;
  }

  virtual void accelerate()=0; //Abstract method for dynamic polymorphism
  virtual void accelerate(int speed)=0; //Abstract method for static polymorphism

  virtual void brake()=0; //Absstract method for dynamic polymorphism

  virtual ~Car(){}
};

class ManualCar:public Car{
  private:
  int currentGear;
  public:
  ManualCar(string b,string m):Car(b,m){
    currentGear=0;
  }
  // specialized method for manual car
  void shiftGear(int gear){
    currentGear=gear;
    cout<<brand<<" "<<model<<"Current gear: "<<currentGear<<endl;
  }
  // Override accelerate - Dynamic polymorphism
  void accelerate(){
    if(isEngineOn){
      currentSpeed+=10;
      currentGear++;
      cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
    }
    else{
      cout<<brand<<" "<<model<<"Please start the engine first"<<endl;
    }
  }

  // Overloading the accelerate function - static polymorphism
  void accelerate(int speed){
    if(isEngineOn){
      currentSpeed+=speed;
      currentGear+=speed/10;
      cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
    }
    else{
      cout<<brand<<" "<<model<<"Please start the engine first"<<endl;
    }
  }

  void brake(){
    currentSpeed-=10;
    currentGear--;
    if(currentSpeed<0){
      currentSpeed=0;
    }
    cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
  }

  void getGear(){
    cout<<brand<<" "<<model<<"Current gear: "<<currentGear<<endl;
  }
};

class ElectricCar: public Car{
  private:
  int battery;
  public:
  ElectricCar(string b,string m):Car(b,m){
    battery=100;
  }
  void chargeBattery(int amount){
    battery+=amount;
    cout<<brand<<" "<<model<<"Battery charge: "<<battery<<endl;
  }

  void accelerate(){
    if(isEngineOn){
      currentSpeed+=15;
      battery-=10;
      cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
    }
    else{
      cout<<brand<<" "<<model<<"Please start the engine first"<<endl;
    }
  }

  void accelerate(int speed){
    if(isEngineOn){
      currentSpeed+=speed;
      battery-=speed/10;
      cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
    }
    else{
      cout<<brand<<" "<<model<<"Please start the engine first"<<endl;
    }
  }

  void brake(){
    currentSpeed-=10;
    battery-=1;
    if(currentSpeed<0){
      currentSpeed=0;
    }
    cout<<brand<<" "<<model<<"Current speed: "<<currentSpeed<<endl;
  }
};

int main(){
  ManualCar* myManualCar=new ManualCar("Ford","Mustang");
  myManualCar->startEngine();
  myManualCar->accelerate();
  myManualCar->shiftGear(3);
  myManualCar->accelerate(40); 
  myManualCar->getGear(); 
  myManualCar->brake();
  myManualCar->stopEngine();
  delete myManualCar;

  cout<<"--------------------- "<<endl;
  ElectricCar* myElectricCar=new ElectricCar("Tesla","Model S");
  myElectricCar->startEngine();
  myElectricCar->accelerate();
  myElectricCar->chargeBattery(50);
  myElectricCar->accelerate(30);
  myElectricCar->brake();
  myElectricCar->stopEngine();
  delete myElectricCar;
  return 0;
}