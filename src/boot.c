#include "common.h"

INCLUDE_ASM("asm/nonmatchings/boot", start);

INCLUDE_ASM("asm/nonmatchings/boot", __main);

INCLUDE_ASM("asm/nonmatchings/boot", __do_global_dtors);

INCLUDE_ASM("asm/nonmatchings/boot", main);

INCLUDE_ASM("asm/nonmatchings/boot", func_8001096C);

INCLUDE_ASM("asm/nonmatchings/boot", func_8001099C);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010A08);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010A98);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010AE0);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010B10);

/* (*gameModeHandlerTable[gameMode])() — 18 handlers @0x800629F4 (entry [7] =
 * DebugMenuHandler). gameMode is a u16 at D_800AF630 + 0xA3AE (= 0x800B99DE) in the
 * main state block. NOTE: `register` is REQUIRED to match — at -O0 (this module) it
 * keeps the struct base in a callee-saved reg with no stack spill, and the 0xA3AE
 * (>0x7FFF) member offset then assembles to the +0x10000/-0x5C52 split. */
extern void (*gameModeHandlerTable[])(void);
extern u8 D_800AF630[];
void GameModeDispatch(void) {
    register u8 *p = D_800AF630;
    gameModeHandlerTable[*(u16 *)(p + 0xA3AE)]();
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80010BB4);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010C7C);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010CEC);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010D60);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010DA0);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010DE0);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010E14);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010E48);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010E7C);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010ED4);

INCLUDE_ASM("asm/nonmatchings/boot", func_80010F80);

INCLUDE_ASM("asm/nonmatchings/boot", func_800110CC);

extern void func_8001A9F8(int);
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_80010AE0(int);
extern void func_80011778(void);
extern void func_80015310(void);
extern u8 D_800AE888;
extern void *loadDestPtrTable;
/* gameMode 7 handler (gameModeHandlerTable[7]) — the TCRF L3 debug menu. Streams the
 * room-select overlay (cdFileLocTable[11] -> 0x800CEDF8) via CdReadRequest, then inits it
 * (func_80011778 / func_80015310). Retail: only room-select works. Phase 3 T8. */
void DebugMenuHandler(void) {
    int iVar1; /* -O0 reserves this local's 8-byte slot (frame 0x20); the original
                * checks CdReadRequest's result directly (no store) — assigning iVar1
                * here would emit a store the target lacks, so it stays declaration-only. */
    func_8001A9F8(0);
    if (CdReadRequest(&D_800AE888, loadDestPtrTable, 0, 0) != 0) {
        func_80010AE0(0x3E0);
        func_80011778();
        func_80015310();
    }
    (void)iVar1;
}

INCLUDE_ASM("asm/nonmatchings/boot", func_800111BC);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011220);

INCLUDE_ASM("asm/nonmatchings/boot", func_8001125C);

INCLUDE_ASM("asm/nonmatchings/boot", func_800112A8);

INCLUDE_ASM("asm/nonmatchings/boot", func_800112C8);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011320);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011350);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011380);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011680);

INCLUDE_ASM("asm/nonmatchings/boot", func_800116E0);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011778);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011818);

INCLUDE_ASM("asm/nonmatchings/boot", func_800118AC);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011928);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011998);

INCLUDE_ASM("asm/nonmatchings/boot", func_800119F0);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011A3C);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011ADC);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011B7C);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011C10);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011C8C);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011CFC);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011D54);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011DA0);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011DCC);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011DF4);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011E24);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011E84);

INCLUDE_ASM("asm/nonmatchings/boot", func_80011EB4);

INCLUDE_ASM("asm/nonmatchings/boot", func_800120DC);

INCLUDE_ASM("asm/nonmatchings/boot", func_8001212C);
