---
ts: 2026-11-06T05:33:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HpQlNszcstwoiBixRrYi
---
The dump shows many functions (the TU has many functions). The first function's reg74 is at line 46 (insn 13?). Hmm, that's a different numbering. Actually the cse2 dump has multiple functions; the first ";; Function func_80181784" region.

This is getting deep. Let me change tack: instead of analyzing, let me try a *bunch* of variants systematically. I'll generate variants programmatically with different combinations and score them all in one sc.sh call. That's cheap.

Dimensions:
A. copy form: `tmp = iVar2;` / `tmp = (s16)iVar2;` / `tmp = (u16)iVar2;` / `tmp = (s32)iVar2;`
B. iVar2 decl: s32 / s16 / u16
C. tmp decl: s32 / s16 / u16
D. copy placement: inside-if (current) / hoisted
E. second test: iVar2 / tmp
F. declaration order: iVar1,iVar2,tmp / tmp,iVar2,iVar1 / iVar2,tmp,iVar1

That's a lot, but sc.sh can score many. Let me generate ~20 combos and score. Each score takes ~1s? The sc.sh loop runs delever_search per file; 20 files might take a minute. Acceptable.

Let me write a generator script under .run (scratch) and run it.

Actually the sed approach is getting messy. Let me write a Python generator that takes the orig.c text and applies a structured template. Let me just build the body from a template with placeholders.

Let me write a script .run/P40/T11/G22/gen2.py that emits variants.

Template:
```c
void func_80181784(s32 a0)
{
    s32 iVar1;
    <IV2DECL>
    <TMPDECL>
    s32 pad[4];

    func_80181B00(a0);
    func_801820F8(a0);

    iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
    iVar2 = CAST_SIGN(s16, iVar1, 0x10);
    <PRE>
    if (iVar2 != 0) {
        <COPY>
        if (<TEST2>) {
            tmp += 0x80;
            ((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;
            if (0 < tmp * 0x10000) {
                ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk10 = 0;
            }
        } else {
            tmp -= 0x80;
            ((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;
            if (tmp * 0x10000 < 0) {
                ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk10 = 0;
            }
        }
        iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
    }

    iVar2 = CAST_SIGN(s16, iVar1, 0x12);
    ... (same for second)
    skip2:
    if (*(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x10) == 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x50;
        CAST_SIGN(u16, a0, 0x2) += 1;
    }
}
```

Let me read the full orig to get the second block exactly. I have orig.c (the exact function). I'll do string replacement on it, which is what I've been doing.

Let me write the generator with the specific replacements and run ~16 combos.

Actually, my earlier attempts covered most of these. The results: any HImode cast copy keeps the copy but swaps iVar1/iVar2. The plain copy merges.

Hmm, so the question is whether ANY variant can both keep the copy and get the right allocation. Given the priority math (iVar2 pri 9.6-12 vs iVar1 5.33), we need iVar2's priority to drop below 5.33 while the copy survives.

iVar2 HImode (size 2): pri 4.8 < 5.33 ✓ — but the copy must survive AND the load must be `lh` (signed). d1 had iVar2 s16 + tmp s16 → lhu + spill. What about iVar2 s16 + tmp s32 + `tmp = (s16)iVar2`? d5 = 8. Hmm, d5 merged?

Let me look at d5's asm. Actually d5 = iVar2 s16, copy `tmp = (s16)iVar2;` → since iVar2 is already s16, `(s16)iVar2` is a no-op → plain copy → merged. Right.

What about iVar2 s16 + `tmp = (s32)iVar2;` = d2 (8). d2 merged too? The `(s32)` cast is also a no-op at the C level.

So to keep the copy with iVar2 HImode, we need a cross-mode op that isn't a no-op. Hmm.

What about iVar2 s16, tmp s32, and the copy written as `tmp = iVar2 + 0;`? Folds.

Hmm, what if iVar2 is s16 and the copy is `tmp = (s16)iVar2;` where tmp is s32 — that's a no-op cast (sign-extend of s16 → s32 is implicit). cse merges.

So HImode iVar2 gives pri 4.8 but the copy merges. And SI iVar2 keeps the copy (with the (s16) cast) but pri 9.6.

Is there a way to get iVar2 HImode in the qty sense but SI in the copy sense? The qty size comes from the mode of the register in the RTL. If iVar2's RTL register is SI (reg74) with the sign-extend chain, size=4.

Hmm, what if the sign-extend is done differently so iVar2's qty is HImode but used as SI via subreg? That's what `s16 iVar2` does.

Let me try: iVar2 s16, tmp s32, copy `tmp = (s32)iVar2;` and see the RTL. d2 scored 8 — let me check d2's diff to see if the copy survived.

Actually, let me check d2 and d5 diffs quickly to know whether they merged or swapped.
