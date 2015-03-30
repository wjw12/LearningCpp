#include "data_struc.h"
#include "traffic.h"

using namespace std;

int main() {
	ifstream file;
	file.open("test_data.txt");
	traffic test(file);
	test.print();
	test.solve();
	test.printSolution();

	system("pause");
	return 0;
}