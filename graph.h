#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<iostream>
#include<fstream>
#include<windows.h>
#include "conio.h"
using namespace std;


#define MAX_STATION 429
class Station{
public:
   int stn_num;
   char stn_name[100];
   int stn_time;
   Station* next;
   Station() :next(NULL){};
   Station(int num, int time, char name[100])
      :stn_num(num), stn_time(time), next(NULL){
      strcpy_s(stn_name, name);
   }
};

class Map{
public:
   char stn_name[10];
   Station* stn;
   bool* visited;
   int* dist;
};

#endif