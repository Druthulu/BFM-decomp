/*----------------------------------------------------------------------------*/
/*-- common.inc                                                             --*/
/*-- Common processes                                                       --*/
/*-- Copyright (C) 2010-2013 CUE                                            --*/
/*--                                                                        --*/
/*-- This program is free software: you can redistribute it and/or modify   --*/
/*-- it under the terms of the GNU General Public License as published by   --*/
/*-- the Free Software Foundation, either version 3 of the License, or      --*/
/*-- (at your option) any later version.                                    --*/
/*--                                                                        --*/
/*-- This program is distributed in the hope that it will be useful,        --*/
/*-- but WITHOUT ANY WARRANTY; without even the implied warranty of         --*/
/*-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           --*/
/*-- GNU General Public License for more details.                           --*/
/*--                                                                        --*/
/*-- You should have received a copy of the GNU General Public License      --*/
/*-- along with this program. If not, see <http://www.gnu.org/licenses/>.   --*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
#ifndef _COMMON_INC_
#define _COMMON_INC_ 

/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/*----------------------------------------------------------------------------*/
typedef unsigned char  U08;
typedef unsigned short U16;
typedef unsigned int   U32;
typedef   signed char  S08;
typedef   signed short S16;
typedef   signed int   S32;

/*----------------------------------------------------------------------------*/
#define BYTE_0   0x00000000
#define KILO_0   0x00000000
#define MEGA_0   0x00000000
#define GIGA_0   0x00000000

#define BYTE_1   0x00000001
#define BYTE_2   0x00000002
#define BYTE_4   0x00000004
#define BYTE_8   0x00000008
#define BYTE_16  0x00000010
#define BYTE_32  0x00000020
#define BYTE_64  0x00000040
#define BYTE_128 0x00000080
#define BYTE_256 0x00000100
#define BYTE_512 0x00000200
#define KILO_1   0x00000400
#define KILO_2   0x00000800
#define KILO_4   0x00001000
#define KILO_8   0x00002000
#define KILO_16  0x00004000
#define KILO_32  0x00008000
#define KILO_64  0x00010000
#define KILO_128 0x00020000
#define KILO_256 0x00040000
#define KILO_512 0x00080000
#define MEGA_1   0x00100000
#define MEGA_2   0x00200000
#define MEGA_4   0x00400000
#define MEGA_8   0x00800000
#define MEGA_16  0x01000000
#define MEGA_32  0x02000000
#define MEGA_64  0x04000000
#define MEGA_128 0x08000000
#define MEGA_256 0x10000000
#define MEGA_512 0x20000000
#define GIGA_1   0x40000000
#define GIGA_2   0x80000000

/*----------------------------------------------------------------------------*/
void  Exit(const char *format, ...);
int   FileExist(char *filename);
int   FileSize(char *filename);
void *FileLoad(char *filename);
void *FileRead(char *filename, int offset, int length);
int   FileSave(char *filename, void *buffer, int length);
int   FileCreate(char *filename);
int   FileAppend(char *filename, void *buffer, int length);
int   FileWrite(char *filename, int offset, void *buffer, int length);
void  Folder(char *path);
int   Extension(char *fn, char *fe);
void *Allocate(int length, int size);
void *ReAllocate(void *buffer, int length, int size);
void  Free(void *buffer);

/*----------------------------------------------------------------------------*/
void Exit(const char *format, ...) {
  va_list args;
  
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  
  exit(EXIT_FAILURE);
}

/*----------------------------------------------------------------------------*/
int FileExist(char *filename) {
  FILE *fp;
  int   fs;

  if ((fp = fopen(filename, "rb")) != NULL) {
    fclose(fp);
    return(1);
  }

  return(0);
}

/*----------------------------------------------------------------------------*/
int FileSize(char *filename) {
  FILE *fp;
  int   fs;

  if ((fp = fopen(filename, "rb")) == NULL) Exit("File open error\n");
  fs = filelength(fileno(fp));
  if (fclose(fp) == EOF) Exit("File close error\n");

  return(fs);
}

/*----------------------------------------------------------------------------*/
void *FileLoad(char *filename) {
  return(FileRead(filename, 0, FileSize(filename)));
}

/*----------------------------------------------------------------------------*/
void *FileRead(char *filename, int offset, int length) {
  FILE *fp;
  char *fb;

  if ((fp = fopen(filename, "rb")) == NULL) Exit("File open error\n");
  if (fseek(fp, offset, SEEK_SET)) Exit("File seek error\n");
  fb = Allocate(length, sizeof(char));
  if (fread(fb, 1, length, fp) != length) Exit("File read error\n");
  if (fclose(fp) == EOF) Exit("File close error\n");

  return(fb);
}

/*----------------------------------------------------------------------------*/
int FileSave(char *filename, void *buffer, int length) {
  FileCreate(filename);
  FileWrite(filename, 0, buffer, length);

  return(length);
}

/*----------------------------------------------------------------------------*/
int FileCreate(char *filename) {
  FILE *fp;

  Folder(filename);
  if ((fp = fopen(filename, "w+b")) == NULL) Exit("File create error\n");
  if (fclose(fp) == EOF) Exit("File close error\n");

  return(0);
}

/*----------------------------------------------------------------------------*/
int FileAppend(char *filename, void *buffer, int length) {
  FileWrite(filename, -1, buffer, length);

  return(length);
}

/*----------------------------------------------------------------------------*/
int FileWrite(char *filename, int offset, void *buffer, int length) {
  FILE *fp;

  if ((fp = fopen(filename, "r+b")) == NULL) Exit("File open error\n");
  if (offset == -1) offset = filelength(fileno(fp));    
  if (fseek(fp, offset, SEEK_SET)) Exit("File seek error\n");
  if (fwrite(buffer, 1, length, fp) != length) Exit("File write error\n");
  if (fclose(fp) == EOF) Exit("File close error\n");

  return(length);
}

/*----------------------------------------------------------------------------*/
void Folder(char *path) {
  int i;

  for (i = 0; path[i]; i++) {
    if ((path[i] == '/') || (path[i] == '\\')) {
      path[i] = 0;
      if (mkdir(path) > 0) Exit("Make directory error\n");
      path[i] = '/';
    }
  }
}

/*----------------------------------------------------------------------------*/
int Extension(char *fn, char *fe) {
  int ln, le;

  ln = strlen(fn);
  le = strlen(fe);

  if (!le || (ln < le)) return(0);

  while (le) if ((fe[--le] & 0xDF) != (fn[--ln] & 0xDF)) return(0);

  return(1);
}

/*----------------------------------------------------------------------------*/
void *Allocate(int length, int size) {
  char *fb;

  fb = (char *)calloc(length, size);
  if (fb == NULL) Exit("Allocate memory error\n");

  return(fb);
}

/*----------------------------------------------------------------------------*/
void *ReAllocate(void *buffer, int length, int size) {
  char *fb;

  fb = realloc(buffer, length * size);
  if (fb == NULL) Exit("Reallocate memory error\n");

  return(fb);
}

/*----------------------------------------------------------------------------*/
void Free(void *buffer) {
  free(buffer);
}

/*----------------------------------------------------------------------------*/
#endif

/*----------------------------------------------------------------------------*/
/*--  EOF                                      Copyright (C) 2010-2013 CUE  --*/
/*----------------------------------------------------------------------------*/
