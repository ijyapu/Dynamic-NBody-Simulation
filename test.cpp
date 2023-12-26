// Copyright 2023 Bikash Shrestha

#include <iostream>
#include <string>
#include <fstream>

#include "Universe.hpp"
#include "CelestialBody.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTest
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(testUniverseAddAndGetBody) {
    // Test adding and getting a body in the Universe
    Universe universe;
    std::shared_ptr<CelestialBody> bodyPtr =
    std::make_shared<CelestialBody>(0, 0, 0, 0, 0, "sun.gif");
    universe.addBody(bodyPtr);
    BOOST_REQUIRE_EQUAL(universe.getBodyCount(), 1);
}

BOOST_AUTO_TEST_CASE(testLoadFromFile) {
    // Test loading data from a file
    Universe universe;
    std::ifstream inFile("planets.txt");
    BOOST_REQUIRE(inFile.is_open());

    int n;
    double uniRadius;
    inFile >> n >> uniRadius;
    universe = Universe(uniRadius, 800, n, inFile);
    inFile.close();
    BOOST_REQUIRE_EQUAL(universe.getBodyCount(), n);
}

BOOST_AUTO_TEST_CASE(testLoadTexture) {
    // Test loading a texture for a CelestialBody
    CelestialBody body;
    BOOST_REQUIRE(body.loadTexture("sun.gif"));
}

BOOST_AUTO_TEST_CASE(testAcceleration) {
    // Test calculating acceleration between two CelestialBodies
    CelestialBody body1(0, 0, 0, 0, 1e6, "sun.gif");
    CelestialBody body2(1, 1, 0, 0, 1e6, "mercury.gif");
    double ctime = 1.0;
    body1.acceleration(body2, ctime);
}

BOOST_AUTO_TEST_CASE(testMove) {
    // Test moving a CelestialBody
    CelestialBody body(0, 0, 1, 1, 1e6, "venus.gif");
    double ctime = 1.0;
    body.move(ctime);
    BOOST_REQUIRE_EQUAL(body.get_xpos(), 1.0);
    BOOST_REQUIRE_EQUAL(body.get_ypos(), 1.0);
}

BOOST_AUTO_TEST_CASE(testUniverseDraw) {
    // Test drawing the Universe
    Universe universe;
    std::ifstream inFile("planets.txt");
    int n;
    double uniRadius;
    inFile >> n >> uniRadius;
    universe = Universe(uniRadius, 800, n, inFile);
    inFile.close();
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 800);
    renderTexture.clear();
    renderTexture.draw(universe);
    renderTexture.display();
}


