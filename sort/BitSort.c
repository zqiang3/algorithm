#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define MAX 1250000
#define MAX_ONE_TIME 1000
#define TIMES 10000
char buf[MAX];
void print_bin(char c);
void bit_sort();
void load_int(int num);
void print_buf(char *filename);
int* read_numbers(FILE *fp);

int main(int argc, char **argv)
{
    int *p;
    char *filename = "numbers.txt";
    FILE *fp = fopen(filename, "r");
    int i;
    for(i = 0; i < TIMES; i++)
    {
        p = read_numbers(fp);
        bit_sort(p);
    }

    print_buf("out.txt");
}

void bit_sort(int* a)
{
    int i;
    for(i = 0; i < MAX_ONE_TIME; i++)
    {
        load_int(a[i]);
    }
}

void load_int(int num)
{
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
    int fd = open(filename, O_WRONLY);
    if(fd < 0)
    {
        perror("open error");
        exit(1);
    }
    int num;
    char temp[9];
    for (i = 0; i < MAX; i++)
    {
        c = buf[i];
        
        for(j = 0; j< 8; j++)
        {
            if(c & (1 << j))
            {
                num = i * 8 + j;
                sprintf(temp, "%d\0", num);
                write(fd, temp, strlen(temp));
                write(fd, "\n", 1);
            }
        }

    }
    close(fd);
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

int* read_numbers(FILE *fp)
{
    char temp[9];
    int num;
    if(fp == NULL)
    {
        perror("fopen error");
        exit(1);
    }

    int *pint = (int*)malloc(sizeof(int) * MAX_ONE_TIME);
    int i = 0;
    while(i < MAX_ONE_TIME)
    {
        fgets(temp, 8, fp);
        num = atoi(temp);
        pint[i++] = num;
    }
    return pint;
}
