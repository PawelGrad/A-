#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Node {
public:
	Node(int,int);
	~Node();
	void drawNodes(sf::RenderWindow&);
	void drawConnections(sf::RenderWindow& );
	bool contains(sf::Vector2f);
	void setColor(sf::Color);
	sf::Color getColor();
	void checkSasiedzi(Node*);
	sf::Vector2f getPosition();
	float getLocal();
	float getGlobal();
	void setLocal(float);
	void setVisited(bool);
	bool getVisited();
	void setGlobal(float);
	bool getObstacle();
	std::vector<Node*> getSasiedzi();
	void setParent(Node*);
	Node* getParent();
	void setObstacle();
private:
	sf::RectangleShape rectNode;
	bool visited = 0;
	bool wall = 0;
	float global = INFINITY;
	float local = INFINITY;
	int posX;
	int posY;
	std::vector<Node*> sasiedzi;
	Node* parent = nullptr;
};


