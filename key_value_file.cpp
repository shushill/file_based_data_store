#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include "json.hpp"

using namespace std;
using namespace std::chrono;
using json = nlohmann::json;

class fileDb{
    std::mutex door;
    fstream file;
public:
    fileDb(){
         unique_lock<std::mutex> ul(door);
        file.open("db.json", fstream::in | fstream::out | fstream::ate );
        if(!file){
            cout<<"File not present or error in file opeining "<<endl;
            cout<<"Make a file name of db.json"<<endl;
        }
    }
    ~fileDb(){
        file.close();
    }
    void create(string key, string value){
         unique_lock<std::mutex> ul(door);
         if(!file){
             cout<<"File not present"<<endl;
             return;
             file.open("db.json", fstream::in | fstream::out | fstream::ate );
         }


        // check file memory of 1 GB capacity
         file.seekg( fstream::beg);
         auto start = file.tellg();
         file.seekg(0, fstream::end);
          auto end = file.tellg();
          if((end-start)>1073741824){
              cout<<"Memory limit of 1 GB exceeded"<<endl;
              return;
          }
          if(key.size() > 32){
              cout<<"Key size capped at 32 Char exceeded "<<endl;
              cout<<"Enter key less than 32 char"<<endl;
              return;
          }
          if(value.size() > 16 *1024){
              cout<<"Value limit Exceeded"<<endl;
              return;
          }
          json k;
          file.seekg(0, fstream::end);
          auto end_mark = file.tellg();
          file.seekg(0, fstream::beg);

           file>>k;

             while(file.tellg() != (end_mark)){
              if(k.count(key)){
                  cout<<"Key is already present"<<endl;
                  cout<<"Read the value of key using read func"<<endl;
                  return;
              }
              auto mark = file.tellg();
              file.seekg(mark);
              if( (end_mark - mark)<5){
                  break;
              }
             file>>k;


          }
          file.seekg(0, fstream::end);
          unordered_map<string, pair<long long, string>> store;
          auto ct = std::chrono::system_clock::now();
          ct = time_point_cast<std::chrono::seconds>(ct);
          auto d = ct.time_since_epoch();
          d = duration_cast<seconds>(d);

          pair<long long, string> p;
          p.first = d.count();
          p.second = value;
          store[key] = p;

          json j(store);
          file<<std::setw(4)<<j<<endl;


    }
    void read(string key, int time_to_live){
        unique_lock<std::mutex> ul(door);
        if(!file){
            cout<<"File not present"<<endl;
            return;
            file.open("db.json", fstream::in | fstream::out | fstream::ate );
        }
        file.seekg( fstream::beg);
        json k;
        file.seekg(0, fstream::end);
        auto end_mark = file.tellg();
        file.seekg(0, fstream::beg);

         file>>k;
           while(file.tellg() != (end_mark)){
            if(k.count(key)){
                auto object = k[key];
                long long time_of_key_created = object.at(0);
                auto ct = std::chrono::system_clock::now();
                ct = time_point_cast<std::chrono::seconds>(ct);
                auto d = ct.time_since_epoch();
                d = duration_cast<seconds>(d);
                long long time_now = d.count();
                long long time_spent = (time_now-time_of_key_created)/1000000000;
                if(time_spent <= time_to_live){
                    string st = object[1].get<std::string>();
                    cout<<"key :"<<key<<"\n"<<"value : "<<st<<endl;
                    return;
                }else{
                    cout<<"Key Expires because time to live has exceeded"<<endl;
                    return;
                }
            }
            auto mark = file.tellg();
            file.seekg(mark);
            if( (end_mark - mark)<5){
                break;
            }
           file>>k;
        }
        cout<<"Key is not available in file"<<endl;
    }
    void dellete(string key, int time_to_live){
        unique_lock<std::mutex> ul(door);
        if(!file){
            cout<<"File not present"<<endl;
            return;
            file.open("db.json", fstream::in | fstream::out | fstream::ate );
        }
        file.seekg( fstream::beg);
        json k;
        file.seekg(0, fstream::end);
        auto end_mark = file.tellg();
        file.seekg(0, fstream::beg);

         file>>k;
           while(file.tellg() != (end_mark)){
            if(k.count(key)){
                auto object = k[key];
                long long time_of_key_created = object.at(0);
                auto ct = std::chrono::system_clock::now();
                ct = time_point_cast<std::chrono::seconds>(ct);
                auto d = ct.time_since_epoch();
                d = duration_cast<seconds>(d);
                long long time_now = d.count();
                long long time_spent = (time_now-time_of_key_created)/1000000000;
                if(time_spent <= time_to_live){
                    k.erase(key);
                    cout<<"Key has been removed from the file"<<endl;
                    return;
                }else{
                    cout<<"Key Expires because time to live has exceeded"<<endl;
                    return;
                }
            }
            auto mark = file.tellg();
            file.seekg(mark);
            if( (end_mark - mark)<5){
                break;
            }
           file>>k;
        }
        cout<<"Key is not available in file"<<endl;
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    fileDb f;
    std::thread t(&fileDb::create, &f, "p5", "sushil");
    t.join();
    std::thread t1(&fileDb::read, &f, "p5", 1000);
    t1.join();
    std::thread t2(&fileDb::dellete, &f, "p5", 10000);
    t2.join();













    return 0;

}
