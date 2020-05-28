#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <assert.h>
#include <math.h>

typedef unsigned long long RANGE; // if modified, IO format
                                  //for printf&scanf should too.
#define SHOW_PROGRESS
//main threads func settings.
#define START 2 /*!currently don't support other begin point \
                 because of we're using Pn table to locate.*/
#define DELTA (RANGE)100
#define THREADS 10
//pn tab gen threads settings.
#define _NO_DEFAULT_ /*NOTE define this to generate Pn table \
                     starts from any number legally allowed.*/
#ifdef _NO_DEFAULT_
#define GEN_START (RANGE)2
#define GEN_DELTA (RANGE)100
#define GEN_THREADS 20
#else //_NO_DEFAULT_
#define GEN_START START
#define GEN_DELTA DELTA
#define GEN_THREADS THREADS
#endif //_NO_DEFAULT_
// flags
#define STDTERMI -1ULL      //represents a legal eof of Pn tab generation, or "18446744073709551615"
#define SHOW_MODE 1         //?seem to be useless
#define USE_FAST_PRODUCTION //?i don't know why i created it??
#undef _ALL_LEGAL_          // in case tmp files are not believed to be legal
// file names and ENDs
#define OUTFILE "0.out"
#define TMPFILEFMT "tmp/tempfile%d.tmp" //! dir must exist
#define END (RANGE)(DELTA * THREADS + START)
// Pn Table Generation default thread setting.
#define PNFILE "Pn.tab"
#define GEN_END (RANGE)(GEN_DELTA * GEN_THREADS + GEN_START)
//
#define MYSYSTEM(cmd)                                                                   \
    switch (system(#cmd))                                                               \
    {                                                                                   \
    case 1:                                                                             \
        break;                                                                          \
    case 0:                                                                             \
        if (#cmd == NULL)                                                               \
            fprintf(stderr, "No shell avaliable!\n");                                   \
        break;                                                                          \
    case -1:                                                                            \
        fprintf(stderr, "Can't create child process or its status can'be retrived!\n"); \
        break;                                                                          \
    case 127:                                                                           \
        fprintf(stderr, "Command " #cmd " execution failed!\n");                        \
        break;                                                                          \
    default:                                                                            \
        break;                                                                          \
    }

#define MYFREAD1(cmd1, cmd2, cmd3, cmd4)                                    \
    if (fread(cmd1, cmd2, cmd3, cmd4) != (cmd3))                            \
    {                                                                       \
        fprintf(stderr, ">>>error@%s:%d:FILE_READ!\n", __FILE__, __LINE__); \
        exit(FILE_READ);                                                    \
    }
#define MYFREAD(cmd1, cmd2, cmd3, cmd4) (fread(cmd1, cmd2, cmd3, cmd4) == (cmd3))
// exit code enumerator
enum ErrorTable
{
    ALL_OK,           // everything ok
    MISSING_ARGUMENT, //
    FILE_READ,        //
    FILE_WRITE,       //
    FILE_ADD,         //
    FILE_EXIST,       //
    INVALID_DIR,      //
    THREAD_CREATE,    // thread_create returns zero
    THREAD_JOIN,      // unused
    PNTAB_ILLEGAL,    // used in checkLegal function
    INTERNAL_ERROR    // internal functional problem, suggested to use when add a new function
};

// arguments to transfer
typedef struct
{
    RANGE current_cnt;
    int fini_threads_cnt;
    long TimeSpent; // currently unused, better as a time_t struct
} ProgManager;      //better managing progress display

typedef struct
{
    RANGE start, end, initialPn;
    int cnt; // patrial sum, seem to be useless.
    int id;  // something like UUID
    ProgManager *pm;
} Sheldon;

typedef struct
{
    RANGE start, end;
    FILE *fp;
    RANGE newdelta;
    int id; // something like UUID
    ProgManager *pm;
} PnTab; // arg transfered to single-processes
         //of creating the Pn table.

typedef struct
{
    RANGE newstart;
    int patchornot;
} CompletePnTab;

#ifndef GEN_ONLY
// functions in .so
#ifndef _TIME_C_
#define DATE_LENGTH 20
long getDateNow(void);
long getTimeNow_long(void);
void getTimeNow_str(char Time[]);
long getRunTime(void (*func)(void *), void *arg);
#endif // _TIME_C_

#ifndef _SHELDON_C_
RANGE fastproduction(RANGE product, char bit);
int ProductProperty(RANGE primenumber, RANGE prime);
void *SingleProcess(void *arg);
void MultiThread(void *arg);
#endif // _SHELDON_C_
#endif

#ifndef _PRIME_C_
int prime(RANGE m);
RANGE getPn(RANGE start, RANGE end);
void initPnTab(RANGE begin, RANGE delta);
int checkLegal(const char filename[], int mode);
void finiPnTab(RANGE begin, RANGE delta);
RANGE getNum(FILE *fp, int index);
void cat_all_tmp_files();
#endif // _PRIME_C_

#ifndef _ERR_HANDLE_C_
//TODO add error interpreter and other stuff about error-handling
#endif // _ERR_HANDLE_C_