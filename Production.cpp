#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

char PT1[] = "  BONUS PAY REPORT ";
char HL1[] = "    Employee Name  Product Number  Quota  Units Produced  Over Quota  Bonus Pay";
char HL2[] = "---------------------------------------------------------------------------------";


class production
{
public:
	void mainLine(void);

public:

	void accumulate();
	void calculate();
	void eoj();
	void initialization();

	void process();
	void prnTotals(void);
	void readIt();
	void writeIt();
	void OpenFile(void);
	void PrnHeadings(void);
	void ShowArrays(void);
	void SortArrays(void);

	bool bEndFlag;

	ifstream bonusFile;

	
	char employee_FN[9];
	char employee_LN[9];
	string productNum;
	int quota;
	int units;
	int overQuota;
	float bonusPay;
	int unitsTotal;
	int overQuotaTotal;
	float bonusPayTotal;

	int index;
	string product_Array[100];
};

int main()
{
	production r1;
	r1.mainLine();

	system("pause");
	return 0;
}

void production::accumulate()
{
	unitsTotal = unitsTotal + units;
	overQuotaTotal = overQuotaTotal + overQuota;
	bonusPayTotal = bonusPayTotal + bonusPay;

	
}

void production::calculate()
{ 
	bonusPay = 0;

	overQuota = units - quota;
	{
		if (overQuota > 0 && overQuota <= 10)
		
			bonusPay = overQuota * 0.60;

		else if (overQuota > 10 && overQuota <= 25)
		
			bonusPay = overQuota * 0.65;

		else if (overQuota > 25 && overQuota <= 45)
		
			bonusPay = overQuota * 0.70;

		else if (overQuota > 45)
	
			bonusPay = overQuota * 0.75;
		
	}
	return;
}

void production::eoj()
{
	bonusFile.close();
	cout << "\n------<E N D  O F  R U N>-------\n";
}

void production::initialization()
{
	index = 0;
	bEndFlag = true;
	OpenFile();
	if (!bonusFile.fail())
	{
		PrnHeadings();
		readIt();
		bEndFlag = false;
	}
}

void production::mainLine()
{
	initialization();
	while (bEndFlag == false)
	{
		process();
	}
	prnTotals();
	eoj();
	
	ShowArrays();
	SortArrays();
	ShowArrays();

}

void production::process()
{
	

	calculate();
	accumulate();
	writeIt();
	readIt();
	
}

void production::readIt()
{
	
		bonusFile>>employee_FN>>employee_LN
			>> productNum >> quota >> units;
		

		//Placing data into the product array.
		product_Array[index] = productNum;
		index = index + 1;

		if (bonusFile.eof() == true)
		{
			bEndFlag = true;
		}

		return;
}


void production::writeIt()
{
	cout << setw(8) << employee_FN<< setw(11)<< employee_LN
		<<setw(10) << productNum
		<< setw(10) << quota << setw(10) << units
		<< setw(12) << overQuota 
		<<setiosflags(ios::fixed)
		<< setiosflags(ios::showpoint)
		<< setw(16) << setprecision(2) << bonusPay << endl;
	return;
}

void production::OpenFile(void)
{
	bonusFile.open("bonusPayReport.dat");
	if (bonusFile.fail())
		cout << " Bonus file open fails" << endl;
	return;
}

void production::PrnHeadings(void)
{
	cout << PT1 << endl;
	cout << endl << endl;
	cout << HL1 << endl;
	cout << HL2 << endl;
	return;
}

void production::ShowArrays(void)
{
	for (int i = 0; i < 10; i++)
		cout << product_Array[i] << endl;


}


void production::SortArrays(void)
{
	string holdItem;

	for (int i = 0; i < 10 - 1; i++)
	{
		if (product_Array[i] > product_Array[i + 1])
		{
			holdItem = product_Array[i];
			product_Array[i] = product_Array[i + 1];
			product_Array[i + 1] = holdItem;
		}

	}
}
void production::prnTotals(void)
{
	cout << endl;
	cout << "Totals:";
	cout << setw(42) <<unitsTotal << setw(12) << overQuotaTotal
		 << setw(16)<< setprecision(2) <<bonusPayTotal <<endl;

}
