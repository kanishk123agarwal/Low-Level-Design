#include <iostream>
#include <vector>

using namespace std;

// Product class representing any item in eCommerce.
class Product {
public:
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

//1. ShoppingCart: Only responsible for Cart related business logic.
class ShoppingCart {
private:
    vector<Product*> products;

public:
    void addProduct(Product* p) { 
        products.push_back(p);
    }

    const vector<Product*>& getProducts() { 
        return products;
    } 

    //Calculates total price in cart.
    double calculateTotal() {
        double total = 0;
        for (auto p : products) {
            total += p->price;
        }
        return total;
    }
};

// 2. ShoppingCartPrinter: Only responsible for printing invoices
class ShoppingCartPrinter {
private:
    ShoppingCart* cart; 

public:
    ShoppingCartPrinter(ShoppingCart* cart) { 
        this->cart = cart; 
    }

    void printInvoice() {
        cout << "Shopping Cart Invoice:\n";
        for (auto p : cart->getProducts()) {
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << cart->calculateTotal() << endl;
    }
};

// Abstract class
class Persistence{
  private:
  ShoppingCart* cart;
  public:
  virtual void save(ShoppingCart* cart)=0;
};

class SQLPersistence: public Persistence{
  public:
  void save(ShoppingCart* cart){
    cout<<"Saving to SQL"<<endl;
  }
};

class MongoPersistence: public Persistence{
  public:
  void save(ShoppingCart* cart){
    cout<<"Saving to Mongo"<<endl;
  }
};

class FilePersistence: public Persistence{
  public:
  void save(ShoppingCart* cart){
    cout<<"Saving to File"<<endl;
  }
};

int main() {
  ShoppingCart* cart = new ShoppingCart();

  cart->addProduct(new Product("Laptop", 50000));
  cart->addProduct(new Product("Mouse", 2000));

  ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
  printer->printInvoice();

  Persistence* db=new SQLPersistence();
  db->save(cart);

  Persistence* mongo=new MongoPersistence();
  mongo->save(cart);

  Persistence* file=new FilePersistence();
  file->save(cart);

  return 0;
}