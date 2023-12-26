// Copyright 2023 Bikash Shrestha

// This file contains the implementation of the Universe class,
// which represents a universe of celestial bodies.
// The Universe class is responsible for managing the celestial bodies,
// updating their positions and velocities, and rendering them to the screen.

#include "Universe.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

// Constructor for the Universe class
Universe::Universe(double r, int w, int numPlanets, std::istream& in)
    : radius(r), windowSize(w) {
    planets.reserve(numPlanets);

    for (int i = 0; i < numPlanets; ++i) {
        CelestialBodyPtr body = std::make_shared<CelestialBody>();
        in >> *body;
        body->set_radius(radius);
        body->set_windowSize(w);
        planets.push_back(body);
    }
}

// Add a celestial body to the universe
void Universe::addBody(const CelestialBodyPtr& body) {
    planets.push_back(body);
}

// Return the number of celestial bodies in the universe
size_t Universe::getBodyCount() const {
    return planets.size();
}

// Draw the universe and its celestial bodies to the given render target
void Universe::draw(sf::RenderTarget& t, sf::RenderStates s) const {
    for (const auto& body : planets) {
        t.draw(*body, s);
    }
}

// Advance the simulation by the given number of seconds
void Universe::step(double seconds) {
    for (auto planet : planets) {
        for (auto other : planets) {
            if (planet != other) {
                planet->acceleration(*other, seconds);
            }
        }
    }
    for (auto planet : planets) {
        planet->move(seconds);
    }
}

// Read a Universe object from an input stream
std::istream& operator>>(std::istream& in, Universe& u) {
    int numPlanets;
    in >> numPlanets >> u.radius;
    u.planets.reserve(numPlanets);

    for (int i = 0; i < numPlanets; ++i) {
        CelestialBodyPtr body = std::make_shared<CelestialBody>();
        in >> *body;
        body->set_radius(u.radius);
        body->set_windowSize(u.windowSize);
        u.planets.push_back(body);
    }
    return in;
}

// Write a Universe object to an output stream
std::ostream& operator<<(std::ostream& out, const Universe& u) {
    out << u.planets.size() << " " << u.radius << std::endl;

    for (const auto& body : u.planets) {
        out << *body << std::endl;
    }

    return out;
}

// Destructor for the Universe class
Universe::~Universe() {
    planets.clear();
}

bool Universe::isMoving() const {
    const double MOVEMENT_THRESHOLD = 0.1;  // Define a suitable threshold
    for (const auto& body : planets) {
        if (body->get_velocity() > MOVEMENT_THRESHOLD) {
            return true;
        }
    }
    return false;
}
