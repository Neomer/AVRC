#ifndef OBJECT_H
#define OBJECT_H

class IObject
{
	friend class IController;
	
protected:
	virtual void update() = 0;
};

#endif // OBJECT_H
