// Ride Sharing Service (Low Level Design)
// Language: C++
// Simplified implementation demonstrating SOLID and Design Patterns
// https://github.com/adityatandon15/LLD
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

//--------------------------------------
// Basic Utility Classes
//--------------------------------------

class Location {
public:
    double x, y;
    Location(double x, double y) : x(x), y(y) {}
    double distanceTo(Location* other) {
        return sqrt(pow(x - other->x, 2) + pow(y - other->y, 2));
    }
};

//--------------------------------------
// Observer Pattern Interfaces
//--------------------------------------

class IObserver {
public:
    virtual void update(const string& message) = 0;
    virtual ~IObserver() = default;
};

//--------------------------------------
// Users
//--------------------------------------

class User {
protected:
    string name, phone;
public:
    User(string name, string phone) : name(name), phone(phone) {}
    virtual ~User() = default;
};

class Rider : public User, public IObserver {
public:
    Rider(string name, string phone) : User(name, phone) {}
    void update(const string& message) override {
        cout << "[Notification to Rider] " << message << endl;
    }
};

class Driver : public User, public IObserver {
private:
    bool available;
    Location* currentLocation;
    double rating;
public:
    string vehicleType;
    Driver(string name, string phone, Location* loc, string vehicleType, double rating)
        : User(name, phone), currentLocation(loc), vehicleType(vehicleType), rating(rating), available(true) {}

    Location* getLocation() const { return currentLocation; }
    bool isAvailable() const { return available; }
    void setAvailable(bool status) { available = status; }
    double getRating() const { return rating; }

    void update(const string& message) override {
        cout << "[Notification to Driver] " << message << endl;
    }
};

//--------------------------------------
// Ride and Related Interfaces
//--------------------------------------

class RideStatus {
public:
    enum Status { REQUESTED, CONFIRMED, ONGOING, COMPLETED };
};

class Ride {
private:
    Rider* rider;
    Driver* driver;
    Location *pickup, *drop;
    RideStatus::Status status;
    double fare;
public:
    Ride(Rider* rider, Location* pickup, Location* drop)
        : rider(rider), pickup(pickup), drop(drop), driver(nullptr), status(RideStatus::REQUESTED), fare(0.0) {}

    void assignDriver(Driver* d) {
        driver = d;
        d->setAvailable(false);
        status = RideStatus::CONFIRMED;
        notify("Driver assigned: " + d->vehicleType);
    }

    void startRide() {
        status = RideStatus::ONGOING;
        notify("Ride started");
    }

    void completeRide() {
        status = RideStatus::COMPLETED;
        fare = calculateFare();
        driver->setAvailable(true);
        notify("Ride completed. Fare: Rs." + to_string(fare));
    }

    double calculateFare() {
        return 50 + pickup->distanceTo(drop) * 10; // Simple fare logic
    }

    void notify(const string& msg) {
        rider->update(msg);
        if (driver) driver->update(msg);
    }
};

//--------------------------------------
// Strategy Pattern for Matching
//--------------------------------------

class MatchingStrategy {
public:
    virtual Driver* match(Rider* rider, Location* pickup, const vector<Driver*>& drivers) = 0;
    virtual ~MatchingStrategy() = default;
};

class NearestDriverStrategy : public MatchingStrategy {
public:
    Driver* match(Rider* rider, Location* pickup, const vector<Driver*>& drivers) override {
        Driver* best = nullptr;
        double minDist = 1e9;
        for (auto* d : drivers) {
            if (d->isAvailable()) {
                double dist = pickup->distanceTo(d->getLocation());
                if (dist < minDist) {
                    minDist = dist;
                    best = d;
                }
            }
        }
        return best;
    }
};

class HighestRatedDriverStrategy : public MatchingStrategy {
public:
    Driver* match(Rider* rider, Location* pickup, const vector<Driver*>& drivers) override {
        Driver* best = nullptr;
        double maxRating = 0;
        for (auto* d : drivers) {
            if (d->isAvailable() && d->getRating() > maxRating) {
                maxRating = d->getRating();
                best = d;
            }
        }
        return best;
    }
};

//--------------------------------------
// Singleton RideManager
//--------------------------------------

class RideManager {
private:
    static RideManager* instance;
    vector<Driver*> drivers;
    vector<unique_ptr<Ride>> rides;
    unique_ptr<MatchingStrategy> strategy;

    RideManager() { strategy = make_unique<NearestDriverStrategy>(); }

public:
    static RideManager* getInstance() {
        if (!instance)
            instance = new RideManager();
        return instance;
    }

    void addDriver(Driver* d) {
        drivers.push_back(d);
    }

    void setStrategy(MatchingStrategy* s) {
        strategy.reset(s);
    }

    void requestRide(Rider* rider, Location* pickup, Location* drop) {
        auto ride = make_unique<Ride>(rider, pickup, drop);
        Driver* matched = strategy->match(rider, pickup, drivers);
        if (!matched) {
            rider->update("No drivers available");
            return;
        }
        ride->assignDriver(matched);
        ride->startRide();
        ride->completeRide();
        rides.push_back(move(ride));
    }
};

RideManager* RideManager::instance = nullptr;

//--------------------------------------
// Main Simulation
//--------------------------------------

int main() {
    auto* rm = RideManager::getInstance();

    // Setup
    Rider* rider1 = new Rider("Alice", "9999");
    Driver* driver1 = new Driver("Bob", "8888", new Location(0, 0), "Sedan", 4.5);
    Driver* driver2 = new Driver("Charlie", "7777", new Location(5, 5), "SUV", 4.9);

    rm->addDriver(driver1);
    rm->addDriver(driver2);

    cout << "\n--- Ride with Nearest Strategy ---\n";
    rm->setStrategy(new NearestDriverStrategy());
    rm->requestRide(rider1, new Location(1, 1), new Location(10, 10));

    cout << "\n--- Ride with Highest Rated Strategy ---\n";
    rm->setStrategy(new HighestRatedDriverStrategy());
    rm->requestRide(rider1, new Location(3, 3), new Location(8, 8));

    return 0;
}
