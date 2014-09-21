#include <iostream>
int main(int argc, char** argv) {
	if (2==argc) {
		model = new Model(argv[1]);
	} else {
		model = new Model("pentomino.txt");
	}
	return 0;
}

