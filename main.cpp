#include <SFML/Graphics.hpp>
#include <ctime>
#include "Voronoi.h"
#include "BinaryTree.h"

float solvefory(double x, double directrixy, point focus)
{
	return (1 / (2 * (focus.y - directrixy))) * ((x - focus.x) * (x - focus.x)) + (0.5 * (focus.y + directrixy));
}

point intersect(point compara, point num2, double directrix)
{
	point point1 = compara;
	point point2 = num2;
	point intersectionpt(0, 0);

	if (point1.y == point2.y) {
		intersectionpt.x = (point1.x + point2.x) / 2;
	}
	else if (point1.y == 1) {
		intersectionpt.x = point1.x;
	}
	else if (point2.y == 1) {
		intersectionpt.x = point2.x;
	}
	else {
		double z0 = 2 * (point1.y - directrix);
		double z1 = 2 * (point2.y - directrix);

		double a = 1 / z0 - 1 / z1;
		double b = -2 * (point1.x / z0 - point2.x / z1);
		double c = ((point1.x*point1.x) + (point1.y * point1.y) - (directrix * directrix))/z0 - ((((point2.x*point2.x) + (point2.y * point2.y) - (directrix * directrix)) / z1));
		//double a = ((1 / (2 * (point1.y - directrix))) - (1 / (2 * (point2.y - directrix))));
		//double b = ((1 / (2 * (point1.y - directrix)) * (point1.x * -2) - ((1 / (2 * (point2.y - directrix)) * (point2.x * -2)))));
		//double c = ((point1.x * point1.x * ((1 / (2 * (point1.y - directrix)))) + (0.5 * (point1.y + directrix))) - (point2.x * point2.x* ((1 / (2 * (point2.y - directrix)))) + (0.5 * (point2.y + directrix))));

		if ((((-b - sqrt(b*b - 4 * a*c))) / (2 * a) < 1920) && (((-b - sqrt(b*b - 4 * a*c))) / (2 * a) > 0)) {
			intersectionpt.x = ((-b + sqrt(b*b - 4 * a*c))) / (2 * a);
		}
		else
			return point(-1, -1);
	}
	intersectionpt.y = solvefory(intersectionpt.x, directrix, point1);
	std::cout << intersectionpt.x << "," << intersectionpt.y << std::endl;
	return intersectionpt;
}

int main() {
	srand(time(NULL));
	std::vector<sf::VertexArray> para;
	std::vector<point> points;
	std::vector<point> breakpointsleft;
	std::vector<point> breakpointsright;

	for (int i = 0; i < 3; i++) {
		points.push_back(point(rand() % (1000 - 0 + 1), rand() % (1000 - 0 + 1)));
	}
	std::sort(points.begin(), points.end());
	breakpointsleft.push_back(point(0, 0));
	breakpointsright.push_back(point(0, 0));
	for (int z = 1; z < points.size()-1; z++) {
		breakpointsleft.push_back(intersect(points[z], points[z - 1], 1000));
		breakpointsright.push_back(intersect(points[z], points[z + 1], 1000));
	}
	breakpointsleft.push_back(intersect(points[points.size()-1], points[points.size()-2], 1000));
	breakpointsright[0] = intersect(points[0], points[1], 1000);
	breakpointsright.push_back((intersect(points[points.size() - 1], points[points.size() - 2], 1000)));
	for (int i = 0; i < points.size(); i++) {
		para.push_back(sf::VertexArray());
		for (int x = 0; x < 1920; x++) {
			if (breakpointsright[i].x == -1 || breakpointsleft[i].x == -1) {
				para[i].append(sf::Vertex(sf::Vector2f(x, solvefory(x, 1000, points[i]))));
			}
			else if (x < breakpointsright[i].x && x > breakpointsleft[i].x) {
				para[i].append(sf::Vertex(sf::Vector2f(x, solvefory(x, 1000, points[i]))));
			} 
		}
		
	}
	srand(time(NULL));
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
			for (int i = 0; i < para.size(); i++) {
				window.draw(para[i]);
			}
			window.display();
		}

		return 0;
	}
