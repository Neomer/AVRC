
#include "dev/m8/ControllerM8.h"
#include "dev/m8/MemoryM8.h"

int main()
{
	ControllerM8 c;
	
	c.setPinDirection(iDDRB, 1, IController::Write);
	
	return 0;
}
