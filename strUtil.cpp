//
// Created by Lenovo on 2020/10/22.
//

// codeThinking.cpp : 定义控制台应用程序的入口点。
//
//https://www.cnblogs.com/zpcoding/p/10645726.html
//#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <cstring>
#include<unordered_map>

using namespace std;

vector<string> split(const string& s, const string& seperator) {
    vector<string> result;
    unsigned int posBegin = 0;
    unsigned int posSeperator = s.find(seperator);

    while (posSeperator != s.npos) {
        result.push_back(s.substr(posBegin, posSeperator - posBegin));//
        posBegin = posSeperator + seperator.size(); // 分隔符的下一个元素
        posSeperator = s.find(seperator, posBegin);
    }
    if (posBegin != s.length()) // 指向最后一个元素，加进来
        result.push_back(s.substr(posBegin));

    return result;
}

void splitTest(const string& str,string& symbol) {
    vector<string> result;
    result = split(str, symbol);
    for (auto & i : result) {
        cout <<atoi(i.c_str())<< endl;  // 把数字字符串转换为 数字
    }
}
//https://blog.csdn.net/qq_44733706/article/details/100799773
std::string getSths(const string& str ,int(*isSthFunc)(int)){
    string outStr;
    for(char ch:str){
        if(isSthFunc(ch)){
            outStr+=ch;
        }
    }
    return outStr;
}

std::string getNums(const string& str){
//    http://c.biancheng.net/ref/4.html
//    isdigit('1');
    return   getSths(str,isdigit);
}
/*std::string getNums(const string& str){
    string outStr;
    for(char ch:str){
        if(isdigit(ch)){
            outStr+=ch;
        }
    }
    return outStr;
}*/
int  isHex(int ch){
    return isdigit(ch)||(ch>='a'&&ch<='f')||(ch>='A'&&ch<='F');
}
std::string getHexes(const string& str){
    return  getSths(str,isHex);
/*    string outStr;
    for(char ch:str){
        if(isHex(ch)){
            outStr+=ch;
        }
    }
    return outStr;*/
}

std::string replace(std::string oldStr,const std::string& dontWant,const std::string& toBe){
    int len=oldStr.length();
    int dontWantLen=dontWant.length();
//    https://www.cnblogs.com/wkfvawl/p/9429128.html
    for(int i=0;i<len;){
        int pos=oldStr.find(dontWant,i);
        if(pos==string::npos)break;
        oldStr=oldStr.replace(pos,dontWantLen,toBe);
        i+=dontWantLen;
    }
    return oldStr;
}
/*

 void stringSamePart(const std::string& a,const std::string& b){
    int aLen=a.length();
    int bLen=b.length();

}
*/

#include <iostream>
#include <string>
using namespace std;

#include "StringInfo.h"
vector<StringInfo> maxCommonSubstrInfo(const string& s1, const string& s2)
{
    string s3 = (s1.length() <= s2.length())?s1:s2;
    string s4 = (s1.length() <= s2.length())?s2:s1;
    int m = s3.length();
    int n = s4.length();
    int **dp = new int*[m+1];
    for(int i = 0; i < m+1; i++)
    {
        dp[i] = new int[n+1];
        for(int j = 0; j < n+1; j++)
            dp[i][j] = 0;
    }
    int start = 0, maxlen = 0;
    for(int i = 1; i < m+1; i++)
    {
        for(int j = 1; j < n+1; j++)
        {
            if(s3[i-1] == s4[j-1])
            {
                dp[i][j] = dp[i-1][j-1]+1;
                if(dp[i][j] > maxlen)
                {
                    maxlen = dp[i][j];
                    start = i - maxlen;
                }
            }
        }
    }
    for(int i = 0; i < m+1; i++)
    {
        delete dp[i];
        dp[i] = nullptr;
    }
    delete [] dp;
    dp = nullptr;
    string substr=s3.substr(start,maxlen);
    int pos=s4.find(substr);
    vector<StringInfo>v;
    v.emplace_back( StringInfo(start,maxlen,s3));
    v.emplace_back(StringInfo(pos,maxlen,s4));
    return v;
//    return s3.substr(start, maxlen);
}

//https://blog.csdn.net/na_beginning/article/details/64921406
string maxCommonSubstr(const string& s1, const string& s2)
{
//    std::move函数可以以非常简单的方式将左值引用转换为右值引用。
//    https://blog.csdn.net/p942005405/article/details/84644069/
//    C++ 标准库使用比如vector::push_back 等这类函数时,会对参数的对象进行复制,连数据也会复制.这就会造成对象内存的额外创建, 本来原意是想把参数push_back进去就行了,通过std::move，可以避免不必要的拷贝操作。
//    std::move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝所以可以提高利用效率,改善性能.。
//    对指针类型的标准库对象并不需要这么做.
    auto stringInfos=  maxCommonSubstrInfo(s1,s2);
   auto stringInfo=stringInfos[0];
    return   stringInfo.getStr().substr(stringInfo.getStartIndex(),stringInfo.getLen());
//    return s3.substr(start, maxlen);

}

std::string formatStr(const std::string& str,int every,char putWhat){
    std::string outStr;
    int cnt=0;
    for(char ch:str){
        cnt++;
        if(cnt==every){
            outStr+=ch;
            outStr+=putWhat;
            cnt=0;
        }else{
            outStr+=ch;
        }

    }
    return outStr;
}
void printSomeWhat(int howMany, char what) {
    for (int i = 0; i < howMany; i++) {
        printf("%c", what);
    }
}

void showStrInfo(const StringInfo& stringInfo){
    const string& string1=stringInfo.getStr();
    cout<<string1<<"\n";
    int index=stringInfo.getStartIndex();
    //index ==9 ,because the first is 0, so we print 9 ' ',then the next
//    is the index==9 thing
    printSomeWhat(index,' ');
    cout<<"^";
   int len=stringInfo.getLen();
   // -2 means we cut the head and tail ^
    printSomeWhat(len-2,' ');
    cout<<"^"<<"\n";
    cout<<stringInfo<<"\n";

    cout<<"substr: "<<string1.substr(index,len)<<"\n";
}
//对齐
void showTwoStrsAlign(vector<StringInfo> stringInfos){
    int index0=stringInfos[0].getStartIndex();
    int index1=stringInfos[1].getStartIndex();
    if(index0<index1){
        int maxIndex=index1;
//        比较长 1
        int preBlankNum=maxIndex-index0;
        printSomeWhat(preBlankNum,' ');
        cout<<stringInfos[0].getStr()<<"\n";
        cout<<stringInfos[1].getStr()<<"\n";
        printSomeWhat(maxIndex,' ');
        cout<<"^";
        printSomeWhat(stringInfos[0].getLen()-2,' ');
        cout<<"^\n";
    }
    else{
        int maxIndex=index0;
//        比较长 1
        int preBlankNum=maxIndex-index1;

        cout<<stringInfos[0].getStr()<<"\n";
        printSomeWhat(preBlankNum,' ');
        cout<<stringInfos[1].getStr()<<"\n";
        printSomeWhat(maxIndex,' ');
        cout<<"^";
        printSomeWhat(stringInfos[0].getLen()-2,' ');
        cout<<"^\n";
    }


}
void testMaxCommonSubstr()
{
    string s1, s2;
    while(cin >> s1 >> s2)
    {
      auto strInfos=  maxCommonSubstrInfo(s1, s2);
//        showStrInfo(strInfos[0]);
//        showStrInfo(strInfos[1]);
        showTwoStrsAlign(strInfos);
//        cout << maxCommonSubstrInfo(s1, s2) << endl;
    }
}




std::vector<std::string> getSthsFromVector(const std::vector<std::string>&v,std::string  (getSthFunc)(const string&)){
    std::vector<std::string>outVector;
    for(const string& val:v){
        outVector.emplace_back(getSthFunc(val));
    }
    return outVector;
}
std::vector<std::string> getNumsFromVector(const std::vector<std::string>&v){
    return getSthsFromVector(v,getNums);
    /*std::vector<std::string>outVector;
    for(const string& val:v){
        outVector.emplace_back(getNums(val));
    }
    return outVector;*/
}

std::vector<std::string> getHexesFromVector(const std::vector<std::string>&v){
    return getSthsFromVector(v,getHexes);
/*    std::vector<std::string>outVector;
    for(const string& val:v){
        outVector.emplace_back(getNums(val));
    }
    return outVector;*/
}
//int _tmain(int argc, _TCHAR* argv[])
//{
//    string widths = "5 5 5 5 5 5 10 10 10 10 10 10 10 10 10 10 10 10 5 5 5 5 5 5 5 5";
//    string symbol = " ";
//
//    splitTest(widths,symbol);
//
//
//    system("pause");
//    return 0;
//}
//
