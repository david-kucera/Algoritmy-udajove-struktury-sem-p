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

		ss.sort(*is, [](auto word1, auto word2)
		{
			return word1.get_official_title() < word2.get_official_title();
		});
	}

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