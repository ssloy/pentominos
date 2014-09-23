#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "piece.h"

using namespace std;
int main(int argc, char** argv) {
    string filename = string(2==argc ? argv[1] : "pentomino.txt");
    ifstream in;
    in.open(filename.c_str(), ifstream::in);
    if (in.fail()) return 1;

    vector<Piece> pieces;
    while (!in.eof()) {
        Piece p = Piece(in);
        if (p.w() && p.h()) pieces.push_back(p);
    }
    in.close();

    pieces[0].print();
    cout << endl;

    srand(time(NULL));
    for (int i=1; i<(int)pieces.size(); i++) {
        int n = rand()%8;
        for (int j=0; j<n; j++) {
            pieces[i].rotate();
        }
        if (rand()%2) pieces[i].flip();
        pieces[i].print();
        cout << endl;
    }

    return 0;
}

