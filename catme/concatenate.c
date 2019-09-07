#include <stdio.h>
#include <include/local/sheldon.h>
#define FILES 5

int main()
{
    FILE *fp_write = fopen("Pn.tab", "wb");
    if (fp_write == NULL)
        exit(FILE_WRITE);
    FILE *fp;
    char filename[20];
    RANGE thisone, pre, prepre,end=STDTERMI;
    // open file
    for (int i = 0; i < FILES; i++)
    {
        sprintf(filename, "%d.tab", i);
        fp = fopen(filename, "rb");
        if (fp == NULL)
            exit(FILE_READ);
        // initialize
        fread(&thisone, sizeof(thisone), 1, fp);
        pre = thisone;
        prepre = pre;
        fread(&thisone, sizeof(thisone), 1, fp);
        pre = thisone;
        fread(&thisone, sizeof(thisone), 1, fp);
        // loop
        while (1)
        {
            if (thisone == STDTERMI)
                break;
            // copy into PNFILE
            fwrite(&prepre, sizeof(prepre), 1, fp_write);
            // refresh new set of thisone, pre &prepre
            fread(&thisone, sizeof(thisone), 1, fp);
            prepre = pre;
            pre = thisone;
        }
        fclose(fp);
    }
    fwrite(&end, sizeof(end), 1, fp_write);
    fclose(fp_write);
    return 0;
}