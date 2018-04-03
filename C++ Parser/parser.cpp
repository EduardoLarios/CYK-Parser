#include<iostream>  
#include<cstring>
#include<algorithm>
#include<string>
#include<cassert>
#include<iomanip>
#include<vector>
using namespace std;

#define MAX 100

//for more readability along the code.-
#define for(i,a,b) for(i=a;i<b; i++)

//-------------------------------------------------------------------------
string inputstring[MAX][MAX];
string productions[MAX][MAX];
string generatedgram[MAX][MAX]; 
string dpr[MAX];
int p,np;   

//-------------------------------------------------------------------------
string concat( string a, string b){
    int i;
    string r=a;
    for(i,0,b.length())
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}
//-------------------------------------------------------------------------
string search_productions(string p){
    //iterators vertical & horizontal
    int j,k;
    //------------------------------------
    string r="";
    for(j,0,np){
        k=1;
        while(generatedgram[j][k] != ""){
            if(generatedgram[j][k] == p){
                r=concat(r,generatedgram[j][0]);
            }
            k++;
        }
    }   
    return r;
}
//-------------------------------------------------------------------------
string generate_combinations(string a, string b){
    int i,j;
    string pri=a,re="";
    for(i,0,a.length()){
        for(j,0,b.length()){
            pri="";
            pri=pri+a[i]+b[j];
            re=re+search_productions(pri);    
        }
    }
    return re;
}
//-------------------------------------------------------------------------
void split_gram(string a){
    //iterator
    int i;
    //-------
    p=0;
    while(a.length()){
        i=a.find(" ");
        if(i>a.length()){
            dpr[p++] = a;
            a="";
        }
        else
        {
            dpr[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}
//-------------------------------------------------------------------------
int main(int argc, char* argv[]){
    //flags & iterators
    bool grammar=true;
    //-----
    int i=0;
    int j=0;
    int k=0;
    //------------------
    
    int pt,l;
    int input_number;
    
    string a,str,r,pr,start;
    std::string line;
    std::vector<std::string> lines;
    //-------------------------
    while(std::getline(std::cin, line)) {
        lines.push_back(line);
        if(line[0]>90 || line[0]<65){
            grammar=false;
            inputstring[i][0]=line;
            i++;
        }
        
        //checks the number of productions there are
        if(grammar){
            productions[j][0] = line;
            if(j==0){
                start=line[0];
            }
            j++;
        }
    }
    //----------------------
    input_number=i;
    np=j;
    //---------------------------
    for(i,0,np){   
        string temp="";
        int temporal;
        for(temporal,0,100){
            temp+=productions[i][temporal];
        }
        a=temp;
        pt=a.find(" ");
        generatedgram[i][0] = a.substr(0,pt);
        
        a = a.substr(pt+1, a.length());
        split_gram(a);
        for(j,0,p){
            generatedgram[i][j+1]=dpr[j];
        }
    }
    
    
    string matrix[MAX][MAX],st;
    //iterator, we could reuse some variables as iterators, but to see the flow of data easier we use different ones;
    int cd;
    for(cd,0,input_number){
        string temp="";
        int temporal;
        for(temporal,0,100){
            temp+=inputstring[cd][temporal];
        }
        str=temp;    
    
        for(i,0,str.length()){
            //
            r="";
            st = "";
            st+=str[i];
            for(j,0,np){
                k=1;
                while(generatedgram[j][k] != ""){
                    if(generatedgram[j][k] == st){
                        r=concat(r,generatedgram[j][0]);
                    }
                    k++;
                }
            }
            matrix[i][i]=r;
        }
        
        
        for(k,1,str.length()){
            for(j,k,str.length()){
                r="";
                for(l,j-k,j){
                    pr = generate_combinations(matrix[j-k][l],matrix[l+1][j]);
                    r = concat(r,pr);
                }
                matrix[j-k][j] = r;
            }
        }
        int f=0;
        bool flag=true;


//-------------------Answer / accepted or rejected-------------------------------------------
        for(i,0,start.length()){
            if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length()){ 
                cout<<"Accepted\n";
                flag=false;
            }
        }
        if(flag){
            cout<<"Rejected\n";
        }
    }
    return 0;
}