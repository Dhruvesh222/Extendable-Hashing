// Extendable Hashing
#include<bits/stdc++.h>
using namespace std;
int g_depth,b_capcity;
vector<int> local_depth;
vector<int> buckets;
vector<vector<int>*> directory;
const int N = 2*1e6;
void insert(int);
void split(int hash1,int hash2){
    // cout<<"hash values "<<hash1<<" "<<hash2<<endl;
    if(local_depth[hash1]<g_depth){
        directory[hash2] = new vector<int>;
        buckets.push_back(hash2);
        local_depth[hash1] += 1;
        local_depth[hash2] = local_depth[hash1];
        vector<int> old_vector = *directory[hash1];
        directory[hash1]->clear();
        for(int i=0;i<b_capcity;i++){
            // cout<<"Inserting "<<old_vector[i]<<"....."<<endl;
            insert(old_vector[i]);
        }
    }else{
        g_depth++;
        // cout<<"directory doubling ..... "<<endl;
        directory.resize(1<<g_depth);
        for(int i=0;i<(1<<(g_depth-1));i++){
            // cout<<"local_depth of "<<i<<" "<<local_depth[i]<<endl;
            directory[i+(1<<(g_depth-1))] = directory[i]; 
        }
        // directory[hash2] = new vector<int>;
        // local_depth[hash1] += 1;
        local_depth[hash2] = local_depth[hash1];
    }
    return ;
}
void insert(int t){
    int hash = (t)&((1<<g_depth)-1);
    // cout<<hash<<" size is "<<directory[hash]->size()<<endl;
    if(directory[hash]->size()<b_capcity){
        (*directory[hash]).push_back(t);
    }else{
        int hash1 = hash,hash2 = hash;
        if(hash1<(1<<local_depth[hash])){
            hash2 += (1<<local_depth[hash]);
        }else{
            hash1 -= (1<<local_depth[hash]);
        }
        split(hash1,hash2);
        // cout<<"After splitting ";
        // cout<<g_depth<<endl;
        // for(int i=0;i<(1<<g_depth);i++){
        //     cout<<directory[i]<<endl;
        // }
        insert(t);
    }
    return ;
}
bool search(int t){
    int hash = (t)&((1<<g_depth)-1);
    // cout<<"hash value is "<<hash<<endl;
    vector<int> v = *directory[hash];
    for(int i=0;i<v.size();i++){
        // cout<<v[i]<<" ";
        if(v[i]==t){
            return true;
        }
    }
    // cout<<endl;
    return false;
}
void deletefunc(int t){
    int hash = (t)&((1<<g_depth)-1);
    vector<int>::iterator it;
    for(it=directory[hash]->begin();it!=directory[hash]->end();it++){
        if(*it==t){
            break;
        }
    }
    directory[hash]->erase(it);
    return ;
}
int main(){
    // #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    // #endif
    cin>>g_depth>>b_capcity;
    directory.resize(1<<g_depth);
    local_depth.resize(N);
    for(int i=0;i<(1<<g_depth);i++){
        vector<int> *v = new vector<int>;
        directory[i] = v;
        buckets.push_back(i);
        local_depth[i] = g_depth;
    }
    int choice=0;
    int t;
    cin>>choice;
    while(choice!=6){
        // if(choice==1){
        //     cout<<"global depth : "<<g_depth<<"\n";
        //     cout<<"number of buckets : "<<buckets.size()<<"\n";
        //     for(int i=0;i<buckets.size();i++){
        //         cout<<(*directory[buckets[i]]).size()<<" size and local depth = "<<local_depth[buckets[i]]<<"\n";
        //     cout<<"address of the bucket "<<directory[buckets[i]]<<endl;
        //         vector<int> v = *directory[buckets[i]];
        //         cout<<"Elements in this bucket are ---> ";
        //         for(int i=0;i<v.size();i++){
        //             cout<<v[i]<<" ";
        //         }
        //         cout<<endl;
        //         cout<<endl;
        //     }
        // }
        if(choice==2){
            cin>>t;
            if(!search(t)){
                insert(t);
            }else{
                // cout<<"This key is already present \n";
            }
        }else if(choice==3){
            cin>>t;
            if(search(t)){
                cout<<"found";
            }else{
                cout<<"Not found";
            }
            cout<<"\n";
        }else if(choice==4){
            cin>>t;
            if(search(t)){
                // cout<<"deleting "<<t<<endl;
                deletefunc(t);
            }
        }else if(choice==5){
            cout<<g_depth<<"\n";
            cout<<buckets.size()<<"\n";
            // cout<<"local depth : "<<g_depth<<"\n";
            // cout<<"number of buckets : "<<buckets.size()<<"\n";
            for(int i=0;i<buckets.size();i++){
                cout<<(*directory[buckets[i]]).size()<<" "<<local_depth[buckets[i]]<<"\n";
                // cout<<(*directory[buckets[i]]).size()<<" size and local depth = "<<local_depth[buckets[i]]<<"\n";
            }
        }

        // if(choice==7){
        //     for(int i=0;i<(1<<g_depth);i++){
        //         cout<<directory[i]<<endl;
        //     }
        // }
        cin>>choice;
    }
    return 0;
}
