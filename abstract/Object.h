#ifndef OBJECT_H
#define OBJECT_H

class IObject
{
	friend class IController;

#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
public:
#else
protected:
#endif
	virtual void update() = 0;
};

#endif // OBJECT_H
