#include <local/sheldon.h>

#ifdef USE_FAST_PRODUCTION
/**
 * @brief 'manually' optimize the process of
 *  one digit x many-digits
 * NOTE this effect is not obvious, 
 * maybe the compiler has somewhat optimized too.
 * 
 * @param product 
 * @param bit 
 * @return RANGE 
 */
RANGE fastproduction(RANGE product, char bit)
{
    //传入bit范围2~9，手动加速
    //gcc可能会优化，写着玩玩
    switch (bit)
    {
    case 3:
        return product + (product << 1);
    case 4:
        return product << 2;
    case 5:
        return product + (product << 2);
    case 6:
        return (product << 2) + (product << 1);
    case 7:
        return (product << 3) - product;
    case 8:
        return product << 3;
    case 9:
        return product + (product << 3);
    default:
        printf("\n***Error: calculating %llu x %hhd.\n", product, bit);
        exit(INTERAL_ERROR);
    }
}
#endif // USE_FAST_PRODUCTION
int ProductProperty(RANGE primenumber, RANGE prime)
{
    RANGE product = 1; //保存乘积。乘法运算的化简是降低O(T(N))的必由之路
    char smallest_bit; //从最低位开始，向高位提取，逐一向右移动所有位，遇到0直接跳出循环

    //分解传入的素数
    while (prime != 0)
    {
        smallest_bit = prime % 10; //取最小位
#ifdef USE_FAST_PRODUCTION
        if (smallest_bit == 0)
            return 0; //考虑实际意义，直接返回即可；1不用改变product的值
        //core
        if (smallest_bit > 2)
            product = fastproduction(product, smallest_bit);
        else if (smallest_bit == 2)
            product <<= 1;
            //end
#else  // USE_FAST_PRODUCTION
        product *= smallest_bit;
#endif // USE_FAST_PRODUCTION

        prime /= 10; //向右移动一位
    }

    //比较乘积与序号是否相同
    if (product == primenumber)
        return 1;
    else
        return 0;
}
void *SingleProcess(void *arg)
{
    Sheldon *inter = arg;
    RANGE index, primenumber = inter->initialPn; //遍历参数，第n个素数
    int sheldonflag = 0;                         //是否为Sheldon素数的标志
    FILE *fp = fopen(OUTFILE, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "***Error: cannot ADD to \"%s\"!\n", OUTFILE);
        exit(FILE_READ);
    }
    printf("\rThread %d, range: [%llu, %llu].\n", inter->id, (inter->start), (inter->end));
    //仿佛听到了CPU的咆哮声……
    for (index = inter->start; index <= inter->end; index++)
    {
#ifdef SHOW_PROGRESS
        printf("\rAll: %.3Lf%%, thread: %d/%d",
               (long double)inter->pm->current_cnt * 100 / (END - START),
               inter->pm->fini_threads_cnt,
               THREADS);
        inter->pm->current_cnt++;
#endif //SHIOW_PROGRESS
        if (prime(index) == 1)
        {
            primenumber++;
            sheldonflag = ProductProperty(primenumber, index);
            if (sheldonflag == 1)
            {
                // output result
                fprintf(fp, "P(%llu) = %llu has product property.\n", primenumber, index);
                inter->cnt++;
            }
        }
    }
#ifdef SHOW_PROGRESS
    inter->pm->fini_threads_cnt++;
    printf("\rAll: %.3Lf%%, thread: %d/%d",
           (long double)inter->pm->current_cnt * 100 / (END - START),
           inter->pm->fini_threads_cnt,
           THREADS);
#endif // SHIOW_PROGRESS
#if SHOW_MODE == 1
    printf("\rThread %d finished. Find %d.\n", inter->id, inter->cnt);
#endif // SHOW_MODE == 1
    fclose(fp);
}
void MultiThread(void *arg)
{
#ifdef DEBUG
    printf(">>>%s:", __PRETTY_FUNCTION__);
#endif // DEBUG
    (Sheldon *)arg;
    pthread_t thread_id[THREADS];
    int total = 0;
    Sheldon threads_info[THREADS];
    ProgManager pm = {0ULL, 0, 0L};
    RANGE start = START;
    RANGE end = START + DELTA;
    //clear OUTFILE, and add a title.
    FILE *fp = fopen(OUTFILE, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "***Error: cannot WRITE \"%s\"!\n", OUTFILE);
        exit(FILE_WRITE);
    }
    fprintf(fp, "Integers With Product Property in [%d, %llu].\n", START, END);
    char buffer_time_now[20];
    getTimeNow_str(buffer_time_now);
    fprintf(fp, "<--Generated on %s-->\n", buffer_time_now);
    fclose(fp);
    // initialize threads.
    for (int i = 0; i < THREADS; i++)
    {
        //initialize
        threads_info[i].start = start;
        threads_info[i].end = end;
        threads_info[i].id = i;
        threads_info[i].cnt = 0;
        threads_info[i].initialPn = getPn(start, end);
        threads_info[i].pm = &pm;
        // make sure thread created success.
        if (pthread_create(&thread_id[i], NULL, SingleProcess, &threads_info[i]) != 0)
        {
            fprintf(stderr, "***cannot create thread %d.\n", i);
            exit(THREAD_CREATE);
        }

        start = end + 1;
        end += DELTA;
    }

    // release resource and traverse works.
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(thread_id[i], NULL);
#if SHOW_MODE == 0 // default
        printf("Thread %d finished. Find %d.\n", i, threads_info[i].cnt);
#endif //SHOW_MODE == 0
#ifdef TOTAL
        total += threads_info[i].cnt;
#endif //TOTAL
    }

#ifdef TOTAL
    printf("Total Find in [%d, %llu]: %d.\n", START, (RANGE)END, total);
#endif //TOTAL
}