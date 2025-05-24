#include <iostream>
#include <vector>
using namespace std;

class Product
{
public:
  string name;
  double price;

  Product(string name, double price)
  {
    this->name = name;
    this->price = price;
  }
};

// Shopping Cart can handle only 1 responsibility that is calculate total
class ShoppingCart
{
private:
  vector<Product *> products;

public:
  void addProduct(Product *p)
  {
    products.push_back(p);
  }

  const vector<Product *> &getProducts()
  {
    return products;
  }

  // 1: calculate total price
  double calculateTotal()
  {
    double total = 0;
    for (auto p : products)
    {
      total += p->price;
    }
    return total;
  }
};

// 2: Shopping cart printer-printing invoices
class ShoppingCartPrinter
{
private:
  ShoppingCart *cart;

public:
  ShoppingCartPrinter(ShoppingCart *cart)
  {
    this->cart = cart;
  }

  // 2: print receipt - Violating SRP
  void printReceipt()
  {
    for (auto p : cart->getProducts())
    {
      cout << p->name << " " << p->price << endl;
    }
    cout << "Total: " << cart->calculateTotal() << endl;
  }
};

// 3: ShoppingCartStorage - Saving to DB
class ShoppingCartStorage
{
private:
  ShoppingCart* cart;

public:

ShoppingCartStorage(ShoppingCart* cart){
  this->cart=cart;
}
  // 3: save to DB - Violating SRP
  void saveToDB()
  {
    // save to DB
    cout << "Saving Shopping cart to database..." << endl;
  }
};

int main()
{
  ShoppingCart *cart = new ShoppingCart();
  cart->addProduct(new Product("Laptop", 1000.0));
  cart->addProduct(new Product("Mobile", 500.0));

  ShoppingCartPrinter *printer = new ShoppingCartPrinter(cart);
  printer->printReceipt();

  ShoppingCartStorage *storage = new ShoppingCartStorage(cart);
  storage->saveToDB();
  return 0;
}