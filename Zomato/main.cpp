#include <iostream>
#include "TomatoApp.h"
using namespace std;

int main() {
    // Create TomatoApp Object
    TomatoApp* tomato = new TomatoApp();

    // Simulate a user coming in (Happy Flow)
    User* user = new User(101, "Kanishk", "Rajasthan");
    cout << "User: " << user->getName() << " is active." << endl;

    // User searches for restaurants by location
    vector<Restaurant*> restaurantList = tomato->searchRestaurants("Delhi");

    if (restaurantList.empty()) {
        cout << "No restaurants found!" << endl;
        return 0;
    }
    cout << "Found Restaurants:" << endl;
    for (auto restaurant : restaurantList) {
        cout << " - " << restaurant->getName() << endl;
    }

    // User selects a restaurant
    tomato->selectRestaurant(user, restaurantList[1]);

    cout << "Selected restaurant: " << restaurantList[1]->getName() << endl;

    // User adds items to the cart
    tomato->addToCart(user, "P1");
    tomato->addToCart(user, "P2");
    tomato->addToCart(user,"P3");

    tomato->printUserCart(user);

    // User checkout the cart
    Order* order = tomato->checkoutNow(user, "Delivery", new UpiPaymentStrategy("1234567890"));
    
    // User pay for the cart. If payment is success, notification is sent.
    tomato->payForOrder(user, order);

    // 2nd user
    User* user1 = new User(101, "Priyanka", "Kolkata");
    cout << "User: " << user1->getName() << " is active." << endl;

    // User searches for restaurants by location
    vector<Restaurant*> restaurantList1 = tomato->searchRestaurants("Kolkata");

    if (restaurantList1.empty()) {
        cout << "No restaurants found!" << endl;
        return 0;
    }
    cout << "Found Restaurants:" << endl;
    for (auto restaurant : restaurantList1) {
        cout << " - " << restaurant->getName() << endl;
    }

    // User selects a restaurant
    tomato->selectRestaurant(user1, restaurantList1[0]);

    cout << "Selected restaurant: " << restaurantList1[0]->getName() << endl;

    // User adds items to the cart
    tomato->addToCart(user1, "P1");
    tomato->addToCart(user1, "P2");
    tomato->addToCart(user1,"P3");

    tomato->printUserCart(user);

    // User checkout the cart
    Order* order1 = tomato->checkoutNow(user1, "Pickup", new UpiPaymentStrategy("1234567890"));
    
    // User pay for the cart. If payment is success, notification is sent.
    tomato->payForOrder(user1, order1);

    // Cleanup Code.
    delete tomato;
    delete user;
    delete user1;
    
    return 0;
}