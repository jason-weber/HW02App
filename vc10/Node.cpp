#include "Node.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
		
Node::Node()
{
}

Node::Node(Vec2f v1, Vec2f v2, Color8u c){
	next_ = prev_ = this;
	this->v1 = v1;
	this->v2 = v2;
	color = c;
}

void Node::draw(){
	gl::color(color);
	gl::drawSolidRect(ci::Rectf(v1,v2));

}