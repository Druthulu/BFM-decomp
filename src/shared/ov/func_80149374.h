/* guess_TransformPosByObjMatrix — shared body (overlay slot 0x80128158, h_exact 26721d91). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_CopyVec3HighHalves(s32 a0, s32 *a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);
/* guess_TransformPosByObjMatrix: transforms position a1 (s32 x/y/z) in place by object a0's model matrix with RotTransSV
 * Confidence high, xref chain: guess_CopyVec3HighHalves(a1, &sv); guess_RotTransSVWithMatrix(*(a0 + 0x20) + 0x34, &sv, &out); func_80015954(&out, a1)
 * Names ledger: config/names.tsv guess_TransformPosByObjMatrix */
void guess_TransformPosByObjMatrix(s32 arg0, s32 arg1)
{
    u64 sp10;
    u64 sp18;
    ((void (*)(s32, void*))guess_CopyVec3HighHalves)(arg1, &sp10);
    {
        void *q = &sp18;
        void *q2;
        ((void (*)(s32, void*, void*))guess_RotTransSVWithMatrix)(*(s32*)(arg0 + 0x20) + 0x34, &sp10, q);
        q = 0;
        q2 = &sp18;
        ((void (*)(void*, s32))func_80015954)(q2, arg1);
    }
}
