#include <stdio.h>
#include <time.h>
#include <string.h>

void Date()
{
    time_t rawtime = time(NULL);
    char day[4], month[4], timezone[6];
    struct tm *ptm;
    ptm = localtime(&rawtime);
    strftime(day, 4, "%a", ptm);
    strftime(month, 4, "%b", ptm);
    printf("%s %s %02d %02d:%02d:%02d %d IST\n", day, month, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec,ptm->tm_year + 1900);
}

void DateU()
{
    time_t rawtime = time(NULL);
    struct tm *ptm;
    char day[4], month[4];
    ptm = gmtime(&rawtime);
    strftime(day, 4, "%a", ptm);
    strftime(month, 4, "%b", ptm);
    printf("%s %s %02d %02d:%02d:%02d %d UTC\n", day, month, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, ptm->tm_year + 1900);
}

void DateR()
{
    time_t rawtime = time(NULL);
    struct tm *ptm;
    char day[4], month[4], timezone[6];
    ptm = localtime(&rawtime);
    strftime(day, 4, "%a", ptm);
    strftime(month, 4, "%b", ptm);
    strftime(timezone, 6, "%z", ptm);
    printf("%s, %02d %s %d %02d:%02d:%02d %s\n", day, ptm->tm_mday, month, ptm->tm_year + 1900, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, timezone);
}

void DateHelp()
{
    printf("\nUsage: date [OPTION]\n");
    printf("Display date and time in the given FORMAT.\n");
    printf("-u \t print or set Coordinated Universal Time (UTC)\n");
    printf("-R \t output date and time in RFC 5322 format.\n");
    printf("--help \t brings up this help text.\n");
}
int main(int argc, char *argv[])
{
    char command[100] = "";
    char flags[100] = "";
    char *token = strtok(argv[1], " ");
    strcpy(command, token);
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        strcpy(flags, token);
    }
    if (!strcmp(flags, ""))
    {
        Date();
    }
    else if (flags[0] == '-' && flags[1] == 'u')
    {
        DateU();
    }
    else if (flags[0] == '-' && flags[1] == 'R')
    {
        DateR();
    }
    else if (flags[0] == '-' && flags[1] == '-' && flags[2] == 'h' && flags[3] == 'e'
                && flags[4] == 'l' && flags[5] == 'p'){
        DateHelp();
    }
    else
    {
        printf("date: invalid option -- '%s'\n", flags);
        return 1;
    }
    return 0;
}