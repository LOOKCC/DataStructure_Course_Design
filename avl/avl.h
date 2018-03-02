#ifndef AVL_H_
#define AVL_H_
#include<string>
using namespace std;
typedef struct AVL_node{
	struct AVL_node* leftchildren;
	struct AVL_node* rightchildren;
	int height;
	int value;
}AVL_node;
typedef struct information{
	int data;
	struct information* next;
}information;
class AVL_tree{
private:
	AVL_node* root;
	void Traverse(AVL_node* node);
	AVL_node* Search(AVL_node* node, int x);
	AVL_node* LL_rotation(AVL_node* node);
	AVL_node* LR_rotation(AVL_node* node);
	AVL_node* RL_rotation(AVL_node* node);
	AVL_node* RR_rotation(AVL_node* node);
	int max(int x, int y);
	int Height(AVL_node* node);
	AVL_node* Insert(AVL_node* node, int x);
	AVL_node* Delete(AVL_node* node, int x);
	AVL_node* maximum(AVL_node* node);
	AVL_node* minimum(AVL_node* node);
	void Destory(AVL_node* node);
public:
	string name;
	AVL_tree();
	~AVL_tree();
	int Search(int x);
	int Destory();
	int Insert(int x);
	int Delete(int x);
	void Traverse();
	int Height();
	AVL_node* Get_root();
	information* to_array_recursive(information* head,AVL_node* node);
};
#endif