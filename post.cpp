#include "post.h"

#include <string>

Post::Post() {
	messageId_ = -1; 
	profileId_ = 0;
	authorId_ = 0;
	message_ = "";
    likes_ = 0;
    likedby_ = {};
}

Post::Post(int profileId, int authorId, std::string message, int likes, std::set<int> likedBy) {
	messageId_ = -1;
	profileId_ = profileId;
	authorId_ = authorId;
	message_ = message;
    likes_ = likes;
    likedby_ = likedBy;
}

int Post::getMessageId() {
	return messageId_;
}

void Post::setMessageId(int id) {
	messageId_ = id;
}

int Post::getProfileId() {
	return profileId_;
}

int Post::getAuthorId() {
	return authorId_;
}

std::string Post::getMessage() {
	return message_;
}

int Post::getLikes() {
	return likes_;
}

std::set<int> Post::getLikedBy() {
    return likedby_;
}

bool Post::addLike(int userId) {
    if (!likedby_.count(userId)) {
        likedby_.insert(userId);
        likes_ = likes_ + 1;
        return true;
    }
    return false;
}

bool Post::removeLike(int userId){
    if(likedby_.count(userId)) {
        likedby_.erase(userId);
        likes_ = likes_ - 1;
        return true;
    }
    return false;
}

std::string Post::getURL() {
	return "";
}

std::string Post::toString() {
	return message_ + " (" + std::to_string(likes_) + " likes)";
}

LinkPost::LinkPost() : Post() {
	url_ = "";
}

LinkPost::LinkPost(int profileId, int authorId, std::string message, int likes, std::string url) : Post(profileId, authorId, message, likes,std::set<int>{}) {
	url_ = url;
}

std::string LinkPost::getURL() {
	return url_;
}

std::string LinkPost::toString() {
    return getMessage() + " (url: " + url_ + ") (" + std::to_string(getLikes()) + " :likes";

}
















