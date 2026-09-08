/* func_80144B14 — shared body (overlay slot 0x80128158, h_exact 87f3b730). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern u16 D_80126B62;
extern s32 func_80013294(void *a0, void *a1);
int func_80144B14(int param_s0)
{
    u16 local_buf1[3];
    u16 local_buf2[3];
    s32 call_result;
    local_buf1[0] = *(u16 *)((char *)param_s0 + 0x6);
    local_buf1[1] = *(u16 *)((char *)param_s0 + 0xA);
    local_buf1[2] = *(u16 *)((char *)param_s0 + 0xE);
    local_buf2[0] = D_80126B5E;
    local_buf2[1] = D_80126B62;
    local_buf2[2] = D_80126B66;
    call_result = func_80013294(local_buf1, local_buf2);
    if (call_result < *(s16 *)((char *)param_s0 + 0xFC)) {
        return *(u32 *)((char *)param_s0 + 0xCC);
    }
    return 0;
}
