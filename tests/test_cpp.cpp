#include "../cpp/ride_sharing.hpp"
#include <cassert>
#include <iostream>
template<class F> void rejects(F f) {
    bool rejected = false;
    try { f(); } catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
}
int main() {
    RidePtr standard = std::make_shared<StandardRide>("S", "A", "B", 10);
    RidePtr premium = std::make_shared<PremiumRide>("P", "A", "B", 5);
    assert(standard->fare() == 17 && premium->fare() == 20);
    assert(premium->rideDetails().find("Premium") != std::string::npos);
    assert(StandardRide("Z", "A", "B", 0).fare() == 2);
    Driver driver("D", "Alex", 4.8);
    Rider rider("U", "Taylor");
    driver.addRide(standard); driver.addRide(premium);
    rider.requestRide(standard); rider.requestRide(premium);
    assert(driver.rideCount() == 2 && rider.rideCount() == 2);
    assert(driver.totalEarnings() == 37);
    rejects([&] { driver.addRide(standard); });
    rejects([&] { rider.requestRide(premium); });
    rejects([&] { driver.addRide(nullptr); });
    rejects([] { StandardRide bad("B", "A", "B", -1); });
    rejects([] { Driver bad("D", "Alex", 6); });
    rejects([] { StandardRide bad("", "A", "B", 1); });
    rejects([] { StandardRide bad("B", "A", "B", NAN); });
    assert(driver.rideCount() == 2 && rider.rideCount() == 2);
    std::cout << "C++ checks passed: fares, dispatch, histories, validation.\n";
}
