#include <iostream>
#include <string>
#include <vector>
#include  <fstream>
using namespace std;
const long long MAD_A = 5;
const long long MAD_B = 341111;
const long long Mad_P =100000009;
vector <string> load_names(const string &Strings_collections) {
    vector <string> names;

    ifstream fin(Strings_collections);  // <--- FIXED

    if (!fin) {
        cout << "Could not open Strings_collections.txt file" << endl;
        return names;
    }

    string word;
    while (fin >> word) {
        names.push_back(word);
    }

    return names;   // <--- REQUIRED
}

/////////////////////////////////////////////////////////////////////////
long long polynomialHash(const string &key, int a) {
    long long hash = 0;
    for (char c: key) {
        hash = hash*a+ c;
    }
    return hash;

}
///////////////////////////////////////////////////////////////////////////
int CompressMOD(long long hashcode, int N) {
    if (hashcode<0)
        hashcode =-hashcode ;
    return hashcode%N;
}
//////////////////////////////////////////////////////////////////////////
int CompressMAD( long long hashcode, int N) {
    if (hashcode<0) hashcode = -hashcode;
    long long MAD_index = (MAD_A * (hashcode % Mad_P) + MAD_B) % Mad_P;
        return MAD_index%N;

}
//////////////////////////////////////////////////////////////////////////
struct HashTable {
    int N;
    int aPoly;
    bool useMAD;
    vector<vector<string>>table;
    HashTable(int N,int aPoly,bool useMAD) {
        this->N = N;
        this->aPoly = aPoly;
        this->useMAD = useMAD;
        table.resize(N);

    }
    int get_index(const string &key) {
        if (useMAD) {
            long long hashcode = polynomialHash(key,N);
            int index_MAD = CompressMAD(hashcode,N);
            return index_MAD;
        }
        long long hashcode = polynomialHash(key,aPoly);
            int index_MOD = CompressMOD(hashcode,N);
            return index_MOD;

    }
    void insert(const string &key) {
        int index = get_index(key);
        table[index].push_back(key);
    }

    bool find(const string &key) {
        int index = get_index(key);
        for (const string &s:table[index]) {
            if (s == key) return true;
        } return false;
    }
    void Display_table() {
        for (int i =0; i< N; i++) {
            if (table[i].empty()) continue;
            cout <<"Hash value "<<i<<":";
            for (int j = 0; j<table[i].size(); j++) {
                cout << " "<<table[i][j];
                if (j+1<table[i].size()) {
                    cout << ",";
                }
            }cout <<'\n';
        }
    }
    int getTotalCollisions() {
        int total = 0;
        for (int i=0; i<N; i++) {
            if (table[i].size()>1) {
                total += table[i].size() - 1;
            }
        } return total;
    }
};
//////////////////////////////////////////////////////////////////////////
int main() {
    vector <string> allnames = load_names("Strings_collections.txt");
    cout << allnames.size()<<endl;
    long long polynomialHash_ = polynomialHash("Charosss", 37);
    cout << polynomialHash_ << endl;
    cout << CompressMAD(polynomialHash_, 100) << endl;
    HashTable ht(50, 39, true);
        ht.insert("Alice");
        ht.insert("Anto");
        ht.insert("Bob");
        ht.insert("Bob");
        ht.insert("Bob");
    ht.Display_table();
    ht.getTotalCollisions();

};
/////////////////////////////////////////////////////////////////////////////
/*int main() {
    vector<int>avalues = {33,37,39,41};
    const int TABLE_SIZE = 10007;
    vector <string> allnames = load_names("Strings_collections.txt");
}*/
