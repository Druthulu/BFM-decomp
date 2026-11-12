/* func_8014B944 — shared body (overlay slot 0x80128158, h_exact 7918269a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_TestGameFlag(s32 arg);
extern u8 guess_g_PlayerRecord[]; // Names ledger: config/names.tsv guess_g_PlayerRecord
extern s32 D_80078EA4;
extern u16 D_80078EA6;
void func_8014B944(s32 a0, s32 a1, s32 a2)
{
    u8 *base = guess_g_PlayerRecord;
    if (a2 != 0) {
        D_80078EA4 += a1;

do {  // !FAKE: do-while
        if ((s16)D_80078EA6 >= 0xA1) {
            D_80078EA4 = 0xA00000;
        }
} while (0);
    } else {
        if ((guess_TestGameFlag(0x1B) & 0xFF) != 0) {
            D_80078EA4 += a1;

do {  // !FAKE: do-while
            if ((s16)D_80078EA6 >= 0xA1) {
                D_80078EA4 = 0xA00000;
            }
} while (0);
        } else {
            if ((s16)D_80078EA6 < 0x80) {
                D_80078EA4 += a1;

do {  // !FAKE: do-while
                if (((union U2 *)&D_80078EA6)->s >= 0x81) {
                    D_80078EA4 = 0x800000;
                }
} while (0);
            }
        }
    }
    if (a2 != 0) {
        *(s32 *)(base + 0x60) += a1;
        if (*(s16 *)(base + 0x62) >= 0xA1) {
            *(s32 *)(base + 0x60) = 0xA00000;
        }
    } else {
        if ((guess_TestGameFlag(0x1B) & 0xFF) != 0) {
            *(s32 *)(base + 0x60) += a1;
            if (*(s16 *)(base + 0x62) >= 0xA1) {
                *(s32 *)(base + 0x60) = 0xA00000;
            }
        } else {
            if (*(s16 *)(base + 0x62) < 0x80) {
                *(s32 *)(base + 0x60) += a1;
                if (*(s16 *)(base + 0x62) >= 0x81) {
                    *(s32 *)(base + 0x60) = 0x800000;
                }
            }
        }
    }
}
