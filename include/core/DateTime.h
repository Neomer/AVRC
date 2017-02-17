#ifndef DATETIME
#define DATETIME

#include <inttypes.h>


typedef 
///
/// \brief The Anonymous:1 struct DateTime
///
struct
{
	uint8_t mseconds;
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t month;
	uint8_t year;
	uint8_t dayOfWeek;
} 
DateTime;

bool operator == (const DateTime &v1, const DateTime &v2) 
{ 
	return (v1.day == v2.day) &&
			(v1.month == v2.month) &&
			(v1.year == v2.year) &&
			(v1.hours == v2.hours) && 
			(v1.minutes == v2.minutes) && 
			(v1.seconds == v2.seconds) && 
			(v1.mseconds == v2.mseconds); 
}

///
/// \brief dt_diff_msecs Вычисляет разницу в миллисекундах между двумя датами. Используется только время. 
/// Дает сбой при смене дня. Считается, что v1 > v2, иначе результат некорректный!
/// \param v1 
/// \param v2
/// \return Разница в мсек
///
inline uint32_t dt_diff_msecs(const DateTime &v1, const DateTime &v2)
{
	uint32_t ret = (v1.mseconds - v2.mseconds) + 
			(v1.seconds - v2.seconds) * 1000 + 
			(v1.minutes - v2.minutes) * 60000 +
			(v1.hours - v2.hours) * 3600000;
	
	if (v1.day > v2.day)
		return (0xFFFF - ret);
	else
		return ret;
}

#endif // DATETIME

