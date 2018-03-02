#include<iostream>
#include<fstream>
#include<string>
#include"set.h"
using namespace std;
typedef struct set_node{
	set* set_info;
	struct set_node* next;
}set_node;
void man();
int init(string infor,set_node** head);
int destory(string infor, set_node** head);
int insert(string infor, set_node** head);
int deleted(string infor, set_node** head);
int print(string infor, set_node** head);
int save(string infor, set_node** head);
int read(string infor, set_node** head);
int cal(string infor, set_node** head);
int len(string infor, set_node** head);
int find(string infor, set_node** head);
int sub(string infor, set_node** head);
int equal(string infor, set_node** head);
set_node* in_list(string name, set_node* head);
set_node* insert_tail(set_node* newnode, set_node* head);
void delete_list(set_node* head);
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
	set_node* head = NULL;
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
int init(string infor,set_node** head){
	if(in_list(infor, *head) != NULL){
		cout<<infor<<" is already in the list, please change a name."<<endl;
		return 0;
	}else{
		set* newset = new set;
		newset->name = infor;
		set_node* newnode = new set_node;
		newnode->set_info = newset;
		newnode->next = NULL;
		*head = insert_tail(newnode, *head);
	}
	return 1;
}
int destory(string infor, set_node** head){
	set_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		set_node* temp = *head;
		set_node* to_delete = NULL;
		if(temp->set_info->name == infor){
			to_delete = temp;
			*head = temp->next;
		}
		else{
			while(temp->next != NULL){
				if(temp->next->set_info->name == infor)
					break;
				temp = temp->next;
			}
			to_delete = temp->next;
			temp->next = temp->next->next;
		}
		to_delete->set_info->destory();
		delete to_delete;
		return 1;
	}
}
//insert a 1 3 4
int insert(string infor, set_node** head){
	int pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	set_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<name<<" in list"<<endl;
		return 0;
	}
	pos = temp.find_first_of(" ");
	while(pos != string::npos){
		string number = temp.substr(0,pos);
		node->set_info->insert(stoi(number));
		temp = temp.substr(pos+1,infor.length()-pos-1);
		pos = temp.find_first_of(" ");
	}
	node->set_info->insert(stoi(temp));
	return 1;
}
//delete b 1 2 3
int deleted(string infor, set_node** head){
	int pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	set_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}
	pos = temp.find_first_of(" ");
	while(pos != string::npos){
		string number = temp.substr(0,pos);
		node->set_info->Delete(stoi(number));
		temp = temp.substr(pos+1,infor.length()-pos-1);
	}
	node->set_info->Delete(stoi(temp));
	return 1;
}
int print(string infor, set_node** head){
	set_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->set_info->print();
		return 1;
	}
}
int save(string infor, set_node** head){
	set_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->set_info->save("./data/"+infor+".set");
		return 1;
	}
}
int read(string infor, set_node** head){
	set_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->set_info->read("./data/"+infor+".set");
		return 1;
	}
}
int cal(string infor, set_node** head){
	int pos1 = infor.find_first_of("=");
	int pos2;
	if(infor.find_first_of("+") != string::npos){
		pos2 = infor.find_first_of("+");
	}else if(infor.find_first_of("-") != string::npos){
		pos2 = infor.find_first_of("-");
	}else if(infor.find_first_of("*") != string::npos){
		pos2 = infor.find_first_of("*");
	}
	if(pos1 < pos2){
		string name1 = infor.substr(0,pos1);
		string name2 = infor.substr(pos1+1,pos2-pos1-1);
		string name3 = infor.substr(pos2+1,infor.length()-pos2-1);
		if(name1 == name2 || name1 == name3 || name2 == name3){
			cout<<"Don't use a=a+b, use a+=b instead."<<endl;
			return 0;
		}
		set_node* node1 = in_list(name1,*head);
		set_node* node2 = in_list(name2,*head);
		set_node* node3 = in_list(name3,*head);
		if(node1 == NULL || node2 == NULL || node3 == NULL){
			cout<<"there are some sets not in the list."<<endl;
			return 0;
		}
		else{
			if(infor[pos2] == '+'){
				node1->set_info->add(*(node2->set_info),*(node3->set_info));
			}
			if(infor[pos2] == '-'){
				node1->set_info->minus(*(node2->set_info),*(node3->set_info));
			}
			if(infor[pos2] == '*'){
				node1->set_info->cross(*(node2->set_info),*(node3->set_info));
			}
			return 1;
		}
	}else{
		string name1 = infor.substr(0,pos2);
		string name2 = infor.substr(pos1+1,infor.length()-pos1-1);
		set_node* node1 = in_list(name1,*head);
		set_node* node2 = in_list(name2,*head);
		if(node1 == NULL || node2 == NULL){
			cout<<"there are some sets not in the list."<<endl;
			return 0;
		}
		else{
			if(infor[pos2] == '+'){
				node1->set_info->add(*(node2->set_info));
			}
			if(infor[pos2] == '-'){
				node1->set_info->minus(*(node2->set_info));
			}
			if(infor[pos2] == '*'){
				node1->set_info->cross(*(node2->set_info));
			}
			return 1;
		}
	}
}
int len(string infor, set_node** head){
	set_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		return node->set_info->length();
	}
}
int find(string infor, set_node** head){
	int pos;
	pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	set_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<name<<" in list"<<endl;
		return 0;
	}else{
		if(node->set_info->find(stoi(temp))){
			return 1;
		}
		else{
			return 0;
		}
	}
}
int sub(string infor, set_node** head){
	int pos;
	pos = infor.find_first_of(" ");
	string name1 = infor.substr(0,pos);
	string name2 = infor.substr(pos+1,infor.length()-pos-1);
	set_node* node1 = in_list(name1,*head);
	set_node* node2 = in_list(name2,*head);
	if(node1 == NULL || node2 == NULL){
		cout<<"there is no "<<name1<<" or "<<name2<<" in list"<<endl;
		return 0;
	}else{
		if(node1->set_info->sub(*(node2->set_info))){
			return 1;
		}else{
			return 0;
		}
	}
}
int equal(string infor, set_node** head){
	int pos;
	pos = infor.find_first_of(" ");
	string name1 = infor.substr(0,pos);
	string name2 = infor.substr(pos+1,infor.length()-pos-1);
	set_node* node1 = in_list(name1,*head);
	set_node* node2 = in_list(name2,*head);
	if(node1 == NULL || node2 == NULL){
		cout<<"there is no "<<name1<<" or "<<name2<<" in list"<<endl;
		return 0;
	}else{
		if(node1->set_info->equal(*(node1->set_info),*(node2->set_info))){
			return 1;
		}else{
			return 0;
		}
	}
}
set_node* in_list(string name, set_node* head){
	set_node* node = head;
	while(node != NULL){
		if(node->set_info->name == name)
			return node;
		node = node->next;
	}
	return NULL;
}
set_node* insert_tail(set_node* newnode, set_node* head){
	if(head == NULL){
		head = newnode;
	}else{
		set_node* node = head;
		while(node->next != NULL){
			node = node->next;
		}
		node->next = newnode;
	}
	return head;
}
void delete_list(set_node* head){
	set_node* temp = head;
	while(temp != NULL){
		set_node* to_delete = temp;
		temp = temp->next;
		delete to_delete;
	}
}