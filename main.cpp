#include <iostream>
#include <fstream>
#include  <vector>
#include <stack>
using namespace std;


vector <vector <int >> vec;
vector <vector <int>> tvec;
vector <vector <int>> sccvec;
vector <bool> visit;
stack<int> Stack;
vector<int>sccnode;
vector<vector<int>> sccrelation;
vector<vector<int>> tsccrelation;



void DFS(int v,int y){

    visit[v]=true;
    sccvec[y].push_back(v);
    sccnode[v]=y;


    for(int i=0;i<tvec[v].size();i++){
        if(!visit[tvec[v][i]]){

            DFS(tvec[v][i],y);
        }

    }


}
void fill(int v){
    visit [v]=true;

    for(int i=0;i< vec[v].size();i++){

        if(!visit[vec[v][i]]){

            fill(vec[v][i]);
        }
    }
    Stack.push(v);



}
void scc(){

    for(int i=0;i<visit.size();i++){

        visit[i]=false;

    }
    for(int i=0;i<visit.size();i++){

        if(visit[i]==false){

            fill(i);
        }
    }

    for(int i=0;i<visit.size();i++){

        visit[i]=false;
    }

    int y=0;

    while(!Stack.empty()){

        int v=Stack.top();
        Stack.pop();

        if(visit[v]==false){

            DFS(v,y);
            y++;
        }
    }

}


int main(int argc, char * argv[]) {

    ifstream infile(argv[1]);
    if(!infile.is_open()){
        cout << "input problem";
        return 0;
    }
    int N;
    infile >> N;


    vec.resize(N);
    tvec.resize(N);
    visit.resize(N);
    sccvec.resize(N);
    sccnode.resize(N);


    for(int i=0;i<N;i++){
        int turn;
        infile >>turn;

        for(int j=0;j<turn;j++){
            int x;
            infile >> x;

            vec[i].push_back(x-1);
            tvec[x-1].push_back(i);

        }

    }
    scc();

    int m=0;
    for(int z=0;z<sccvec.size();z++) {
        if (sccvec[z].size()!=0){
            m++;

        }

    }
    sccrelation.resize(m);
    tsccrelation.resize(m);

    for(int i=0;i<sccvec.size();i++){


        for(int j=0;j<sccvec[i].size();j++){


            for(int k=0;k<vec[sccvec[i][j]].size();k++){


            if(sccnode[sccvec[i][j]]!=sccnode[vec[sccvec[i][j]][k]]){
                sccrelation[i].push_back(sccnode[vec[sccvec[i][j]][k]]);
                tsccrelation[sccnode[vec[sccvec[i][j]][k]]].push_back(i);


            }
            }

        }


    }

    int counter=0;

    for(int y=0;y<tsccrelation.size();y++){

        if(tsccrelation[y].size()==0){
            counter ++;



        }

    }
    ofstream output;
    output.open(argv[2]);
    output << counter<<" ";


    for(int h=0;h<tsccrelation.size();h++){

        if(tsccrelation[h].size()==0){
            output << (sccvec[h][0] + 1)<<" ";

        }

    }
    output.close();

    return 0;
}