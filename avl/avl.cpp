#include "avl.h"
#include<iostream>
using namespace std;
int AVL_tree::Height(){
	return Height(this->root);
}
int AVL_tree::Height(AVL_node* node){
	if(node == NULL){
		return 0;
	}else{
		return max(Height(node->leftchildren),Height(node->rightchildren))+1;
		//return node->height;
	}
}
int AVL_tree::max(int x, int y){
	if(x > y)
		return x;
	else
		return y;
}
AVL_node* AVL_tree::LL_rotation(AVL_node* node){
	AVL_node* temp = node->leftchildren;
	node->leftchildren  = temp->rightchildren;
	temp->rightchildren = node;
	node->height = max(Height(node->leftchildren),Height(node->rightchildren)) + 1;
	temp->height = max(Height(temp->leftchildren),Height(temp->rightchildren)) + 1;
	return temp;
}
AVL_node* AVL_tree::LR_rotation(AVL_node* node){
	node->leftchildren = RR_rotation(node->leftchildren);
	return LL_rotation(node);
}
AVL_node* AVL_tree::RL_rotation(AVL_node* node){
	node->rightchildren = LL_rotation(node->rightchildren);
	return RR_rotation(node);
}
AVL_node* AVL_tree::RR_rotation(AVL_node* node){
	AVL_node* temp = node->rightchildren;
	node->rightchildren  = temp->leftchildren;
	temp->leftchildren = node;
	node->height = max(Height(node->leftchildren),Height(node->rightchildren)) + 1;
	temp->height = max(Height(temp->leftchildren),Height(temp->rightchildren)) + 1;
	return temp;	
}
int AVL_tree::Insert(int x){
	if(Search(x)){ 
		cout<<x<<" is already in the tree"<<endl;
		return  0;
	}else{
		this->root = Insert(this->root,x);
		return 1;	
	}
}
AVL_node* AVL_tree::Insert(AVL_node* node, int x){
	if(node == NULL){
		node = new AVL_node;
		node->value = x;
		node->height = 0;
		node->leftchildren = NULL;
		node->rightchildren = NULL;
		if(node == NULL){
			cout<<"no space"<<endl;
			return NULL;
		}
	}else if(x < node->value){
		node->leftchildren = Insert(node->leftchildren, x);
		if(Height(node->leftchildren) - Height(node->rightchildren) == 2){
			if(x < node->leftchildren->value)
				node = LL_rotation(node);
			else
				node = LR_rotation(node);
		}
	}else if(x > node->value){
		node->rightchildren = Insert(node->rightchildren, x);
		if(Height(node->rightchildren) - Height(node->leftchildren) == 2){
			if(x > node->rightchildren->value)
				node = RR_rotation(node); 
			else
				node = RL_rotation(node);
		}
	}else{
		;//cout<<x<<" is already in the tree"<<endl;
	}
	node->height = max(Height(node->leftchildren),Height(node->rightchildren)) + 1;
	return node;		
}
int AVL_tree::Delete(int x){
	if(Search(x)){
		this->root = Delete(this->root,x);
		return  1;
	}
	cout<<x<<" delete failled."<<endl;
	return 0;
}
AVL_node* AVL_tree::Delete(AVL_node* node, int x){
	if(node == NULL)
		return NULL;
	if(x < node->value){
		node->leftchildren = Delete(node->leftchildren, x);
		if(Height(node->rightchildren) - Height(node->leftchildren) == 2){
			AVL_node* temp = node->rightchildren;
			if(Height(temp->rightchildren) > Height(temp->leftchildren))
				node = RR_rotation(node);
			else
				node = RL_rotation(node);
		}
	}else if(x > node->value){
		node->rightchildren = Delete(node->rightchildren, x);
		if(Height(node->leftchildren) - Height(node->rightchildren) == 2){
			AVL_node* temp = node->leftchildren;
			if(Height(temp->leftchildren) > Height(temp->rightchildren))
				node = LL_rotation(node);
			else
				node = LR_rotation(node);
		}
	}else{
		if(node->leftchildren != NULL && node->rightchildren != NULL){
			if(Height(node->leftchildren) > Height(node->rightchildren)){
				AVL_node* max = maximum(node->leftchildren);
				node->value = max->value;
				node->leftchildren = Delete(node->leftchildren,max->value); 
			}else{
				AVL_node* min = minimum(node->rightchildren);
				node->value = min->value;
				node->rightchildren = Delete(node->rightchildren,min->value);
			}
		}else{
			AVL_node* temp = node;
			if(node->leftchildren == NULL)
				node = node->rightchildren;
			else
				node = node->leftchildren;
			delete temp; 
		}
	}
	return node;
}
AVL_node* AVL_tree::maximum(AVL_node* node){
	if(node == NULL)
		return NULL;
	while(node->rightchildren != NULL){
		node = node->rightchildren;
	}
	return node;
}
AVL_node* AVL_tree::minimum(AVL_node* node){
	if(node == NULL)
		return NULL;
	while(node->leftchildren != NULL){
		node = node->leftchildren;
	}
	return node;
}
void AVL_tree::Traverse(){
	Traverse(this->root);
	cout<<endl;
}
void AVL_tree::Traverse(AVL_node* node){
	if(node == NULL)
		return ;
	Traverse(node->leftchildren);
	cout<<node->value<<" ";
	Traverse(node->rightchildren);
}
int AVL_tree::Destory(){
	Destory(this->root);
	return 1;
}
void AVL_tree::Destory(AVL_node* node){
	if(node == NULL){
		return ;
	}else{
		Destory(node->leftchildren);
		Destory(node->rightchildren);
		delete node;
		return ;
	}
}
int AVL_tree::Search(int x){
	if(Search(this->root,x) != NULL)
		return 1;
	else
		return 0;
}
AVL_node* AVL_tree::Search(AVL_node* node, int x){
	if(node == NULL)
		return NULL;
	if(node->value == x)
		return node;
	AVL_node* left = Search(node->leftchildren, x);
	AVL_node* right = Search(node->rightchildren, x);
	if(left == NULL && right == NULL)
		return NULL;
	if(left != NULL && right == NULL)
		return left;
	if(left == NULL && right != NULL)
		return right;
	return NULL;
}
AVL_tree::AVL_tree(){
	this->name = "";
	this->root = NULL;
}
AVL_tree::~AVL_tree(){
	Destory();
}
information* AVL_tree::to_array_recursive(information* head,AVL_node* node){
	if(node == NULL)
		return head;
	head = to_array_recursive(head,node->leftchildren);
	information* newnode = new information;
	newnode->data = node->value;
	newnode->next = NULL;
	if(head == NULL){
		head = newnode;
	}else{
		information* temp = head;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	head = to_array_recursive(head,node->rightchildren);
	return head;
}
AVL_node* AVL_tree::Get_root(){
	return this->root;
}