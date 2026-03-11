#include "network.h"
#include "user.h"
#include "post.h"

#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <algorithm>

Network::Network() {

}

User* Network::getUser(int id) {
	if (id >= 0 && id < users_.size()){
		return users_[id];
	}
	return nullptr; 
}

void Network::addUser(User* user) {
	users_.push_back(user);

}

int Network::addConnection(std::string s1, std::string s2) {
	 int id1 = getId(s1);
	 int id2 = getId(s2);

	 if (id1 < 0 || id2 < 0){
	 	return -1;
	 }

	 User* user1 = getUser(id1);
	 User* user2 = getUser(id2);

	 user1->addFriend(id2);
	 user2->addFriend(id1);

	 return 0;

}

int Network::deleteConnection(std::string s1, std:: string s2) {

	int id1 = getId(s1);
	int id2 = getId(s2);

	if (id1 < 0 || id2 < 0){
		return -1;
	}

	User* user1 = getUser(id1);
	User* user2 = getUser(id2);

	user1->deleteFriend(id2);
	user2->deleteFriend(id1);

	return 0;

}

int Network::getId(std::string name) {

	for (int i = 0; i < users_.size(); i++) {
		if (users_[i]->getName() == name) {
			return users_[i]->getId();
		}
	}
	return -1; 

}

int Network::numUsers() {
	return users_.size();
}

void Network::readUsers(const char* fname) {
	std::ifstream fileIn(fname);

	std::string line;
	int num; 

	getline(fileIn, line);
	std::stringstream s(line);

	s >> num; 

	for (int i = 0; i < num; i++) {
		int id; 
		int year;
		int zip;
		std::string name;
        std::set<int> friends;
        std::string bio;

		getline(fileIn, line);
		std::stringstream s1(line);
		s1 >> id; 

		getline(fileIn, line);
		std::stringstream s2(line);
		std::string firstName;
		s2 >> firstName;
		getline(s2, name);
		name = firstName + name;

		getline(fileIn, line);
		std::stringstream s3(line);
		s3 >> year;

		getline(fileIn, line);
		std::stringstream s4(line);
		s4 >> zip;

		getline(fileIn, line);
		std::stringstream s5(line);
		int friendsIds;
		while(s5 >> friendsIds) {
			friends.insert(friendsIds);
		}

        getline(fileIn, line);
        bio = line.substr(1);

        User* user = new User(id,name,year,zip,friends,bio);
		addUser(user);

	}

}

void Network::writeUsers(const char* fname) {

	std::ofstream fileOut(fname);

	fileOut << users_.size() << std::endl;

	for (int i = 0; i < users_.size(); i++) {
		User* user = users_[i];

		fileOut << user->getId() << std::endl;

		fileOut << "\t" << user->getName() << std::endl; 

		fileOut << "\t" << user->getYear() << std::endl;

		fileOut << "\t" << user->getZip() << std::endl;

		std::set<int> friends = user->getFriends();
		fileOut << "\t";
		for(int friendIds : friends) {
			fileOut << friendIds << " ";
		}

        fileOut << "\t" << user->getBio() << std::endl;

		fileOut << std::endl;
	}

}

std::vector<int> Network::shortestPath(int from, int to) {
	std::queue<int> q;
	std::vector<bool> visited(numUsers(), 0);
	std::vector<int> parent(numUsers(), -1);

	 
	visited[from] = true;
	q.push(from);

	while(q.size() > 0) {
		int cur = q.front();
		q.pop();

		for (int neighbor : users_[cur]->getFriends()) {
			if (!visited[neighbor]) {
				parent[neighbor] = cur;
				visited[neighbor] = true;
				q.push(neighbor);
			}
		}
	}

	std::vector<int> list;

	if(visited[to] == false){
		return list;
	}




	int current = to;
	while(current != -1) {
		list.push_back(current);
		current = parent[current];
	}

	std::reverse(list.begin(), list.end());
	return list;
}

std::vector<int> Network::distanceUser(int from, int& to, int distance) {
	std::queue<int> q; 
	std::vector<bool> visited(numUsers(), 0);
	std::vector<int> dist(numUsers(), -1);

	dist[from] = 0;
	visited[from] = true;
	q.push(from);

	while(q.size() > 0) {
		int cur = q.front();
		q.pop();

		if(dist[cur] == distance) {
			to = cur;
			return shortestPath(from, to);
		}

		for(int neighbor : users_[cur]->getFriends()) {
			if(!visited[neighbor]) {
				dist[neighbor] = dist[cur] + 1;
				visited[neighbor] = true;
				q.push(neighbor);
			}
		}
	}

	to = -1;
	return std::vector<int>();
}

std::vector<std::vector<int>> Network::groups() {
	std::vector<bool> visited(numUsers(), 0);
	std::vector<std::vector<int>> components;

	for (int i = 0; i < numUsers(); i++) {
		if(!visited[i]) {
			std::vector<int> component;
			dfsHelper(i,visited,component);
			components.push_back(component);
		}
	}
	return components;
}

void Network::dfsHelper(int user, std::vector<bool>& visited, std::vector<int>& component) {
	visited[user] = true;
	component.push_back(user);

	for(int friendsId : users_[user]->getFriends()) {
		if(!visited[friendsId]) {
			dfsHelper(friendsId, visited, component);
		}
	}
}

void Network::addPost(Post* post) {
	int total = 0;

	for (int i = 0; i < posts_.size(); i++) {
		total += posts_[i].size();
	}
	post->setMessageId(total);

	int id = post->getProfileId();
	while (posts_.size() <= id) {
		posts_.push_back(std::vector<Post*>());
	}

	posts_[id].push_back(post);
}

std::vector<Post*> Network::getPosts(int id) {
	if (id>= 0 && id < posts_.size()) {
		return posts_[id];
	}
	return std::vector<Post*>();
}

std::string Network::postDisplayString(Post* post) {
	std::string name = getUser(post->getAuthorId())->getName();
	return name + " wrote: " + post->toString();
}


std::string Network::getPostsString(int ProfileId, int howMany) {
    std::vector<Post*> posts = getPosts(ProfileId);

    int total = posts.size();
    int counter = std::min(howMany, total);
    std::string end = "";

    for (int i = 0; i < counter; i++) {
        Post* post = posts[total - 1 - i];
        if (i > 0) {
            end += "\n\n";
        }
        end += postDisplayString(post);
    }
    return end;
}


int Network::readPosts(char* fname) {
	std::ifstream fileIn(fname);
	if(!fileIn.is_open()) {
		return -1; 
	}

	std::string line;
	int num;

	getline(fileIn, line);
	std::stringstream s(line);
	s >> num;

	for (int i = 0; i < num; i++) {
		int messageId;
		std::string message;
		int profileId;
		int authorId;
		int likes;
		std::string url;
	

	getline(fileIn, line);
	std::stringstream s1(line);
	s1 >> messageId;

	getline(fileIn, line);
	message = line.substr(1);

	getline(fileIn, line);
	std::stringstream s2(line);
	s2 >> profileId;

	getline(fileIn, line);
	std::stringstream s3(line);
	s3 >> authorId;

	getline(fileIn, line);
	std::stringstream s4(line);
	s4 >> likes;

	getline(fileIn, line);
	if(!line.empty() && line[0] == '\t') {
		url = line.substr(1);
	} 
	else {
		url = line;
	}

	Post* post; 
	if(url.empty()) {
        post = new Post(profileId, authorId, message, likes,std::set<int>{});
	}
	else {
		post = new LinkPost(profileId, authorId, message, likes, url);
	}

	addPost(post);


	}

	return 0;

}


bool comparePost(Post* a, Post* b) {
	return a->getMessageId() < b->getMessageId();
}

int Network::writePosts(char* fname) {
	std::ofstream fileOut(fname);
	if (!fileOut.is_open()) {
		return -1;
	}

	std::vector<Post*> aPost;
	for (int i = 0; i < posts_.size(); i++) {
		for (int j = 0; j < posts_[i].size(); j++) {
			aPost.push_back(posts_[i][j]);
		}
	}

	std::sort(aPost.begin(), aPost.end(), comparePost);

	fileOut << aPost.size() << std::endl;

	for (int i = 0; i < aPost.size(); i++) {
		Post* post = aPost[i];


		fileOut << post->getMessageId() << std::endl;

		fileOut << "\t" << post->getMessage() << std:: endl;
		fileOut << "\t" << post->getProfileId() << std::endl;
		fileOut << "\t" << post->getAuthorId() << std::endl;
		fileOut << "\t" << post->getLikes() << std::endl;
		fileOut << "\t" << post->getURL() << std::endl;
	}

	return 0;


}

std::vector<int> Network::suggestFriends(int who, int &score) {
    std::set<int> whoFriends = users_[who]->getFriends();
    std::vector<int> fSuggestions;
    score = 0;

    for (int i = 0; i < numUsers(); i++) {

        if (i == who || whoFriends.count(i) > 0) {
            continue;
        }

        std::set<int> fFriends = users_[i]->getFriends();
        int same = 0;
        for (int id : whoFriends) {
            if (fFriends.count(id) > 0) {
                same++;
            }
        }

        if (same > score) {
            score = same;
            fSuggestions.clear();
            fSuggestions.push_back(i);
        }
        else if (score == same & same > 0) {
            fSuggestions.push_back(i);
        }

    }

    return fSuggestions;

}









