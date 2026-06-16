/* src/shared/clearTbl40.h — shared body for the byte-identical pair func_80037004 / func_80037334
 * (Phase 11 dedup proof, group I0). The body is authored ONCE here as a macro and instantiated at
 * each member site in src/800.c, so the same bytes land at both vrams (0x80037004 + 0x80037334).
 * Registered in config/dedup.us.yaml; byte-honesty validated by tools/dedup_integrate.py.
 *
 * Clears 5 bytes of a table: D_80076251[i] = 0 for i = 0x40,0x30,0x20,0x10,0x00 (down-counting). */
#ifndef SHARED_CLEARTBL40_H
#define SHARED_CLEARTBL40_H
#include "common.h"

extern u8 D_80076251;

#define CLEAR_TBL40(name)                              \
    void name(void) {                                  \
        s32 i;                                          \
        for (i = 0x40; i >= 0; i -= 0x10) {            \
            (&D_80076251)[i] = 0;                       \
        }                                               \
    }

#endif /* SHARED_CLEARTBL40_H */
