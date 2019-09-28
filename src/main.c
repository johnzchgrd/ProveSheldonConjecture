/*
 *author: Johnzchgrd
 *create date: 2019/05/11 16:16
 *descriptions: test for Proof of Sheldon Conjecture, only n=7,21,181440 fit?
 *
 *Theory Base: Researchers have proved that it must in range [2,1e64] using,
 * I guess, some Super Computers. And I want to try to prove on my
 * own machine too. (Jusrt for fun & learning!)
 * 
 *CPU: Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz 1.99GHz
 *
 *（Single-threaded）Manually using 3 threads, CPU occupation stays around 52%
 *(Multi-threaded)Now:
 *verified domain:   runtime(not including generating Pn table)
 *2~1e8(7,21,181440)         76556ms
 *2~1e9(above three)         11615903ms
 *2~1610099952(above three)  17844241ms
 *
 * Update:
 * 2019-08-16 Johnzchgrd:
 *     working on Multi-Thread. First find primes that has
 *     product property.
 * 2019-08-17 Johnzchgrd
 *     change to `Makefile` mode to have a better developing structure.
 * 2019-08-22 Johnzchgrd
 *     verified new domain.
 * 2019-09-07 Jonzchgrd
 *    deprecate function `getLastNum()` in replace of getNum()
 *    verified new domain.
 * 2019-09-28 Johnzchgrd
 *    add return value check for system() and fread() using Macros.
 * 
 */

/*TODO
 * 1.Add pthread_cancel
 * 3.add filename:line to functions' debug info(when DEBUG is defined).
 * 
 */

#include <local/sheldon.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Missing argument.\nOptions:\n");
		printf("\t0 - Create New Pn table(May cause replacing pervious one)\n");
		printf("\t1 - finish temporary Pn table\n");
		printf("\t2 - Find Integers that has Product Property\n");
		printf("\t3 - Check whether %s is legal seriously(add prime check)\n", PNFILE);
		exit(MISSING_ARGUMENT);
	}
#ifdef SHOW_PROGRESS
	// hide caret
	printf("\033[?25l");
#endif //SHOE_PROGRESS
#ifndef _TIME_C_
	char time_now[DATE_LENGTH];
	getTimeNow_str(time_now);
	printf("Start time is: %s.\n", time_now);
#endif // _TIME_C_
	switch (argv[1][0])
	{
	case '0':
		initPnTab(GEN_START, GEN_DELTA);
		break;
	case '1':
		finiPnTab(GEN_START, GEN_DELTA);
		break;
	case '2':
		printf("Total Time: %ldms.\n", getRunTime(MultiThread, NULL));
		//once this is an unreachable sentence...
		printf("Search finished.\n");
		break;
	case '3':
		printf("Legal Pn table file Check: %d.\n", checkLegal(PNFILE, argv[1][1]));
		break;
	default:
		printf("Invalid argument!\n");
		break;
	}
#ifndef _TIME_C_
	getTimeNow_str(time_now);
	printf("Terminate time is: %s.\n", time_now);
#endif // _TIME_C_
#ifdef SHOW_PROGRESS
	// show caret
	printf("\033[?25h");
#endif // SHOW_PROGRESS
	//MYSYSTEM("shutdown /s");
	return 0;
}