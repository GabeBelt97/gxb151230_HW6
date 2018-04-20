/*
 * Gabriel Beltran
 * gxb151230@utdallas.edu
 * CS 3377.502
 */

#include <iostream>
#include <fstream>
#include <string>
#include "cdk.h"
#include "program6.h"
#include <sstream>
#include <iomanip>
#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"0","a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"0", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  //Read the binary file "cs3377.bin"
  ifstream fin;
  fin.open("cs3377.bin", ios::in | ios::binary);
  if(!fin){ //check if file opened successfully
    return -1;
  }
  //allocate file header space and read it first
  BinaryFileHeader *head = new BinaryFileHeader();
  fin.read((char *) head, sizeof(BinaryFileHeader));

  //Read the next 4 records in the file
  BinaryFileRecord *rec1 = new BinaryFileRecord();
  fin.read((char *) rec1, sizeof(BinaryFileRecord));
  
  BinaryFileRecord *rec2 = new BinaryFileRecord();
  fin.read((char *) rec2, sizeof(BinaryFileRecord));

  BinaryFileRecord *rec3 = new BinaryFileRecord();
  fin.read((char *) rec3, sizeof(BinaryFileRecord));

  BinaryFileRecord *rec4 = new BinaryFileRecord();
  fin.read((char *) rec4, sizeof(BinaryFileRecord));
  
  //close binary file
  fin.close();
  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay first row (Binary file's header)
   */
  //Use stringstream and iomanip's hex to convert the unsigned int into a hexadecimal string
  stringstream hexstream;
  hexstream << "0x" << std::hex << head->magicNumber; //store value into stringstream
  string hexnum(hexstream.str()); //store the stringstream string
  string magic = "Magic: " +  hexnum; 
  string version = "Version: " + to_string(head->versionNumber);
  string records = "NumRecords: " + to_string(head->numRecords);
  setCDKMatrixCell(myMatrix, 1, 1, magic.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, records.c_str());
  
  //Display the 4 records read 
  string strlen = "strlen: " + to_string(rec1->strLength);
  setCDKMatrixCell(myMatrix, 2, 1, strlen.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, rec1->stringBuffer);

  strlen = "strlen: " + to_string(rec2->strLength);
  setCDKMatrixCell(myMatrix, 3, 1, strlen.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, rec2->stringBuffer);

  strlen = "strlen: " + to_string(rec3->strLength);
  setCDKMatrixCell(myMatrix, 4, 1, strlen.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, rec3->stringBuffer);

  strlen = "strlen: " + to_string(rec4->strLength);
  setCDKMatrixCell(myMatrix, 5, 1, strlen.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, rec4->stringBuffer);

  drawCDKMatrix(myMatrix, true);    /* required  */
  


  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
