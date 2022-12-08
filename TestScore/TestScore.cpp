#include <iostream>
#include<algorithm>
#include<HighScoreManagger.h>
#include <SFML/Graphics.hpp>

HighScoreManagger* HighScoreManagger::instance = nullptr;

int main()
{
    HighScoreManagger::getinstance()->create_vector();
    auto score_1 = HighScoreManagger::getinstance()->dev_score("Nico", 1);
    HighScoreManagger::getinstance()->add_score(score_1);
    HighScoreManagger::getinstance()->add_score(Scores("Belen", 24000));
    HighScoreManagger::getinstance()->add_score(Scores("Nestor", 2300));
    HighScoreManagger::getinstance()->add_score(Scores("Benjamin", 2200));
    HighScoreManagger::getinstance()->add_score(Scores("Noelia", 2500));
    HighScoreManagger::getinstance()->add_score(Scores("Lucas", 250));
    HighScoreManagger::getinstance()->add_score(Scores("Emi", 500000));
    HighScoreManagger::getinstance()->add_score(Scores("Alejandra", 5000012));
    HighScoreManagger::getinstance()->add_score(Scores("Facundo", 500001));
    HighScoreManagger::getinstance()->add_score(Scores("Messi", 5000011));
    HighScoreManagger::getinstance()->add_score(Scores("Pablo", 24001));
    HighScoreManagger::getinstance()->read_vector();
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        HighScoreManagger::getinstance()->draw_text(window);
        window.display();
    
    }
}
