#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Ebook{
public:
    Ebook(){
         users_read_to_page_.resize(1001);
    }
    void SaveReadInfo(int user_id, int page_num){
        if (user_id >= page_for_user_.size()){
            page_for_user_.resize(2*user_id+2);
        }
        int read_before = page_for_user_[user_id];
        if (read_before == 0) ++active_readers_;
        page_for_user_[user_id] = page_num;
        for (int i = read_before+1; i <=  page_num; ++i){
            ++users_read_to_page_[i];
        }   
    }
    
    double CheerUser(int user_id){
        if (user_id >= page_for_user_.size()) return 0;
        int read_pages = page_for_user_[user_id];
        if (read_pages == 0) return 0;
        if (active_readers_ == 1) return 1;
        int worse_readers = active_readers_ - users_read_to_page_[read_pages];    
        return 1.0 * worse_readers / (active_readers_-1);
    }
private:
    vector<int> page_for_user_;
    vector<int> users_read_to_page_;
    int active_readers_ = 0;
};

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

void ReadCommand(Ebook& ebook){
    string s;
    int user;
    int page;
    cin >> s;
    if (s== "CHEER"){
        cin >> user;
        cout<< ebook.CheerUser(user)<<endl;;
    }
    if (s == "READ"){
        cin >> user >> page;
        ebook.SaveReadInfo(user, page);
    }
    ReadLine();
}

int main(){
   Ebook ebook;
   int i = 0;
   int request_counter = ReadLineWithNumber();
   while (i < request_counter){
       ReadCommand(ebook);
       ++i;
   }
}