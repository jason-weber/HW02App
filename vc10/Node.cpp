#include "Node.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
		
Node::Node()
{
}

Node::Node(Vec2f v1, Vec2f v2){
	next_ = prev_ = this;
	this->v1 = v1;
	this->v2 = v2;
}

void Node::draw(){
	gl::drawSolidRect(ci::Rectf(v1,v2));

}