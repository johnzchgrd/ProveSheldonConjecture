#include <local/sheldon.h>
/**
 * @brief Get the Datenow 
 * 
 * @return long date fromat like 20190101
 */
long getDateNow(void)
{
	time_t now;
	long date;
	struct tm *datenow; //define struct to store time information
	time(&now);
	datenow = localtime(&now);
	date = (datenow->tm_year + 1900) * 10000 +
		   (datenow->tm_mon + 1) * 100 +
		   datenow->tm_mday;
	return date;
}
/**
 * @brief Get the TimeNow
 * 
 * @return long time format like 123456(12'34"56)
 */
long getTimeNow_long(void)
{
	time_t now;
	long Time;
	struct tm *timenow; //define struct to store time information
	time(&now);
	timenow = localtime(&now);
	Time = timenow->tm_hour * 10000 + timenow->tm_min * 100 + timenow->tm_sec;
	return Time;
}
/**
 * @brief dump the full time(date+time) into
 * passed in buffer.
 * 
 * @param Time 
 * @return char* 
 */
void getTimeNow_str(char Time[])
{
	time_t now;
	struct tm *timenow; //define struct to store time information
	time(&now);
	timenow = localtime(&now);
	//yyyy-mm-dd hh-mm-ss\0 = DATE_LENGTH
	sprintf(Time, "%04d-%02d-%02d %02d:%02d:%02d",
			timenow->tm_year + 1900,
			timenow->tm_mon + 1,
			timenow->tm_mday,
			timenow->tm_hour,
			timenow->tm_min,
			timenow->tm_sec);
}
#ifdef __linux__
/**
 * @brief Get the Run Time of the function
 * parameter's usage is similar to pthread_create()
 * -- use an interface. Instead of write all the 
 * basic data type needed, you may add them in a structure.
 * 
 * @param func 
 * @param arg 
 * @return long 
 */
long getRunTime(void (*func)(void *), void *arg)
{
	struct timespec a = {0, 0}, b = {0, 0};
	clock_gettime(CLOCK_REALTIME, &a);
	func(arg);
	clock_gettime(CLOCK_REALTIME, &b);
	long delta = (b.tv_sec - a.tv_sec) * 1000 + (b.tv_nsec - a.tv_nsec) / 1000000;
	return delta;
}
#endif // __linux__
