#include "quinemclusky.h"

int main()
{
	char ch = 'y';
	int choice;
	while (ch == 'y')
	{

		cout << "--------------FLIP FLOP CONVERSION-------------" << endl;
		cout << "1. SR to Others. " << endl;
		cout << "2. JK to Others. " << endl;
		cout << "3. T to Others. " << endl;
		cout << "4. D to Others. " << endl;
		cout << "Select a choice :: ";
		cin >> choice;
		switch(choice)
		{
			case 1:
			{
				SRFF srff;
				srff.ToJK();
				srff.ToD();
				srff.ToT();		
			}
			break;

			case 2:
			{
				JKFF jkff;
				jkff.ToSR();
				jkff.ToD();
				jkff.ToT();
			}
			break;

			case 3:
			{
				TFF tff;
				tff.ToD();
				tff.ToSR();
				tff.ToJK();
			}
			break;

			case 4:
			{
				DFF dff;
				dff.ToT();
				dff.ToSR();
				dff.ToJK();
			}
			break;

			default:
			cout << endl << "Enter a valid choice. " << endl;
		}
		cout << "Do you want to continue (y/n) : ";
		cin >> ch;
	}
	// QuineMc();
}
