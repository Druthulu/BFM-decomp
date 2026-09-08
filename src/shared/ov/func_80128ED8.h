/* func_80128ED8 — shared body (overlay slot 0x80128158, h_exact e4095201). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80128ED8(s32 param_1, s32 *param_2) {
    register s32 iVar4 __asm__("$8");   /* base ptr, lives whole fn in $t0 */
    register s32 cnt   __asm__("$2");   /* decremented count in $v0 */
    register s32 cc    __asm__("$3");   /* preserved count copy in $v1 (forces the bne-delay-slot copy) */
    register s32 idx   __asm__("$3");   /* offset-4 index, loaded into $v1 */
    register s32 idc   __asm__("$7");   /* $a3: preserved idx copy, forced SEPARATE from the multiply */
    u32 uVar3;
    s32 frame_pad[4];                   /* phantom 0x10 frame the target reserves (induce via clobber anchor) */
    __asm__ __volatile__("" : : "r"(&frame_pad) : "memory");
    iVar4 = *param_2;
    cnt = *(s16 *)((s32)param_2 + 6);
    if (cnt == 0) {
        return 1;
    }
    cc = cnt;
    __asm__ __volatile__("" : "=r"(cc) : "0"(cc));   /* force the count-preserve copy ($v1=$v0) */
    cnt = cc - 1;
    *(s16 *)((s32)param_2 + 6) = (s16)cnt;
    if (cnt * 0x10000 < 1) {
        idx = *(s16 *)((s32)param_2 + 4);
        __asm__ __volatile__("" : "=r"(idx) : "0"(idx));   /* pin the index into $v1 */
        uVar3 = *(u32 *)(idx * 8 + iVar4 + 4);
        idc = idx;
        if ((uVar3 & 0xc0) == 0xc0) {
            *(s16 *)((s32)param_2 + 6) = 0;
            return 1;
        }
        if ((uVar3 & 0x80) != 0) {
            *(s16 *)((s32)param_2 + 4) = 0;
        } else {
            cnt = idc + 1;                       /* reuse the dead $v0 pin so idc+1 lands in $v0, not $a3 */
            *(s16 *)((s32)param_2 + 4) = cnt;
        }
        *(u16 *)((s32)param_2 + 6) =
            (u16)(*(u32 *)((s16)param_2[1] * 8 + iVar4 + 4) & 0x3f);
        *(u16 *)(param_1 + 0x28) = *(u16 *)((s16)param_2[1] * 8 + iVar4);
        *(u16 *)(param_1 + 0x2a) = *(u16 *)((s16)param_2[1] * 8 + iVar4 + 2);
    }
    return 0;
}
