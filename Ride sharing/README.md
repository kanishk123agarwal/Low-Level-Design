# Ride Sharing Service Implementation

A simplified ride-sharing service implementation demonstrating SOLID principles and Design Patterns in C++.

## Features

* User Management (Riders and Drivers)
* Location-based Services
* Dynamic Driver Matching Strategies
* Real-time Notifications
* Ride Status Tracking

## Architecture Overview

The system implements several key patterns:

### 1. Observer Pattern
Used for notifications between riders and drivers
- Riders and Drivers implement the IObserver interface
- Ride acts as the subject notifying observers of status updates

### 2. Strategy Pattern
Enables flexible driver matching algorithms
- NearestDriverStrategy: Matches drivers based on proximity
- HighestRatedDriverStrategy: Prioritizes driver ratings
- Extensible design allows for new strategies

### 3. Singleton Pattern
Ensures single instance of RideManager
- Centralized ride management
- Global access point for ride operations

## Design Decisions

* Smart pointers (unique_ptr) for automatic memory management
* Abstract classes/interfaces for extensibility
* Enum-based status tracking
* Template-based strategy pattern implementation

## Usage Example

```cpp
// Create ride manager instance
auto* rm = RideManager::getInstance();

// Add drivers
Driver* driver1 = new Driver("Bob", "8888", new Location(0, 0), "Sedan", 4.5);
rm->addDriver(driver1);

// Request a ride
Rider* rider1 = new Rider("Alice", "9999");
rm->requestRide(rider1, new Location(1, 1), new Location(10, 10));
```

## Key Components

* **Location**: Handles coordinate-based positioning
* **User/Rider/Driver**: Implements user hierarchy with observer pattern
* **RideStatus**: Enumerates ride states
* **Ride**: Manages ride lifecycle and notifications
* **MatchingStrategy**: Abstract strategy for driver selection
* **RideManager**: Singleton managing system operations

## Extensibility Points

* New driver matching strategies can be implemented by inheriting from MatchingStrategy
* Additional notification channels can be added to observers
* New ride status states can be added to RideStatus enum
* Custom fare calculation logic can be integrated