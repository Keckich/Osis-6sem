#include <iostream>
#include "algo.h"

using namespace std;


int main() {
	string str;
	while (getline(cin, str)) {	
		cout<<reverse(str)<<endl;		
	}	
	return 0;
}
