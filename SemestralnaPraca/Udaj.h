// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyModernizeUseNodiscard
#pragma once
#include <iostream>
#include <string>

class Udaj
{
private:
	std::string sort_number_;
	std::string code_;
	std::string official_title_;
	std::string medium_title_;
	std::string short_title_;
	std::string note_;
public:
	Udaj(std::string sort_number, std::string code, std::string official_title, std::string medium_title, std::string short_title, std::string note) :
		sort_number_(std::move(sort_number)), code_(std::move(code)), official_title_(std::move(official_title)), medium_title_(std::move(medium_title)), short_title_(std::move(short_title)), note_(std::move(note)) {}
	Udaj() {};
	void print() const
	{
		std::cout << this->sort_number_ << " " << this->code_ << " " << this->official_title_ << " " << this->medium_title_ << " " << this->short_title_ << " " << this->note_ << std::endl;
	}

	std::string get_sort_number() { return sort_number_; }
	std::string get_code() { return code_; }
	std::string get_official_title() { return official_title_; }
	std::string get_medium_title() { return medium_title_; }
	std::string get_short_title() { return short_title_; }
	std::string get_note() { return note_; }

	bool operator==(const Udaj& udaj) const
	{
		if (code_ == udaj.code_ && official_title_ == udaj.official_title_) return true;
		return false;
	}
	~Udaj() {}
};

