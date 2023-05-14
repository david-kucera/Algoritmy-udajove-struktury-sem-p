#pragma once
#include "Udaj.h"
#include "libds/adt/sorts.h"
#include "libds/amt/implicit_sequence.h"

class sorting_algo
{
	static void sort(ds::amt::ImplicitSequence<Udaj> is)
	{
		ds::adt::ShellSort<Udaj> ss;
	}
};