#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <vector>


class User {
public:

	User();
    User(int id, std::string name, int year, int zip, std::set<int> friends, std::string bio);
 
 	//Pre: 
 	//Post: Add a friend for user
	void addFriend(int id);

	//Pre:
	//Post: Deletes a friend for a user
	void deleteFriend(int id); 

	//Pre:
	//Post: Gets user id 
	int getId();

	//Pre:
	//Post: Gets users name
	std::string getName();

	//Pre:
	//Post: Gets users year 
	int getYear();

	//Pre:
	//Post: Gets users zip 
	int getZip();

    //Pre:
    //Post:: Gets users bio
    std::string getBio();

	//Pre:
	//Post: Gets users set of friends
	std::set<int>& getFriends(); 

private:

	int id_;
	std::string name_;
	int year_;
	int zip_;
    std::set<int> friends;
    std::string bio_;

};

#endif
