extern u8 D_800AF630[];
extern s32 D_80074784;
extern s32 D_8007478C;
extern u16 D_800B99E8;
extern s32 D_800629D4[];
extern u8 D_800629D6[];
extern u16 D_800629E8[];
extern u8 D_800D3A68[];
extern s32 D_800AE6A8;

extern void func_800295D4(void);
extern void func_80029664(void);
extern void func_80011DCC(void);
extern void func_80011E24(void);
extern void func_8005C4CC(s32);
extern void func_8002D4C8(s32, s32);
extern void func_80011B7C(s32);
extern void func_800118AC(void);
extern void func_80011EB4(void);
extern void func_800CEDFC(void);
extern s32 func_80014CAC(s32, s32);
extern void func_80011DA0(void);
extern void func_800D1724(s32);

/* main:func_80011380 (-O0, boot.c) -- the cookbook §474 "PROVED C-level floor" row, cracked (T5x Fable agent).
 *
 * The target's D_800629D6 index is TWO chained anonymous x2 expansions: lw;copy;sll;copy;sll (expand_mult's
 * copy_to_mode_reg + shift, expmed.c:2227/2244, twice, adjacent). §474 proved no TREE can carry MULT(MULT(i,2),2):
 * fold-const.c:882 split_tree merges it, and every escape (stmt-expr note, register decl (use) brackets) costs a suid.
 * The escape §474 did not consider is that the nested MULT need not exist at TREE level at all. In the EXPAND_SUM
 * (address) route, expr.c:5368 "Apply distributive law if OP0 is x+c" rewrites (x + c) * k with x ALREADY a (mult ..)
 * rtx into (plus (mult (mult X 2) 2) c*k) -- a nested MULT built AFTER fold, which fold never sees; fold has no
 * MULT-over-PLUS distribution, so `(i*2 + 1) * 2` survives as MULT(PLUS(MULT(i,2),1),2). The spurious +2 is cancelled
 * by the `- 2` on the index: both_summands (expr.c:5248) + simplify_binary_operation/plus_constant fold sym-2+2 into
 * the BARE symbol, so the address is (plus (mult (mult X 2) 2) sym) -> force_operand expands the two multiplies
 * back-to-back and expand_binop's copy_to_mode_reg(sym) gives the target's `la $a0; addu $v1,$v1,$a0; lbu $a0,0($v1)`.
 * No note, no variable: stupid.c's born+2 rule 2-colours the chain $v1/$a0 exactly as the target. Verified: match_one
 * MATCH 192/192 and rtu_match MATCH in src/boot.c (--o0). Semantics: (i*2+1)*2-2 == i*4. */
void func_80011380(void) {
    typedef struct {
        u8 pad00[0x16];
        u8 unk16;
    } Unk;
    register u8 *p = D_800AF630;
    Unk *q = (Unk *)&D_800AE6A8;

    switch (*(u16 *)(p + 0xA3B4)) {
    case 0:
        D_800B99E8 = 0;
        func_800295D4();
        if (D_80074784 >= 5) {
            D_80074784 = 0;
        }
        *(u16 *)(p + 0xA3D8) = D_800629D4[D_80074784];
        *(u16 *)(p + 0xA3DA) = (u16)D_800629D4[D_80074784] & 0xF000;
        q->unk16 = D_800629D6[(D_80074784 * 2 + 1) * 2 - 2];
        D_8007478C = D_800629E8[D_80074784];
        if (D_80074784 == 0) {
            func_80029664();
        }
        func_80011DCC();
        func_80011E24();
        func_8005C4CC(1);
        *(p + 0xA434) = 1;
        *(p + 0xA3E0) = 0;
        ++D_80074784;
        func_8002D4C8(0x28, 0);
        func_80011B7C(0);
        func_800118AC();
        break;
    case 1:
        if (*(p + 0xA3E0) != 0) {
            func_80011EB4();
        }
        func_800CEDFC();
        if ((s16)(++D_800B99E8) > D_8007478C ||
            ((s16)func_80014CAC(0, 0x840) != 0 && *(p + 0xA3E0) != 0)) {
            func_80011DA0();
            func_800D1724((s32)D_800D3A68);
            func_800118AC();
        }
        break;
    case 2:
        func_800CEDFC();
        break;
    }
}
