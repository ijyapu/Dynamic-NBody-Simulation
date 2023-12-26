// Copyright 2023 Bikash Shrestha

#include "CelestialBody.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <utility>

// This file contains the implementation of the CelestialBody class,
// which represents a celestial body in space.
// It includes methods for loading textures, setting radius and window size,
// getting position, drawing, calculating acceleration, and moving.
// It also includes overloaded input and output stream operators for reading
// and writing CelestialBody objects.

// Constructor that initializes the CelestialBody object with given parameters
CelestialBody::CelestialBody(double xpos, double ypos, double xvel, double yvel,
double mass, const std::string& filename)
    : xpos(xpos), ypos(ypos), xvel(xvel), yvel(yvel),
    mass(mass), filename(filename) {
    texture = std::make_shared<sf::Texture>();
}

// Default constructor that initializes the CelestialBody object with default values
CelestialBody::CelestialBody()
    : xpos(0), ypos(0), xvel(0), yvel(0), mass(0), radius(0), windowSize(0) {
    texture = std::make_shared<sf::Texture>();
}

// Method that loads the texture of the CelestialBody object from the given file.
bool CelestialBody::loadTexture(const std::string& filename) {
    if (!texture->loadFromFile(filename)) {
        return false;
    }
    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
    return true;
}

// set the radius of the CelestialBody object
void CelestialBody::set_radius(double r) {
    radius = r;
}

// set the window size of the CelestialBody object
void CelestialBody::set_windowSize(double size) {
    windowSize = size;
}

// return the x position of the CelestialBody object
double CelestialBody::get_xpos() const {
    return xpos;
}

// return the y position of the CelestialBody object
double CelestialBody::get_ypos() const {
    return ypos;
}

// move the CelestialBody object based on its velocity and the given time step
void CelestialBody::move(double ctime) {
    xpos = (xpos + xvel * ctime);
    ypos = (ypos + yvel * ctime);
}

// draw the CelestialBody object on the given render target
void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sf::Vector2u size = target.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;
    sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
    double adjusted_xpos = (xpos * (width / (2 * radius))) + (width / 2.0);
    double adjusted_ypos = (width / 2.0) - (ypos * (height / (2 * radius)));
    sprite.setPosition(adjusted_xpos, adjusted_ypos);
    target.draw(sprite, states);
}

// calculate the acceleration of the CelestialBody object
// due to the gravitational force of another CelestialBody object
void CelestialBody::acceleration(const CelestialBody& planet, double ctime) {
    double G = 6.67e-11;
    double cx = planet.xpos - xpos;
    double cy = planet.ypos - ypos;
    double r = sqrt((cx * cx) + (cy * cy));

    double F = (G * mass * planet.mass) / (r * r);
    double Fx = F * (cx / r);
    double Fy = F * (cy / r);

    double Ax = Fx / mass;
    double Ay = Fy / mass;

    xvel = (xvel + ctime * Ax);
    yvel = (yvel + ctime * Ay);
}

// Overloaded input stream operator that reads a CelestialBody object from the given input stream
std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.xpos >> body.ypos >> body.xvel >> body.yvel >> body.mass >> body.filename;
    if (!body.loadTexture(body.filename)) {
        std::cerr << "Error: Failed to load texture: " << body.filename << std::endl;
    }
    return in;
}

// Overloaded output stream operator that writes a CelestialBody object to the given output stream
std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << body.xpos << " "
        << body.ypos << " "
        << body.xvel << " "
        << body.yvel << " "
        << body.mass << " "
        << body.filename;
    return out;
}

double CelestialBody::get_velocity() const {
    return std::sqrt(xvel * xvel + yvel * yvel);
}
