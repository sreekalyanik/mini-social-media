#include<bits/stdc++.h>
using namespace std;
int profileDisplay(map<string,vector<string>> &mp,vector<int> &posts,vector<string> &headings,vector<vector<vector<int>>> &connections,map<int,string> &pid)
{
    cout<<"Enter profile Name:\n";
    string str;
    cin>>str;
    int i=0;
    int id=stoi(mp[str][0]);
    id-=1;
    // displaying profileID,occupation,contact ,location
    cout<<"NAME: "<<str<<endl;
    for(auto it: mp[str]){
        cout<<headings[i]<<" "<<it<<endl;
        i++;
    }
    // printing number of posts
    cout<<headings[i]<<" "<<posts[id];

    // printing followes, following ,friends list
    cout<<"\nFollowers List: ";
    for(int i=0;i<26;i++){
        if(connections[id][0][i]==1){
            cout<<pid[i+1]<<" ";
        }
    }
    cout<<"\nFollowing List: ";
    for(int i=0;i<26;i++){
        if(connections[id][1][i]==1){
            cout<<pid[i+1]<<" ";
        }
    }
    cout<<"\nFriendsList: ";
    for(int i=0;i<26;i++){
        if(connections[id][2][i]==1){
            cout<<pid[i+1]<<" ";
        }
    }
    cout<<endl;
    return 0;
}
int makeFriends(map<string,vector<string>> &mp,vector<vector<vector<int>>> &connections)
{
    int x=1;
    do{
        string str1,str2;
        printf("Enter 1st profile Name:\n");
        cin>>str1;
        printf("Enter 2nd profile Name:\n");
        cin>>str2;
        int id1=stoi(mp[str1][0]);
        int id2=stoi(mp[str2][0]);
        id1-=1;
        id2-=1;
        connections[id1][2][id2]=1;
        connections[id2][2][id1]=1;
        cout<<str1<<" and "<<str2<<" are friends now"<<endl;
        cout<<"\nEnter 1.To make More friends\n2.To exit \n";
        cout<<"Enter your choice:\n";
        cin>>x;
    }while(x==1);
    return 0;
}
int follow(map<string,vector<string>> &mp,vector<vector<vector<int>>> &connections,map<int,string> &pid)
{
    cout<<"\nEnter the profile Name:\n";
    string str;
    cin>>str;
    int id=stoi(mp[str][0]);
    id=id-1;
    cout<<"Enter 1.To get followers\n2.To get following\n";
    int x;
    cin>>x;
    if(x==1){
        cout<<"Followers List: "<<endl;
        for(int i=0;i<26;i++){
            if(connections[id][0][i]==1){
                cout<<pid[i+1]<<" ";
            }
        }
        cout<<endl;
    }
    else if(x==2){
        cout<<"Following  List: "<<endl;
        for(int i=0;i<26;i++){
            if(connections[id][1][i]==1){
                cout<<pid[i+1]<<" ";
            }
        }
        cout<<endl;
    }
    else{
        cout<<"\nEntered wrong input!\n";
    }
    return 0;
}
int mutualFriends(map<string,vector<string>> &mp,vector<vector<vector<int>>> &connections,map<int,string> &pid)
{
    cout<<"\nEnter 1st profile Name:\n";
    string str1;
    cin>>str1;
    cout<<"\nEnter 2nd profile Name:\n";
    string str2;
    cin>>str2;
    int id1=stoi(mp[str1][0]);
    int id2=stoi(mp[str2][0]);
    id1=id1-1;
    id2=id2-1;
    set<string> st;
    for(int i=0;i<26;i++){
        if(connections[id1][2][i]==1){
            st.insert(pid[i+1]);
        }
    }
    cout<<"Mutual Friends: ";
    for(int i=0;i<26;i++){
        if(connections[id2][2][i]==1){
            if(st.find(pid[i+1])!=st.end()){
                cout<<pid[i+1]<<" ";
            }
        }
    }
    cout<<endl;
    return 0;
}
int friendSuggestions(map<string,vector<string>> &mp,vector<vector<vector<int>>> &connections,map<int,string> &pid){
    string str;
    cout<<"\nEnter profile Name:\n";
    cin>>str;
    int id=stoi(mp[str][0]);
    set<string> st;
    cout<<"Suggested Friends: ";
    for(int i=0;i<26;i++){
        if(connections[id-1][2][i]==1){
            for(int j=0;j<26;j++){
                if(j!=id-1 and connections[i][2][j]==1 and connections[id-1][2][j]!=1){
                    st.insert(pid[j+1]);
                }
            }
        }
    }
    for(auto it: st){
        cout<<it<<" ";
    }
    cout<<endl;
}
int mostPopular(vector<int> &followerscount,map<int,string> &pid){
     int id=0;
    int count=0;
    for(int i=0;i<26;i++){
        if(count<followerscount[i]){
            count=followerscount[i];
            id=i;
        }
    }
    cout<<"Most Popular: "<<pid[id+1]<<endl;
    return 0;
}
int numberposts(map<string,vector<string>> &mp,vector<int> &posts)
{
    cout<<"\nEnter profile Name:\n";
    string str;
    cin>>str;
    int id=stoi(mp[str][0]);
    cout<<"Number of posts by "<<str<<" :"<<posts[id-1]<<endl;
    return 0;

}
int topInFollowing(vector<int> &followingcount,map<int,string> &pid){
    int id=0;
    int count=0;
    for(int i=0;i<26;i++){
        if(count<followingcount[i]){
            count=followingcount[i];
            id=i;
        }
    }
    cout<<"Most Popular: "<<pid[id+1]<<endl;
}
int main(){


    // posts array stores number of posts of the user
    vector<int> posts(26,0);

    // followerscount array stores number of followers of the user
    // followingcount array stores number of followings of user
    vector<int> followerscount(26);
    vector<int> followingcount(26);



    // connections is a 3D MATRIX  where 
    // connections(x,0,z) means  x is follower of Z
    // connections(x,1,z) means x is following Z
    // connections(x,2,z) means x is friend of z
    vector<vector<vector<int>>> connections(26,vector<vector<int>>(3,vector<int>(26,0)));

    // using map to store string data(profileID,PHONE,LOCATION,gender)
    map<string,vector<string>> mp;


    // this is used to name & id (key value)  pairs 
    map<int,string> pid;

    // Headings Section - column names 
    vector<string> headings;
    headings.push_back("Profile ID:");
    headings.push_back("Address:");
    headings.push_back("Phone Number:");
    headings.push_back("Gender:");
    headings.push_back("Occupation:");
    headings.push_back("Posts Count:");

    do{
        cout<<"-----------------------------\nEnter \n1.Create Accounts \n2.Profile Display \n3.Make Friends\n4.Follow\n5.Mutual Friends\n6.Friends Suggestions\n7.Most Popular\n8.Posts\n9.Top in Following\n10.Close\n"<<endl;
        int n;
        cout<<"\nEnter your choice:\n";
        cin>>n;
        switch(n){
            case 1:{
                
                for(int i=0;i<26;i++){
                    posts[i]=(i+5)%7;
                }

                
                for(int i=0;i<26;i++){
                    followerscount[i]=(i+3)%7;
                    followingcount[i]=26-((i)%12);
                }
            
                

                
                string name="A";
                string loc="Aa";
                long long contact=9000123451;
                int g=1;
                string occ="OCC_A";
                int post=0;


                // filling map with some data
                for(int i=0;i<26;i++){
                    mp[name].push_back(to_string(i+1));
                    pid[i+1]=name;
                    mp[name].push_back(loc);
                    mp[name].push_back(to_string(contact));
                    if(g==1){
                        mp[name].push_back("male");
                        g=0;
                    }
                    else{
                        mp[name].push_back("famale");
                        g=1;
                    }
                    mp[name].push_back(occ);
                    name[0]=name[0]+1;
                    loc[1]=loc[1]+1;
                    contact+=1;
                    occ[4]=occ[4]+1;
                }
                // A-FOLLOWERS
                connections[0][0][1]=1;
                connections[0][0][4]=1;
                connections[0][0][12]=1;
                connections[0][0][14]=1;

                // D-FOLLOWERS
                connections[3][0][9]=1;
                connections[3][0][10]=1;
                connections[3][0][11]=1;

                // H-FOLLOWERS
                connections[7][0][0]=1;
                connections[7][0][2]=1;
                connections[7][0][13]=1;
                connections[7][0][15]=1;
                connections[7][0][23]=1;

                // D-FOLLOWING
                connections[3][1][22]=1;
                connections[3][1][6]=1;
                connections[3][1][10]=1;

                // P-FOLLOWING
                connections[15][1][4]=1;
                connections[15][1][8]=1;
                connections[15][1][17]=1;

                // A-FRIENDS
                connections[0][2][10]=1;
                connections[0][2][11]=1;
                connections[0][2][12]=1;
                connections[0][2][13]=1;
                connections[0][2][14]=1;
                connections[0][2][15]=1;
                connections[0][2][2]=1;
                connections[0][2][1]=1;


                // B-FRIENDS
                connections[1][2][14]=1;
                connections[1][2][15]=1;
                connections[1][2][16]=1;
                connections[1][2][17]=1;
                connections[1][2][18]=1;
                connections[1][2][19]=1;
                connections[1][2][2]=1;

                // C-FRIENDS
                connections[2][2][18]=1;
                connections[2][2][19]=1;
                connections[2][2][14]=1;
                connections[2][2][21]=1;
                connections[2][2][1]=1;


                // RANDOM CONNECTIONS 
                connections[2][0][7]=1;
                connections[1][0][9]=1;
                connections[3][0][24]=1;
                connections[12][0][19]=1;
                connections[7][0][11]=1;
                connections[22][0][8]=1;
                connections[8][0][14]=1;
                connections[9][0][12]=1;
                connections[10][0][20]=1;
                connections[12][1][19]=1;
                connections[7][1][11]=1;
                connections[22][1][8]=1;
                connections[11][1][2]=1;
                connections[2][0][7]=1;
                connections[1][0][9]=1;
                connections[3][2][24]=1;
                connections[12][2][19]=1;
                connections[7][2][11]=1;
                connections[22][2][8]=1;
                connections[16][2][22]=1;
                connections[18][2][11]=1;
                connections[19][2][0]=1;
                connections[21][2][0]=1;
                cout<<"26 PROFILES CREATED\n";

                break;
            }
            case 2:{
                profileDisplay(mp,posts,headings,connections,pid);
                break;
            }
            case 3:{
                makeFriends(mp,connections);
                break;
            }
            case 4:{
                follow(mp,connections,pid);
                break;
            }
            case 5:{
                mutualFriends(mp,connections,pid);
                break;
            }
            case 6:{
                friendSuggestions(mp,connections,pid);
                break;
            }
            case 7:{
                mostPopular(followerscount,pid);
                break;
            }
            case 8:{
                numberposts(mp,posts);
                break;
            }
            case 9:{
                topInFollowing(followingcount,pid);
                break;
            }
            case 10:{
                return 0;
            }
            default:{
                cout<<"WRONG INPUT\n";
            }

        }
        
    }while(true);
}
