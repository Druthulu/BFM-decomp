/* func_8012C098 — shared body (overlay slot 0x80128158, h_exact df79b18a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C218(void *a0);
/* $v0 at exit: leftover of void func_8012C218; no byte-neutral return: `return 0;` puts `move v0,zero` at +0x48 and moves `addiu sp` into the jr delay slot +0x50, ov_SC02_027 objdump */
s32 func_8012C098(void *param_1)
{
    int iVar1;
    iVar1 = *(int *)((char *)param_1 + 0x68);
    if ((iVar1 != 0) && ((*(short *)((char *)param_1 + 0x72) & 0x8000) != 0)) {
        *(unsigned short *)(iVar1 + 10) = *(unsigned short *)(iVar1 + 10) & 0x7fff;
    }
    func_8012C218(param_1);
    return;
}
