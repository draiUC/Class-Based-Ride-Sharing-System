#ifndef RIDE_SHARING_HPP
#define RIDE_SHARING_HPP
#include <cmath>
#include <iomanip>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Ride {
private:
    std::string rideID_, pickupLocation_, dropoffLocation_;
    double distance_;
    mutable double fareValue_ = 0; // Refreshed on every fare calculation.
protected:
    double distance() const { return distance_; }
    double calculateFare(double base, double rate) const {
        fareValue_ = base + distance_ * rate;
        return fareValue_;
    }
public:
    Ride(std::string id, std::string pickup, std::string dropoff, double miles)
        : rideID_(std::move(id)), pickupLocation_(std::move(pickup)),
          dropoffLocation_(std::move(dropoff)), distance_(miles) {
        if (rideID_.empty() || pickupLocation_.empty() || dropoffLocation_.empty())
            throw std::invalid_argument("Ride fields must not be empty");
        if (!std::isfinite(miles) || miles < 0)
            throw std::invalid_argument("Distance must be finite and nonnegative");
    }
    virtual ~Ride() = default;
    const std::string& rideID() const { return rideID_; }
    virtual double fare() const { return calculateFare(2.0, 1.5); }
    virtual std::string rideDetails() const {
        std::ostringstream out;
        out << rideID_ << " | " << pickupLocation_ << " -> " << dropoffLocation_
            << " | " << std::fixed << std::setprecision(2) << distance_
            << " miles | $" << fare();
        return out.str();
    }
};
class StandardRide : public Ride {
public:
    using Ride::Ride;
    double fare() const override { return calculateFare(2.0, 1.5); }
    std::string rideDetails() const override {
        return "Standard | " + Ride::rideDetails();
    }
};
class PremiumRide : public Ride {
public:
    using Ride::Ride;
    double fare() const override { return calculateFare(5.0, 3.0); }
    std::string rideDetails() const override {
        return "Premium  | " + Ride::rideDetails();
    }
};
// Const shared objects preserve subtype behavior and allow shared ride history.
using RidePtr = std::shared_ptr<const Ride>;
inline void addUniqueRide(std::vector<RidePtr>& rides, RidePtr ride) {
    if (!ride) throw std::invalid_argument("Ride must not be null");
    for (const auto& existing : rides)
        if (existing->rideID() == ride->rideID())
            throw std::invalid_argument("Duplicate ride ID");
    rides.push_back(std::move(ride));
}
class Driver {
private:
    std::string driverID_, name_;
    double rating_;
    std::vector<RidePtr> assignedRides_; // Completed rides, never exposed.
public:
    Driver(std::string id, std::string name, double rating)
        : driverID_(std::move(id)), name_(std::move(name)), rating_(rating) {
        if (driverID_.empty() || name_.empty())
            throw std::invalid_argument("Driver fields must not be empty");
        if (!std::isfinite(rating) || rating < 0 || rating > 5)
            throw std::invalid_argument("Rating must be between 0 and 5");
    }
    void addRide(RidePtr ride) { addUniqueRide(assignedRides_, std::move(ride)); }
    std::size_t rideCount() const { return assignedRides_.size(); }
    double totalEarnings() const {
        double total = 0;
        for (const auto& ride : assignedRides_) total += ride->fare();
        return total;
    }
    void getDriverInfo(std::ostream& out) const {
        out << driverID_ << " | " << name_ << " | Rating: " << std::fixed
            << std::setprecision(2) << rating_ << " | Completed rides: " << rideCount()
            << " | Gross fares: $" << std::setprecision(2) << totalEarnings() << '\n';
    }
};
class Rider {
private:
    std::string riderID_, name_;
    std::vector<RidePtr> requestedRides_;
public:
    Rider(std::string id, std::string name)
        : riderID_(std::move(id)), name_(std::move(name)) {
        if (riderID_.empty() || name_.empty())
            throw std::invalid_argument("Rider fields must not be empty");
    }
    void requestRide(RidePtr ride) { addUniqueRide(requestedRides_, std::move(ride)); }
    std::size_t rideCount() const { return requestedRides_.size(); }
    void viewRides(std::ostream& out) const {
        out << riderID_ << " | " << name_ << " | Requested rides: " << rideCount() << '\n';
        for (const auto& ride : requestedRides_) out << ride->rideDetails() << '\n';
    }
};
#endif
