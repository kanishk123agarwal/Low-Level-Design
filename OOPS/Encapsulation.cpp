#include<iostream>
#include<string>
using namespace std;

class SportsCar{
  private:
  string brand;
  string model;
  bool isEngineOn;
  int currentSpeed;
  string tyreCompany;

  public:
  // constructor
  SportsCar(string b,string m){
    this->brand=b;
    this->model=m;
    isEngineOn=false;
    currentSpeed=0;
    tyreCompany="MRF";
  }

  // getters and setters
  string getTyreCompany(){
    return tyreCompany;
  }

  void setTyreCompany(string tc){
    tyreCompany=tc;
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

  ~SportsCar(){}
};

int main(){
  SportsCar* myCar=new SportsCar("ford","Mustang");
  myCar->startEngine();
  myCar->accelerate();
  myCar->accelerate();
  myCar->brake();
  myCar->stopEngine();
  cout<<"Tyre Company name is "<<myCar->getTyreCompany()<<endl;
  myCar->setTyreCompany("Pirelli");
  cout<<"Tyre Company name is "<<myCar->getTyreCompany()<<endl;
  delete myCar;
  return 0;
}