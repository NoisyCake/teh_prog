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

    ~Point() 
    {
        // Нет необходимости в явном освобождении ресурсов, так как точка не рисуется
    }

    virtual void draw(sf::RenderWindow& window) = 0;

    void hide()
    {
        sf::Color::Black;
    };

    void move(int dxx, int dyy)
    {
        x = dxx;
        y = dyy;
    }
};

class Tline : public Point
{
protected:
    int dx, dy;

public:
    Tline() : Point()
    {
        dx = 300;
        dy = 0;
    }

    Tline(int x, int y, int dxx, int dyy, sf::Color col) : Point(x, y, col)
    {
        dx = dxx;
        dy = dyy;
        color = col;
    }

    ~Tline() 
    {
        // Нет необходимости в явном освобождении ресурсов, так как sf::VertexArray управляет своей памятью самостоятельно
    }

    virtual void draw(sf::RenderWindow& window)
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
        x = 0;
        y = 0;
        dx = 0;
        dy = 0;
    }

    // Меняет положение конца линии с dx, dy на dxx, dyy
    void move(int dxx, int dyy)
    {
        dx = dxx;
        dy = dyy;
    }

    void rotate(double fi)
    {
        double angle_rad = fi * 3.1415926535 / 180.0; // Переводим угол из градусов в радианы
        double length = sqrt(dx * dx + dy * dy);      // Находим расстояние от начала линии до конца
        double angle = atan2(dy, dx);                 // Находим угол между линией и горизонталью
        angle += angle_rad;                           // Добавляем угол поворота к текущему углу

        // Вычисляем новые координаты конца линии
        dx = (length * cos(angle));
        dy = (length * sin(angle));
    }
};

class Square : public Tline
{
public:
    Square() : Tline() {}

    Square(int xx, int yy, int dxx, int dyy, sf::Color col) : Tline(xx, yy, dxx, dyy, col) {}

    ~Square()
    {
        // Нет необходимости в явном освобождении ресурсов, так как sf::RectangleShape управляет своей памятью самостоятельно
    }

    virtual void draw(sf::RenderWindow& window)
    {
        sf::RectangleShape square(sf::Vector2f(abs(dx - dy), abs(dy - dx))); // Создаем квадрат с размерами dx и dy
        square.setPosition(x, y);                                            // Устанавливаем позицию квадрата
        square.setFillColor(color);
        window.draw(square);
    }
};

class Rhomb : virtual public Square
{
protected:
    int fi;

public:
    Rhomb() : Square() 
    {
        fi = 30;
    }

    Rhomb(int xx, int yy, int dxx, int dyy, int fik, sf::Color col) : Square(xx, yy, dxx, dyy, col)
    {
        fi = fik;
    }

    ~Rhomb()
    {
        // Нет необходимости в явном освобождении ресурсов, так как sf::ConvexShape управляет своей памятью самостоятельно
    }

    virtual void draw(sf::RenderWindow& window)
    {
        double length = sqrt(dx * dx + dy * dy);
        double PI = 3.14;

        int xi = int(asin(dy / length) * 180 / PI);

        int dxx = int((length * cos((xi + 180 - fi) * PI / 180)));
        int dyy = int((length * sin((xi + 180 - fi) * PI / 180)) + 1);

        sf::ConvexShape rhombus(4);
        rhombus.setPoint(0, sf::Vector2f(x, y));                       // первая вершина
        rhombus.setPoint(1, sf::Vector2f(x + dx, y + dy));             // вторая вершина
        rhombus.setPoint(2, sf::Vector2f(x + dx + dxx, y + dy + dyy)); // третья вершина
        rhombus.setPoint(3, sf::Vector2f(x + dxx, y + dyy));           // четвертая вершина

        rhombus.setFillColor(color);
        window.draw(rhombus);
    }
};

class Rectangle : virtual public Square
{
public:
    Rectangle() : Square() {}

    Rectangle(int xx, int yy, int dxx, int dyy, sf::Color col) : Square(xx, yy, dxx, dyy, col) {}

    ~Rectangle() {}

    virtual void draw(sf::RenderWindow& window)
    {
        sf::RectangleShape rect(sf::Vector2f(dx, dy)); // Создаем прямоугольник с размерами dx и dy
        rect.setPosition(x, y);                        // Устанавливаем позицию квадрата
        rect.setFillColor(color);                      // Устанавливаем цвет квадрата
        window.draw(rect);
    }
};

class Parallelogram : public Rhomb, public Rectangle
{
public:
    Parallelogram() : Square() 
    {
        fi = 0;
    }

    Parallelogram(int xx, int yy, int dxx, int dyy, int fik, sf::Color col) : Square(xx, yy, dxx, dyy, col)
    {
        fi = fik;
    }

    ~Parallelogram() {}

    virtual void draw(sf::RenderWindow& window)
    {
        sf::ConvexShape parallelogram(4);

        double angle_rad = fi * 3.1415926535 / 180.0; // Переводим угол из градусов в радианы

        parallelogram.setPoint(0, sf::Vector2f(x, y));
        parallelogram.setPoint(1, sf::Vector2f(x + dx, y));
        parallelogram.setPoint(2, sf::Vector2f(x + dx + dy * cos(angle_rad), y + dy * sin(angle_rad)));
        parallelogram.setPoint(3, sf::Vector2f(x + dy * cos(angle_rad), y + dy * sin(angle_rad)));

        parallelogram.setFillColor(color);
        window.draw(parallelogram);
    }
};

int main() 
{

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    // Создаём объекты
    Tline my_line(300, 100, 500, 0, sf::Color::Cyan);
    Square my_square(400, 500, 800, 900, sf::Color::Magenta);
    Rectangle my_rect(900, 900, 800, 100, sf::Color::Yellow);
    Rhomb my_rhombus(1300, 200, 300, 100, 30, sf::Color::Red);
    Parallelogram my_par(400, 400, 100, 250, 30, sf::Color::Green);

    // Проверка работы позднего связывания
    Tline* my_rhombus2;
    my_rhombus2 = new Rhomb();

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

        window.clear();          // Очищаем окно, чтобы предотвратить наложение графиков

        // Рисуем фигуры
        my_line.draw(window);
        my_square.draw(window);
        my_rect.draw(window);
        my_rhombus.draw(window);
        my_par.draw(window);

        // Рисуем через позднее связывание
        my_rhombus2->draw(window);

        window.display();        // Отображаем окно
    }

    return 0;
}