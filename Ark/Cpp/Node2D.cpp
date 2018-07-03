#include "Node2D.h"

Node2D::Node2D():xn(0),yn(0),msq(new MacroQuantity()),use(new int(1)) 
{
//
// 	msq = new MacroQuantity();
// //
// 	use = new int(1);
}
void Node2D::assign(Node2D const &rhs)
{
	h = rhs.h;
	f = rhs.f;
	msq = rhs.msq;
}
Node2D::Node2D(Node2D const &rhs)
{
	assign(rhs);
//	
	use = rhs.use;
	++*use;
}
Node2D& Node2D::operator=(Node2D const &rhs)
{
	if(use != rhs.use)
	{
		if(--*use == 0)
		{
			delete msq;
	//	
			delete use;
		}
		assign(rhs);
//	
		use = rhs.use;
		++*use;
	}
	return *this;
}
Node2D::~Node2D()
{
	if(0 == --*use)
	{
		delete msq;
//
		delete use;
	}
}