"GNU Smalltalk 3.2.5. All prices are illustrative US dollars."
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance fareValue |
    Ride class >> id: anID pickup: pickup dropoff: dropoff distance: miles [
        ^self new initializeID: anID pickup: pickup dropoff: dropoff distance: miles
    ]
    initializeID: anID pickup: pickup dropoff: dropoff distance: miles [
        ((anID isEmpty or: [pickup isEmpty]) or: [dropoff isEmpty])
            ifTrue: [self error: 'Ride fields must not be empty'].
        (miles isNumber and: [miles >= 0])
            ifFalse: [self error: 'Distance must be nonnegative'].
        rideID := anID copy. pickupLocation := pickup copy.
        dropoffLocation := dropoff copy. distance := miles.
        fareValue := 0. ^self
    ]
    rideID [ ^rideID copy ]
    fare [ fareValue := 2 + (distance * 1.5). ^fareValue ]
    money: amount [
        | cents fraction |
        cents := (amount * 100) rounded.
        fraction := (cents \\ 100) printString.
        fraction size = 1 ifTrue: [fraction := '0', fraction].
        ^(cents // 100) printString, '.', fraction
    ]
    rideDetails [
        ^rideID, ' | ', pickupLocation, ' -> ', dropoffLocation,
            ' | ', (self money: distance), ' miles | $', (self money: self fare)
    ]
]
Ride subclass: StandardRide [
    fare [ fareValue := 2 + (distance * 1.5). ^fareValue ]
    rideDetails [ ^'Standard | ', super rideDetails ]
]
Ride subclass: PremiumRide [
    fare [ fareValue := 5 + (distance * 3). ^fareValue ]
    rideDetails [ ^'Premium  | ', super rideDetails ]
]
Object subclass: Driver [
    | driverID name rating assignedRides |
    Driver class >> id: anID name: aName rating: aRating [
        ^self new initializeID: anID name: aName rating: aRating
    ]
    initializeID: anID name: aName rating: aRating [
        (anID isEmpty or: [aName isEmpty])
            ifTrue: [self error: 'Driver fields must not be empty'].
        (aRating isNumber and: [aRating >= 0 and: [aRating <= 5]])
            ifFalse: [self error: 'Rating must be between 0 and 5'].
        driverID := anID copy. name := aName copy. rating := aRating.
        assignedRides := OrderedCollection new. ^self
    ]
    addRide: aRide [
        (aRide isKindOf: Ride) ifFalse: [self error: 'A Ride is required'].
        (assignedRides anySatisfy: [:existing | existing rideID = aRide rideID])
            ifTrue: [self error: 'Duplicate ride ID'].
        assignedRides add: aRide
    ]
    rideCount [ ^assignedRides size ]
    totalEarnings [
        ^assignedRides inject: 0 into: [:total :ride | total + ride fare]
    ]
    getDriverInfo [
        | formatter |
        formatter := Ride new.
        stdout nextPutAll: driverID, ' | ', name, ' | Rating: ', (formatter money: rating),
            ' | Completed rides: ', self rideCount printString,
            ' | Gross fares: $', (formatter money: self totalEarnings); nl
    ]
]
Object subclass: Rider [
    | riderID name requestedRides |
    Rider class >> id: anID name: aName [
        ^self new initializeID: anID name: aName
    ]
    initializeID: anID name: aName [
        (anID isEmpty or: [aName isEmpty])
            ifTrue: [self error: 'Rider fields must not be empty'].
        riderID := anID copy. name := aName copy.
        requestedRides := OrderedCollection new. ^self
    ]
    requestRide: aRide [
        (aRide isKindOf: Ride) ifFalse: [self error: 'A Ride is required'].
        (requestedRides anySatisfy: [:existing | existing rideID = aRide rideID])
            ifTrue: [self error: 'Duplicate ride ID'].
        requestedRides add: aRide
    ]
    rideCount [ ^requestedRides size ]
    viewRides [
        stdout nextPutAll: riderID, ' | ', name, ' | Requested rides: ',
            self rideCount printString; nl.
        requestedRides do: [:ride | stdout nextPutAll: ride rideDetails; nl]
    ]
]
