#include <iostream>
#include <vector>
using namespace std;
class User(){
private:
    string username;
    string password;
public:
   User(const string& user, const string& pass)
        : username(user), password(pass) {}
    void logIn() {}
    void logOut(){}
};

class App(){
private:
    vector<User> Users;
public:
    void newUser(string username, string pass){
        Users.push_back(User(username, pass));
    }


};

int main(){





return 0;
}
