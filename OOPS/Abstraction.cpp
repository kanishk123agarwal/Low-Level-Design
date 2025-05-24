#include<iostream>
#include<string>
using namespace std;

class Car{
  public:
  virtual void startEngine()=0;
  virtual void stopEngine()=0;
  virtual void accelerate()=0;
  virtual void brake()=0;
  virtual ~Car(){}
};

class SportsCar:public Car{
  public:
  string brand;
  string model;
  bool isEngineOn;
  int currentSpeed;

  // constructor
  SportsCar(string b,string m){
    this->brand=b;
    this->model=m;
    isEngineOn=false;
    currentSpeed=0;
  }

  void startEngine(){
    isEngineOn=true;
    cout<<"Engine started"<<endl;
  }

  void accelerate(){
    if(isEngineOn){
      if(currentSpeed==0){
        currentSpeed+=10;
        cout<<"Current speed: "<<currentSpeed<<endl;
      }
      else{
        currentSpeed+=30;
      cout<<"Current speed: "<<currentSpeed<<endl;
      }
    }
    else{
      cout<<"Please start the engine first"<<endl;
    }
  }

  void brake(){
    if(currentSpeed==0){
      cout<<"Please start the Engine first"<<endl;
    }
    else {
      currentSpeed-=10;
      cout<<"Current speed: "<<currentSpeed<<endl;
    }
  }

  void stopEngine(){
    isEngineOn=false;
    currentSpeed=0;
    cout<<"Engine stopped"<<endl;
  }
};

int main(){
  Car* myCar=new SportsCar("ford","Mustang");
  myCar->startEngine();
  myCar->accelerate();
  myCar->accelerate();
  myCar->brake();
  myCar->stopEngine();
  delete myCar;
  return 0; 
}