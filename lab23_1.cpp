#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>&name, vector<int>&S, vector<char>&G){
    ifstream text(filename);
    //text.open("name_score.txt");
    string textline;
    //getline(text,textline);
    char format[] = "%99[^:]:%d %d %d";
    char n[100];
    int a,b,c,g;

    while (getline(text,textline)){
    sscanf(textline.c_str(),format,n,&a,&b,&c);
    name.push_back(n);
    g = a+b+c;
    S.push_back(g);
    G.push_back(score2grade(g));
    }
    text.close();

}

void getCommand(string &command, string &key){
    char format[] = "%s %[^:]s";
    char text1[100] ,text2[100];
    string t;
    cout<<"Please input your command:\n";
    getline(cin,t);
    sscanf(t.c_str(),format,&text1,&text2);
    command = text1;
    key = text2;

}

void searchName(vector<string>&name, vector<int>&S, vector<char>&G ,string key){
    int r=-1;
    int s=name.size();
    for (int i = 0; i < s; i++)
    {
        if (toUpperStr(key)==toUpperStr(name[i])){
            r=i;
        }
    }
    
    if (r!=-1)
    {
        cout << "---------------------------------\n";
        cout << name[r] << "'s score = " << S[r] << endl;
        cout << name[r] << "'s grade = " << G[r] << endl;
        cout << "---------------------------------\n";
    }
    else {
        cout << "---------------------------------\n";
        cout << "Cannot found."<< endl;
        cout << "---------------------------------\n";
    }

}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){

    int r=0;
    int s=names.size();
    char k = key[0];
    cout << "---------------------------------\n";
    for (int i = 0; i < s; i++){
        if (k == grades[i]){
            r++;
            cout << names[i] << " ("<< scores[i] << ")\n";
        }      
    }
    if(r==0) {
        cout << "Cannot found."<< endl;
        cout << "---------------------------------\n";
    }
    else{cout << "---------------------------------\n";}
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
