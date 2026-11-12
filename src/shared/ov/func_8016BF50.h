/* guess_UpdateAttachedPos — shared body (overlay slot 0x80128158, h_exact 1c5bc11f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ObjRotTransSV(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
/* guess_UpdateAttachedPos: places an object at its local offset (+0x12/+0x16/+0x1A) transformed by the model matrix of its parent (*(a0 + 0x34))
 * Confidence medium, xref chain: buf = halfwords +0x12/+0x16/+0x1A; guess_ObjRotTransSV(*(a0 + 0x34), buf, buf); func_80015954 stores buf into the position +4/+8/+C
 * Names ledger: config/names.tsv guess_UpdateAttachedPos */
s32 guess_UpdateAttachedPos(s32 param)
{
    u16 buf[3];
    s32 arg;
    arg = *(s32 *)(param + 0x34);
    buf[0] = *(u16 *)(param + 0x12);
    buf[1] = *(u16 *)(param + 0x16);
    buf[2] = *(u16 *)(param + 0x1a);
    ((void (*)(s32, void *, void *))guess_ObjRotTransSV)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, param + 4);
}
