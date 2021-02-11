#include <string>
using namespace std; 


string reverse(string str) {
	char tmp_right, tmp_left;
	int n = str.length();
	for (int i = 0; i < n/2; i++) {
		tmp_left = str[i];
		str[i] = str[n - 1 - i];
		str[n - 1 - i] = tmp_left;
	}	
	return str;
}
