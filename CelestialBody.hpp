// Copyright 2023 Bikash Shrestha

// This file defines the CelestialBody class, which represents a celestial body in a simulation.
// It inherits from sf::Drawable to allow for rendering in a SFML window.
// It also includes overloaded input and output stream operators for easy I/O.

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>

class CelestialBody : public sf::Drawable {
 public:
    CelestialBody();

    CelestialBody(double xpos, double ypos, double xvel, double yvel,
    double mass, const std::string& filename);

    void set_radius(double radius);
    void set_windowSize(double size);
    void move(double ctime);

    double get_xpos() const;
    double get_ypos() const;

    bool loadTexture(const std::string& filename);
    double get_velocity() const;

    void acceleration(const CelestialBody& planet, double ctime);

    friend std::istream& operator>>(std::istream& in, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);

 private:
    double xpos, ypos, xvel, yvel, mass, radius;
    std::string filename;
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    double windowSize;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
using CelestialBodyPtr = std::shared_ptr<CelestialBody>;
