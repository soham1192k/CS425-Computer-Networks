#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
class Edge{
public:
    char a;
    char b;
    int cost;
    Edge(char a,char b,int cost){
        this->a=a;
        this->b=b;
        this->cost=cost;
    }
};
Edge* edges[26];
int main(){
    edges[0]=new Edge('A','B',1);
    edges[1]=new Edge('B','A',1);
    edges[2]=new Edge('A','E',1);
    edges[3]=new Edge('E','A',1);
    edges[4]=new Edge('B','C',1);
    edges[5]=new Edge('C','B',1);
    edges[6]=new Edge('C','G',1);
    edges[7]=new Edge('G','C',1);
    edges[8]=new Edge('C','F',3);
    edges[9]=new Edge('F','C',3);
    edges[10]=new Edge('C','J',4);
    edges[11]=new Edge('J','C',4);
    edges[12]=new Edge('D','J',2);
    edges[13]=new Edge('J','D',2);
    edges[14]=new Edge('F','K',1);
    edges[15]=new Edge('K','F',1);
    edges[16]=new Edge('K','D',1);
    edges[17]=new Edge('D','K',1);
    edges[18]=new Edge('D','H',1);
    edges[19]=new Edge('H','D',1);
    edges[20]=new Edge('D','E',5);
    edges[21]=new Edge('E','D',5);
    edges[22]=new Edge('G','H',1);
    edges[23]=new Edge('H','G',1);
    edges[24]=new Edge('E','G',1);
    edges[25]=new Edge('G','E',1);
    char src,dest;
    cout<<"Enter the id of the source node: ";
    cin>>src;
    cout<<"Enter the id of the destination node: ";
    cin>>dest;
    if(src<'A'||src>'Z'||dest<'A'||dest>'Z'){
        cout<<"Invalid Input\n";
        return 0;
    }
    map<char,int>nodeid;
    nodeid['A']=0;nodeid['B']=1;
    nodeid['C']=2;nodeid['D']=3;
    nodeid['E']=4;nodeid['F']=5;
    nodeid['G']=6;nodeid['H']=7;
    nodeid['J']=8;nodeid['K']=9;
    vector<int>dist(10,INF);
    dist[nodeid[src]]=0;
    map<char,char>par;
    for(;;){
        bool any=false;
        for(int j=0;j<26;j++){
            if(dist[nodeid[edges[j]->a]]<INF){
                if(dist[nodeid[edges[j]->b]]>dist[nodeid[edges[j]->a]]+edges[j]->cost){
                    dist[nodeid[edges[j]->b]]=dist[nodeid[edges[j]->a]]+edges[j]->cost;
                    par[edges[j]->b]=edges[j]->a;
                    any=true;
                }
            }
        }
        if(!any) break;
    }
    if(dist[nodeid[dest]]==INF) cout<<"No path from "<<src<<" to "<<dest<<'\n';
    else{
        vector<char>path;
        for(char curr=dest;curr!=src;curr=par[curr]) path.push_back(curr);
        path.push_back(src);
        reverse(path.begin(),path.end());
        cout<<"Shortest Distance from "<<src<<" to "<<dest<<" is: "<<dist[nodeid[dest]]<<" [Using Bellman Ford Algorithm]"<<'\n';
        cout<<"The corresponding path is: ";
        for(auto x:path) cout<<x<<" ";
        cout<<'\n';
    }
}