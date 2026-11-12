/* guess_InitPacketModel — shared body (overlay slot 0x80128158, h_exact f769ff89). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013C0F8(s32 a0);
/* guess_InitPacketModel: stores the data a1 and its body (a1 + 0x14) at +8/+0xC of a0 and relocates the data's packet links in place, once
 * Confidence low, xref chain: +8 = a1, +0xC = a1 + 0x14; func_8013C0F8 adds the base to the offsets and to the link of each GPU polygon packet (codes 0x24..0x3E)
 * Names ledger: config/names.tsv guess_InitPacketModel */
void guess_InitPacketModel(void *a0, void *a1) {
    void *p = a1;
    ((E_13C08C_8013C08C *)a0)->f8 = a1;
    ((E_13C08C_8013C08C *)a0)->fC = (u8 *)p + 0x14;
    func_8013C0F8((s32)a1);
}
