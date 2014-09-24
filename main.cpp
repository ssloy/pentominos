#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "piece.h"

using namespace std;

void print_piece(Piece *p) {
    if (!p) return;
    int w = p->w();
    int h = p->h();
    char *data = new char[w*h];
    for (int i=0; i<w*h; i++) {
        data[i] = ' ';
    }
    for (int i=0; i<p->size(); i++) {
        Vec2i pt = p->cell(i);
        data[pt.x + pt.y*w] = '#';
    }
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            cout << data[i+j*w];
        }
        cout << endl;
    }
    delete [] data;
}

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

    print_piece(&(pieces[0]));
    cout << endl;

    srand(time(NULL));
    for (int i=1; i<(int)pieces.size(); i++) {
        int n = rand()%8;
        for (int j=0; j<n; j++) {
            pieces[i].rotate();
        }
        if (rand()%2) pieces[i].flip();
        print_piece(&(pieces[i]));
        cout << endl;
    }

    return 0;
}

