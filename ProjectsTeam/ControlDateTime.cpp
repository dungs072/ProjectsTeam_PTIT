#include "ControlDateTime.h"
ControlDateTime::ControlDateTime()
{
	int twentyYearAgo = 1900 + ltm->tm_year - 20;
	day = new string[31];
	month = new string[12];
	year = new string[21];
	for (int i = 0; i < 31; i++)
	{
		if (i + 1 < 10)
		{
			day[i] = "0" + to_string(i + 1);
			month[i] = "0" + to_string(i + 1);
		}
		else
		{
			day[i] = to_string(i + 1);
			if (i < 12)
			{
				month[i] = to_string(i + 1);
			}
		}
		
		if (i <= 20)
		{
			year[i] = to_string(twentyYearAgo);
			twentyYearAgo++;
		}
	}
	//I dont know I should put local var in constructor or not:)

}
