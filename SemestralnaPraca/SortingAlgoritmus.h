#pragma once
#include <locale>

#include "Udaj.h"
#include "libds/adt/sorts.h"
#include "libds/amt/implicit_sequence.h"

class sorting_algo
{
public:
	static void sort_compareVowelsCount(ds::amt::ImplicitSequence<Udaj>* is)
	{
		ds::adt::ShellSort<Udaj> ss;
		ss.sort(*is, [](auto word1, auto word2)
		{
			return count_vowels(word1.get_official_title()) > count_vowels(word2.get_official_title());
		});
	}

	static void sort_compareAlphabetical(ds::amt::ImplicitSequence<Udaj>* is)
	{
		ds::adt::ShellSort<Udaj> ss;
		std::locale::global(std::locale("Slovak_Slovakia.1250"));
		/*ss.sort(*is, [](auto udaj1, auto udaj2)
		{
			auto word1 = udaj1.get_official_title();
			auto word2 = udaj2.get_official_title();
			return std::lexicographical_compare(word1.begin(), word1.end(), word2.begin(), word2.end());
		});*/

		ss.sort(*is, [](auto word1, auto word2)
		{
			return word1.get_official_title() < word2.get_official_title();
		});

		/*ss.sort(*is, [](auto word1, auto word2)
		{
			return word2.get_official_title().compare(word1.get_official_title()) > word1.get_official_title().compare(word2.get_official_title());
		});*/

		/*ss.sort(*is, [](auto word1, auto word2)
		{
			const std::string w1 = word1.get_official_title();
			const std::string w2 = word2.get_official_title();
			return local_compare(w1, w2);
		});*/
	}

	/*static bool local_compare(const std::string& str1, const std::string& str2)
	{
		const std::locale loc("Slovak_Slovakia.1250");
		const auto& col = std::use_facet<std::collate<char>>(loc);

		const char* pb1 = str1.data();
		const char* pb2 = str2.data();

		return col.compare(pb1, pb1 + str1.size(), pb2, pb2 + str2.size());
	}*/

	static int count_vowels(const std::string& word)
	{
		int count = 0;
		for (const char c : word) {
			if (std::tolower(c) == 'a' || std::tolower(c) == 'e' ||
				std::tolower(c) == 'i' || std::tolower(c) == 'o' ||
				std::tolower(c) == 'u' || std::tolower(c) == 'y' ||
				std::tolower(c) == 'ä' || std::tolower(c) == 'á' ||
				std::tolower(c) == 'é' || std::tolower(c) == 'í' ||
				std::tolower(c) == 'ó' || std::tolower(c) == 'ú' ||
				std::tolower(c) == 'ý')
			{
				count++;
			}
		}
		return count;
	}
};