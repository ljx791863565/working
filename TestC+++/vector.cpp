#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v1;
	v1.push_back(6);
	v1.push_back(7);
	
	vector<int>::iterator it = v1.begin();
	for (; it != v1.end(); it++){
		cout << *it << endl;
	}
	for (int i = 0; i < 2; i++){
		cout << v1[i] << endl;
	}

	return 0;
}
