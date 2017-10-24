#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <list>

#include <gtest/gtest.h>

const std::string PATTERN = "\\b";
const std::string TARGET_WORD = "HITLER";


struct case_insensitive_less : public std::binary_function< char, char, bool >
{
	bool operator () (char x, char y) const
	{
		return toupper(static_cast< unsigned char >(x)) <
			toupper(static_cast< unsigned char >(y));
	}
};

bool NoCaseLess(const std::string &a, const std::string &b)
{
	return std::lexicographical_compare(a.begin(), a.end(),
		b.begin(), b.end(), case_insensitive_less());
}

TEST(CaseInsensitiveTest, Pos) { 
    ASSERT_TRUE(NoCaseLess("TESTSTR", "Test_str"));
    ASSERT_FALSE(NoCaseLess("TESTSTR", "Teststr"));
}

int main(int argc, char* argv[])
{
	std::string line, word;
	std::list<std::string> list;
	std::ifstream file("File.txt");
	std::ofstream output("Output.txt");
	std::regex target(PATTERN + TARGET_WORD + PATTERN, std::regex_constants::icase);

	while (std::getline(file, line)) 
	{
		line = std::regex_replace(line, target, "");
	    std::istringstream istream(line);

		while (istream >> word)
			list.push_back(word);
		list.sort(NoCaseLess);
	
		for (std::list<std::string>::iterator i = list.begin(); i != list.end(); ++i)
			output << *i << ' ';
		output << '\n';

		list.clear();
	}

	return 0;
}