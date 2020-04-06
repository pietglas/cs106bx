#pragma once

#include <string>
using std::string;

bool Prefix(const string& prefix, const string& word) {
	bool starts_with = true;
	if (prefix.length() > word.length()) {
		starts_with = false;
		return starts_with;
	}

	for (int i = 0; i != prefix.length(); i++) {
		if (prefix.at(i) != word.at(i)) {
			starts_with = false;
			break;
		}
	}
	return starts_with;
}