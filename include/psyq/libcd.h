/* psyq/libcd.h — PSY-Q libcd (CD-ROM) types & prototypes used by the file loader.
 *
 * Struct layouts are the authoritative ones from the imported PsyQ 4.0 .gdt
 * (Ghidra category /LIBCD.H) — verified offsets/sizes, not guessed (G1). Function
 * prototypes use the canonical PsyQ signatures; their symbols are pinned in
 * config/symbols.us.txt (and already named in the Ghidra DB). Grow this as more
 * libcd surface is matched. Companion to common.h (provides the u8/u32 typedefs).
 */
#ifndef PSYQ_LIBCD_H
#define PSYQ_LIBCD_H

#include "common.h"

/* CD logical location — minute/second/sector are BCD. 4 bytes. (/LIBCD.H) */
typedef struct {
    u8 minute; /* +0x00 */
    u8 second; /* +0x01 */
    u8 sector; /* +0x02 */
    u8 track;  /* +0x03 */
} CdlLOC;

/* CD file descriptor (CdSearchFile result / directory entry). 24 bytes. (/LIBCD.H) */
typedef struct {
    CdlLOC pos;      /* +0x00  file start location */
    u32    size;     /* +0x04  file size in bytes   */
    char   name[16]; /* +0x08  file name            */
} CdlFILE;

/* libcd prototypes (symbols in config/symbols.us.txt). */
extern CdlFILE *CdSearchFile(CdlFILE *fp, char *name); /* 0x80045374 */
extern int      CdPosToInt(CdlLOC *p);                 /* 0x80043B1C */
extern CdlLOC  *CdIntToPos(int i, CdlLOC *p);          /* 0x80043A18 */

#endif /* PSYQ_LIBCD_H */
