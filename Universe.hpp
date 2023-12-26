// Copyright 2023 Bikash Shrestha

// This file defines the Universe class, which represents a collection of celestial bodies in space.
// It inherits from sf::Drawable to allow for rendering in a SFML window.

#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>

using CelestialBodyPtr = std::shared_ptr<CelestialBody>;

class Universe : public sf::Drawable {
 public:
    Universe() : radius(0), windowSize(0) {}
    Universe(double radius, int windowSize, int num_of_planets, std::istream& in);


    void step(double seconds);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void addBody(const CelestialBodyPtr& body);

    size_t getBodyCount() const;

    friend std::istream& operator>>(std::istream& input, Universe& universe);
    friend std::ostream& operator<<(std::ostream& output, const Universe& universe);

    virtual ~Universe();
    bool isMoving() const;

 private:
    std::vector<CelestialBodyPtr> planets;
    double radius;
    int windowSize;
};
