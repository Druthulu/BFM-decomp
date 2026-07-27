#include "common.h"
extern s32 D_801ED9F4;
extern void B(void);
void pA(void){ D_801ED9F4++; if (D_801ED9F4 > 0x8A) { B(); } }
void pB(void){ D_801ED9F4++; if (D_801ED9F4 >= 0x8B) { B(); } }
void pC(void){ D_801ED9F4++; if (0x8A < D_801ED9F4) { B(); } }
void pD(void){ D_801ED9F4++; if (0x8B <= D_801ED9F4) { B(); } }
void pE(void){ D_801ED9F4++; if (!(D_801ED9F4 <= 0x8A)) { B(); } }
void pF(void){ if (++D_801ED9F4 > 0x8A) { B(); } }
void pG(void){ D_801ED9F4++; if (D_801ED9F4 <= 0x8A) return; B(); }
void pH(void){ s32 k = 0x8A; D_801ED9F4++; if (k < D_801ED9F4) { B(); } }
