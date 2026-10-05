# Ride Sharing System in C++ and Smalltalk

An educational class-based system demonstrating encapsulation, inheritance,
and polymorphism. The Smalltalk dialect is **GNU Smalltalk 3.2.5**; the C++
implementation requires **C++17**. GNU Smalltalk bracket class syntax is not
intended to be pasted unchanged into Pharo or Squeak.

## Fare rules

- Standard: USD 2.00 base + USD 1.50 per mile.
- Premium: USD 5.00 base + USD 3.00 per mile.
- Zero distance is allowed and incurs the base fare.
- Prices are classroom assumptions, not prices from a ride-sharing provider.

## Run C++

From this project's root, with GCC or Clang available:

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic cpp/main.cpp -o build/ride_cpp
./build/ride_cpp
g++ -std=c++17 -Wall -Wextra -Wpedantic tests/test_cpp.cpp -o build/test_cpp
./build/test_cpp
```

On Windows, run these commands in a GCC-enabled terminal (such as MSYS2),
or compile `cpp/main.cpp` in Visual Studio with the C++17 language standard.

## Run GNU Smalltalk

With `gst` on PATH, from this project's root:

```sh
gst -q smalltalk/RideSharing.st smalltalk/demo.st
gst -q smalltalk/RideSharing.st tests/test_smalltalk.st
```

Use a GNU Smalltalk installation or a Linux environment such as WSL on Windows.
Both commands must include the class definitions before the demo or checks.
