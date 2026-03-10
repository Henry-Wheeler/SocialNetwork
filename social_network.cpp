#include "network.h"
#include "user.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	Network network;
	
	network.readUsers("users.txt");
	network.readPosts("posts.txt");
	
	while (true) {

		cout << "Options:" << endl;
		cout << "1. Add a user" << endl;
		cout << "2. Add a friend connection" << endl;
		cout << "3. Delete a friend connection" << endl;
		cout << "4. Write to file" << endl;
		cout << "5. View posts for a user" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your option: " << endl;
		
		int choice;
		cin >> choice;
		cin.ignore();
		

		if (choice == 1) {
			string line;
			cout << "Enter users first name, last name, birth year, zip code (no commas): " << endl;
			getline(cin, line);
			
			stringstream s(line);
			string first;
			string last;
			int year;
			int zip;
			
			s >> first;
			s >> last;
			s >> year;
			s >> zip;
			
			string name = first + " " + last;
			int id = network.numUsers();
			set<int> friends;
			
			User* nUser = new User(id, name, year, zip, friends);
			network.addUser(nUser);
			
			cout << "User added" << endl;
		}
		

		else if (choice == 2) {
			string line;
			cout << "Enter two names: ";
			getline(cin, line);
			
			stringstream s(line);
			string first1;
			string last1;
			string first2;
			string last2;
			
			s >> first1;
			s >> last1;
			s >> first2;
			s >> last2;
			
			string name1 = first1 + " " + last1;
			string name2 = first2 + " " + last2;
			
			int worked = network.addConnection(name1, name2);
			
			if (worked == -1) {
				cout << "Error: user not found." << endl;
			} else {
				cout << "Friend connection added" << endl;
			}
		}
		

		else if (choice == 3) {
			string line;
			cout << "Enter two names: ";
			getline(cin, line);
			
			stringstream s(line);
			string first1;
			string last1;
			string first2;
			string last2;
			
			s >> first1;
			s >> last1;
			s >> first2;
			s >> last2;
			
			string name1 = first1 + " " + last1;
			string name2 = first2 + " " + last2;
			
			int result = network.deleteConnection(name1, name2);
			
			if (result == -1) {
				cout << "Error: users not found or not friends." << endl;
			} else {
				cout << "Friend connection deleted." << endl;
			}
		}
		
		else if (choice == 4) {
			string line;
			cout << "Enter filename: ";
			getline(cin,line);


			stringstream s(line);
			char filename[100];
			s >>filename;

			
			network.writeUsers(filename);
			
			cout << "Wrote " << network.numUsers() << " users to file." << endl;
		}

		else if (choice == 5) {
			string line;
			cout << "Enter name and number of posts to show: ";
			getline(cin, line);

			stringstream s(line);
			string first;
			string last;
			int howMany;

			s >> first;
			s >> last;
			s >> howMany;

			string name = first + " " + last;
			int id = network.getId(name);

			if (id == -1) {
				cout << "Error" << endl;
			}
			else {
				cout << network.getPostsString(id, howMany) << endl;
			}
		}

		
		else {
			cout << "Exited" << endl;
			break;
		}
		
		cout << endl;
	}
	
	return 0;
}









