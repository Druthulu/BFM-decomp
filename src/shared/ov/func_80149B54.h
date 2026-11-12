/* guess_IsTrianglePressed — shared body (overlay slot 0x80128158, h_exact fc2a0a65). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 func_8014BEF8(void);
/* guess_IsTrianglePressed: returns 1 when Triangle (0x10) is newly pressed (+0xAC) and game flag 0x80 is set, 0 when bit 0x400 of +0x44 is set
 * Confidence medium, xref chain: +0x44 & 0x400 -> 0; func_8014BEF8() (guess_TestGameFlag(0x80)) == 0 -> 0; else (+0xAC & 0x10) != 0
 * Names ledger: config/names.tsv guess_IsTrianglePressed */
s32 guess_IsTrianglePressed(s32 * arg0)
{
    s32 var_v0;
    u32 temp;
    if ((*(u32*)((u8*)arg0 + 0x44) & 0x400) != 0) { var_v0 = 0; goto end; }
    if (((s32(*)(s32*))func_8014BEF8)(arg0) == 0) { var_v0 = 0; goto end; }
    temp = *(u16*)((u8*)arg0 + 0xAC) & 0x10;
    var_v0 = temp != 0;
end:
    return var_v0;
}
