/* func_8012D098 — shared body (overlay slot 0x80128158, h_exact 182a812c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012D3B4(s32 arg0, s32 arg1, s32 arg2);
void func_8012D098(u16 *param_1, u32 param_2)
{
    s32 bufA[2];
    s32 bufB[2];
    s32 bufC[2];
    s32 bufD[2];
    s32 bufE[2];
    s32 bufF[2];
    s32 bufG[2];
    s32 bufH[2];
    u16 scratch[3];
    if (param_1 != 0 && *param_1 != 0) {
        if (param_2 == 0) {
            if (*(u32 *)(param_1 + 0x2c) == 0) {
                return;
            }
            param_2 = (*(u32 *)(param_1 + 0x2c) & 0xfffffff) | 0x80000000;
        }
        scratch[0] = *(u16 *)(param_2 + 4);
        scratch[1] = *(u16 *)(param_2 + 8);
        scratch[2] = *(u16 *)(param_2 + 0xc);
        func_8012F214(param_1, scratch, bufA);
        scratch[0] = *(u16 *)(param_2 + 6);
        scratch[1] = *(u16 *)(param_2 + 8);
        scratch[2] = *(u16 *)(param_2 + 0xc);
        func_8012F214(param_1, scratch, bufB);
        scratch[0] = *(u16 *)(param_2 + 4);
        scratch[1] = *(u16 *)(param_2 + 0xa);
        scratch[2] = *(u16 *)(param_2 + 0xc);
        func_8012F214(param_1, scratch, bufC);
        scratch[0] = *(u16 *)(param_2 + 6);
        scratch[1] = *(u16 *)(param_2 + 0xa);
        scratch[2] = *(u16 *)(param_2 + 0xc);
        func_8012F214(param_1, scratch, bufD);
        scratch[0] = *(u16 *)(param_2 + 4);
        scratch[1] = *(u16 *)(param_2 + 8);
        scratch[2] = *(u16 *)(param_2 + 0xe);
        func_8012F214(param_1, scratch, bufE);
        scratch[0] = *(u16 *)(param_2 + 6);
        scratch[1] = *(u16 *)(param_2 + 8);
        scratch[2] = *(u16 *)(param_2 + 0xe);
        func_8012F214(param_1, scratch, bufF);
        scratch[0] = *(u16 *)(param_2 + 4);
        scratch[1] = *(u16 *)(param_2 + 0xa);
        scratch[2] = *(u16 *)(param_2 + 0xe);
        func_8012F214(param_1, scratch, bufG);
        scratch[0] = *(u16 *)(param_2 + 6);
        scratch[1] = *(u16 *)(param_2 + 0xa);
        scratch[2] = *(u16 *)(param_2 + 0xe);
        func_8012F214(param_1, scratch, bufH);
        func_8012D3B4(bufA, bufB, 0xffffff);
        func_8012D3B4(bufB, bufD, 0xffffff);
        func_8012D3B4(bufD, bufC, 0xffffff);
        func_8012D3B4(bufC, bufA, 0xffffff);
        func_8012D3B4(bufE, bufF, 0xffffff);
        func_8012D3B4(bufF, bufH, 0xffffff);
        func_8012D3B4(bufH, bufG, 0xffffff);
        func_8012D3B4(bufG, bufE, 0xffffff);
        func_8012D3B4(bufA, bufE, 0xffffff);
        func_8012D3B4(bufB, bufF, 0xffffff);
        func_8012D3B4(bufC, bufG, 0xffffff);
        func_8012D3B4(bufD, bufH, 0xffffff);
    }
    return;
}
