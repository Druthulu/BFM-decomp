/*----------------------------------------------------------------------------*/
/*--  brave.c                                                               --*/
/*--  Simple extractor for 'Brave Fencer Musashi' - PSX                     --*/
/*--  Copyright (C) 2012-2013 CUE                                           --*/
/*--                                                                        --*/
/*--  This program is free software: you can redistribute it and/or modify  --*/
/*--  it under the terms of the GNU General Public License as published by  --*/
/*--  the Free Software Foundation, either version 3 of the License, or     --*/
/*--  (at your option) any later version.                                   --*/
/*--                                                                        --*/
/*--  This program is distributed in the hope that it will be useful,       --*/
/*--  but WITHOUT ANY WARRANTY; without even the implied warranty of        --*/
/*--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          --*/
/*--  GNU General Public License for more details.                          --*/
/*--                                                                        --*/
/*--  You should have received a copy of the GNU General Public License     --*/
/*--  along with this program. If not, see <http://www.gnu.org/licenses/>.  --*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
#include "common.inc"

/*----------------------------------------------------------------------------*/
#define SECTOR_SIZE  0x800

#define PAC_HEADER   0x00434150

/*----------------------------------------------------------------------------*/
#define POS_BITS  10
#define THRESHOLD 1
#define N         (1 << POS_BITS)
#define F         ((1 << (16 - POS_BITS)) + THRESHOLD)
unsigned char     ring[N+F-1];

/*----------------------------------------------------------------------------*/
void Title(void);
void Usage(void);
void Extract(char *filename);
void UnPAC(char *filename, unsigned char *buffer);
void Decode(char *filename, unsigned char *buffer, unsigned int length);

/*----------------------------------------------------------------------------*/
int main(int argc, char **argv) {
  int arg;

  Title();
  if (argc < 2) Usage();

  for (arg = 1; arg < argc; arg++) Extract(argv[arg]);

  printf("\nDone\n");

  exit(EXIT_SUCCESS);
}

/*----------------------------------------------------------------------------*/
void Title(void) {
  printf(
    "\n"
    "BRAVE - Copyright (C) 2012-2013 CUE\n"
    "Simple extractor for 'Brave Fencer Musashi' - PSX\n"
    "\n"
  );
}

/*----------------------------------------------------------------------------*/
void Usage(void) {
  Exit(
    "Usage: brave file [file [...]]\n"
    "\n"
    "* multiple filenames and wildcards are permitted\n"
    "* file must be a valid '.cd' file from the game\n"
  );
}

/*----------------------------------------------------------------------------*/
void Extract(char *filename) {
  unsigned char *buffer, name[256];
  unsigned int  *ptr, length, total, pos, len;
  unsigned int   i;

  printf("- %s\n", filename);

  length = FileSize(filename);
  if (length > MEGA_128) Exit("File too big\n");
  buffer = FileLoad(filename);

  ptr = (unsigned int *)buffer;

  total = *ptr++;
  ptr++;

  for (i = 0; i < total; i++) {
    pos = *ptr++ * SECTOR_SIZE;
    len = *ptr++;

    sprintf(name, "%s.dir/FILE_%03d", filename, i);
    printf("  + FILE_%03d", i);

    FileSave(name, buffer + pos, len);

    UnPAC(name, buffer + pos);
  }

  free(buffer);
}

/*----------------------------------------------------------------------------*/
void UnPAC(char *filename, unsigned char *buffer) {
  unsigned char name[256];
  unsigned int  header, pos, len, num, end;
  unsigned int  i;

  header = *(unsigned int *)buffer;
  if (header == PAC_HEADER) {
    pos = 0;
    do {
      num = buffer[pos + 0x04];
      end = buffer[pos + 0x05];
      len = *(unsigned int *)(buffer + pos + 0x0C);

      sprintf(name, "%s.dir/%03d", filename, num);
      printf(", %03d", num);

      if (num == 4)
        Decode(name, buffer + pos + SECTOR_SIZE, len - SECTOR_SIZE);
      else
        FileSave(name, buffer + pos + SECTOR_SIZE, len - SECTOR_SIZE);

      pos += (len + SECTOR_SIZE - 1) & -SECTOR_SIZE;
    } while (!end);
  }

  printf("\n");
}

/*----------------------------------------------------------------------------*/
void Decode(char *dec_name, unsigned char *encoded, unsigned int length) {
  unsigned char *decoded;
  unsigned int   max_size, dec_size, enc_size, r, flags, code, pos, len;
  unsigned int   i;

  max_size = KILO_128;
  decoded = Allocate(max_size, sizeof(char));

  dec_size = 0;
  enc_size = 0;

  r = 0;
  flags = 0;

  while (enc_size < length) {
    if (!((flags >>= 1) & 0xFF00)) flags = 0xFF00 | encoded[enc_size++];

    if (flags & 1) {
      code = encoded[enc_size++];
      decoded[dec_size++] = code; ring[r] = code; r = (r + 1) & (N - 1);
    } else {
      code = *(unsigned short *)(encoded + enc_size); enc_size += 2;

      pos = code & (N - 1);
      len = (code >> POS_BITS) + THRESHOLD;

      for (i = 0; i <= len; i++) {
        code = ring[(pos - 1 + i) & (N - 1)];
        decoded[dec_size++] = code; ring[r] = code; r = (r + 1) & (N - 1);
      }
    }

    if (dec_size + KILO_1 >= max_size) {
      while (dec_size + KILO_1 >= max_size) max_size += KILO_64;
      decoded = ReAllocate(decoded, max_size, sizeof(char));
    }
  }

  FileSave(dec_name, decoded, dec_size);

  Free(decoded);
}

/*----------------------------------------------------------------------------*/
/*--  EOF                                      Copyright (C) 2012-2013 CUE  --*/
/*----------------------------------------------------------------------------*/
