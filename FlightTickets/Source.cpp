// the program display a table of seats ,if the seat is not reversed the will print its ID ,else will print X
// then ask the user to input as available seat, this seat will be checked first before update the seats
// if this seat is not available or already reversed, will ask the user to input another seat.
// to avoid a lot of loops which will affect on efficiency of the program...
// a getInfo() function been written to divide the input_string(seat_id) to integer which will be the row(th)index and char which will be (column)th index
// hstrcmp() also been written to compare between two strings .
#include<iostream>
#include<string>
#include<iomanip> 
using namespace std;

#define MAX_ROW 10                                                      
#define MAX_COL 5  


typedef struct
{
	string id;
	bool reversed = false;
}seats;

seats seat[MAX_ROW][MAX_COL];

bool display(); // to display the data
void getData();// to get the data from user
bool getInfo(string, int&, int&);// assign the row, and column, from input_string(seat_id)
bool check(int, int);// to check if the data enterd is true
void update(int, int);// if true then the data will be updated
bool hstrcmp(string, string);// to compare two strings                              

//let the journey begins, take the first step professor <3
int main()
{
	int again = 1;
	while (again)
	{//program will exit only if there is no seat available, OR user input \Z
		system("cls");//to clear the window
		if (display())
		{
			cout << "Sorry..No more seat available" << endl;
			system("pause");
			return 0;
		}
		getData();
		cout << "Continue? YES(1), NO(0): ";
		cin >> again;
	}
	system("pause");
}
bool display()
{//display the data, with gap 4 between them, if seat was reseved will print x else will print seat_id
 // and will give each seat its id.
	bool is_full = true;
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (seat[i][j].reversed == false)
			{
				seat[i][j].id = to_string(i) + char('A' + j);
				cout << setw(4) << seat[i][j].id;
				is_full = false;
			}
			else
				cout << setw(4) << "X";
		}
		cout << endl;
	}
	return is_full;
}
void getData()
{// ask the user to choose the seat, untill give an available seat
	int row, column;
	string seat_id;//to save choosen seat
	cout << "Choose your seat: ";
	cin >> seat_id;

	//give the row and column its value from the seat_id
	while (!getInfo(seat_id, row, column))
	{//seat dont have a complete data, so re-ask.
		cout << "sorry...this seat is not available" << endl;
		cout << "Choose your seat: ";
		cin >> seat_id;
		getInfo(seat_id, row, column);
	}

	while (!check(row, column))//if the seat is not available ,then ask again
	{
		cout << "sorry...this seat is not available" << endl;
		cout << "Choose your seat: ";
		cin >> seat_id;
		getInfo(seat_id, row, column);
	}
}
bool getInfo(string seat_id, int& row, int& column)
{//this function loops the string and take the first integers to be the row number, 
 //and the remaining char will be the column which will be turned into integer.

	int len = seat_id.length(), i = 0;
	string temp;//will hold the integer as string befor being turned into integer

	while (seat_id[i] >= 48 && seat_id[i] <= 48 + 9)
		//this char is number so add it as temporary string ,after getting all the digits then ...
		temp += seat_id[i++];

	if (i == 0)//if number of rows is dont entered, return false.
		return false;
	//then return row and column
	row = stoi(temp);
	column = seat_id[i] - 'A'; //convert the remaining char to be int as the index_column
	return true;
}
bool check(int row, int column)
{	//return true if the seat is available ,false otherwise
	bool is_available = false;
	if (row < 0 || row >= MAX_ROW || column < 0 || column >= MAX_COL) return false;//if the row and column is not available return false
	if (seat[row][column].reversed == false)//else update, and return true
	{
		update(row, column);
		return true;
	}
	return false;//if the seat is already reversed then return false	
}
void update(int row, int column)
{//after get data and check it, this will be called to save the new result 

	seat[row][column].reversed = true;// set the seat to be reversed
	cout << "Table has been updated!!" << endl;

}
bool hstrcmp(string s1, string s2)
{ //return true if the 2 strings are similar
	bool is_similar = false;
	if (s1.length() != s2.length())//compare the lenghts of the strings, if they are not the same then return false
		return false;
	int len = s1.length();
	for (int i = 0; i < len; i++)//compare each char in the two strings
		if (s1[i] != s2[i])
			return false;
	return true;
}

