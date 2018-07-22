#include <SFML\Graphics.hpp>
#include <iostream>
#include "Node.h"
#include <vector>
#include <memory>
#include <list>
using namespace sf;

void AStar(std::vector<Node*> Nodes, Node* Start, Node* End) {
	for (std::vector<Node*>::iterator it = Nodes.begin(); it<Nodes.end(); it++)
	{
		(*it)->setParent(nullptr);
		(*it)->setGlobal(INFINITY);
		(*it)->setLocal(INFINITY);
		(*it)->setVisited(0);
	}
	auto distance = [](Node* a, Node* b) {return sqrtf(
		((a->getPosition().x - b->getPosition().x)*
		(a->getPosition().x - b->getPosition().x))
		+
		((a->getPosition().y - b->getPosition().y)*
		(a->getPosition().y - b->getPosition().y))
	); };

	auto heuristic = [distance](Node* a, Node* b) {return distance(a, b); };

	Node* currentNode = nullptr;
	Start->setLocal(0.0f);
	Start->setGlobal(heuristic(Start, End));

	std::list<Node*> notVisited;
	notVisited.push_back(Start);
	int iter = 0;
	while (!notVisited.empty() && currentNode != End)
	{
		
		notVisited.sort([](Node* lhs, Node* rhs) {return lhs->getGlobal() < rhs->getGlobal(); }); ////////////////?????
	
		while (!notVisited.empty() && notVisited.front()->getVisited()) notVisited.pop_front();
		
		if (notVisited.empty()) break;

		currentNode = notVisited.front();
		currentNode->setVisited(1);
		
		std::vector<Node*> temp = currentNode->getSasiedzi();
		for (std::vector<Node*>::iterator it = temp.begin(); it < temp.end(); it++)
		{
			
			if (!(*it)->getVisited() && (*it)->getObstacle()==0)
				notVisited.push_back(*it);

			float lowerGoal = currentNode->getLocal() + distance(currentNode, *it);
			
			if (lowerGoal < (*it)->getLocal())
			{
				(*it)->setParent(currentNode);
				(*it)->setLocal(lowerGoal);
		
				(*it)->setGlobal((*it)->getLocal() + heuristic((*it), End));
			}
		
		}
	}
	notVisited.clear();
}


int main()
{
	
	unsigned int gridSize = 16;
	std::vector<Node*> Nodes;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			Node* node = new Node(i, j);
			Nodes.push_back(node);

		}
	}

	RenderWindow window{ VideoMode{ gridSize * 35 + 5,gridSize * 35 + 5 }, "A*" };
	window.setFramerateLimit(60);

	Event event;

	
		sf::Vector2f point;
		for (std::vector<Node*>::iterator it = Nodes.begin(); it < Nodes.end(); it++)
		{
			
			point = (*it)->getPosition() + sf::Vector2f(35, 0);
			for (std::vector<Node*>::iterator it2 = Nodes.begin(); it2 < Nodes.end(); it2++)
			{
				
				if ((*it2)->contains(point)) (*it)->checkSasiedzi(*it2);
			
			}
			
			point = (*it)->getPosition() + sf::Vector2f(-35, 0);
			for (std::vector<Node*>::iterator it2 = Nodes.begin(); it2 < Nodes.end(); it2++)
			{
			
				if ((*it2)->contains(point)) (*it)->checkSasiedzi(*it2);
			
			}
			
			point = (*it)->getPosition() + sf::Vector2f(0, 35);
			for (std::vector<Node*>::iterator it2 = Nodes.begin(); it2 < Nodes.end(); it2++)
			{
			
				if ((*it2)->contains(point)) (*it)->checkSasiedzi(*it2);
				
			}
			
			point = (*it)->getPosition() + sf::Vector2f(0, -35);
			for (std::vector<Node*>::iterator it2 = Nodes.begin(); it2 < Nodes.end(); it2++)
			{
				
				if ((*it2)->contains(point)) (*it)->checkSasiedzi(*it2);
			
			}





		
	}


	Vector2f mouseCoords;
	bool LmouseClicked=0;
	bool RmouseClicked = 0;
	bool F1Clicked = 0;
	Node* sNode = nullptr;
	Node* eNode = nullptr;

	while (1)
	{
		mouseCoords = window.mapPixelToCoords(Mouse::getPosition(window));
		window.pollEvent(event);

		if (event.type == Event::Closed)
		{
			window.close();
			break;
		}

		if (LmouseClicked = event.mouseButton.button == sf::Mouse::Left)
		{
			
			
			for (std::vector<Node*>::iterator it = Nodes.begin(); it < Nodes.end(); it++)
			{
				if ((*it)->getColor() == sf::Color::Yellow) {
					(*it)->setColor(sf::Color(98, 133, 208));
					sNode = nullptr;
				}
				if ((*it)->contains(mouseCoords))
				{
					(*it)->setColor(sf::Color::Yellow);
					sNode = *it;
				}
			}
			LmouseClicked = 0;
		}
			
		if (RmouseClicked = event.mouseButton.button == sf::Mouse::Right)
		{
			
			
			for (std::vector<Node*>::iterator it = Nodes.begin(); it < Nodes.end(); it++)
			{

				if ((*it)->getColor() == sf::Color::Green) {
					(*it)->setColor(sf::Color(98, 133, 208));
					eNode = nullptr;
				}
				if ((*it)->contains(mouseCoords))
				{
					(*it)->setColor(sf::Color::Green);
					eNode = *it;
				}
			}
			RmouseClicked = 0;

		}

		if (F1Clicked = event.key.code == sf::Keyboard::F1)
		{
	
			for (std::vector<Node*>::iterator it = Nodes.begin(); it < Nodes.end(); it++)
			{

				
				if ((*it)->contains(mouseCoords))
					
					{
						(*it)->setObstacle();
						
					}
				
			}
			F1Clicked = 0;
		}


		
	
			
			if (sNode != nullptr && eNode != nullptr)
			{
				AStar(Nodes, sNode, eNode);			
			}
		

			window.clear();
			for (auto it : Nodes)
			{
				it->drawConnections(window);
				
			}
			for (auto it : Nodes)
			{
				it->drawNodes(window);

			}
			
			if (sNode != nullptr && eNode != nullptr)
			{
				
				Node*p = eNode;
				while (p->getParent() != nullptr)
				{
				
					sf::Vertex line[] =
					{
						sf::Vertex(p->getPosition(),sf::Color::Yellow),
						sf::Vertex(p->getParent()->getPosition(),sf::Color::Yellow)
					};
					window.draw(line, 2, sf::Lines);

					
					p = p->getParent();
				}
			}
			window.display();
		}

		return 0;
}
