#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAX 1250000          // 125w字节，刚好有1000w个位
#define MAX_ONE_TIME 10000   // 一次从文件读取数据个数
#define TIMES 1000           // 重复处理1000次

char buf[MAX];               // 1250000 byte
int arr[MAX_ONE_TIME];       // 40000 byte

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

    int *p;
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("open %s failure: ", filename);
        perror("");
        exit(1);
    }

    int i;
    for(i = 0; i < TIMES; i++)
    {
        read_numbers(fp);
        bit_sort();
    }

    print_buf("out.txt");
}


// 位排序 将int数组的所有数值排序
void bit_sort()
{
    int i;
    for(i = 0; i < MAX_ONE_TIME; i++)
    {
        load_int(arr[i]);
    }
}


// 将num对应的位设为1
void load_int(int num)
{
    int m = num / 8;
    int n = num % 8;
    buf[m] = buf[m] | (1 << n);
}


// 输出结果
void print_buf(char *filename)
{
    FILE *fp = fopen(filename, "w");
    if(fp == NULL)
    {
        perror("open error");
        exit(1);
    }

    int i;
    int j;
    char c;
    int num;
    char temp[8];
    for (i = 0; i < MAX; i++)
    {
        c = buf[i];
        
        for(j = 0; j< 8; j++)
        {
            if(c & (1 << j))   // 若该位为1，表示对应的数字存在
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


// 一次读取MAX_ONE_TIME个数放到int数组里
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


// 打印二进制
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
