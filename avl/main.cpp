#include<iostream>
#include<fstream>
#include<string>
#include"avl.h"
using namespace std;
typedef struct tree_node{
	AVL_tree* tree_info;
	struct tree_node* next;
}tree_node;
void man();
int init(string infor,tree_node** head);
int destory(string infor, tree_node** head);
int insert(string infor, tree_node** head);
int deleted(string infor, tree_node** head);
int print(string infor, tree_node** head);
int find(string infor, tree_node** head);
tree_node* in_list(string name, tree_node* head);
tree_node* insert_tail(tree_node* newnode, tree_node* head);
void delete_list(tree_node* head);
string process(string str);

int main(){
	//instructions
	cout<<"It's a code or interactive shell for set"<<endl;
	cout<<"Version 0.0"<<endl;
	cout<<"Please input which mode do you want use, 1 is shell, 0 is code."<<endl;
	int mode;                   //use shell mode or code mode
	cin>>mode;                  //get mode
	string temp;                //the command to read
	string garbage;             //read a garbage enter
	string filename;            //code mode filename
	ifstream fin;               //code mode file
	tree_node* head = NULL;
	getline(cin,garbage);
	if (mode == 1){
		cout<<">>> ";
		getline(cin,temp);
	}
	else{
		cout<<"Please input the file name"<<endl;
		cin>>filename;
		fin.open(filename);
		if(!fin){
			cout<<"file open fail"<<endl;
			return 0;
		}
		getline(fin,temp);
	}
	while(temp != "exit"){
		//cout<<temp<<endl;
		temp = process(temp);
		int pos;
		pos = temp.find_first_of(" ");
		string Operator = temp.substr(0,pos);
		string infor = temp.substr(pos+1,temp.length()-pos-1);
		if(Operator == "man"){
			man();
		}
		else if(Operator == "init"){
			init(infor,&head);
		}
		else if(Operator == "destory"){
			destory(infor,&head);
		}
		else if(Operator == "insert"){
			insert(infor,&head);
		}
		else if(Operator == "delete"){
			deleted(infor,&head);
		}
		else if(Operator == "print"){
			print(infor,&head);
		}
		else if(Operator == "find"){
			if(find(infor,&head) == 1)
				cout<<"yes"<<endl;
			else
				cout<<"no"<<endl;
		}
		else{
			cout<<"can 't analysis shell"<<endl;
		}
		if(mode == 1){
			cout<<">>> ";
			getline(cin,temp);	
		}else{
			getline(fin,temp);
		}
	}
	delete_list(head);
	return 0;
}

string process(string str){
	while(str[0] == ' '){
		str = str.erase(0,1);
	}
	while(str[str.length()-1] == ' '){
		str = str.erase(str.length()-1,1);
	}
	int flag = 0;
	for(int i = 0; i < int(str.length()); ){
		if(str[i] == ' '){
			if(flag == 0){
				flag = 1;
				i++;
			}else{
				str = str.erase(i,1);
			}
		}else{
			flag =0;
			i++;
		}
	}
	return str;
} 
void man(){
	cout<<"init a //初始化一个名为a的AVL"<<endl;
	cout<<"destory b //销毁一个名为b的AVL"<<endl;
	cout<<"insert a 1 2 //向AVLa中添加元素1和2"<<endl;
	cout<<"delete a 3 //在AVLa中删除元素3"<<endl;
	cout<<"print a //打印AVLa中的元素"<<endl;
	cout<<"find a 3 //3是否在AVLa中"<<endl;
}
int init(string infor,tree_node** head){
	if(in_list(infor, *head) != NULL){
		cout<<infor<<" is already in the list, please change a name."<<endl;
		return 0;
	}else{
		AVL_tree* newavl = new AVL_tree;
		newavl->name = infor;
		tree_node* newnode = new tree_node;
		newnode->tree_info = newavl;
		newnode->next = NULL;
		*head = insert_tail(newnode, *head);
	}
	return 1;
}
int destory(string infor, tree_node** head){
	tree_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		tree_node* temp = *head;
		tree_node* to_delete = NULL;
		if(temp->tree_info->name == infor){
			to_delete = temp;
			*head = temp->next;
		}
		else{
			while(temp->next != NULL){
				if(temp->next->tree_info->name == infor)
					break;
				temp = temp->next;
			}
			to_delete = temp->next;
			temp->next = temp->next->next;
		}
		to_delete->tree_info->Destory();
		delete to_delete;
		return 1;
	}
}
//insert a 1 3 4
int insert(string infor, tree_node** head){
	int pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	tree_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<name<<" in list"<<endl;
		return 0;
	}
	pos = temp.find_first_of(" ");
	while(pos != int(string::npos)){
		string number = temp.substr(0,pos);
		node->tree_info->Insert(stoi(number));
		temp = temp.substr(pos+1,infor.length()-pos-1);
		pos = temp.find_first_of(" ");
	}
	node->tree_info->Insert(stoi(temp));
	return 1;
}
//delete b 1 2 3
int deleted(string infor, tree_node** head){
	int pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	tree_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}
	pos = temp.find_first_of(" ");
	while(pos != int(string::npos)){
		string number = temp.substr(0,pos);
		node->tree_info->Delete(stoi(number));
		temp = temp.substr(pos+1,infor.length()-pos-1);
	}
	node->tree_info->Delete(stoi(temp));
	return 1;
}
int print(string infor, tree_node** head){
	tree_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->tree_info->Pre_Traverse();
		node->tree_info->In_Traverse();
		node->tree_info->Af_Traverse();
		return 1;
	}
}
int find(string infor, tree_node** head){
	int pos;
	pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	tree_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<name<<" in list"<<endl;
		return 0;
	}else{
		if(node->tree_info->Search(stoi(temp))){
			return 1;
		}
		else{
			return 0;
		}
	}
}
tree_node* in_list(string name, tree_node* head){
	tree_node* node = head;
	while(node != NULL){
		if(node->tree_info->name == name)
			return node;
		node = node->next;
	}
	return NULL;
}
tree_node* insert_tail(tree_node* newnode, tree_node* head){
	if(head == NULL){
		head = newnode;
	}else{
		tree_node* node = head;
		while(node->next != NULL){
			node = node->next;
		}
		node->next = newnode;
	}
	return head;
}
void delete_list(tree_node* head){
	tree_node* temp = head;
	while(temp != NULL){
		tree_node* to_delete = temp;
		temp = temp->next;
		delete to_delete;
	}
}