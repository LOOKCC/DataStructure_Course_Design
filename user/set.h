#ifndef SET_H_
#define SET_H_
#include "avl.h"
#include <string>
using namespace std;
class set{
private:
	AVL_tree* data;
	int len;
	int NO;
	void delete_infor(information* head);
public:
	void set_NO(int x);
	int get_NO();
	string name;
	information* to_array();
	void add(set &a, set &b);
	void add(set &a);
	void minus(set &a, set &b);
	void minus(set &a);
	void cross(set &a, set &b);
	void cross(set &a);
	int length();
	int find(int x);
	int sub(set &a);
	int equal(set &a,set &b);
	void print();
	int insert(int x);
	int Delete(int x);
	set();
	~set();
	int init(string name);
	int destory();
	int save(string filename);
	int read(string filename);
};
#endif