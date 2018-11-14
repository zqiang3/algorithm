#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAX 1250000
#define MAX_ONE_TIME 10000
#define TIMES 1000
char buf[MAX];
int arr[MAX_ONE_TIME];
void print_bin(char c);
void bit_sort();
void load_int(int num);
void print_buf(char *filename);
void read_numbers(FILE *fp);
void printb(char c);

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage: <cmd> <filename>\n");
        exit(1);
    }
    printf("sizeof buf = %d\n", sizeof(buf));


    int *p;
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("open %s failure: ", filename);
        perror("");
        exit(1);
    }
    int ti;
    for(ti = 0; ti < TIMES; ti++)
    {
        read_numbers(fp);
        bit_sort();
        
    }

    print_buf("out.txt");
}

void bit_sort()
{
    int i;
    for(i = 0; i < MAX_ONE_TIME; i++)
    {
        load_int(arr[i]);
    }
}

void load_int(int num)
{
    if(num == 4)
    {
        int a = num;
        char ccc;
    }
    int m = num / 8;
    int n = num % 8;
    char c = buf[m];
    buf[m] = c | (1 << n);
}

void print_buf(char *filename)
{
    int i;
    int j;
    char c;
    FILE *fp = fopen(filename, "w");
    if(fp == NULL)
    {
        perror("open error");
        exit(1);
    }
    int num;
    char temp[8];
    for (i = 0; i < MAX; i++)
    {
        c = buf[i];
        
        for(j = 0; j< 8; j++)
        {
            if(c & (1 << j))
            {
                num = i * 8 + j;
                sprintf(temp, "%d", num);
                fputs(temp, fp);
                fputs("\n", fp);
            }
        }

    }
    fclose(fp);
}

void print_bin(char c)
{
    char b[8];
    int n = 8;
    int i;
    for(i = 0; i < n; i++)
    {
        b[i] = c % 2;
        c >>= 1;
    }
    for (i = 7; i >= 0; i--)
    {
        printf("%d", b[i]);
    }
    printf("\n");
}

void read_numbers(FILE *fp)
{
    char temp[9];  // 最后一位填\0, 倒数第二位填\n， 剩余7位对应最大7位数，n < 10000000
    int num;
    if(fp == NULL)
    {
        perror("fopen error");
        exit(1);
    }

    int i = 0;
    while(i < MAX_ONE_TIME)
    {
        fgets(temp, 9, fp);
        num = atoi(temp);
        arr[i++] = num;
    }
}

void printb(char c)
{
    char temp[8];
    int i;
    for (i = 0; i < 8; i++)
    {
        temp[i] = c % 2;
        c = c << 1;
    }
    for (i = 7; i >= 0; i--)
        printf("%d", temp[i]);
    printf("\n");
}
