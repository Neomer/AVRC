


#include "dev/m8/ControllerM8.h"
#include "dev/m8/MemoryM8.h"
#include "sensors/ButtonPullUp.h"

int main()
{
	ControllerM8 c;
	ButtonPullUp b(avr_bit_s(iPORTB, 0), &c);
}
