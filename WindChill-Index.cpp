// Sources of logic assistance:  
// https://docs.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/stl-sqrt-pow-functions
// https://docs.microsoft.com/en-us/cpp/standard-library/iomanip-functions?view=msvc-170
// https://www.weather.gov/media/epz/wxcalc/windChill.pdf
// https://stackoverflow.com/questions/23777226/how-to-display-degree-celsius-in-a-string-in-c

#include <iostream> // To use cin/cout
#include <iomanip> // To access setw for output width
#include <cmath> // Access power function for calculations
using namespace std;

const double MIN_TEMP = -5.0;
const double MAX_TEMP = 50.0;
const double MIN_WIND_SPEED = 5.0;
const double MAX_WIND_SPEED = 45.0;

int main()
{
	// Initialize variables 
	double actualTemp, windchillTemp, windSpeed = 0.0;

	int colWidth = 9, numRows = 12, numColumns = 10,
		tableWidth = numColumns * colWidth, 
		columnHeaderValue = 0;

	string tempHeader = "TEMP (\370F)",
		windspeedHeader = " WIND SPEED (MPH) ",
		headerBar = "";

	while (headerBar.length() < 
		(colWidth * numColumns - colWidth - windspeedHeader.length() - 2) / 2)
	{
		headerBar += "-";
	}

	actualTemp = MIN_TEMP;

	// Program output title
	cout << "Wind Chill Index Table Program" << endl
		<< "By Forrest Moulin" << endl << endl;

	// Column headers
	cout << right << setw(colWidth) << ""
		<< "  " << headerBar << windspeedHeader << headerBar << "-" << endl;

	// Populate wind speed values up to 45 degrees F
	for (columnHeaderValue; columnHeaderValue <= MAX_WIND_SPEED; 
		columnHeaderValue = columnHeaderValue + 5)
	{
		if (columnHeaderValue == 0)
		{
			cout << right << setw(colWidth) << tempHeader;
		}
		else
		{
			cout << right << setw(colWidth) << columnHeaderValue;
		}
	}
	cout << endl;

	// Equation for Wind Chill:
	// T_wc - Wind chill temp
	// T_a  - Actual temp
	// V    - Wind speed
	// T_wc = 35.74 + 0.6215 * T_a - 35.75 
	// * V^0.16 + 0.4275 * T_a * V^0.16

	// Nested for loop to populate the table
	// First loop handles each row
	for (int i = 0; i < numRows; i++)
	{
		// Nested loop intersects the row 
		// with each column
		for (int j = 0; j < numColumns; j++)
		{
			// Wind chill temp is equal to actual temp
			// when wind speed is 0
			if (j == 0)
			{
				windSpeed = 0.0;
				windchillTemp = actualTemp;
			}

			// Otherwise calculate the wind chill
			else {
				windchillTemp = 35.74 + 0.6215 * actualTemp
					- 35.75 * pow(windSpeed, 0.16) + 0.4275
					* actualTemp * pow(windSpeed, 0.16);
			}

			cout << fixed << setprecision(1)
				<< right << setw(colWidth) << windchillTemp;
			
			// After column is finished, move to
			// next speed/column
			windSpeed += 5;
		}

		cout << endl;

		// After each row is finished, move to
		// next temperature/row
		actualTemp += 5;
	}
}
/*
* CONSOLE OUTPUT
* Wind Chill Index Table Program
* By Forrest Moulin
*
*             ------------------------------ WIND SPEED (MPH) -------------------------------
*  TEMP (°F)        5       10       15       20       25       30       35       40       45
*      - 5.0    -16.4    -22.1    -25.8    -28.6    -30.8    -32.7    -34.3    -35.7    -37.0
* 	     0.0    -10.5    -15.9    -19.4    -22.0    -24.1    -25.9    -27.4    -28.8    -30.0
* 	     5.0     -4.6     -9.7    -13.0    -15.4    -17.4    -19.1    -20.5    -21.8    -23.0
* 	    10.0      1.2     -3.5     -6.6     -8.9    -10.7    -12.3    -13.6    -14.8    -15.9
* 	    15.0      7.1      2.7     -0.2     -2.3     -4.0     -5.5     -6.8     -7.9     -8.9
* 	    20.0     13.0      8.9      6.2      4.2      2.6      1.3      0.1     -0.9     -1.8
* 	    25.0     18.9     15.1     12.6     10.8      9.3      8.1      7.0      6.1      5.2
* 	    30.0     24.7     21.2     19.0     17.4     16.0     14.9     13.9     13.0     12.2
* 	    35.0     30.6     27.4     25.4     23.9     22.7     21.7     20.8     20.0     19.3
* 	    40.0     36.5     33.6     31.8     30.5     29.4     28.5     27.7     26.9     26.3
* 	    45.0     42.3     39.8     38.2     37.0     36.1     35.3     34.5     33.9     33.3
* 	    50.0     48.2     46.0     44.6     43.6     42.8     42.0     41.4     40.9     40.4
*
* C:\Users\Forrest\cmpsc121\homework\Project1-Windchill-Index\x64\Debug\Project1-Windchill-Index.exe
* (process 26340) exited with code 0.
*/
