#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <set>
#include <vector>
#include "user.h"
#include "post.h"


class Network {
public:

	Network(); 

	//Pre: Take in ID 
	//Post: Return Pointer to corresponding user, if not user with id return nullptr
	User* getUser(int id);

	//Pre: 
	//Post:Add a user to network database should accept pointer to a user object 
	void addUser(User*);

	//Pre: Take two string [first name] [lastname] format the names of two users 
	//Post: adds a friends connections if it doesnt exist return -1 if either user is invalid and 0 otherwise
	int addConnection(std::string s1, std::string s2);

	//Pre: s1 and s2 exist
	//Post: Deletes friend connection between s1 and s2 
	int deleteConnection(std::string s1, std:: string s2);

	//Pre: user exists 
	//Post: Gets users id 
	int getId(std::string name);

	//Pre:
	//Post: Returns the number of users in the users vector
	int numUsers();

	//Pre: The file exists
	//Post: Reads in the users information from a txt file ignoring tab characters and in the specifc order
	void readUsers(const char* fname);

	//Pre: The file exists 
	//Post: Writes in the users with the tabs and in the same order as the input files
	void writeUsers(const char* fname);

	std::vector<int> shortestPath(int from, int to); 

	std::vector<int> distanceUser(int from, int& to, int distance);

	std::vector<std::vector<int>> groups();

	//Pre: Post exists with profileId set to a user that does exist 
	//Post: Assigns the next messageId to the post and it adds it the users posts vector 
	void addPost(Post* post);

	//Pre: user id exsits 
	//Post: Returns the vector of Post pointers for the user with that id 
	std::vector<Post*> getPosts(int id);

	//Pre: Post exisits 
	//Post: Returns string in special format 
	std::string postDisplayString(Post* post);

	//Pre: howMany is greator that -1 and profile id is a real id 
	//Post: Returns the most recent howMany posts for the user with the most recent first and seperated by two newline chars 
	std::string getPostsString(int profileId, int howMany);

	//Pre:
	//Post:
	int readPosts(char* fname);

	//Pre:
	//Post:
	int writePosts(char* fname);

    std::vector<int> suggestFriends(int who, int &score);


private:

void dfsHelper(int user, std::vector<bool>& visited, std::vector<int>& component);


std::vector<User*> users_;

std::vector<std::vector<Post*>> posts_;

};

#endif
