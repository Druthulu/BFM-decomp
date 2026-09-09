/* func_8014680C — shared body (overlay slot 0x80128158, h_exact 41135668). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_8011F9D0;
extern unsigned short D_8011F9D6;
extern unsigned short D_8011F9DA;
extern unsigned short D_8011F9DE;
extern int   D_8011FA1C;
extern int   D_8011FA20;
extern int   D_8011FA24;
unsigned short *func_8014680C(short *param_1)
{
    int iVar1, iVar2;
    unsigned short *psVar3;
    register unsigned short *psVar4 __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B headers1)
    iVar2 = 0;
    psVar4 = (unsigned short *)&(*(unsigned short *)&D_8011F9D0);
    psVar3 = psVar4;
    iVar1 = 0;
    for (; iVar2 < 8;
         psVar4 = psVar4 + 0x34, psVar3 = psVar3 + 0x34, iVar2 = iVar2 + 1, iVar1 = iVar1 + 0x68) {
        if (*psVar3 == 0) {
            *(int *)((char *)&D_8011FA1C + iVar1) = *(int *)(param_1 + 4);
            *psVar3 = *param_1;
            *(short *)((char *)&D_8011F9D6 + iVar1) = param_1[1];
            *(short *)((char *)&D_8011F9DA + iVar1) = param_1[2];
            *(short *)((char *)&D_8011F9DE + iVar1) = param_1[3];
            *(int *)((char *)&D_8011FA20 + iVar1) = *(int *)(param_1 + 6);
            *(int *)((char *)&D_8011FA24 + iVar1) = *(int *)(param_1 + 8);
            return psVar4;
        }
    }
    return (unsigned short *)0;
}
