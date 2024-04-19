#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Point 
{
protected:
    int x, y;              // Координаты точки
    sf::Color color;       // и её цвет

public:
    Point()
    {
        x = 960;
        y = 540;
        color = sf::Color::White;
    }

    Point(int xx, int yy, sf::Color col)
    {
        x = xx;
        y = yy;
        color = col;
    }

    ~Point() {}

    void draw(sf::RenderWindow& window)
    {

        sf::CircleShape point(4);               // Устанавливаем раземер точки в 4 пикселя
        point.setPosition(x, y);                // Устанавливаем позицию точки
        point.setFillColor(sf::Color(color));   // Задаем ей цвет
        window.draw(point);                     // Отрисовываем
    }

    void hide() 
    {
        x = 2000;
        y = 2000;
    }

    void move(int dxx, int dyy) 
    {
        x += dxx;
        y += dyy;
    }
};

class Tline : public Point
{
protected:
    int dx, dy;

public:
    Tline()
    {
        Point();
        dx = 0;
        dy = 0;
    }

    Tline(int x, int y, int dxx, int dyy, sf::Color col)
    {
        Point(x, y, col);
        dx = dxx;
        dy = dyy;
        color = col;
    }

    ~Tline() {}

    void draw(sf::RenderWindow& window)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[1].position = sf::Vector2f(x + dx, y + dy);
        line[0].color = color;
        line[1].color = color;
        window.draw(line);
    }

    void hide()
    {
        x += 2000;
        y += 2000;
        dx = 0;
        dy = 0;
    }

    void move(int dxx, int dyy)
    {
        dx += dxx;
        dy += dyy;
    }
    void rotate(double fi)
    {
        double newX = x * cos(fi) - y * sin(fi);
        double newY = x * sin(fi) + y * cos(fi);
        double newDx = dx * cos(fi) - dy * sin(fi);
        double newDy = dx * sin(fi) + dy * cos(fi);
        x = static_cast<int>(newX);
        y = static_cast<int>(newY);
        dx = static_cast<int>(newDx);
        dy = static_cast<int>(newDy);
    }
};

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Point Example");

    Tline first_line(960, 540, 250, 250, sf::Color::Red);



 //   Point first(490, 300, sf::Color::Blue);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();  // Закрываем окно, если нажат крестик
            }
        }

        window.clear();          // Очищаем окно


        first_line.draw(window); // Рисуем точку


        window.display();        // Отображаем окно
    }
    

    return 0;
}