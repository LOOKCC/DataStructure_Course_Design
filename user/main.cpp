#include<iostream>
#include<fstream>
#include<string>
#include"set.h"
using namespace std;
typedef struct user_node{
	user* user_info;
	struct user_node* next;
}user_node;
void man();
int init(string infor,user_node** head);
int destory(string infor, user_node** head);
int insert(string infor, user_node** head);
int deleted(string infor, user_node** head);
int print(string infor, user_node** head);
int save(string infor, user_node** head);
int read(string infor, user_node** head);
int find(string infor, user_node** head);
user_node* in_list(string name, user_node* head);
user_node* insert_tail(user_node* newnode, user_node* head);
void delete_list(user_node* head);
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
	user_node* head = NULL;
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
		else if(Operator == "save"){
			save(infor,&head);
		}
		else if(Operator == "read"){
			read(infor,&head);
		}
		else if(Operator == "cal"){
			cal(infor,&head);
		}
		else if(Operator == "len"){
			cout<<len(infor,&head)<<endl;	
		}
		else if(Operator == "find"){
			if(find(infor,&head) == 1)
				cout<<"yes"<<endl;
			else
				cout<<"no"<<endl;
		}
		else if(Operator == "sub"){
			if(sub(infor,&head) == 1)
				cout<<"yes"<<endl;
			else
				cout<<"no"<<endl;
		}
		else if(Operator == "equal"){
			if(equal(infor,&head) == 1)
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
	for(int i = 0; i < str.length(); ){
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
	cout<<"init a //初始化一个名为a的集合"<<endl;
	cout<<"destory b //销毁一个名为b的集合"<<endl;
	cout<<"insert a 1 2 //向集合a中添加元素1和2"<<endl;
	cout<<"delete a 3 //在集合a中删除元素3"<<endl;
	cout<<"print a //打印集合a中的元素"<<endl;
	cout<<"cal c=a+b //求集合a和b的并"<<endl;
	cout<<"cal c=a*b //求集合a和b的交"<<endl;
	cout<<"cal c=a-b //求集合a和b的差"<<endl;
	cout<<"len a //求集合a的长度"<<endl;
	cout<<"find a 3 //3是否在集合a中"<<endl;
	cout<<"sub a b //b是否为a的子集"<<endl;
	cout<<"equal a b //a和b是否相等"<<endl;
	cout<<"save a //将集合a存到文件名为a.set的文件里"<<endl;
	cout<<"read d //读取集合d.set"<<endl;
}
int init(string infor,user_node** head){
	if(in_list(infor, *head) != NULL){
		cout<<infor<<" is already in the list, please change a name."<<endl;
		return 0;
	}else{
		set* newset = new set;
		newset->name = infor;
		user_node* newnode = new user_node;
		newnode->user_info = newset;
		newnode->next = NULL;
		*head = insert_tail(newnode, *head);
	}
	return 1;
}
int destory(string infor, user_node** head){
	user_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		user_node* temp = *head;
		user_node* to_delete = NULL;
		if(temp->user_info->name == infor){
			to_delete = temp;
			*head = temp->next;
		}
		else{
			while(temp->next != NULL){
				if(temp->next->user_info->name == infor)
					break;
				temp = temp->next;
			}
			to_delete = temp->next;
			temp->next = temp->next->next;
		}
		to_delete->user_info->destory();
		delete to_delete;
		return 1;
	}
}
//insert a 1 3 4
int insert(string infor, user_node** head){
	int pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	user_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<name<<" in list"<<endl;
		return 0;
	}
	pos = temp.find_first_of(" ");
	while(pos != string::npos){
		string number = temp.substr(0,pos);
		node->user_info->insert(stoi(number));
		temp = temp.substr(pos+1,infor.length()-pos-1);
		pos = temp.find_first_of(" ");
	}
	node->user_info->insert(stoi(temp));
	return 1;
}
//delete b 1 2 3
int deleted(string infor, user_node** head){
	int pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	user_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}
	pos = temp.find_first_of(" ");
	while(pos != string::npos){
		string number = temp.substr(0,pos);
		node->user_info->Delete(stoi(number));
		temp = temp.substr(pos+1,infor.length()-pos-1);
	}
	node->user_info->Delete(stoi(temp));
	return 1;
}
int print(string infor, user_node** head){
	user_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->user_info->print();
		return 1;
	}
}
int save(string infor, user_node** head){
	user_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->user_info->save("./data/"+infor+".set");
		return 1;
	}
}
int read(string infor, user_node** head){
	user_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->user_info->read("./data/"+infor+".set");
		return 1;
	}
}
int find(string infor, user_node** head){
	int pos;
	pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	user_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<name<<" in list"<<endl;
		return 0;
	}else{
		if(node->user_info->find(stoi(temp))){
			return 1;
		}
		else{
			return 0;
		}
	}
}
user_node* in_list(string name, user_node* head){
	user_node* node = head;
	while(node != NULL){
		if(node->user_info->name == name)
			return node;
		node = node->next;
	}
	return NULL;
}
user_node* insert_tail(user_node* newnode, user_node* head){
	if(head == NULL){
		head = newnode;
	}else{
		user_node* node = head;
		while(node->next != NULL){
			node = node->next;
		}
		node->next = newnode;
	}
	return head;
}
void delete_list(user_node* head){
	user_node* temp = head;
	while(temp != NULL){
		user_node* to_delete = temp;
		temp = temp->next;
		delete to_delete;
	}
}