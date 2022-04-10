//
// Created by Lenovo on 2020/10/21.
//


#include <stdio.h>
#include "csSysPrinciple.h"
#include <malloc.h>
#include <string>
#include <stack>
#include <iostream>
#include "myAlloc.h"
//2020年11月3日16:18:13
void highSameLow0() {
    int n = 32;
    int x = 0x12345678;
//    往右边移动24位，也就是说那24位都不要了，然后移动回来，就补充0了
    int y = (x >> (n - 8)) << (n - 8);
    printf("x=%#x,y=%#x\n", x, y);
}

void high0LowSame() {
    int n = 32;
    int x = 0x12345678;
//    往右边移动24位，也就是说那24位都不要了，然后移动回来，就补充0了
    int y = (x << (n - 8)) >> (n - 8);
    printf("x=%#x,y=%#x\n", x, y);
}

void highFanLow0() {
    int n = 32;
    int x = 0x12345678;
//    往右边移动24位，也就是说那24位都不要了，然后移动回来，就补充0了
    int y = (x >> (n - 8));
    y = ~y;
    y = y << (n - 8);
    printf("x=%#x,y=%#x\n", x, y);
}

//cant
void highSameLow1() {
    int n = 32;
    int x = 0x12345678;
//    往右边移动24位，也就是说那24位都不要了，然后移动回来，就补充0了
    int y = (x >> (n - 8));
    y ^= 1;
    y = y << (n - 8);
    printf("x=%#x,y=%#x\n", x, y);
}
//2020年11月3日16:18:20



struct Point {
    int x, y;
};


//计算机原理实验里面抄来的代码
// 打印这块内存
//typedef unsigned char *byte_pointer;
//这是 unsigned char * ，所以里面的东西应该是unsigned char
void show_bytes(byte_pointer start, int len) {
    printf("你的机器里面内存的状态\n");
    int i;
    std::stack<unsigned char> st;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
        st.push(start[i]);
    }

    // 一个字节是8位,也就是两个4位
    printf(" H\n");
    std::cout << "下面是和上面相反的，如果机器是小端的，那下面的是正常顺序\n";
    while (!st.empty()) {
//        std::cout<<st.top();
        printf(" %.2x", st.top());
        st.pop();
    }
    std::cout << "H\n";
}
//
//std::string getFloatBytes(float floatNum){
//    return getBytes((byte_pointer) &floatNum, sizeof(float));
//}
/**
 * 小端机器的正常顺序16进制
 * @param start
 * @param len
 * @return
 */
std::string getBytes(byte_pointer start, int len) {

//    printf("你的机器里面内存的状态\n");
    int i;
//    std::stack<unsigned char>st;
    std::stack<char *> st;
//    std::string str;
//    char *str=alloc_chars(len);
//    char str[len];
    for (i = 0; i < len; i++) {
//        printf(" %.2x", start[i]);
//        sprintf(str," %.2x", start[i]);
//        std::string tmp;
        char *tmp = alloc_chars(2);
//        char tmp[2];
//  用这个申请内存 好像会出错误，还是乖乖的在堆上申请，然后free吧
        sprintf(tmp, "%.2x", start[i]);
        st.push(tmp);
//        free(tmp);
//        st.push(start[i]);

    }


    // 一个字节是8位,也就是两个4位
//    printf(" H\n");
//    std:: cout<<"下面是和上面相反的，如果机器是小端的，那下面的是正常顺序\n";
    std::string string;
    while (!st.empty()) {
//        std::cout<<st.top();
//        printf("%.2x",st.top());
//        sprintf(str," %.2x", st.top());
//
        string += st.top();
        free(st.top());
        st.pop();
    }
//    string +="H";
    return string;
}


// 打印int类型数字的内存
void show_int(int x) {
    // 这里关键是把x 一个int 型的数的地址 转成unsigned char *型的，
    // 其他的如果是float型的地址，也可以转成unsigned char *型的，
    // 这样所有数据类型都可以用一个show_bytes函数查看内存了
    show_bytes((byte_pointer) &x, sizeof(int));
}

//https://blog.csdn.net/renanrenan/article/details/83094956
void hexToFloat() {
    unsigned char pMem[] = {0x66, 0xE6, 0xF0, 0x42};
    float *p = (float *) pMem;
    printf("%g\r\n", *p);
}

void hexToFloat(unsigned char *pMem) {
//    unsigned char pMem[] = {0x66,0xE6,0xF0,0x42};
    float *p = (float *) pMem;
    printf("%g\r\n", *p);
}

void showFloatFromHex() {
    int i = 0x0000108B;
//    3f8ccccd
    hexToFloat((unsigned char *) &i);
}

void showFloatFromHex(int floatNumButIntFormat) {
//    int i=0x0000108B;
//    3f8ccccd
    hexToFloat((unsigned char *) &floatNumButIntFormat);
}

std::string getIntBytes(int x) {
    // 这里关键是把x 一个int 型的数的地址 转成unsigned char *型的，
    // 其他的如果是float型的地址，也可以转成unsigned char *型的，
    // 这样所有数据类型都可以用一个show_bytes函数查看内存了
    return getBytes((byte_pointer) &x, sizeof(int));
}

// 打印float类型数字的内存
void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

// 打印指针类型的内存
void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}

// 打印float类型数字的内存
std::string getFloatBytes(float x) {
    return getBytes((byte_pointer) &x, sizeof(float));
}

// 打印指针类型的内存
std::string getPointerBytes(void *x) {
    return getBytes((byte_pointer) &x, sizeof(void *));
}


/**
 * 设计一个C语言程序，输出一个整数对应的有符号值和无符号值。
 */
void printSignedAndUnsigned(int integer) {
    printf("Signed: %d\n", integer);
    printf("Unsigned: %u\n", integer);
}

void testPrintSignedAndUnsigned() {
    int integer;
    printf("input number ,output its signed and unsigned number.");
//    printf("输入数字，输出他的有符号值和无符号值。");
    scanf("%d", &integer);
    printSignedAndUnsigned(integer);
}

//补码
//char *getComplementCode(int n) {
//    return  (~n)+1;
//}
//
//int getComplementCode(int n) {
//    return  (~n)+1;
//}

void intComplementCode(int n) {
    printf("intComplementCode : %lld\n", (~n) + 1);
}

void intComplementCodeUseStr(int n) {
    printf("intComplementCode : %lld\n", (~n) + 1);
}

void printComplementCode(int n) {
    printf("Complement Code of %d is :%x\n", n, n);
}

const int MAX_NUMBER_LIST_LEN = 100;

ArrayList pushNumberToList(int n) {
//    int numbers[MAX_NUMBER_LIST_LEN];
//    malloc is in the heap ,so we can return
    int *numbers = int_array_create(MAX_NUMBER_LIST_LEN);
    int index = 0;
    while (n % 10 > 0) {
        numbers[index++] = n % 10;
        n /= 10;
    }
//    Variable has incomplete type 'ArrayList'
    ArrayList arrayList;
    arrayList.array = numbers;
    arrayList.length = MAX_NUMBER_LIST_LEN;

//    https://blog.csdn.net/weixin_40710708/article/details/107696694
//    这是个蛮愚蠢的错误，我把局部变量的地址作为返回，但是局部数组变量是位于stack区的，
//    函数结束后这个地址中的数据将失去意义; 这种情况怎么办呢，可以被局部变量数组添加static即可;
//    Address of stack memory associated with local variable 'numbers' returned
    return arrayList;
}

//https://bbs.csdn.net/topics/90358831
void doubleToComplementCode(double val) {

    long long *p = (long long *) &val;
    printf("sizeof(val): %d\n", sizeof(val));

//    cout << sizeof(val) << endl;

    long long newval = ~(*p) + 1;
    printf("newval: %lld\n", newval);
    printBinary(newval);
    //自定义一个函数printBinary
//    cout << newval << endl;

}



//我们bai用按位运du算符:右移>> 和按位运算符与^，这两个功能就可zhi以实现。
//#include<stdio.h>
//void printBinary(int number);//这是声明一个自定义的dao函数，让编译器知道我们造了一个这么个函数，功能：将整数以二进制形式输出。

//int main()
//{
//    printBinary(22);//括号里面可以填上你要输出的整数，比如要输出22的二进制形式
//    return 0;
//}
//真的吗 感觉是错的啊 392778521570631415 不像是二进制数字
//void printBinary(int number)//自定义一个函数printBinary
//{
//    int temp = sizeof(number)-1;// 定义一个变量 ：如果你的编译器是32位的，也就是int temp = 31；
//
//    while(temp >= 0) // temp 是循环的次数，不需要纠结判断是>= 还是>, 写完之后检验一下就知道哪个对了。
//    {
//        int value = number>>temp^1;// a>>temp。temp移动后，是把这个整数的二进制形式中最后一位，依次与1进行按位与运算。假如temp=31，就是把这个整数的二进制形式右移31位，只剩下了这个整数的二进制形式的开头第一个数字，然后与1进行按位与运算。真则为1，假则为0。
//
//        printf("%d", value);//每次输出整数的二进制形式的一个数字，从开头开始输出。.
//        temp--;// 按位右移循环，直到把整数内存中所有的位移完毕。从内存中二进制形式的第一位开始。
//
//    }
//
//
//}

/**
 * 1、如何理解 n&1<<i?1:0 ，加上括号： (n&(1<<i))?1:0

2、因为int类型有4个字节，所以也就是32位二进制，从bit0到bit31，所以，1<<i，就是将1位移31，
 然后和n位与，用于将n的最高位取出，因为取出后如果为0，那么结果就是0，如果为1，结果就是一个正整数，
 所以这里加了一个问号表达式，来将结果变为0和1。后面的就很明了了。

3、复习一下运算符的优先级。按位与&是9级，移位是6级，问号表达式是14级，
 所以计算顺序是：移位>>按位与>>问号表达式。正好符合要求，所以一个括号也不用。
 00000000000000000111101010110110
 * @param number
 */
void printBinary(int number)//自定义一个函数printBinary
{
//    int n=12;
    printf("erjin zhi of %d:\n", number);
    for (int i = 31; i >= 0; i--) {
        printf("%1d", (number & (1 << i)) ? 1 : 0);
    }
    puts("");
}

#include <iostream>
#include <vector>

void printBinaryFromDirtySentences() {
    using namespace std;
    string dirtySentence = "1 |  0111,1111 | 0001，1001，1001，1001，1001，100";
    vector<string> v;
    v.emplace_back(dirtySentence);
    v.emplace_back("1   011,1111,1000,1100,1100,1100,1100,1101");
    for (const string &s:v) {
        printBinaryFromDirtySentence(s);
    }

}

void printBinaryFromDirtySentence(const std::string &dirtySentence) {
    using namespace std;
    for (char ch:dirtySentence) {
        if (ch == '1' || ch == '0') {
            cout << ch;
        }
    }
    cout << "\n";
}

std::string getBinaryFromDirtySentence(const std::string &dirtySentence) {
    using namespace std;
    string outStr;
    for (char ch:dirtySentence) {
        if (ch == '1' || ch == '0') {
//            cout<<ch;
            outStr += ch;
        }
    }

    return outStr;
}
//https://blog.csdn.net/w_y_x_y/article/details/78092259
#include "iostream"
#include <cmath>
#include <string.h>

#define MAX 50


int sameStr(char *a, char *b) {
    return strcmp(a, b) == 0;
}

void binaryToHexNoInput() {
    using namespace std;
    char elem2[MAX] = "10111111100011001100110011001100";
    int flag = 1;
    char ch;
//    int i = 0;


    int length = strlen(elem2);
    int n = 0;
    int sum = 0;
    int product = 0;
    if (length % 4 != 0)//将缺位的二进制码用0补齐
    {
        int n = 4 - length % 4;
        int i = 0;
        for (i = length - 1; i >= 0; i--)
            elem2[i + n] = elem2[i];
        length += n;
        for (i = 0; i < n; i++)
            elem2[i] = '0';
        cout << "补齐之后的内容是：" << endl;
        for (i = 0; i < length; i++)
            cout << elem2[i] << " ";
        cout << endl;
    }
    for (n = 0; n < length; n++)//判断是否是二进制数
    {
        if ('1' == elem2[n] || '0' == elem2[n])
            sum++;
    }
    if (sum == length) {
        char elem16[MAX];
        int r = 0;
        int m = 0;
        int p = 0;
        int q = 0;
        for (m = length - 1; m >= 0; m--) {
            q = elem2[m] - '0';
            product += q * pow(2, p);
            p++;
            if (4 == p) {
                if (product > 9)
                    elem16[r] = product + 55;//输出A...F范围
                else {
                    elem16[r] = product + 48;//输出0...9范围
                }
                r++;
                p = 0;
                product = 0;
            }
        }
        int j = 0;
        cout << "对应的十六进制数是：OX";
        for (j = r - 1; j >= 0; j--)
            cout << elem16[j];
        cout << endl;

    } else {
        cout << "你输入的不是二进制数！" << endl;
    }
}

int _2to16()//二转十六
{
    using namespace std;
    cout << "请输入二进制数，并以‘$’结束：";
    char elem2[MAX];
    int flag = 1;
    char ch;
    int i = 0;
    while (flag) {
        cin >> ch;
        if (ch != '$') {
            elem2[i] = ch;
            i++;
        } else {
            flag = 0;
        }
    }
//    ISO C++11 does not allow conversion from string literal to 'char *
//    char const *eof="eof";
    char eof[] = "eof";
    if (sameStr(elem2, eof)) {
        return STOP;
    }
    int length = i;
    int n = 0;
    int sum = 0;
    int product = 0;
    if (length % 4 != 0)//将缺位的二进制码用0补齐
    {
        int n = 4 - length % 4;
        int i = 0;
        for (i = length - 1; i >= 0; i--)
            elem2[i + n] = elem2[i];
        length += n;
        for (i = 0; i < n; i++)
            elem2[i] = '0';
        cout << "补齐之后的内容是：" << endl;
        for (i = 0; i < length; i++)
            cout << elem2[i] << " ";
        cout << endl;
    }
    for (n = 0; n < length; n++)//判断是否是二进制数
    {
        if ('1' == elem2[n] || '0' == elem2[n])
            sum++;
    }
    if (sum == length) {
        char elem16[MAX];
        int r = 0;
        int m = 0;
        int p = 0;
        int q = 0;
        for (m = length - 1; m >= 0; m--) {
            q = elem2[m] - '0';
            product += q * pow(2, p);
            p++;
            if (4 == p) {
                if (product > 9)
                    elem16[r] = product + 55;//输出A...F范围
                else {
                    elem16[r] = product + 48;//输出0...9范围
                }
                r++;
                p = 0;
                product = 0;
            }
        }
        int j = 0;
        cout << "对应的十六进制数是：OX";
        for (j = r - 1; j >= 0; j--)
            cout << elem16[j];
        cout << endl;

    } else {
        cout << "你输入的不是二进制数！" << endl;
    }
    return CONTINUE;

}

void many2To16() {
    using namespace std;
    cout << "多次输入二进制，可以转化为16进制，输入eof$停止\n";
//    string binStr;
    while (true) {
        if (_2to16() == STOP)break;
    }
}


void printStrKindNumber(const char *numStr) {
    int len = strlen(numStr);
    for (int i = 0; i < len; i++) {
        printf("%c", numStr[i]);
    }
}

int floatIsZero(float f) {
    return f < 1e-6 && f > -1e-6;
}

enum {
    NOPOS = -1
} Position;

int findDotPos(const char *floatStr, int length) {
    for (int i = 0; i < length; i++) {
        if (floatStr[i] == '.')
            return i;
    }
    return NOPOS;
}

char *subString(const char *oldStr, int from, int len) {
    char *outStr = alloc_chars(len);
    int outStrIndex = 0;
    for (int i = 0; i < len; i++) {
        outStr[outStrIndex++] = oldStr[from + i];
//        *(oldStr+from);
    }
    outStr[outStrIndex++] = '\0';
    return outStr;
}

void testSubString() {
    const char *string = "12345";
    printf("sub %s\n", subString(string, 3, 2));
    printf("sub %s\n", subString(string, 2, 4));
}

#include <stdio.h>
#include <stdlib.h>
/*
num是要展示的float数,bin是保存所有二进制位的数组
*/
//https://blog.csdn.net/wayway0554/article/details/84111889
void getFloatBin(float num, char bin[]) {
    int t = 1;//用来按位与操作
    int *f = (int *) (&num);//将float的解释成int，即float的地址转成int*
    for (int i = 0; i < 32; i++) {
        //从最高位开始按位与，如果为1，则bin[i]=1，如果为0，则bin[i]=0
        //这里没有将bin存成字符，而是数字1 0
        bin[i] = (*f) & (t << 31 - i) ? 1 : 0;
    }
}

void testGetFloatBin() {
    float test = -1.1;
    char c[32];
    printf("测试float数为:%f\n", test);
    printf("二进制表示为:");
    getFloatBin(test, c);
    for (int i = 0; i < 32; i++) {
        printf("%d", c[i]);
        if (i == 0)
            printf(", ");
        if (i == 8)
            printf(", ");
    }

}


unsigned int float2hexRepr(float *a) {
    unsigned int c;
    //uint 32bit ,float的内存我就直接当做是unit了
//    这个指针取得第一个地址放着的uint，就像数组那样
    c = ((unsigned int *) a)[0];
//    取到第一块unsigned int 长度的东西，这块地方放着float的那些二进制的，一定
    return c;
}

//虽然不知道什么意思但是可以使用
unsigned long long double2hexRepr(double *a) {
    unsigned long long c;
//    ull 64bit
    c = ((unsigned long long *) a)[0];
    return c;
}

//打印double and float their hex format
//https://www.cnblogs.com/tlz888/p/9211600.html
void testFloat2hexRepr() {
    printf("%s\n", "== in float representation == ");
//    float f1 = 15213.0;
    float f1 = -1.1;
    printf("float %f , its hex is %x\n", f1, float2hexRepr(&f1));
    double double1 = 10.5;
    printf("double of %lf ,its hex is %llx\n", double1, double2hexRepr(&double1));
}

char *getHex(float f) {

    char *s = alloc_chars(32);
    sprintf(s, "%x", float2hexRepr(&f));
    return s;
}


char *getHex(int intNum) {
    char *s = alloc_chars(32);
    sprintf(s, "%x", intNum);
    return s;
}

char *getHex(short num) {
    char *s = alloc_chars(16);
    sprintf(s, "%x", num);
    return s;
}


char *getHex(double d) {

    char *s = alloc_chars(64);
    sprintf(s, "%llx", double2hexRepr(&d));
    return s;
}


//unsigned  long long
void hex2binaryStr(unsigned int x, char *str) {
    unsigned int xCopy = x;
    for (int i = 0; i < 32; ++i) {
//        从最高位开始
        str[31 - i] = (xCopy & 1) ? '1' : '0';
        xCopy = xCopy >> 1;
//        右移动
    }
}

void doubleHex2binaryStr(unsigned long long x, char *str) {
    unsigned long long xCopy = x;
    for (int i = 0; i < 64; ++i) {
//        从最高位开始
        str[63 - i] = (xCopy & 1) ? '1' : '0';
        xCopy = xCopy >> 1;
//        右移动
    }
}

void printBinaryOfStrKind(char *str) {
    printf("printBinaryOfStrKind\n");

    for (int i = 0; i < 32; ++i) {
        printf("%c", str[i]);
        if (((1 + i) % 4 == 0) && ((1 + i) != 32)) {
            printf("%c", ',');
        }
    }
    printf("\n");

}

void printDoubleBinaryOfStrKind(char *str) {
    printf("printDoubleBinaryOfStrKind\n");

    for (int i = 0; i < 64; ++i) {
        printf("%c", str[i]);
        if (((1 + i) % 4 == 0) && ((1 + i) != 64)) {
            printf("%c", ',');
        }
    }
    printf("\n");

}

#include <algorithm>

std::string binTo16(std::string binStr) {
    binStr=getBinaryFromDirtySentence(binStr);
    int len = binStr.size();
    int toAppend = len % 4;
//    1 --3
//    2---2
//    3---1
//    4--0
//    5--3
//        toAppend=len%4;
    if(toAppend!=0){
        toAppend=4-toAppend;
    }

    std::vector<char> hexes = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    std::vector<std::string> bins = {"0000", "0001", "0010", "0011",
                                     "0100", "0101", "0110", "0111",
                                     "1000", "1001", "1010", "1011",
                                     "1100", "1101", "1110", "1111"};
    binStr=binStr.insert(0, toAppend, '0');
//    std::cout<<"bu ling :"<<binStr<<"\n";
    std::string retHexStr;
    int cnt = 0;
    std::string tmp;
    for (char ch:binStr) {
        cnt++;
        tmp += ch;
        if (cnt == 4) {
            cnt = 0;
//           std::cout<<"tmp: "<<tmp<<"\n";
            int index = std::find(bins.begin(), bins.end(), tmp) - bins.begin();
            retHexStr += hexes[index];
            tmp = "";
        }
    }
    return retHexStr;
}

void showFloatAccuracy() {
//    float f=-1.1;
//    float f2=-1.111;
//    float f3=-1.1111;
//
//    float f4=-1.11111;
    float f5 = -1.11111;
    float f6 = -1.111111;
    float f7 = -1.1111111;
    float f8 = -1.11111111;
    float f9 = -1.111111111;


    printf("打印小数点后面7位\n");
    printf("给出float 小数点后面5个1 %.7f\n", f5);
    printf("给出float 小数点后面6个1 %.7f\n", f6);
    printf("给出float 小数点后面7个1 %.7f\n", f7);
    printf("给出float 小数点后面8个1 %.7f\n", f8);
    printf("给出float 小数点后面9个1 %.7f\n", f9);


    printf("打印小数点后面8位\n");
    printf("给出float 小数点后面5个1 %.8f\n", f5);
    printf("给出float 小数点后面6个1 %.8f\n", f6);
    printf("给出float 小数点后面7个1 %.8f\n", f7);
    printf("给出float 小数点后面8个1 %.8f\n", f8);
    printf("给出float 小数点后面9个1 %.8f\n", f9);


    printf("打印小数点后面9位\n");
    printf("给出float 小数点后面5个1 %.9f\n", f5);
    printf("给出float 小数点后面6个1 %.9f\n", f6);
    printf("给出float 小数点后面7个1 %.9f\n", f7);
    printf("给出float 小数点后面8个1 %.9f\n", f8);
    printf("给出float 小数点后面9个1 %.9f\n", f9);



//    float floatArr[6]={-1.1,-1.111,-1.1111,-1.11111,-1.111111,-1.1111111};
//    for(int i=0;i<6;i++){
//        printf("float %f\n",floatArr[i]);
//    }
}

void showDoubleAccuracy() {

    double d9 = -1.11111111;
    double d10 = -1.111111111;
    double d11 = -1.1111111111;
    double d15 = -1.111111111111111;
    double d16 = -1.1111111111111111;
    double d17 = -1.11111111111111111;
    double d18 = -1.111111111111111111;
    double doubleArr[6] = {-1.11111111, -1.111111111, -1.1111111111,
                           -1.111111111111111, -1.1111111111111111, -1.11111111111111111};
    //  8 ,   15 最后两个16   17 个1
//    一共16位所以double的精度为16，
//    http://www.baidu.com/s?word=double%E7%9A%84%E7%B2%BE%E5%BA%A6&tn=92363592_hao_pg


    printf("打印小数点后面14位\n");
    printf("给出double 小数点后面8个1 %.14f\n", d9);
    printf("给出double 小数点后面9个1 %.14f\n", d10);
    printf("给出double 小数点后面10个1 %.14f\n", d11);
    printf("给出double 小数点后面14个1 %.14f\n", d15);
    printf("给出double 小数点后面15个1 %.14f\n", d16);
    printf("给出double 小数点后面16个1 %.14f\n", d17);

    printf("打印小数点后面15位\n");
    printf("给出double 小数点后面8个1 %.15f\n", d9);
    printf("给出double 小数点后面9个1 %.15f\n", d10);
    printf("给出double 小数点后面10个1 %.15f\n", d11);
    printf("给出double 小数点后面14个1 %.15f\n", d15);
    printf("给出double 小数点后面15个1 %.15f\n", d16);
    printf("给出double 小数点后面16个1 %.15f\n", d17);

    printf("打印小数点后面16位\n");
    printf("给出double 小数点后面8个1 %.16f\n", d9);
    printf("给出double 小数点后面9个1 %.16f\n", d10);
    printf("给出double 小数点后面10个1 %.16f\n", d11);
    printf("给出double 小数点后面14个1 %.16f\n", d15);
    printf("给出double 小数点后面15个1 %.16f\n", d16);
    printf("给出double 小数点后面16个1 %.16f\n", d17);

    printf("打印小数点后面17位\n");
    printf("给出double 小数点后面8个1 %.17f\n", d9);
    printf("给出double 小数点后面9个1 %.17f\n", d10);
    printf("给出double 小数点后面10个1 %.17f\n", d11);
    printf("给出double 小数点后面14个1 %.17f\n", d15);
    printf("给出double 小数点后面15个1 %.17f\n", d16);
    printf("给出double 小数点后面16个1 %.17f\n", d17);

    printf("打印小数点后面18位\n");
    printf("给出double 小数点后面8个1 %.18f\n", d9);
    printf("给出double 小数点后面9个1 %.18f\n", d10);
    printf("给出double 小数点后面10个1 %.18f\n", d11);
    printf("给出double 小数点后面14个1 %.18f\n", d15);
    printf("给出double 小数点后面15个1 %.18f\n", d16);
    printf("给出double 小数点后面16个1 %.18f\n", d17);
    printf("给出double 小数点后面17个1 %.18f\n", d18);

//
//    printf("打印小数点后面14位\n");
//    printf("给出double 9 位有效数字 %.14f\n",d9);
//    printf("给出double 10 位有效数字 %.14f\n",d10);
//    printf("给出double 11 位有效数字 %.14f\n",d11);
//    printf("给出double 15 位有效数字 %.14f\n",d15);
//    printf("给出double 16 位有效数字 %.14f\n",d16);
//    printf("给出double 17 位有效数字 %.14f\n",d17);

//    printf("打印小数点后面15位\n");
//    printf("给出double 9 位有效数字 %.15f\n",d9);
//    printf("给出double 10 位有效数字 %.15f\n",d10);
//    printf("给出double 11 位有效数字 %.15f\n",d11);
//    printf("给出double 15 位有效数字 %.15f\n",d15);
//    printf("给出double 16 位有效数字 %.15f\n",d16);
//    printf("给出double 17 位有效数字 %.15f\n",d17);
//
//    printf("打印小数点后面16位\n");
//    printf("给出double 9 位有效数字 %.16f\n",d9);
//    printf("给出double 10 位有效数字 %.16f\n",d10);
//    printf("给出double 11 位有效数字 %.16f\n",d11);
//    printf("给出double 15 位有效数字 %.16f\n",d15);
//    printf("给出double 16 位有效数字 %.16f\n",d16);
//    printf("给出double 17 位有效数字 %.16f\n",d17);
//
//    printf("打印小数点后面17位\n");
//    printf("给出double 9 位有效数字 %.17f\n",d9);
//    printf("给出double 10 位有效数字 %.17f\n",d10);
//    printf("给出double 11 位有效数字 %.17f\n",d11);
//    printf("给出double 15 位有效数字 %.17f\n",d15);
//    printf("给出double 16 位有效数字 %.17f\n",d16);
//    printf("给出double 17 位有效数字 %.17f\n",d17);

//    for(int i=0;i<6;i++){
//        printf("double %.15lf\n",doubleArr[i]);
//    }
//
//
//    printf("小数点后面16位\n");
//    for(int i=0;i<6;i++){
//        printf("double %.16lf\n",doubleArr[i]);
//    }
//
//
//     printf("小数点后面17位\n");
//    for(int i=0;i<6;i++){
//        printf("double %.17lf\n",doubleArr[i]);
//    }
//
//    printf("小数点后面18位\n");
//    for(int i=0;i<6;i++){
//        printf("double %.18lf\n",doubleArr[i]);
//    }
}

/* strutil 有 实现
void printSomeWhat(int howMany, char what) {
    for (int i = 0; i < howMany; i++) {
        printf("%c", what);
    }
}
*/

void howManyNumbers() {
    char num[] = "1111111111111111";
    printf("len %d\n", strlen(num));
}

int getIndex(char *hex, char toFind) {
    int len = strlen(hex);
    for (int i = 0; i < len; i++) {
        if (hex[i] == toFind) {
            return i;
        }
    }
    return -1;
}

//
//void printBins(int len){
//    const char* hexToBin[]={"0000","0001","0010","0011",
//                            "0100","0101","0110","0111",
//                            "1000","1001","1010","1011",
//                            "1100","1101","1110","1111"};
//
//    char hex[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
//    printf("hex %s\n",hexStr);
//    printf("binary: ");
//    for(int i=0;i<len;i++){
//        printf("%s,",hexToBin[getIndex(hex,hexStr[i])]);
//    }
//}

void printBinFromHexStr(const char *hexStr) {
    const char *hexToBin[] = {"0000", "0001", "0010", "0011",
                              "0100", "0101", "0110", "0111",
                              "1000", "1001", "1010", "1011",
                              "1100", "1101", "1110", "1111"};

    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    int len = strlen(hexStr);
    printf("hex: 0x%s\n", hexStr);
    printf("binary: ");
    for (int i = 0; i < len; i++) {

        char toFind = hexStr[i];
        if (isupper(toFind)) {
            toFind = tolower(toFind);
        }
//      std::cout<<"toFind: "<<toFind<<"\n";
        int index = getIndex(hex, toFind);

        printf("%s ", hexToBin[index]);
    }
    printf("\n");
}

/**
 * 把一个16进制str转换成二进制，打印出来，用“,”分隔开，比较看得清楚，每4个分隔一个
 * @param hexStr
 */
void printBinFromHexStr(std::string hexStr) {
    const char *hexToBin[] = {"0000", "0001", "0010", "0011",
                              "0100", "0101", "0110", "0111",
                              "1000", "1001", "1010", "1011",
                              "1100", "1101", "1110", "1111"};

    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    int len = hexStr.size();
//    printf("hex %s\n",hexStr);

    std::cout << "hex : 0x" << hexStr << "\n";
    printf("binary: ");
    for (int i = 0; i < len; i++) {
        char toFind = hexStr[i];
        if (isupper(toFind)) {
            toFind = tolower(toFind);
        }
//      std::cout<<"toFind: "<<toFind<<"\n";
        int index = getIndex(hex, toFind);
//        std::cout<<"index: "<<index<<"\n";
        printf("%s ", hexToBin[index]);
    }
}

/**
 * 计算float的二进制的1.M 的 M部分的这串二进制串的十进制是多少
 * @param afterDotNumStr
 * @return
 */
double calAfterDot(const std::string &afterDotNumStr) {
    std::vector<double> toMultis;
//    todo
    int len = afterDotNumStr.length();
    double num = 0.5;
    for (int i = 0; i < len; i++) {
        toMultis.emplace_back(num);
        num /= 2;
    }
    double outData = 0;
    int i = 0;
    for (char ch:afterDotNumStr) {
        outData += toMultis[i] * (ch - '0');
        i++;
    }
    return outData;
}

/**
 * 打印一个float 的二进制
 * @param f
 */
void printBin(float f) {
    printf("float : %f\n",f);
    printBinFromHexStr(getHex(f));
}

void printBin(int intNum) {
    printf("int : %d\n",intNum);
    printBinFromHexStr(getHex(intNum));
}

void printBin(short num){
    printf("short : %hd\n", num);
    printBinFromHexStr(getHex(num));
}

void getHexArr() {
    for (int i = 0; i < 10; i++) {
        printf("'%d',", i);
    }
    for (char i = 'a'; i <= 'f'; i++) {
        printf("'%c',", i);
    }
}

void printSomeBitCal(int x,int y){

    printf("x: %d\n",x);
    printf("y: %d\n",y);
    printf("x^y: %#x\n",x^y);
    printf("x&y: %#x\n",x&y);
    printf("x|y: %#x\n",x|y);
    printf("~x|~y: %#x\n",~x|~y);
    printf("x&!y: %#x\n",x&!y);
    printf("x&&y: %#x\n",x&&y);
    printf("x || y: %#x\n",x || y);
    printf("!x || !y: %#x\n",!x || !y);
    printf("x&&~y: %#x\n",x&&~y);
    printf("--------------------------------\n\n");

}