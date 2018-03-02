#include "set.h"
#include <iostream>
#include <fstream>
using namespace std;

set::set(){
	this->data = new AVL_tree;
	this->len = 0;
}
set::~set(){
	destory();
}
int set::init(string name){
	this->name = name;
	this->len = 0;
	return 1;
}
int set::destory(){
	if(this->len == -1)
		return 0;
	this->data->Destory();
	this->len = -1;
	this->name = "";
	//delete this->data;
	return 1;
}
void set::add(set &a,set &b){
	information* a_info = a.to_array();
	information* b_info = b.to_array();
	for(int i = 0; i < a.length(); i++){
		this->insert(a_info->data);
		a_info = a_info->next;
	}
	for(int i = 0; i < b.length(); i++){
		this->insert(b_info->data);
		b_info = b_info->next;
	}
	delete_infor(a_info);
	delete_infor(b_info);
}
void set::cross(set &a,set &b){
	information* a_info = a.to_array();
	for(int i = 0; i < a.length(); i++){
		if(b.find(a_info->data))
			this->insert(a_info->data);
		a_info = a_info->next;
	}
	delete_infor(a_info);
}
void set::minus(set &a,set &b){
	information* a_info = a.to_array();
	for(int i = 0; i < a.length(); i++){
		if(!b.find(a_info->data))
			this->insert(a_info->data);
		a_info = a_info->next;
	}
	delete_infor(a_info);
}
int set::length(){
	return this->len;
}
int set::find(int x){
	if(data->Search(x) == 0){
		return 0;
	}else{
		return 1;
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
}
int set::sub(set &a){
	int flag = 1;
	information* a_info = a.to_array(); 
	for(int i = 0; i < a.length(); i++){
		if(this->find(a_info->data) != 1){
			flag = 0;
			break;
		}
		a_info = a_info->next;
	}
	delete_infor(a_info);
	if(flag)
		return 1;
	else
		return 0;
}
int set::equal(set &a, set &b){
	if(a.length() != b.length())
		return 0;
	information* a_info = a.to_array();
	information* b_info = b.to_array();
	int flag = 1;
	for(int i = 0; i < a.length(); i++){
		if(a_info->data != b_info->data){
			flag = 0;
			break;
		}
		a_info = a_info->next;
		b_info = b_info->next;
	}
	delete_infor(a_info);
	delete_infor(b_info);
	if(flag)
		return 1;
	else
		return 0;
}
void set::print(){
	this->data->Traverse();
}
int set::insert(int x){
	int result = this->data->Insert(x);
	if(result){
		this->len++;
		return 1;
	}
	else
		return 0;
}
int set::Delete(int x){
	int result = this->data->Delete(x);
	if(result){
		this->len--;
		return 1;
	}
	else
		return 0;
}
information* set::to_array(){
	information* head = NULL;
	head = this->data->to_array_recursive(head,this->data->Get_root());
	return head;
}
int set::save(string filename){
	if(this->len == -1)
		return 0;
	information* info = to_array();
	ofstream fout(filename);
	fout<<this->name<<" "<<length()<<" "<<info->data;
	for(int i = 1; i < length(); i++){
		fout<<" "<<info->data;
		info = info->next;
	}
	delete_infor(info);
	return 1;
}
int set::read(string filename){
	if(this->len == -1)
		return 0;
	string name;
	int len;
	ifstream fin(filename);
	fin>>name>>len;
	this->name = name;
	for(int i = 0; i < len; i++){
		int a;
		fin>>a;
		insert(a);
	}
	return 1;
}
void set::delete_infor(information* head){
	information* temp = head;
	while(temp != NULL){
		information* to_delete = temp;
		temp = temp->next;
		delete to_delete;
	}
}







//name length { 1 2 3 4 5 }
