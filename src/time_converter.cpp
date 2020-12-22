/* time_converter.cpp : Defines the entry point for the application.
	Author: Alex Giazitzis
	Date: 28/7/20
*/

#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>

//declared here in order to make expanding the converter easier
const short int units_variety = 7;
const short int locale_count = 2;

std::wstring locale_unit_text(short int locale, int i)
{
	std::wstring Units_List[locale_count][units_variety] =
	{
		{ L"Gregorian Years", L"Months", L"Weeks", L"Days", L"Hours", L"Minutes", L"Seconds" },
		{ L"Γρηγοριανά έτοι", L"Μήνες", L"Εβδομάδες", L"Ημέρες", L"Ώρες", L"Λεπτά", L"Δευτερόλεπτα" }
	};
	return Units_List[(locale - 1)][i];
}

//prompt to choose preferred language
void choose_locale(short int* locale)
{
	std::wcout << L"To use the English menu, type the number 1 and hit Enter.\n" << L"Για να χρησιμοποιήσετε το Ελληνικό"
		<< L" μενού πληκτρολογίστε το νούμερο 2 και πατήστε το Enter. " << L" > " << std::flush;
	std::cin >> *locale;
	std::wcout << std::endl;
}

//checks if locale choice is in the amount of choices that exist
bool check_locale(short int* locale)
{
	if (*locale <= locale_count && locale > 0)
	{
		return false;
	}
	else
	{
		std::cout << "No locale found matching the given option. Please choose from the list." << std::endl;
		return true;
	}
}

//displays the menus each time for the user	
void menus(short int locale, unsigned short int input_choice)
{
	std::wstring menus[6][locale_count] =
	{
		{ L"Units of time supported to convert from\n", L"Υποστηριζόμενες μονάδες χρόνου για μετατροπή από\n" },
		{ L"=======================================\n", L"================================================\n" },
		{ L"8.Exit program.\n", L"8.Έξοδος από το πρόγραμμα.\n" },
		{ L"Available units to convert to:\n", L"Υποστηριζόμενες μονάδες για να μετατροπή σε:\n" },
		{ L"==============================\n",L"================================================\n" },
		{ L"7.Exit program.\n", L"7.Έξοδος από το πρόγραμμα.\n" }

	};
	switch (input_choice)
	{
	case 0:
		std::wcout << menus[0][(locale - 1)] << menus[1][(locale - 1)]
			<< std::endl;
		for (short int i = 0; i < units_variety; i++)
		{
			std::wcout << i + 1 << "." << locale_unit_text(locale, i) << "." << std::endl;
		}
		std::wcout << menus[2][(locale - 1)] << std::endl;
		break;

	default:
		std::wcout << menus[3][(locale - 1)] << menus[4][(locale - 1)] << std::endl;
		bool check_i = false;
		for (short int i = 0; i < units_variety - 1; i++)
		{
			bool check = input_choice - 1 > i;

			switch (check)
			{
			case true:
				std::wcout << i + 1 << "." << locale_unit_text(locale, i) << "." << std::endl;
				break;

			case false:
				if (check_i == false)
				{
					i++;
					check_i = true;
				}
				std::wcout << i << "." << locale_unit_text(locale, i) << "." << std::endl;
				break;
			}
		}
		std::wcout << menus[5][(locale - 1)] << std::endl;
		break;
	}
}

//asks the user the the appropriate input depending on the variables.
void user_inputs(short int locale, unsigned short int* input_choice, unsigned short int* output_choice, double* time_input)
{
	std::wstring user_input_text[3][locale_count] =
	{
		{ L"Enter the number of the unit of time you want to convert from > ", L"Εισάγετε τον αριθμό που βρίσκετε αριστερά από την μονάδα του χρόνου που θα γίνει η μετατροπή > " },
		{ L"Enter the number of the unit of time you want to convert to > ", L"Εισάγετε τον αριθμό που βρίσκετε αριστερά από την μονάδα του χρόνου στη οποία θα γίνει η μετατροπή > "},
		{ L"Enter the amount of time you want to convert > ", L"Εισάγετε την ποσότητα του χρόνου την οποία επιθυμείτε να μετατρέψετε > " }
	};

	switch (*input_choice)
	{
	case 0:
		std::wcout << user_input_text[0][(locale - 1)] << std::flush;
		std::cin >> *input_choice;
		break;

	default:
		switch (*output_choice)
		{
		case 0:
			std::wcout << user_input_text[1][(locale - 1)] << std::flush;
			std::cin >> *output_choice;
			std::wcout << std::endl;
			break;

		default:
			std::wcout << user_input_text[2][(locale - 1)] << std::flush;
			std::cin >> *time_input;
			std::wcout << std::endl;
			break;
		}
	}
}

//asks the user if they want to perform another conversion
bool restart(short int locale)
{
	wchar_t restart;
	bool stop = false;

	std::wstring restart_text[2][locale_count] =
	{
		{L"Do you want to perform another conversion ? (1 for yes/ 0 for no) > ", L"Θέλετε να εκτελέσετε άλλη μετατροπή ; (Γράψτε 1 για ναι/0 για όχι) > " },
		{ L"Wrong choice given. Use y for yes or n for no.", L"Εισήχθηκε λάθος επιλογή. Χρησιμοποιήστε το ν για να απαντήσετε ναι ή το ο για να απαντήσετε όχι." }
	};

		do
		{
			std::wcout << restart_text[0][(locale - 1)] << std::flush;

			std::wcin >> restart;

			if (restart == '1')
			{
				std::wcout << std::endl;
				stop = true;
				return false;
			}
			else if (restart == '0')
			{
				stop = true;
				return true;
			}
			else
			{
				std::wcout << restart_text[1][(locale - 1)] << std::endl;
			}
		} while (!stop);
}

//outputs the converted time for the user to be able to see.
void output_time(short int locale, unsigned short int input_choice, unsigned short int output_choice, double* time_input, double* time_output)
{
	std::wstring equal_text[locale_count] = { L"is equivalent to ", L"ισούται με " };

		std::wcout << *time_input << " " << locale_unit_text(locale, input_choice - 1) << " " << equal_text[(locale - 1)] << std::flush;
		if (output_choice < input_choice)
		{
			std::wcout << std::setprecision(3) << *time_output << " " << locale_unit_text(locale, output_choice - 1) << ".\n" << std::endl;
		}
		else if (output_choice >= input_choice)
		{
			std::wcout << std::setprecision(3) << *time_output << " " << locale_unit_text(locale, output_choice) << ".\n" << std::endl;
		}

}

//converts inputed amount of time, from default unit to seconds
void toSeconds(unsigned short int input_choice, double* time_input, double* time_output)
{
	switch (input_choice)
	{
	case 1:	//fromYears
		*time_output = *time_input * 31536000.0; // instead of (((((52.0 * 7) + 1) * 24) * 60) * 60);	the +1 exists because 52 * 7 =364
		break;

	case 2:	//fromMonths
		*time_output = *time_input * 2592000.0; //instead of (((30.0 * 24) * 60) * 60); 
		break;

	case 3:	//fromWeeks
		*time_output = *time_input * 604800.0; //instead of (((7.0 * 24) * 60) * 60);
		break;

	case 4:	//fromDays
		*time_output = *time_input * 86400.0; //instead of ((24.0 * 60) * 60);
		break;

	case 5:	//fromHours
		*time_output = *time_input * 3600.0; //instead of (60.0 * 60);
		break;

	case 6:	//fromMinutes
		*time_output = *time_input * 60.0;
		break;

	default:
		std::cout << "Wrong input_choice called toSeconds()." << std::endl;
	}
}

//converts the time given in seconds (either from input or from toSeconds()) to another unit
void fromSeconds(unsigned short int input_choice, unsigned short int output_choice, double* time_input, double* time_output)
{
	if (output_choice >= input_choice)
	{
		output_choice++;
	}

	switch (output_choice)
	{
	case 1:	//toYears
		*time_output = *time_input / 31536000.0; // instead of (((((52.0 * 7) + 1) * 24) * 60) * 60);
		break;

	case 2: //toMonths
		*time_output = *time_input / 2592000.0; //instead of (((30.0 * 24) * 60) * 60);
		break;

	case 3:	//toWeeks
		*time_output = *time_input / 604800.0; //instead of (((7.0 * 24) * 60) * 60);
		break;

	case 4:	//toDays
		*time_output = *time_input / 86400.0; //instead of ((24.0 * 60) * 60);
		break;

	case 5:	//toHours
		*time_output = *time_input / 3600.0; //instead of (60.0 * 60);
		break;

	case 6:	//toMinutes
		*time_output = *time_input / 60.0;
		break;

	default:
		std::cout << "Wrong value output_choice passed in fromSeconds()" << std::endl;
	}
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);	//makes the output able to be unicode characters to support multiple locales
	bool exit = false;
	short int locale;
	do
	{
		choose_locale(&locale);
	} while (check_locale(&locale));
	do
	{
		unsigned short int input_choice = 0;
		unsigned short int output_choice = 0;
		double time_input;
		double time_output;

		menus(locale, input_choice); //calls first set of menus
		user_inputs(locale, &input_choice, &output_choice, &time_input);//asks the users input unit of time choice
		if (input_choice < 8)
		{
			std::wcout << std::endl;
			menus(locale, input_choice); //calls second set of menus
			user_inputs(locale, &input_choice, &output_choice, &time_input);//asks the users output unit of time choice
			if (output_choice == 7)
			{
				exit = true;
			}
			else if (output_choice < 7)
			{
				user_inputs(locale, &input_choice, &output_choice, &time_input);//asks the amount to convert
				switch (input_choice)
				{
				case 7:
					fromSeconds(input_choice, output_choice, &time_input, &time_output);
					/*we use &time_input instead of &time_output because we will convert from user given seconds
					meaning that time_input is already in seconds*/
					break;
				default:
					toSeconds(input_choice, &time_input, &time_output);
					switch (output_choice)
					{
					case 6:
						break;

					default:
						fromSeconds(input_choice, output_choice, &time_output, &time_output);
						break;
					}
					break;
				}
				output_time(locale, input_choice, output_choice, &time_input, &time_output);
				exit = restart(locale);
			}
			else
			{
				std::cout << "Invalid option chose. Please choose from the list shown." << std::endl;
			}
		}
		else if (input_choice == 8)
		{
			exit = true;
		}
		else
		{
			std::cout << "Invalid option chosen. Please choose from the list shown." << std::endl;
		}
	} while (!exit);

	return 0;
}