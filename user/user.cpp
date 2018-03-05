#include "user.h"
user::user(){
	this->NO = 0;
	this->name = "";
	this->fans = new set;
	this->follows = new set;
	this->friends = new set;
}
user::~user(){
	this->Destory();
}
int user::Set_NO(int x){
	this->NO = x;
	this->fans->name = this->name+"_fans";
	this->fans->set_NO(this->NO);
	this->friends->name = this->name+"_friends";
	this->friends->set_NO(this->NO);
	this->follows->name = this->name+"_follows";
	this->follows->set_NO(this->NO);
	return 1;
}
int user::Get_NO(){
	return this->NO;
}
int user::Destory(){
	delete this->fans;
	delete this->friends;
	delete this->follows;
	return 1;
}
int user::Insert_follows(int x){
	if(this->follows->insert(x))
		return 1;
	else
		return 0;
}
int user::Insert_fans(int x){
	if(this->fans->insert(x))
		return 1;
	else
		return 0;
}
int user::Insert_friends(int x){
	if(this->friends->insert(x))
		return 1;
	else
		return 0;
}
int user::Delete_follows(int x){
	if(this->follows->Delete(x))
		return 1;
	else
		return 0;
}
int user::Delete_fans(int x){
	if(this->fans->Delete(x))
		return 1;
	else
		return 0;
}
int user::Delete_friends(int x){
	if(this->friends->Delete(x))
		return 1;
	else
		return 0;
}
int user::Search_follows(int x){
	if(this->follows->find(x))
		return 1;
	else
		return 0;
}
int user::Search_fans(int x){
	if(this->fans->find(x))
		return 1;
	else
		return 0;
}
int user::Search_friends(int x){
	if(this->friends->find(x))
		return 1;
	else
		return 0;
}
int user::Read(){
	if(this->fans->read("./data/"+to_string(this->NO)+"_fans.set") &&
		this->follows->read("./data/"+to_string(this->NO)+"_follows.set") &&
		this->friends->read("./data/"+to_string(this->NO)+"_friends.set")){
		int pos  = this->fans->name.find_first_of("_");
		this->name = this->fans->name.substr(0,pos);
		return 1;
	}
	else{
		this->name = to_string(this->NO);
		cout<<"file open error,the user is empty"<<endl;
		return 0;
	}
}
int user::Save(){
	if(this->fans->save("./data/"+to_string(this->NO)+"_fans.set") &&
		this->follows->save("./data/"+to_string(this->NO)+"_follows.set") &&
		this->friends->save("./data/"+to_string(this->NO)+"_friends.set"))
		return 1;
	else
		return 0;
}
set* user::Get_follows(){
	return this->follows;
}
set* user::Get_friends(){
	return this->friends;
}
set* user::Get_fans(){
	return this->fans;
}
int user::Same_follows(user &a){
	set result;
	result.cross(*(this->follows),*(a.Get_follows()));
	result.print();
	return 1;
}
int user::Second_friends(){
	information* info = this->friends->to_array();
	set result;
	for(int i = 0; i < this->friends->length(); i++){
		set temp;
		temp.read("./data/"+to_string(info->data)+"_friends.set");
		result.add(temp);
		//result.Delete(this->NO);
		//result.Delete(info->data);
		info = info->next;
	}
	result.minus(*(this->friends));
	result.Delete(this->NO);
	result.print();
	return 1;
}
int user::Print(){
	cout<<"fans:"<<endl;
	this->fans->print();
	cout<<"friends:"<<endl;
	this->friends->print();
	cout<<"follows:"<<endl;
	this->follows->print();
	return 1;
}
int user::Same_level(user &a){
	set fans_add;
	fans_add.add(*(this->fans),*(a.Get_fans()));
	set fans_cross;
	fans_cross.cross(*(this->fans),*(a.Get_fans()));
	float fans_result = fans_cross.length()*1.0/fans_add.length();

	set friends_add;
	friends_add.add(*(this->friends),*(a.Get_friends()));
	set friends_cross;
	friends_cross.cross(*(this->friends),*(a.Get_friends()));
	float friends_result = friends_cross.length()*1.0/friends_add.length();

	set follows_add;
	follows_add.add(*(this->follows),*(a.Get_follows()));
	set follows_cross;
	follows_cross.cross(*(this->follows),*(a.Get_follows()));
	float follows_result = follows_cross.length()*1.0/follows_add.length();

	//cout<<fans_result<<" "<<friends_result<<" "<<follows_result<<endl;
	cout<<"Same_level: "<<(fans_result+follows_result+friends_result)/3.0<<endl;
	return 1;
}