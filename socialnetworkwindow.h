#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    void loginButtonClick();
    void display();
    void friendClicked(int r, int c);
    void backButtonClick();
    void addButtonClick();
    void suggestedFriendClick(int r, int c);
    void postButtonClick();
    void likeButtonClick(int i);


private:
    Ui::SocialNetworkWindow *ui;
    Network* network;
    User* currentUser;
    User* displayUser;
    Post* post;
    std::string displayname;
    std::vector<Post*> displayedPosts;
    int state;

};
#endif // SOCIALNETWORKWINDOW_H
