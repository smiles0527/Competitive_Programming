#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);

	int n, k;
	cin >> n >> k;

	int word_len = 0;
	for (int i = 0; i < N; i++) {
		string word;
		cin >> word;

		word_len += word.length();
		if (word_len <= K) {

			if (i != 0) { cout << ' '; }
			cout << word;
		} else {
			cout << "\n" << word;
			word_len = word.length();
		}
	}
}