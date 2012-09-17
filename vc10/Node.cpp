#include "Node.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"



using namespace ci;

/*
* Default Node constructor
*/
Node::Node()
{
}

/*
* Constructs Node with given points and color
* @param v1 Top left vertex of rectangle
* @param v2 Bottom right vertex of rectangle
* @param c Color the rectangle should be drawn
*/
Node::Node(Vec2f v1, Vec2f v2, Color8u c){
	next_ = prev_ = this; //Sets up first node to create circular linked list
	this->v1 = v1;
	this->v2 = v2;
	color = c;
	children_ = NULL; //Node start with no children
}

/*
* Inserts a node after the given node
* @param posNode Where the node should be placed after
* @param insNode Node to insert
*/
void Node::insertAfter(Node* posNode, Node* insNode)
{
	//assigns variables in next_ direction
	insNode->next_ = posNode->next_;
	posNode->next_ = insNode;

	//assigns variables in prev_ direction
	insNode->next_->prev_ = insNode;
	insNode->prev_ = posNode;
}

/*
* Adds a child to a node
* @param v1 Top left vertex of child rectangle
* @param v2 Bottom right vertex of child rectangle
* @param c Color to draw child
*/
void Node::addChild(Vec2f v1, Vec2f v2, Color8u c)
{
	if(children_ == NULL)
	{
		children_ = new Node(v1,v2,c);
	}
	else{
		insertAfter(children_, new Node(v1,v2,c));
	}
}

//Draws Node and all children
void Node::draw(){
	//Parent node drawing
	gl::color(Color8u(0,0,0));
	gl::drawSolidRect(ci::Rectf(v1,(v2 + Vec2f(5,5))));
	gl::color(color);
	gl::drawSolidRect(ci::Rectf(v1,v2));

	//Node children drawing
	Node* childTemp = children_;
	if(childTemp != NULL)
	{
		do{
			gl::color(Color8u(0,0,0));
			gl::drawSolidRect(ci::Rectf(childTemp->v1,(childTemp->v2 + Vec2f(5,5))));
			gl::color(childTemp->color);
			gl::drawSolidRect(ci::Rectf(childTemp->v1,childTemp->v2));
			childTemp = childTemp->next_; //Go to next node
		}
		while(childTemp != children_);
	}
}