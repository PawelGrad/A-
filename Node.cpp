#include "Node.h"
#include <iostream>

Node::Node(int x, int y) {
	rectNode.setSize(sf::Vector2f(30, 30));
	rectNode.setFillColor(sf::Color(98,133,208));
	rectNode.setPosition(sf::Vector2f(20 + (x*35),20+(y*35)));
	rectNode.setOrigin(rectNode.getLocalBounds().height / 2, rectNode.getLocalBounds().width / 2);
	posY = 20 + (y * 35);
	posX = 20 + (x * 35);
}

Node::~Node() {

}

bool Node::contains(sf::Vector2f point)
{
	if (rectNode.getGlobalBounds().contains(point))
	{
		return 1;
	}
	else
		return 0;
	
}

void Node::setColor(sf::Color color) {
	rectNode.setFillColor(color);
	wall = 0;
}

void Node::setObstacle() {
	rectNode.setFillColor(sf::Color(169, 169, 169));
	wall = 1;
	
}
sf::Color Node::getColor()
{
	return rectNode.getFillColor();
}

void Node::checkSasiedzi(Node* node) {
	sasiedzi.push_back(node);

}

sf::Vector2f Node::getPosition() {
	return sf::Vector2f(posX, posY);
}

void Node::setGlobal(float a){
	global = a;
}
void Node::setLocal(float a) {
	local = a;
}
float Node::getGlobal() {
	return global;
}
float Node::getLocal() {
	return local;
}
void Node::setVisited(bool a) {
	visited = a;
}
bool Node::getVisited() {
	return visited;
}
void Node::drawConnections(sf::RenderWindow& window) {
	
	for (std::vector<Node*>::iterator it = sasiedzi.begin(); it < sasiedzi.end(); it++)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(posX,posY)),
		    sf::Vertex((*it)->getPosition())
		};
		window.draw(line, 2, sf::Lines);
	}
	
	
}

void Node::drawNodes(sf::RenderWindow& window) {

	window.draw(rectNode);

}

std::vector<Node*> Node::getSasiedzi() {
	return sasiedzi;
}

bool Node::getObstacle() {
	return wall;
}

void Node::setParent(Node* a) {
	parent = a;
	}
Node* Node::getParent() {
	return parent;
}