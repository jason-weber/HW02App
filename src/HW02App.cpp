#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "C:\Users\Jweb\Desktop\CSE274\HW02App\vc10\Node.h"



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

	Node* head;
};

void HW02App::insertAfter(Node* posNode, Node* insNode){
	insNode->next_ = posNode->next_;
	posNode->next_ = insNode;
	insNode->prev_ = posNode;
	insNode->next_->prev_ = insNode;
}

void HW02App::setup()
{
	head = new Node(Vec2f(0.0,0.0), Vec2f(50.0,50.0));
	insertAfter(head, new Node(Vec2f(25.0,25.0), Vec2f(75.0,75.0)));
	
}

void HW02App::mouseDown( MouseEvent event )
{
}

void HW02App::update()
{
}

void HW02App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	Node* temp = head;
	do{
		temp->draw();
		temp = temp->next_;
	}while(temp != head);
}

CINDER_APP_BASIC( HW02App, RendererGl )
