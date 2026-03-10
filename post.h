#ifndef POST_H
#define POST_H

#include <string>
#include <set>

class Post {
public: 

	Post();

    Post(int profileId, int authorId, std::string message, int likes, std::set<int> likedby);

	//Pre: 
	//Post: Returns the message id 
	int getMessageId();

	//Pre:
	//Post: Sets the message id 
	void setMessageId(int id);

	//Pre:
	//Post: Returns the profile owners id 
	int getProfileId();

	//Pre:
	//Post: Returns the authors id 
	int getAuthorId();

	//Pre:
	//Post: Returns the message of the post
	std::string getMessage();

	//Pre: 
	//Post: Returns the number of likes 
	int getLikes();

    //Pre:
    //Post: Return the set of users who liked a post
    std::set<int> getLikedBy();

    //Pre: userId is a valid Id
    //Post: Add userId to likedBy and increase like count
    bool addLike(int userId);

    //Pre: userId is a valid Id
    //Post: Remove userId from likedBy and decrease the like count
    bool removeLike(int UserId);

	//Pre:
	//Post: Returns the URL associaed with the post 
	virtual std::string getURL();

	//Pre: 
	//Post: Retuns a string of the post in a specfic form 
	virtual std::string toString(); 

private:

	int messageId_;
	int profileId_;
	int authorId_;
	std::string message_;
	int likes_;
    std::set<int> likedby_;


};

#endif 


#ifndef LINKPOST_H
#define LINKPOST_H

class LinkPost : public Post {
public:

	LinkPost();

	LinkPost(int profileId, int authorId, std::string message, int likes, std::string url);

	//Pre:
	//Post: Returns the URL that goes with the post 
	std::string getURL();

	//Pre:
	//Post: Returns a steing in a special format that includes the URL
	std::string toString();

private:

	std::string url_;

};

#endif













