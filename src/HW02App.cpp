#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
//For some reason I get an error if i try to just include Node.h
//So I had to give its full filepath to avoid this error
//change the following line to Node.h's filepath on your computer
#include "C:\Users\Jweb\Desktop\CSE274\HW02App\vc10\Node.h"
#include "cinder/Text.h"


using namespace ci;
using namespace ci::app;
using namespace std;

//@author Jason Weber
//This App satisfies requirements A,B,C,D,E, and I
class HW02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void keyDown(KeyEvent event);
	void reverse(Node* head);

	static const int kAppWidth = 800; // Window width
	static const int kAppHeight = 600; // Window height
	Node* head;//Not technically a head, but provides access to circular linked list
	Font* font; //Font for instructions
	bool removeText; //When true, removes the instructions
};

/*
* Prepares window size and prevents resizing
* @param settings The settings object to change
*/
void HW02App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

/*
* Method for detecting keyboard presses
* Provides controls to remove the instructions, bring nodes to front, and reverse the list
* @param event The keyboard event to detect
*/
void HW02App::keyDown(KeyEvent event)
{
	if(event.getChar() == '?')//If ? is pressed, set removeText to true
	{
		removeText = true;
	}
	if(event.getCode() == KeyEvent::KEY_LEFT)//If left arrow key is pressed, travel to previous node
	{
		head = head->prev_;
	}
	if(event.getCode() == KeyEvent::KEY_RIGHT)
	{
		//Because of the order my nodes are drawn in, this appears to improperly reorder 
		//nodes in the background. It is just because my nodes are drawn in reverse order so
		//the current head node always appears on top
		head = head->next_;
	}
	if(event.getChar() == 'r')//If 'r' key is pressed, reverse the list
	{
		reverse(head);
	}
}

/*
* Reverses the order of the list, selected Node will remain selected
* @param head The node that provides access to the list
*/
void HW02App::reverse(Node* head)
{
	head = head->prev_;
	Node* temp = head;
	do{
		Node* swap = temp->next_;
		temp->next_ = temp->prev_;
		temp->prev_ = swap;
		temp = temp->next_;

	}
	while(temp != head);
}

//Initial setup function
void HW02App::setup()
{
	//Adding various nodes
	head = new Node(Vec2f(0.0f,0.0f), Vec2f(50.0f,50.0f), Color8u(255,0,0));
	head->insertAfter(head, new Node(Vec2f(25.0f,25.0f), Vec2f(75.0f,75.0f), Color8u(0,255,0)));
	head->insertAfter(head->next_, new Node(Vec2f(50.0f,50.0f), Vec2f(100.0f,100.0f), Color8u(0,0,255)));
	head->insertAfter(head, new Node(Vec2f(10.0,10.0f), Vec2f(60.0f,60.0f), Color8u(0,255,255)));

	//Adding children to head node
	head->addChild(Vec2f(0.0f,5.0f),Vec2f(20.0f,25.0f),Color8u(255,255,0));
	head->addChild(Vec2f(10.0f,10.0f), Vec2f(30.0f,30.0f), Color8u(255,0,255));

	//Setup text
	font = new Font("Ariel",30); 
	removeText = false;
	
}

/*
* Detects mouse presses. moves node and children to mouses position
* @param event Mouse event to detect
*/
void HW02App::mouseDown( MouseEvent event )
{
	if(event.isLeftDown())
	{
		Vec2f headOrigin = head->v1; //Stores the heads initial top left vertex
		Node* childTemp = head->children_; //Node used for iterating through children nodes

		//Width and height to redraw node with the correct size
		float difX = head->v2.x - head->v1.x;
		float difY = head->v2.y - head->v1.y;

		//Move head node to mouse position
		head->v1 = event.getPos();
		head->v2.x = event.getX() + difX;
		head->v2.y = event.getY() + difY;
		
		
		if(childTemp != NULL){//Skip if no children
			//Store position of children within the parent Node
			float cX1 = 0.0f;
			float cY1 = 0.0f;
			float cX2 = 0.0f;
			float cY2 = 0.0f;
			do{
				cX1 = childTemp->v1.x - headOrigin.x;
				cY1 = childTemp->v1.y - headOrigin.y;
				cX2 = childTemp->v2.x - childTemp->v1.x;
				cY2 = childTemp->v2.y - childTemp->v1.y;

				//Move children nodes
				childTemp->v1.x = event.getX() + cX1;
				childTemp->v1.y = event.getY() + cY1;
				childTemp->v2.x = event.getX() + cX1 + cX2;
				childTemp->v2.y = event.getY() + cY1 + cY2;
				childTemp = childTemp->next_;
			}
			while(childTemp != head->children_);//Stops once childTemp == head->children_ again
		}
	}
}

//Not used
void HW02App::update()
{
}

void HW02App::draw()
{
	if(!removeText)//If ? hasn't been pressed, draw instructions
	{
		gl::drawString("Use the left arrow key to select objects and r to reverse order", Vec2f(50.0f,200.0f),Color(0.0f,0.5f,0.0f),*font);
		gl::drawString("Press ? to remove text, remove before starting", Vec2f(50.0f,250.0f),Color(0.0f,0.5f,0.0f),*font);
	}else
	{
		gl::clear(Color(1.0f,1.0f,1.0f));//Clear out text and makes screen white to better see occlusion
	}

	//Draw Nodes
	Node* temp = head->prev_;//Node for traveling through list
	do{
		temp->draw();
		temp = temp->prev_;
	}while(temp != head->prev_);//Stop if temp == head->prev_ again
}

CINDER_APP_BASIC( HW02App, RendererGl )
