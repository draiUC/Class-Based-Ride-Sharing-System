#include "ride_sharing.hpp"
#include <iostream>
int main() {
    std::vector<RidePtr> rides{
        std::make_shared<StandardRide>("R001", "Downtown", "Airport", 10.0),
        std::make_shared<PremiumRide>("R002", "Museum", "Hotel", 5.0),
        std::make_shared<StandardRide>("R003", "Campus", "Station", 2.0)};
    Driver driver("D001", "Alex Morgan", 4.8);
    Rider rider("U001", "Taylor Lee");
    std::cout << "RIDE SHARING SYSTEM - C++\nMixed ride collection\n";
    for (const auto& ride : rides) {
        rider.requestRide(ride);
        std::cout << ride->rideDetails() << '\n';
        std::cout << "Polymorphic fare(): $" << std::fixed << std::setprecision(2)
                  << ride->fare() << '\n';
        driver.addRide(ride);
    }
    std::cout << "\nDriver summary\n";
    driver.getDriverInfo(std::cout);
    std::cout << "\nRider history\n";
    rider.viewRides(std::cout);
}
