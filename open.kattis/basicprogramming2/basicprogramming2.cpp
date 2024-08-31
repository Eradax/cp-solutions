#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

std::string t1(int n, std::vector<int> arr) {
	std::unordered_set<int> vals;
	for (int i: arr) {
		int temp = 7777-i;
		if (vals.find(temp) != vals.end()) {
			return "Yes";
		} else {
			vals.insert(i);
		}
	}
	return "No";
}

std::string t2(int n, std::vector<int> arr) {
	std::unordered_set<int> seen;
	for (int i: arr) {
		if (seen.find(i) != seen.end()) {
			return "Contains duplicate";
		} else {
			seen.insert(i);
		}
	}
	return "Unique";
}

std::string t3(int n, std::vector<int> arr) {
	std::map<int, int> count;
	int currMax = 0;
	int currVal = 0;
	for (int i: arr) {
		if (count.count(i)>0) {
			count[i] += 1;
			if (count[i]>currMax) {currMax=count[i];currVal=i;}
		} else {
			count[i] = 1;
		}
	}
	return currMax > n/2 ? std::to_string(currVal) : std::to_string(-1);
}

std::string t4(int n, std::vector<int> arr) {
	std::sort(arr.begin(), arr.end());
	if (n%2) {
		return std::to_string(arr[n/2]);
	} else {
		return std::to_string(arr[n/2-1]) + " " + std::to_string(arr[n/2]);
	}
}

std::string t5(int n, std::vector<int> arr) {
	std::vector<int> vals;
	for (int i: arr) {
		if (100 <= i and i < 1000) {
			vals.push_back(i);
		}
	}
	std::string ans = "";
	std::sort(vals.begin(), vals.end());
	for (int i: vals) {
		ans += std::to_string(i) + " ";
	}
	return ans;
}

int main() {
	int n, t;
	std::cin >> n >> t;

	std::vector<int> arr;
	for (int i; i<n; i++) {
		int t;
		std::cin >> t;
		arr.push_back(t);
	}

	std::string ans;
	switch (t) {
		case 1:
		ans = t1(n, arr);
		break;
		case 2:
		ans = t2(n, arr);
		break;
		case 3:
		ans = t3(n, arr);
		break;
		case 4:
		ans = t4(n, arr);
		break;
		case 5:
		ans = t5(n, arr);
		break;
	
	}

	std::cout << ans << std::endl;
}