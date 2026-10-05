| check rejects standard premium driver rider |
check := [:condition | condition ifFalse: [self error: 'Check failed']].
rejects := [:action |
    | caught |
    caught := false.
    [action value] on: Error do: [:ex | caught := true].
    check value: caught
].
standard := StandardRide id: 'S' pickup: 'A' dropoff: 'B' distance: 10.
premium := PremiumRide id: 'P' pickup: 'A' dropoff: 'B' distance: 5.
check value: (standard fare = 17).
check value: (premium fare = 20).
check value: (premium rideDetails startsWith: 'Premium').
check value: ((StandardRide id: 'Z' pickup: 'A' dropoff: 'B' distance: 0) fare = 2).
driver := Driver id: 'D' name: 'Alex' rating: 4.8.
rider := Rider id: 'U' name: 'Taylor'.
driver addRide: standard; addRide: premium.
rider requestRide: standard; requestRide: premium.
check value: (driver rideCount = 2 and: [rider rideCount = 2]).
check value: (driver totalEarnings = 37).
rejects value: [driver addRide: standard].
rejects value: [rider requestRide: premium].
rejects value: [driver addRide: nil].
rejects value: [StandardRide id: 'B' pickup: 'A' dropoff: 'B' distance: -1].
rejects value: [Driver id: 'D' name: 'Alex' rating: 6].
rejects value: [StandardRide id: '' pickup: 'A' dropoff: 'B' distance: 1].
check value: (driver rideCount = 2 and: [rider rideCount = 2]).
stdout nextPutAll: 'Smalltalk checks passed: fares, dispatch, histories, validation.'; nl.
