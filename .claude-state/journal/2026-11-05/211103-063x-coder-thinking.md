---
ts: 2026-11-06T04:11:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_r5frrzlRYni6Vw6KelEB
---
The first load became `lhu + sll + sra` again (60 ins), and the second load appeared (`lh v0,46` at 38? target[38]). Wait, the diff shows target[38:40] = lh v0,46; lhu v1,14, and mine has lhu+sll+sra for the first. So the double-load DID happen (the dead reset worked!), but the first load got compiled as lhu+sll+sra instead of lh. Why?

Because `x` is a separate s32 variable assigned from the s16 load, and then `diff -= x`. The compiler used a zero-extending load + sign extension? Weird. Actually, `lhu` + `sll 16` + `sra 16` is a sign extension of a halfword — but why not `lh`? Maybe because the load is HImode and the destination is a pseudo that combine/cse decides to... hmm. In the original, `diff -= *(s16*)` produced `lh` directly because the load's result feeds a SImode subu — GCC's expand emits `(set (reg) (sign_extend (mem)))` and the machine description matches sign_extend+load into `lh`? Actually for MIPS, `lh` is generated for sign_extend of HImode memory. Why would assigning to a temp change it?

Maybe the difference: with `x` as a variable, the front-end emits `x = (s32)*(s16*)` = sign_extend, and then `diff -= x`. The first assignment may be optimized... The `lhu + sll + sra` pattern suggests the load was zero-extended then sign-extended — perhaps because `x = 0` (the dead store) made cse/combine treat x as unsigned? Hmm, `x = 0` is a constant; the load into x... 

Wait, the first `lhu v1,46` then `sll v1,v1,0x10` then `sra v0,v1,0x10`: that's `(s16)lhu` — sign-extending a zero-extended halfword. GCC would do this if the source type were `u16` cast to `s16`. But our source is `*(s16*)`. Strange.

Maybe it's an artifact of cse's LOAD_EXTEND_OP handling: when it sees a HImode MEM load used as SImode, it may pick a related wider value. Hmm.

Let me try making x `s16` instead of s32:
```
s16 x;
x = *(s16*)(...);
diff -= x;
```
Then the load into x is HImode (lh), and diff -= x sign-extends x. That might produce `lh` + subu (with x in a register sign-extended already). Let me test.

Actually, in the ORIGINAL body, `diff -= *(s16*)...` gives lh. If x is s16, `x = *(s16*)` is an HImode copy (lh), and `diff -= x` needs SImode → sign_extend of x, which combine may fold back into lh? Let's test.

Also, the dead reset could be applied without a temp: how to dead-reset the load's value register without a variable? The load's result is consumed directly; there's no C variable to reassign. So we need the temp.

Let me try c9: x as s16.
```
    {
        s16 x;
        s32 diff = 8;
        x = *(s16 *)((s32)s0 + 0x2E);
        diff -= x;
        t = diff << 9;
        x = 0;
    }
```
Hmm, `x = 0` then x unused. cse invalidates x. Then second load.

But will the dead `x = 0` be seen by cse1? Yes.

Let me test c9. Also c10: x s16 but use `diff = 8 - x;`.

Actually wait: in c8, the double load happened but the FIRST load's codegen changed. The target's first load is lh. The lhu+sll+sra is 3 insns; target 1. So we need the first load to be lh.

Why did it change? Let me test c9 (s16 x).
