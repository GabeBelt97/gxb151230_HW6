#ifndef PROGRAM6_H_
#define PROGRAM6_H_
/*
 * Gabriel Beltran
 * gxb151230@utdallas.edu
 * CS 3377.502
 */
#include <stdint.h>
const int maxRecordStringLength = 25;
class BinaryFileHeader{
 public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

#endif
