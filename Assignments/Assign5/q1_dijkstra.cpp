#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
class Node{
public:
    vector<pair<char,int>>edges;
    Node(vector<pair<char,int>>edges){
        this->edges=edges;
    }
};
int main(){
    vector<pair<char,int>>temp={{'B',1},{'E',1}};
    Node* a=new Node(temp);
    temp={{'A',1},{'C',1}};
    Node* b=new Node(temp);
    temp={{'B',1},{'G',1},{'J',4},{'F',3}};
    Node* c=new Node(temp);
    temp={{'E',5},{'H',1},{'K',1},{'J',2}};
    Node* d=new Node(temp);
    temp={{'A',1},{'G',1},{'D',5}};
    Node* e=new Node(temp);
    temp={{'K',1},{'C',3}};
    Node* f=new Node(temp);
    temp={{'H',1},{'E',1},{'C',1}};
    Node* g=new Node(temp);
    temp={{'D',1},{'G',1}};
    Node* h=new Node(temp);
    temp={{'D',2},{'C',4}};
    Node* j=new Node(temp);
    temp={{'F',1},{'D',1}};
    Node* k=new Node(temp);
    map<char,Node*>mp;
    mp['A']=a;mp['B']=b;mp['C']=c;mp['D']=d;mp['E']=e;mp['F']=f;mp['G']=g;mp['H']=h;mp['J']=j;mp['K']=k;
    char src,dest;
    cout<<"Enter the id of the source node: ";
    cin>>src;
    cout<<"Enter the id of the destination: ";
    cin>>dest;
    if(mp[src]==NULL||mp[dest]==NULL) {cout<<"Wrong inputs!\n";return 0;}
    vector<int>dist(10);map<char,char>par;
    map<char,int>nodeid;
    nodeid['A']=0;nodeid['B']=1;
    nodeid['C']=2;nodeid['D']=3;
    nodeid['E']=4;nodeid['F']=5;
    nodeid['G']=6;nodeid['H']=7;
    nodeid['J']=8;nodeid['K']=9;
    for(int i=0;i<10;i++) dist[i]=INF;
    dist[nodeid[src]]=0;
    using pic=pair<int,char>;
    priority_queue<pic,vector<pic>,greater<pic>>q;
    q.push({0,src});
    while(!q.empty()){
        char v=q.top().second;
        int d_v=q.top().first;
        q.pop();
        if(d_v!=dist[nodeid[v]]) continue;
        for(auto edge:mp[v]->edges){
            char to=edge.first;
            int len=edge.second;
            if(dist[nodeid[v]]+len<dist[nodeid[to]]){
                dist[nodeid[to]]=len+dist[nodeid[v]];
                par[to]=v;
                q.push({dist[nodeid[to]],to});
            }
        }
    }
    if(dist[nodeid[dest]]==INF) {cout<<"No path between "<<src<<" and "<<dest<<'\n';return 0;}
    cout<<"Shortest Distance between "<<src<<" and "<<dest<<" is: "<<dist[nodeid[dest]]<<" [Using Dijsktra Algorithm]"<<'\n';
    vector<char>path;
    char curr=dest;
    while(curr!=src){
        path.push_back(curr);
        curr=par[curr];
    }
    path.push_back(src);
    reverse(path.begin(),path.end());
    cout<<"The corresponding path is: ";
    for(auto x:path) cout<<x<<" ";
    cout<<'\n';
}