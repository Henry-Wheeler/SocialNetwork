#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include "network.h"
#include "post.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("QMainWindow { background-color: #f5f0e8; }");

    QString labelStyle = "QLabel { color: #2b2b2b; }";
    ui->profileLabel->setStyleSheet(labelStyle);
    ui->messageLabel->setStyleSheet(labelStyle);
    ui->loginLabel->setStyleSheet(labelStyle);
    ui->bioLabel->setStyleSheet(labelStyle);

    QString buttonStyle = "QPushButton { background-color: #e8784d; color: #ffffff; border: none; border-radius: 4px; }";

    ui->loginButton->setStyleSheet(buttonStyle);
    ui->postButton->setStyleSheet(buttonStyle);
    ui->backButton->setStyleSheet(buttonStyle);
    ui->addButton->setStyleSheet(buttonStyle);
    ui->likeButton1->setStyleSheet(buttonStyle);
    ui->likeButton2->setStyleSheet(buttonStyle);
    ui->likeButton3->setStyleSheet(buttonStyle);
    ui->likeButton4->setStyleSheet(buttonStyle);
    ui->likeButton5->setStyleSheet(buttonStyle);

    ui->friendsWidget->setStyleSheet("QTableWidget {background-color: #e8e4dc; color: #2b2b2b; gridline-color: #d0ccc4; border: none; }"
                                     "QHeaderView::section { background-color: #e8e4dc; color: #2b2b2b; border none; }");

    ui->loginEdit->setStyleSheet("QTextEdit { background-color: #e8e4dc; color: #2b2b2b; border: none; }" );
    ui->postEdit->setStyleSheet("QTextEdit { background-color: #e8e4dc; color: #2b2b2b; border: none; }" );

    network = new Network();
    network->readUsers("users.txt");
    network->readPosts("posts.txt");
    state = 0;
    currentUser = nullptr;
    displayUser = nullptr;

    connect(ui->loginButton,
            &QPushButton::clicked,
            this,
            &SocialNetworkWindow::loginButtonClick);

    display();

    connect(ui->friendsWidget,
            &QTableWidget::cellClicked,
            this,
            &SocialNetworkWindow::friendClicked);

    connect(ui->backButton,
            &QPushButton::clicked,
            this,
            &SocialNetworkWindow::backButtonClick);

    connect(ui->addButton,
            &QPushButton::clicked,
            this,
            &SocialNetworkWindow::addButtonClick);

    connect(ui->friendsWidget,
            &QTableWidget::cellClicked,
            this,
            &SocialNetworkWindow::suggestedFriendClick);

    connect(ui->postButton,
            &QPushButton::clicked,
            this,
            &SocialNetworkWindow::postButtonClick);
    connect(ui->likeButton1,
            &QPushButton::clicked,
            this, [this]() {
            likeButtonClick(0); });

    connect(ui->likeButton2,
            &QPushButton::clicked,
            this, [this]() {
            likeButtonClick(1); });

    connect(ui->likeButton3,
            &QPushButton::clicked,
            this, [this]() {
            likeButtonClick(2); });

    connect(ui->likeButton4,
            &QPushButton::clicked,
            this, [this]() {
            likeButtonClick(3); });

    connect(ui->likeButton5,
            &QPushButton::clicked,
            this, [this]() {
            likeButtonClick(4); });

}

void SocialNetworkWindow::display() {

    ui->loginButton->hide();
    ui->loginEdit->hide();
    ui->loginLabel->hide();
    ui->profileLabel->hide();
    ui->messageLabel->hide();
    ui->friendsWidget->hide();
    ui->backButton->hide();
    ui->addButton->hide();
    ui->postButton->hide();
    ui->postEdit->hide();
    ui->likeButton1->hide();
    ui->likeButton2->hide();
    ui->likeButton3->hide();
    ui->likeButton4->hide();
    ui->likeButton5->hide();
    ui->bioLabel->hide();

    if (state == 0){
        ui->loginButton->show();
        ui->loginEdit->show();
        ui->loginLabel->show();
    }

    if (state == 1) {
        displayUser = currentUser;
        ui->profileLabel->setText("My Profile,");
        ui->friendsWidget->setRowCount(currentUser->getFriends().size());
        ui->friendsWidget->setColumnCount(2);
        std::set<int> friends = currentUser->getFriends();
        int friendsSize = friends.size();
        int count = 0;
        int count2 = 0;
        for (auto friends : friends) {

            int id = friends;
            std::string name = network->getUser(id)->getName();
            QTableWidgetItem* Qname = new QTableWidgetItem(QString::fromStdString(name));

            ui->friendsWidget->setItem(count,0,Qname);
            count++;

            if (count == friendsSize) {
                break;
            }

        }
        int score;
        int id = currentUser->getId();
        std::vector<int> suggestions = network->suggestFriends(id,score);

        for (auto suggestion : suggestions) {
            int id = suggestion;
            std::string name = network->getUser(id)->getName();
            QTableWidgetItem* Qname = new QTableWidgetItem(QString::fromStdString(name));

            ui->friendsWidget->setItem(count2, 1, Qname);
            count2++;

        }

        displayedPosts.clear();
        std::vector<Post*> aPosts = network->getPosts(id);
        int total = aPosts.size();
        int number = std::min(5, total);

        for(int i = 0; i < number; i++) {
            displayedPosts.push_back(aPosts[total - 1 - i]);
        }


        std::string posts = network->getPostsString(id, 5);
        QString Qpost = QString::fromStdString(posts);

        ui->bioLabel->clear();
        std::string bio = currentUser->getBio();
        QString Qbio = QString::fromStdString(bio);
        ui->bioLabel->setText(Qbio);
        ui->bioLabel->setWordWrap(true);

        ui->bioLabel->show();
        ui->likeButton1->show();
        ui->likeButton2->show();
        ui->likeButton3->show();
        ui->likeButton4->show();
        ui->likeButton5->show();
        ui->postButton->show();
        ui->postEdit->show();
        ui->friendsWidget->verticalHeader()->setDefaultSectionSize(45);
        ui->messageLabel->setWordWrap(true);
        ui->messageLabel->setText(Qpost);
        ui->profileLabel->show();
        ui->messageLabel->show();
        ui->friendsWidget->show();


        std::vector<QPushButton*> likeButtons = {ui->likeButton1, ui->likeButton2, ui->likeButton3, ui->likeButton4, ui->likeButton5};
        for(int i = 0; i < displayedPosts.size(); i++) {
            if (displayedPosts[i]->getLikedBy().count(currentUser->getId())){
                likeButtons[i]->setText("Unlike");
            }
            else {
                likeButtons[i]->setText("Like");
            }
        }
    }

    if (state == 2) {

        int id = displayUser->getId();

        displayedPosts.clear();
        std::vector<Post*> aPosts = network->getPosts(id);
        int total = aPosts.size();
        int number = std::min(5, total);

        for(int i = 0; i < number; i++) {
            displayedPosts.push_back(aPosts[total - 1 - i]);
        }

        std::string posts = network->getPostsString(id, 5);
        QString Qpost = QString::fromStdString(posts);

        ui->friendsWidget->setRowCount(displayUser->getFriends().size());
        ui->friendsWidget->setColumnCount(1);
        std::set<int> friends = displayUser->getFriends();
        int friendsSize = friends.size();
        int count = 0;
        for (auto friends : friends) {

            int id = friends;
            std::string name = network->getUser(id)->getName();
            QTableWidgetItem* Qname = new QTableWidgetItem(QString::fromStdString(name));

            ui->friendsWidget->setItem(count,0,Qname);
            count++;

            if (count == friendsSize) {
                break;
            }

        }

        ui->bioLabel->clear();
        std::string bio = displayUser->getBio();
        QString Qbio = QString::fromStdString(bio);
        ui->bioLabel->setText(Qbio);
        ui->bioLabel->setWordWrap(true);


        ui->bioLabel->show();
        ui->likeButton1->show();
        ui->likeButton2->show();
        ui->likeButton3->show();
        ui->likeButton4->show();
        ui->likeButton5->show();
        ui->postButton->show();
        ui->postEdit->show();
        ui->addButton->show();
        ui->friendsWidget->show();
        ui->messageLabel->show();
        ui->backButton->show();
        ui->profileLabel->show();
        ui->messageLabel->setText(Qpost);

        std::vector<QPushButton*> likeButtons = {ui->likeButton1, ui->likeButton2, ui->likeButton3, ui->likeButton4, ui->likeButton5};

        for(int i = 0; i < displayedPosts.size(); i++) {
            if (displayedPosts[i]->getLikedBy().count(currentUser->getId())){
                likeButtons[i]->setText("Unlike");
            }
            else {
                likeButtons[i]->setText("Like");
            }
        }
    }


}

void SocialNetworkWindow::loginButtonClick() {
    std::string loginText = ui->loginEdit->toPlainText().toStdString();
    int id = network->getId(loginText);
    if (id != -1) {

        currentUser = network->getUser(id);
        state = 1;
        display();

    }
    else{
        ui->loginLabel->setText("Error: Enter a new name");
        ui->loginEdit->clear();
    }
}

void SocialNetworkWindow::friendClicked(int r, int c) {

    if (c == 0) {
        QTableWidgetItem* Qname = ui->friendsWidget->item(r,c);
        std::string name = Qname->text().toStdString();
        displayname = name;
        QString profile = "'s profile";

        int id = network->getId(name);
        displayUser = network->getUser(id);
        ui->profileLabel->setText(Qname->text() + profile);
        state = 2;
        display();
    }

}

void SocialNetworkWindow::addButtonClick() {

    int id = network->getId(displayname);
    currentUser->addFriend(id);
    network->writeUsers("users.txt");
}

void SocialNetworkWindow::backButtonClick() {
    state = 1;
    display();
}

void SocialNetworkWindow::suggestedFriendClick(int r, int c) {
    if (c == 1) {
        QTableWidgetItem* Qname = ui->friendsWidget->takeItem(r,c);
        std::string name = Qname->text().toStdString();
        int id = network->getId(name);
        currentUser->addFriend(id);
        network->writeUsers("users.txt");
        state = 1;
        display();


    }
}

void SocialNetworkWindow::postButtonClick() {
    int uid = currentUser->getId();
    int pid = displayUser->getId();
    int likes = 0;

    std::string post = ui->postEdit->toPlainText().toStdString();

    Post* nPost = new Post(pid,uid,post,likes,std::set<int> {});

    network->addPost(nPost);
    network->writePosts("posts.txt");
    ui->postEdit->clear();
    display();

}

void SocialNetworkWindow::likeButtonClick(int i) {

    int uid = currentUser->getId();

    if(displayedPosts[i]->getLikedBy().count(uid)) {
        displayedPosts[i]->removeLike(uid);
    }
    else{
        displayedPosts[i]->addLike(uid);
    }
    network->writePosts("posts.txt");
    display();

}




SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}
