//
// Created by Lenovo on 2020/10/22.
//
#include <stdio.h>
#include <malloc.h>
#include <cstring>

//https://blog.csdn.net/TSZ0000/article/details/82881888
int *int_array_create(int n)//参数n为数组元素个数
{
    int *r;
    if (n <= 0) return NULL;//参数错误
    r = (int *) malloc(sizeof(int) * n);//申请内存空间，大小为n个int长度。
    return r;//返回得到的整型数组的指针。
}

char *alloc_chars(int howMany){
    char  *r;
    if (howMany <= 0) return NULL;//参数错误
    r = (char *) malloc(sizeof(char) * howMany);//申请内存空间，大小为n个int长度。
    return r;//返回得到的整型数组的指针。
}

void test_alloc_chars(){
    char *string=alloc_chars(4);
  printf("len %d \n",strlen(string));
//  free(string);
    strcpy(string,"11");
    printf("len %d \n",strlen(string));
    printf("str %s\n",string);

}