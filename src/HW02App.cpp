#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"
/* I had to include the whole filepath to include Node.h
on my computer. I'm not really sure why.
-bakersc3
*/
//#include "C:/Users/BassPanda/My Documents/CSE 274/HW02_jweber/vc10/Node.h"
#include "cinder/Text.h"


using namespace ci;
using namespace ci::app;
using namespace std;

//@author Jason Weber
//This App satisfies requirements A,B,C,D,E, and I

/* Good job on most counts. The only thing that I'm not sure if I see
is requirement C. I read that requirement as creating a 
window-like setup, where you can click to bring whatever object to 
the top that you want, and reorder them by clicking on the objects in 
different orders. This code rotates the list, which is similar to 
reordering, but isn't quite the same thing.
-bakersc3
*/

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

/* The instructions say that pressing '?' should turn
the instructions on and off, so I went ahead and made
it so you can toggle the text.
-bakersc3
*/
void HW02App::keyDown(KeyEvent event)
{
	if(event.getChar() == '?')//If ? is pressed, set removeText to true
	{
		if(removeText == true)
			removeText = false;
		else if(removeText == false)
			removeText = true;
	}
	if(event.getCode() == KeyEvent::KEY_LEFT)//If left arrow key is pressed, travel to previous node
	{
		head = head->prev_;
	}
	if(event.getCode() == KeyEvent::KEY_RIGHT)
	{
		head = head->next_;
	}
		//Because of the order my nodes are drawn in, this appears to improperly reorder 
		//nodes in the background. It is just because my nodes are drawn in reverse order so
		//the current head node always appears on top
	if(event.getChar() == 'r')//If 'r' key is pressed, reverse the list
	{
		reverse(head);
	}
}

/*
* Reverses the order of the list, selected Node will remain selected
* @param head The node that provides access to the list
*/

/* Your reverse works well enough, but it has one more line
of code than the version we came up with in class. The first
line isn't actually necessary, as far as I can tell.
-bakersc3
*/
void HW02App::reverse(Node* head)
{
	//head = head->prev_;
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

	/* It's "Arial," not "Ariel."
	-bakersc3
	*/
	font = new Font("Arial",30); 
	removeText = false;

}

/*
* Detects mouse presses. moves node and children to mouses position
* @param event Mouse event to detect
*/
void HW02::mouseDown( MouseEvent event )
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

/* I added directions for clicking to move the selected object,
as well as making the screen clear not depend on removeText
being f.
-bakersc3
*/
void HW02App::draw()
{
	/*Moving this clear to the top makes it so the objects
	can be moved properly without removing the text. Before,
	it was showing a copy of the head node wherever I clicked
	when the instructions were up.
	-bakersc3
	*/
	gl::clear(Color(1.0f,1.0f,1.0f));

	/* This wasn't really necessary, but I moved the
	node drawing section above the instruction section
	so the nodes will render underneath the text when
	you click when the instructions are still up.
	-bakersc3
	*/
	//Draw Nodes
	Node* temp = head->prev_;//Node for traveling through list
	do{
		temp->draw();
		temp = temp->prev_;
	}while(temp != head->prev_);//Stop if temp == head->prev_ again

	/* I took out the instruction "remove text before
	starting," because with the changes I made, it is
	no longer necessary to remove the text.
	-bakersc3
	*/
	if(!removeText)//If ? hasn't been pressed, draw instructions
	{
		gl::drawString("Use the left arrow key to select objects and r to reverse order", Vec2f(50.0f,200.0f),Color(0.0f,0.5f,0.0f),*font);
		gl::drawString("Click anywhere to move the selected object", Vec2f(50.0f, 150.0f), Color(0.0f,0.5f,0.0f),*font);
		gl::drawString("Press ? to remove text", Vec2f(50.0f,250.0f),Color(0.0f,0.5f,0.0f),*font);
	}
}

CINDER_APP_BASIC( HW02App, RendererGl )