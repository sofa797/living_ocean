#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "ocean.hpp"
#include "algae.hpp"
#include "herbivore.hpp"
#include "predator.hpp"
#include <exception>
#include <stdexcept>

int main() {
    try {
        sf::Texture algaeTexture;
        sf::Texture herbivoreTexture;
        sf::Texture predatorTexture;

        if (!algaeTexture.loadFromFile("assets/algae.png")) {
            std::cerr << "Ошибка загрузки algae.png\n";
        }
        if (!herbivoreTexture.loadFromFile("assets/herbivore.png")) {
            std::cerr << "Ошибка загрузки herbivore.png\n";
        }
        if (!predatorTexture.loadFromFile("assets/predator.png")) {
            std::cerr << "Ошибка загрузки predator.png\n";
        }
            std::srand(std::time(nullptr));

        const size_t WIDTH = 20;
        const size_t HEIGHT = 20;
        const int CELL_SIZE = 20;

        Ocean ocean(WIDTH, HEIGHT);

    int numAlgae = 10 + rand() % 11;
    int numHerbivores = 5 + rand() % 6;
    int numPredators = 10 + rand() % 15;

    auto place_random = [&](std::shared_ptr<Entity> entity) {
        for (int attempt = 0; attempt < 100; ++attempt) {
            int x = rand() % WIDTH;
            int y = rand() % HEIGHT;
            if (!ocean.getCell(x, y)) {
                entity->setOcean(&ocean);
                entity->setPosition(x, y);
                ocean.setCell(x, y, entity);
                break;
            }
        }
    };

    for (int i = 0; i < numAlgae; ++i) {
        place_random(std::make_shared<Algae>());
    }

    for (int i = 0; i < numHerbivores; ++i) {
        place_random(std::make_shared<HerbivoreFish>());
    }

    for (int i = 0; i < numPredators; ++i) {
        place_random(std::make_shared<PredatorFish>());
    }


    sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), "Ocean Simulation");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::cout << "Start simulation\n";
        ocean.tick();
        std::cout << "After one tick\n";


        window.clear(sf::Color::Black);

        for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            auto entity = ocean.getCell(x, y);
            if (!entity || !entity->isAlive()) continue;

            sf::Sprite sprite;
            sprite.setScale(0.05f, 0.05f);
            sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);

            if (entity->getType() == "Algae") {
                sprite.setTexture(algaeTexture);
            } else if (entity->getType() == "HerbivoreFish") {
                sprite.setTexture(herbivoreTexture);
            } else if (entity->getType() == "PredatorFish") {
                sprite.setTexture(predatorTexture);
            }

            window.draw(sprite);
        }
    }

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка диапазона: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "Произошло исключение: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Произошло неизвестное исключение." << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}