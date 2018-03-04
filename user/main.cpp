#include<iostream>
#include<fstream>
#include<string>
#include"user.h"
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
user_node* in_list(int NO, user_node* head);
user_node* insert_tail(user_node* newnode, user_node* head);
void delete_list(user_node* head);
string process(string str);
int same_follows(string infor, user_node** head);
int second_friends(string infor, user_node** head);
int same_level(string infor, user_node** head);

int number;

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
	ifstream number_file;
	number_file.open("./data/number.txt");
	number_file>>number;
	number_file.close();
	for(int i = 0; i < number+1; i++){
		read(to_string(i),&head);
	}
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
		else if(Operator == "find"){
			if(find(infor,&head) == 1)
				cout<<"yes"<<endl;
			else
				cout<<"no"<<endl;
		}
		else if(Operator == "same_follows"){
			same_follows(infor,&head);
		}
		else if(Operator == "second_friends"){
			second_friends(infor,&head);
		}
		else if(Operator == "same_level"){
			same_level(infor,&head);
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
	user_node* temp_node = head;
	while(temp_node != NULL){
		temp_node->user_info->Save();
		temp_node = temp_node->next;
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
		user* newuser = new user;
		newuser->name = infor;
		newuser->Set_NO(number + 1);
		number++;
		newuser->Save();
		user_node* newnode = new user_node;
		newnode->user_info = newuser;
		newnode->next = NULL;
		*head = insert_tail(newnode, *head);
		cout<<"add a new user."<<endl;
		cout<<"name: "<<newuser->name<<endl;
		cout<<"NO: "<<newuser->Get_NO()<<endl;
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
		to_delete->user_info->Destory();
		delete to_delete;
		return 1;
	}
}
//insert a fans 1 3 4
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
	string f = temp.substr(0,pos);
	temp = temp.substr(pos+1,infor.length()-pos-1);
	
	pos = temp.find_first_of(" ");
	while(pos != int(string::npos)){
		string number = temp.substr(0,pos);
		if(f == "fans"){
			node->user_info->Insert_fans(stoi(number));
			user_node* other_node = in_list(stoi(number),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Insert_follows(node->user_info->Get_NO());
		}
		if(f == "friends"){
			node->user_info->Insert_friends(stoi(number));
			user_node* other_node = in_list(stoi(number),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Insert_friends(node->user_info->Get_NO());	
		}
		if(f == "follows"){
			node->user_info->Insert_follows(stoi(number));	
			user_node* other_node = in_list(stoi(number),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Insert_fans(node->user_info->Get_NO());
		}
		temp = temp.substr(pos+1,infor.length()-pos-1);
		pos = temp.find_first_of(" ");
	}
	if(f == "fans"){
			node->user_info->Insert_fans(stoi(temp));
			user_node* other_node = in_list(stoi(temp),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Insert_follows(node->user_info->Get_NO());
		}
		if(f == "friends"){
			node->user_info->Insert_friends(stoi(temp));
			user_node* other_node = in_list(stoi(temp),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Insert_friends(node->user_info->Get_NO());	
		}
		if(f == "follows"){
			node->user_info->Insert_follows(stoi(temp));	
			user_node* other_node = in_list(stoi(temp),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Insert_fans(node->user_info->Get_NO());
		}
	return 1;
}
//delete b 1 2 3
int deleted(string infor, user_node** head){
	int pos = infor.find_first_of(" ");
	string name = infor.substr(0,pos);
	string temp = infor.substr(pos+1,infor.length()-pos-1);
	user_node* node = in_list(name,*head);
	if(node == NULL){
		cout<<"there is no "<<name<<" in list"<<endl;
		return 0;
	}
	pos = temp.find_first_of(" ");
	string f = temp.substr(0,pos);
	temp = temp.substr(pos+1,infor.length()-pos-1);
	
	pos = temp.find_first_of(" ");
	while(pos != int(string::npos)){
		string number = temp.substr(0,pos);
		if(f == "fans"){
			node->user_info->Delete_fans(stoi(number));
			user_node* other_node = in_list(stoi(number),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Delete_follows(node->user_info->Get_NO());
		}
		if(f == "friends"){
			node->user_info->Delete_friends(stoi(number));
			user_node* other_node = in_list(stoi(number),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Delete_friends(node->user_info->Get_NO());	
		}
		if(f == "follows"){
			node->user_info->Delete_follows(stoi(number));	
			user_node* other_node = in_list(stoi(number),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Delete_fans(node->user_info->Get_NO());
		}
		temp = temp.substr(pos+1,infor.length()-pos-1);
		pos = temp.find_first_of(" ");
	}
	if(f == "fans"){
			node->user_info->Delete_fans(stoi(temp));
			user_node* other_node = in_list(stoi(temp),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Delete_follows(node->user_info->Get_NO());
		}
		if(f == "friends"){
			node->user_info->Delete_friends(stoi(temp));
			user_node* other_node = in_list(stoi(temp),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Delete_friends(node->user_info->Get_NO());	
		}
		if(f == "follows"){
			node->user_info->Delete_follows(stoi(temp));	
			user_node* other_node = in_list(stoi(temp),*head);
			if(other_node == NULL){
				cout<<"add a not exist user"<<endl;
				return 0;
			}
			other_node->user_info->Delete_fans(node->user_info->Get_NO());
		}
	return 1;
}
int print(string infor, user_node** head){
	user_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->user_info->Print();
		return 1;
	}
}
int save(string infor, user_node** head){
	user_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->user_info->Save();
		return 1;
	}
}
int read(string infor, user_node** head){
	int NO = stoi(infor);
	if(NO > number){
		cout<<"no such user"<<endl;
		return 0;
	}
	user* newuser = new user;
	newuser->Set_NO(stoi(infor));
	newuser->Read();
	string name = newuser->name;
	user_node* node = in_list(name,*head);
	if(node != NULL){
		cout<<"there is "<<name<<" already in list"<<endl;
		delete newuser;
		return 0;
	}
	user_node* newnode = new user_node;
	newnode->user_info = newuser;
	newnode->next = NULL;
	*head = insert_tail(newnode, *head);
	cout<<"the user name is "<<newuser->name<<" NO is "<<stoi(infor)<<endl;
	return 1;
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
		pos = temp.find_first_of(" ");
		string f = temp.substr(0,pos);
		temp = temp.substr(pos+1,infor.length()-pos-1);
		int flag = 0;
		if(f == "fans"){
			flag = node->user_info->Search_fans(stoi(temp));
		}
		if(f == "friends"){
			flag = node->user_info->Search_friends(stoi(temp));
		}
		if(f == "follows"){
			flag = node->user_info->Search_follows(stoi(temp));
		}
		if(flag)
			return 1;
		else
			return 0;
	}
}
int same_follows(string infor, user_node** head){
	int pos;
	pos = infor.find_first_of(" ");
	string name1 = infor.substr(0,pos);
	string name2 = infor.substr(pos+1,infor.length()-pos-1);
	user_node* node1 = in_list(name1,*head);
	user_node* node2 = in_list(name2,*head);
	if(node1 == NULL || node2 == NULL){
		cout<<"there is no "<<name1<<" or "<<name2<<" in list"<<endl;
		return 0;
	}else{
		if(node1->user_info->Same_follows(*(node2->user_info))){
			return 1;
		}else{
			return 0;
		}
	}
}
int second_friends(string infor, user_node** head){
	user_node* node = in_list(infor,*head);
	if(node == NULL){
		cout<<"there is no "<<infor<<" in list"<<endl;
		return 0;
	}else{
		node->user_info->Second_friends();
		return 1;
	}
}
int same_level(string infor, user_node** head){
	int pos;
	pos = infor.find_first_of(" ");
	string name1 = infor.substr(0,pos);
	string name2 = infor.substr(pos+1,infor.length()-pos-1);
	user_node* node1 = in_list(name1,*head);
	user_node* node2 = in_list(name2,*head);
	if(node1 == NULL || node2 == NULL){
		cout<<"there is no "<<name1<<" or "<<name2<<" in list"<<endl;
		return 0;
	}else{
		if(node1->user_info->Same_level(*(node2->user_info))){
			return 1;
		}else{
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
user_node* in_list(int NO, user_node* head){
	user_node* node = head;
	while(node != NULL){
		if(node->user_info->Get_NO() == NO)
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