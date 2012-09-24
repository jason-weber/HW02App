#include "cinder/Rect.h"
#include "cinder/Color.h"

class Node{

	public:
		Node* next_; //next node in linked list
		Node* prev_; //previous node in linked list
		Node* children_;//children head node of children linked list

		ci::Vec2f v1; //Top left vertex of rectangle
		ci::Vec2f v2; //Bottom right vertex of rectangle

		ci::Color8u color; //Color of rectangle drawn
		
		//Constructors
		Node();
		Node(Node* node);
		Node(ci::Vec2f v1, ci::Vec2f v2, ci::Color8u c);

		void insertAfter(Node* posNode, Node* insNode); //insert node after given node
		void addChild(ci::Vec2f v1, ci::Vec2f v2, ci::Color8u c);//adds child to node
		void draw();

		


};