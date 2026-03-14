# C++ Game Project — Fairground Stall

A 3D fairground throwing game built in C++ using openFrameworks. The player charges a throw by holding the mouse button, aims at a shelf of rotating objects, and releases to launch a ball with physically simulated trajectory. Knock objects off the shelf to score — some colours are worth more than others.

## What It Is

A timed arcade game set in a 3D room with a shelf of coloured objects. Three object types sit on the shelf — a snowman, a racket, and a spear — each built from primitive shapes and slowly spinning. Objects respawn after being knocked off. The game ends when the timer runs out.

## Technical Implementation

**Physics Simulation**
The ball uses a basic but genuine physics model implemented from scratch — no engine physics, no library helpers. Force, mass, acceleration, drag, and gravity are all calculated manually each update tick. The ball's mass is set to 0.17kg, drag simulates air resistance along the Z axis, and gravity pulls it downward throughout flight. Force is translated into Z-axis acceleration at throw time based on `F = ma`.

**Object-Oriented Architecture**
All shelf objects inherit from a base `object` class that handles collision detection, colour, and the core setup/update/draw interface. Each subclass — `snowman`, `racket`, `spear` — overrides those methods to define its own shape using openFrameworks primitives. Adding a new object type requires only a new subclass.

**Collision Detection**
Collision is handled via sphere-based distance checking between the ball position and each object's world position. When the distance between centres is less than the sum of their radii, a hit is registered.

**Charge Mechanic**
The player holds the mouse button to charge force and releases to throw. A force meter UI visualises the current charge level.

## Built With

- C++ / openFrameworks
- Solo project — C++ for Creative Practice, Goldsmiths University of London, BSc Games Programming (2nd Year)

## Notes

This was one of several concurrent assignments built under time pressure. The physics values were worked out and tuned manually rather than taken from a template. The object class hierarchy was a deliberate exercise in applying OOP principles in C++ for the first time.
