bool checkPalindrome(string s)
{
	if (s.size() == 1 || s.size() == 0) {
		return true;
	}
	if (s.at(0) == s.at(s.length() - 1)) {
		//if the first letter is the same as the last
		return checkPalindrome(s.substr(1, s.length() - 2));
	}
	else {
		return false;
	}

}