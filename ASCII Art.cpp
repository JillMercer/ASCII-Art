/* Jill Mercer CPSC 246 Adv Programming Principles
	Spring Section 02 2014

Assignment 1 ASCII Art in 2D arrays : 
	Takes a picture from a ppm file and changes the pixles into ASCII letters with similar gray scale values*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//Global Constants
int MAXSIZE=70;// The max size the ppm image can be

//Function prototypes 
bool openFile(fstream &inFile);//Taken from Dr.Valentine's program
void validateFileData(fstream &inFile, int& numRows, int& numCols);//Taken from Dr. Valentine's program
double getGrayValue(fstream &inFile, int numRows, int numCols);//Taken from Dr. Valentine's program
double readRedGreenBlue(fstream &inFile);
char findAsciiLetter (fstream &inFile, double grayValue);
void printAscii (fstream &inFile, int numRows, int numCols);

//Structures

struct AsciiValues{
	double asciiGrayScale;
	char letter;
};

/*************************************
****************MAIN******************
**************************************/
int main() 
{
	//Var Dictionary 
	int numRows, numCols;	//size of our ppm image
	bool isGoodFile;		//tells if file opened OK
	double grayValue;		//grayscale: avg of all pixels in img
	fstream inFile;			//file holding ppm image

	//1.0 Init & print headers ******************
	cout<<"\nJill Mercer ~ CpSc246 Adv Programming ~ Spring 2014\n";
	cout<<"Compute average grayscale value of ASCII PPM image\n\n";
	isGoodFile = openFile(inFile);

	//2.0 Process File **************************
	if (isGoodFile) {//we have a file to process
		validateFileData(inFile, numRows, numCols);

		if ( (numRows>0) && (numCols>0) ) {//we have proper PPM file
			grayValue = getGrayValue(inFile, numRows, numCols);
			cout << "\nThe average value for this image is: " 
											<< grayValue << endl;
		} else //file did not match PPM spec's
			cout<<"The file was not in proper ASCII PPM format\n\n";

	}//isGoodFile
	else //file failed to open properly
		cout<<"File failed to open correctly\n";

	//3.0 Finish up *****************************
	inFile.close();	//must always CLOSE all files we open
	cout<<"\n\n\n\t<<< Normal Termination >>>\n\n";

	return 0;

}
/************************************************
***************************** openFile **********
************************************************/
bool openFile (fstream &inFile) {
//Receives fstream input file
//Prompts user for path/name & attempts to open file
//Returns T/F if open succeeded or not
char fileName[80];
cout<< "\nPlease enter name of PPM file: ";
cin >> fileName;
cout << "\nYour file is: " << fileName << endl;

inFile.open(fileName);
	if (inFile.fail()){
		cerr<< "File faild to open ";
		exit (1);}


	return true;	
}


/************************************************
***************************** validateFileData **
************************************************/
void validateFileData(fstream &inFile, int& numRows, int& numCols){
//Receives fstream input file (already opened)
//Processes (and verifies) file is ASCII PPM format
//Returns with numCols (width) and numRows (height) of image
//   and the file pointer at the first pixel of file
//   If file is not in PPM format, will print errMsg
//   and return -1 for numRows/numCols.
	int width, height, maxColor;	//PPM characteristics
	bool isGoodPPM = true;			//flag for our tests
	char myLine[80];				//lines of PPM file (text)

	//1.0) Test 1st line: "P3"
	cout<<"\nData echo of file input:\n";
	inFile.getline(myLine, 80);	//grab whole 1st line
	cout<<myLine<<endl;			//echo it back to human

	if ( (myLine[0]!='P') || (myLine[1]!='3') ) //test it
		isGoodPPM = false;	//we have bad file

	//2.0 Test 2nd line (if needed): "# any old comment"
	if (isGoodPPM) {//keep testing ONLY if file still alive
		inFile.getline(myLine,80);	//grab whole 2nd line
		cout<<myLine<<endl;			//echo it back to human

		if (myLine[0]!='#')	//test for comment
			isGoodPPM = false;	//bad file
	}

	//3.0 Test 3rd & 4th lines: "<width> <height> <255>
	if (isGoodPPM) {
		inFile >> width >> height >> maxColor;	//grab 3 integers 
		cout << width << " " << height << endl	//echo back
			<< maxColor << endl;

		//test our numbers
		if ( (width<=0) || (height<=0) || (maxColor!=255) )
			isGoodPPM = false;	//bad file
	}

	//
	if (isGoodPPM) { //file passed inspection
		numCols = width;  numRows = height; 
	} else {
		numCols = numRows = -1;	//bad file
}
}//validateFileData

/************************************************
***************************** getAvgPixel *******
************************************************/
double getGrayValue(fstream &inFile, int numRows, int numCols){
//Receives fstream input file, with pointer at first pixel value
//         and the numRows (height) and numCols (width) of image
//Reads all pixels (RGB Values) 
//Returns the average (double) of all the pixels (grayScale value)

	
	double sum=0;
	double average=0;
	int arraySize = numRows * numCols * 3;
	int data;
	int count=0;
	for (int i=0; i<arraySize; i++){
		inFile >> data;
		sum += data;
		count++;
	}
	average = sum / count;

	return average;	
}//getGrayValue