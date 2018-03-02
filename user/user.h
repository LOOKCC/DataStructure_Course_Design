#ifndef USER_H_
#define USER_H_
#include "set.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class user{
private:
	set* fans;
	set* follows;
	set* friends;
	int NO;
public:
	string name;
	int Set_NO(int x);
	int Get_NO();
	set* Get_fans();
	set* Get_friends();
	set* Get_follows();
	user();
	~user();
	int Destory();
	int Insert_follows(int x);
	int Insert_fans(int x);
	int Insert_friends(int x);
	int Delete_follows(int x);
	int Delete_fans(int x);
	int Delete_friends(int x);
	int Search_follows(int x);
	int Search_fans(int x);
	int Search_friends(int x);
	int Read();
	int Save();
	int Same_follows(user &a);
	int Second_friends();
	int Same_level(user &a);
	int print();
}


#endif
