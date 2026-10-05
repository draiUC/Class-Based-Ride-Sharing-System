| rides driver rider |
rides := OrderedCollection new.
rides add: (StandardRide id: 'R001' pickup: 'Downtown' dropoff: 'Airport' distance: 10).
rides add: (PremiumRide id: 'R002' pickup: 'Museum' dropoff: 'Hotel' distance: 5).
rides add: (StandardRide id: 'R003' pickup: 'Campus' dropoff: 'Station' distance: 2).
driver := Driver id: 'D001' name: 'Alex Morgan' rating: 4.8.
rider := Rider id: 'U001' name: 'Taylor Lee'.
stdout nextPutAll: 'RIDE SHARING SYSTEM - Smalltalk'; nl;
    nextPutAll: 'Mixed ride collection'; nl.
rides do: [:ride |
    rider requestRide: ride.
    stdout nextPutAll: ride rideDetails; nl.
    stdout nextPutAll: 'Polymorphic fare: $', (ride money: ride fare); nl.
    "Each requested trip is treated as completed in this demonstration."
    driver addRide: ride
].
stdout nl; nextPutAll: 'Driver summary'; nl.
driver getDriverInfo.
stdout nl; nextPutAll: 'Rider history'; nl.
rider viewRides.
