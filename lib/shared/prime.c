#include <local/sheldon.h>

/* --------------------------------- GENERAL -------------------------------- */
/**
 * @brief ��0�4??�쨨??�쨨??��0�4??��0�3��0�9��0�1�쨦��0�6?�쨨??1?7
 * 
 * @param m 
 * @return int isprime->1, nonprime->0
 */
int prime(RANGE m)
{
    if (m == 0 || m == 1)
        return 0;
    RANGE i;
    RANGE termi = sqrt(m);
    for (i = 2; i <= termi; i++)
        if (m % i == 0)
            break;
    if (i > termi)
        return 1;
    else
        return 0;
}

/* ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2 */

/* --------------------------- Pn table functions --------------------------- */
/*
 * ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2 GETPN ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2
 */
/**
 * @brief Get the start Pn index of 
 * range [start, end] 
 * 
 * @param start 
 * @param end 
 * @return RANGE Pn index
 */
RANGE getPn(RANGE start, RANGE end)
{
    FILE *fp = fopen(PNFILE, "rb");
    if (fp == NULL)
    {
        fprintf(stderr,
                "***Error: No \"%s\" found in current dir!\n",
                PNFILE);
        exit(FILE_EXIST);
    }
    RANGE Pn = 0, TMP;
    while (1)
    {
        MYFREAD(&TMP, sizeof(RANGE), 1, fp);
        if (TMP == STDTERMI || feof(fp))
            break;
        // place A
        if (TMP >= start && TMP <= end) // may have problem
            break;
        Pn++; //NOTE why not place A? To avoid conflict of duplication while accumulating Pn.
    }
    if (feof(fp))
    {
        fprintf(stderr, "***Error: Illegal Pn Table file: %s!\n", PNFILE);
        exit(PNTAB_ILLEGAL);
    }
    return Pn;
}
/*
 * ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2 SINGLE TASK FOR MULTI-THREAD ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2
 */

/**
 * @brief �쨨��0�4?�쨨??��0�4??��0�4?��0�1��0�5?��0�6�쨦��0�6?�쨨??1?7
 * REVIEW Change to The Sieve of Eratosthenes
 * @param arg 
 * @return void* unused
 */
static void *partialPnTab(void *arg)
{
    PnTab *pn = arg;
    RANGE termi = STDTERMI;
    for (RANGE i = pn->start; i < pn->end; i++)
    {
#ifdef SHOW_PROGRESS
        // update progress
        pn->pm->current_cnt++;
        printf("\rAll: %.3Lf%%, thread: %d/%d",
               (long double)pn->pm->current_cnt * 100 / (pn->newdelta),
               pn->pm->fini_threads_cnt,
               GEN_THREADS);
#endif // SHOW_PROGRESS

        if (prime(i) == 1)
        {
            fwrite(&i, sizeof(i), 1, pn->fp);
        }
    }
#ifndef _ALL_LEGAL_
    if (pn->id == GEN_THREADS - 1)
    {
#endif // _ALL_LEGAL_
        fwrite(&termi, sizeof(termi), 1, pn->fp);
#ifndef _ALL_LEGAL_
    }
#endif // _ALL_LEGAL_
    fclose(pn->fp);
#ifdef SHOW_PROGRESS
    pn->pm->fini_threads_cnt++;
    // update progress
    printf("\rAll: %.3Lf%%, thread: %d/%d",
           (long double)pn->pm->current_cnt * 100 / (pn->newdelta),
           pn->pm->fini_threads_cnt,
           GEN_THREADS);
#endif           // SHOW_PROGRESS
    return NULL; // to avoid warning.
}

static void MultiThreadforPn(PnTab threads_info[])
{
#ifdef DEBUG
    printf(">>>%s:", __PRETTY_FUNCTION__);
#endif // DEBUG
    pthread_t thread_id[GEN_THREADS];
    //init threads
    for (int i = 0; i < GEN_THREADS; i++)
    {
        // make sure thread created success.
        if (pthread_create(&thread_id[i],
                           NULL,
                           partialPnTab,
                           &threads_info[i]) != 0)
        {
            fprintf(stderr, "***cannot create thread %d!\n", i);
            exit(THREAD_CREATE);
        }
    }
    //uninit threads
    for (int i = 0; i < GEN_THREADS; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    //cat files
#ifdef _ALL_LEGAL_
    for (int i = 0; i < GEN_THREADS; i++)
    {

        FILE *eachfp;
        char FileNameTmp[20];
        sprintf(FileNameTmp, TMPFILEFMT, i);
        eachfp = fopen(FileNameTmp, "rb"); // read-only
        if (eachfp == NULL)
        {
            fprintf(stderr, "***Error: cannot READ \"%s\"!\n", FileNameTmp);
            exit(FIEL_READ);
        }
        //FIXME This part is not completed yet!
        fcolse(fp);
    }
#else
    cat_all_tmp_files();
    printf("\n%s created. We strongly recommend you to run "
           "checkLegal on this Pn.tab file.\n",
           PNFILE);
#ifndef DEBUG
    MYSYSTEM("rm -f tmp/*");
    printf("tmp files removed.\n");
#endif // DEBUG
#endif // _ALL_LEGAL_
}

void initPnTab(RANGE begin, RANGE delta)
{
    RANGE stop = begin + delta * GEN_THREADS;
#ifdef DEBUG
    printf(">>>%s:", __PRETTY_FUNCTION__);
#endif // DEBUG
    printf("-->Generating Pn Tab.\nThreads=%d, Range=[%llu, %llu).\n",
           GEN_THREADS,
           begin,
           stop);
#ifdef GEN_MODE_SINGLE //when generating small numbers, it's even faster!
    FILE *pnfp = fopen(PNFILE, "wb");
    RANGE termi = STDTERMI;

    for (RANGE i = begin; i <= stop; i++)
    {
#ifdef SHOW_PROGRESS
        printf("\r%lld%%", i * 100 / (delta * GEN_THREADS));
#endif //SHOW_PROGRESS
        if (prime(i) == 1)
        {
            fwrite(&i, sizeof(i), 1, pnfp);
        }
    }
    fwrite(&termi, sizeof(termi), 1, pnfp); // terminator number, or "18446744073709551615" before EOF
    fclose(pnfp);
#else
    FILE *fp;
    PnTab threads_info[GEN_THREADS];
    RANGE start = begin, end = begin + delta;
    // single PM
    ProgManager pm = {0ULL, 0, 0};
    MYSYSTEM("mkdir tmp");
    for (int i = 0; i < GEN_THREADS; i++)
    {
        // open different file for async write
        printf("\rCreating Thread %d.", i);
        char FileNameTmp[20];
        sprintf(FileNameTmp, TMPFILEFMT, i);
        fp = fopen(FileNameTmp, "wb");
        if (fp == NULL)
        {
            fprintf(stderr, "***cannot WRITE \"%s\"!\n", FileNameTmp);
            exit(FILE_WRITE);
        }
        //init threads_info
        threads_info[i].id = i;
        threads_info[i].start = start;
        threads_info[i].end = end;
        threads_info[i].newdelta = GEN_THREADS * delta;
        threads_info[i].fp = fp;
        threads_info[i].pm = &pm;
        start = end + 1;
        end += delta;
    }
    MultiThreadforPn(threads_info);
    printf("<--Pn Table Generated.\n");
#endif // GEN_MODE_SINGLE
}
/**
 * @brief assume that all tmp files are legal -- end with STDTERMI
 */
void cat_all_tmp_files()
{
    FILE *fp_write = fopen(PNFILE, "wb");
    if (fp_write == NULL)
    {
        fprintf(stderr, ">>>error@%s:%d\n", __FILE__, __LINE__);
        exit(FILE_WRITE);
    }
    FILE *fp;
    char filename[20];
    RANGE thisone, pre, prepre, end = STDTERMI;
    // open file
    for (int i = 0; i < GEN_THREADS; i++)
    {
        sprintf(filename, TMPFILEFMT, i);
        fp = fopen(filename, "rb");
        if (fp == NULL)
        {
            fprintf(stderr, ">>>error@%s:%d\n", __FILE__, __LINE__);
            exit(FILE_READ);
        }
        // initialize
        MYFREAD(&thisone, sizeof(thisone), 1, fp);
        pre = thisone;
        prepre = pre;
        MYFREAD(&thisone, sizeof(thisone), 1, fp);
        pre = thisone;
        MYFREAD(&thisone, sizeof(thisone), 1, fp);
        // loop
        while (1)
        {
            if (thisone == STDTERMI)
            {
                if (fflush(fp_write) != 0)
                    exit(FILE_WRITE);
                break;
            }
            // copy into PNFILE
            if (fwrite(&prepre, sizeof(prepre), 1, fp_write) != 1)
                exit(FILE_WRITE);
            if (fflush(fp_write) != 0)
                exit(FILE_WRITE);
            // refresh new set of thisone, pre &prepre
            if (!MYFREAD(&thisone, sizeof(thisone), 1, fp))
                break;
            prepre = pre;
            pre = thisone;
        }
        fclose(fp);
    }
    if (fwrite(&end, sizeof(end), 1, fp_write) != 1)
    {
        fprintf(stderr, ">>>error@%s:%d\n", __FILE__, __LINE__);
        exit(FILE_WRITE);
    }
    fclose(fp_write);
}
/* ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2 */

/* ----------------------------- legality check ----------------------------- */
/*
         * ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2 I ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2
         *   :::::: U S E F U L   S I M P L E   F U N C T I O N S : :  :   :    :     :        :          :
         * ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2
         */

/**
 * @brief Get the `index` Number in the file(using file handle)
 * NOTE need to be in READ mode
 * @param fp file handle
 * @param index the index of number required
 * @return RANGE last number
 */
RANGE getNum(FILE *fp, int index)
{
    RANGE num = 0;
    long CurPos;
#ifdef DEBUG
    printf(">>>%s:", __PRETTY_FUNCTION__);
#endif // DEBUG
    // remeber where the curpos is
    CurPos = ftell(fp);
    if (index < 0)
        fseek(fp, index * sizeof(RANGE), SEEK_END);
    else
        fseek(fp, index * sizeof(RANGE), SEEK_SET);
    if (feof(fp))
        return 0;
    MYFREAD(&num, sizeof(num), 1, fp);

    // restore curpos
    fseek(fp, CurPos, SEEK_SET);
    return num;
}
//returns nonzero if PNFILE is legal(ended with STDTERMI).
int checkLegal(const char filename[], int mode)
{
#ifdef DEBUG
    printf(">>>%s:", __PRETTY_FUNCTION__);
#endif // DEBUG
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "***cannot READ \"%s\"!\n", filename);
        exit(FILE_READ);
    }
    RANGE previous, thisone, lastone;
    if (getNum(fp, 0) != STDTERMI)
        lastone = getNum(fp, -2);
    else
    {
        fprintf(stderr, "***Illegal PnFile!\n");
        exit(PNTAB_ILLEGAL);
    }
    int legal = 1; //default as legal
    MYFREAD(&previous, sizeof(RANGE), 1, fp);
    thisone = previous;
    lastone -= thisone;
    printf("-->Check Start: [%llu, %llu].\n", thisone, lastone);
    switch (mode)
    {
        /*
         * ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2 II ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2
         *   :::::: O P T I M I Z E   T H I S : :  :   :    :     :        :          :
         * ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2
         */

    case 0: // simple mode
        printf("in FAST Mode\n");
        while (1)
        {
            if (thisone == STDTERMI)
                break;
            if (feof(fp) && legal == 1)
            {
                legal = 0;
                break;
            }

            MYFREAD(&thisone, sizeof(RANGE), 1, fp);
            if (thisone <= previous)
            {
                long failed_addr = ftell(fp);
                fprintf(stderr, "***0x%lx:thisone(%llu) should be"
                                "greater than previous(%llu)!\n",
                        failed_addr,
                        thisone,
                        previous);
                exit(PNTAB_ILLEGAL);
            }
            previous = thisone;
        }
        break;
    case 1: // serious mode
        printf("in SECURE Mode\n");
        while (1) // TODO change this to multi-thread
        {
            if (thisone == STDTERMI)
                break;
            if (feof(fp) && legal == 1)
            {
                legal = 0;
                break;
            }
            if (prime(thisone) == 0)
            {
                long failed_addr = ftell(fp);
                fprintf(stderr, "***0x%lx:thisone(%llu) is not a prime!\n", failed_addr, thisone);
                exit(PNTAB_ILLEGAL);
            }
            MYFREAD(&thisone, sizeof(RANGE), 1, fp);
            if (thisone <= previous)
            {
                long failed_addr = ftell(fp);
                fprintf(stderr, "***0x%lx:thisone(%llu) should be"
                                "greater than previous(%llu)!\n",
                        failed_addr,
                        thisone,
                        previous);
                exit(PNTAB_ILLEGAL);
            }

#ifdef SHOW_PROGRESS
            printf("\rProgress: %.3lf%%", (double)previous * 100 / lastone);
#endif // SHOW_PROGRESS
            previous = thisone;
        }
        break;
    default:
        printf("Unkown mode.\n");
        break;
    }
    printf("\n<--Check End.\n");
    fclose(fp);
    return legal; //nonzero return if legal
}
/**
 * @brief Get the Next Prime of `thisone`
 * NOTE may not exist in PNFILE
 * 
 * @param thisone 
 * @return RANGE next prime of thisone
 */
RANGE getNextPrime(RANGE thisone)
{
    RANGE next = 0;   // not a prime
    if (thisone == 2) // almost impossible
        return (RANGE)3;
    else
    {
        for (next = thisone + 2; prime(next) == 0; next += 2)
        {
        }
        return next;
    }
}
/**
 * @brief finish tmp file of Pn Table.
 * NOTE must in the correct directory.
 * @param begin 
 * @param delta 
 */
void finiPnTab(RANGE begin, RANGE delta)
{
    FILE *fp;
    PnTab threads_info[GEN_THREADS];
    RANGE end = begin + delta;
    // single PM
    ProgManager pm = {0ULL, 0, 0};
#ifdef DEBUG
    printf(">>>%s:", __PRETTY_FUNCTION__);
#endif
    // open many files for async write
    printf("-->Finishing temp Pn Tab files...\n");
    MYSYSTEM("mkdir tmp");
    for (int i = 0; i < GEN_THREADS; i++)
    {
        printf("\rCreating Thread %d.", i);
        char FileNameTmp[20];
        sprintf(FileNameTmp, TMPFILEFMT, i);
        fp = fopen(FileNameTmp, "ab+"); // not ab because getNum() need READ access.
        if (fp == NULL)
        {
            fprintf(stderr, "***cannot ADD to \"%s\"!\n", FileNameTmp);
            exit(FILE_ADD);
        }
        RANGE start_number = getNum(fp, -2);
        // initialize
        threads_info[i].id = i;
        threads_info[i].start = start_number == 0 ? begin : getNextPrime(start_number);
        threads_info[i].end = end;
        threads_info[i].newdelta = threads_info[i].end - threads_info[i].start;
        threads_info[i].fp = fp;
        threads_info[i].pm = &pm;
        begin = end;
        end += delta;
#ifdef DEBUG
        printf("{Thread:%d, start:%llu, end:%llu, newdelta:%llu}\n",
               threads_info[i].id, threads_info[i].start, threads_info[i].end, threads_info[i].newdelta);
#endif
    }
    MultiThreadforPn(threads_info);
    printf("<--Temp Pn Table file finished!\nLegal check result: %d.\n",
           checkLegal(PNFILE, 0));
}
/* ��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2��0�1??��0�2 */