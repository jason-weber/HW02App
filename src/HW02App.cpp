#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "C:\Users\Jweb\Desktop\CSE274\HW02App\vc10\Node.h"
#include "cinder/Text.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class HW02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void insertAfter(Node* posNode, Node* insNode);
	void keyDown(KeyEvent event);
	void reverse(Node* head);

	Node* head;
	Font* font;
	bool removeText;
};


void HW02App::insertAfter(Node* posNode, Node* insNode)
{
	insNode->next_ = posNode->next_;
	posNode->next_ = insNode;
	insNode->next_->prev_ = insNode;
	insNode->prev_ = posNode;
}

void HW02App::keyDown(KeyEvent event)
{
	if(event.getChar() == '?')
	{
		removeText = true;
	}
	if(event.getCode() == KeyEvent::KEY_RIGHT)
	{
		head = head->next_;		
	}
	if(event.getCode() == KeyEvent::KEY_LEFT)
	{
		head = head->prev_;
	}
}

void HW02App::setup()
{
	head = new Node(Vec2f(0.0,0.0), Vec2f(50.0,50.0), Color8u(255,0,0));
	insertAfter(head, new Node(Vec2f(25.0,25.0), Vec2f(75.0,75.0), Color8u(0,255,0)));
	insertAfter(head->next_, new Node(Vec2f(50.0,50.0), Vec2f(100.0,100.0), Color8u(0,0,255)));
	insertAfter(head, new Node(Vec2f(10.0,10.0), Vec2f(60.0,60.0), Color8u(0,255,255)));

	font = new Font("Ariel",30);
	removeText = false;
	
}

void HW02App::mouseDown( MouseEvent event )
{
	while(event.isLeftDown())
	{
		float difX = head->v2.x - head->v1.x;
		float difY = head->v2.y - head->v1.y;

		head->v1 = event.getPos();
		head->v2.x = event.getX() + difX;
		head->v2.y = event.getY() + difY;
	}
}

void HW02App::update()
{
}

void HW02App::draw()
{
	if(!removeText)
	{
		gl::drawString("Use the left and right arrow keys to select objects", Vec2f(50.0,200.0),Color(1.0f,1.0f,1.0f),*font);
		gl::drawString("Press ? to remove text", Vec2f(50.0,250.0),Color(1.0f,1.0f,1.0f),*font);
	}else
	{
		//gl::drawString("Use the left and right arrow keys to reorder objects", Vec2f(50.0,200.0),Color(0.0f,0.0f,0.0f),*font);
		//gl::drawString("Press ? to remove text", Vec2f(50.0,250.0),Color(0.0f,0.0f,0.0f),*font);
		gl::clear(Color(0.0f,0.0f,0.0f));
	}
	Node* temp = head->prev_;
	do{
		temp->draw();
		temp = temp->prev_;
	}while(temp != head->prev_);
}

CINDER_APP_BASIC( HW02App, RendererGl )
