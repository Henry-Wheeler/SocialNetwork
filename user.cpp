#include "user.h"
#include "network.h"
#include <string>
#include <set>
#include <vector>

User::User() {
    id_ = 0;
    name_ = "Henry";
	year_ = 0;
	zip_ = 0; 
	this->friends = {23};
    bio_ = "";

} 

User::User(int id, std::string name, int year, int zip, std::set<int> friends, std::string bio) {
	id_ = id;
	name_ = name;
	year_ = year;
	zip_ = zip;
	this->friends = friends;
    bio_ = bio;

}

void User::addFriend(int id) {
	friends.insert(id);
}

void User::deleteFriend(int id) {
	friends.erase(id);
}

int User::getId() {
	return id_;
}

std::string User::getName() {
	return name_;
}

int User::getYear() {
	return year_;
}

int User::getZip() {
	return zip_;
}

std::string User::getBio() {
    return bio_;
}

std::set<int>& User::getFriends() {
	return friends; 
}
