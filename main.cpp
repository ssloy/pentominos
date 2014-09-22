#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

    for (int i=0; i<(int)pieces.size(); i++) {
        for (int j=0; j<i; j++) {
            pieces[i].rotate();
            if (j%3) pieces[i].flip();
        }
        pieces[i].print();
        std::cout << std::endl;
    }

    pieces[3].print();
    return 0;
}

