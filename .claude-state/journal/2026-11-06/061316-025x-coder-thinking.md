---
ts: 2026-11-06T13:13:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NWVuGm8g1di4sq0BNthX
---
So barrier-free = score 23, 189 ins vs 196. Now we need a real-C way to keep both copies.

The two copies:
- case 1 tail:
```
        ((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
        if (((Unkstruct_800B5CB8 *)param_1)->unk1C < 0x10) {
            goto TAIL;
        }
        goto HITSTUN;
```
- case 3 body:
```
    case 3:
        ((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
        if (((Unkstruct_800B5CB8 *)param_1)->unk1C < 0x10) {
            goto TAIL;
        }
        goto HITSTUN;
```

Wait, actually which pair is merged? The barrier is in case 3. Comment says case1's counter tail is byte-identical to whole of case 3's body.

Idea: make case 3's version use a different statement order/expression that compiles to the same instructions but different RTL. Since rtx_renumbered_equal_p allows register renaming, we need an opcode/operand-shape difference that vanishes in final code. 

Zero-cost RTL differences that don't affect final code are rare. But one classic: an extra (set (reg) (reg)) copy that local-alloc coalesces away (move a,a deleted). Or a USE/CLOBBER — win: `if (GET_CODE (p1) != USE && GET_CODE (p1) != CLOBBER)` — USE/CLOBBER insns are skipped for matching and don't count toward minimum! Wait: at "win:", if the pattern is USE or CLOBBER, it does NOT set last1/last2 and does NOT decrement minimum. But it still required `rtx_renumbered_equal_p(p1,p2)` to pass! So a USE/CLOBBER in one stream only would cause mismatch at that point and break. Hmm, unless both have it.

Hmm. But the mismatch breaks the walk and minimum stays 2 → no merge. That's what we want, and USE/CLOBBER insns emit no code! But how to generate a USE insn from real C? A use of a variable after... Actually USE insns are generated for things like `__builtin_apply` or asm operands. Real C doesn't produce bare USE. CLOBBER is produced for things... at jump2 stage, CLOBBER insns appear for return value regs? Actually expand emits (clobber (reg)) at function entry? Hmm.

Alternative: cause a REG_EQUAL note difference? The special case at 2476: if patterns don't match but both have REG_EQUAL notes to the same constant, it can substitute and retry. Not helpful.

Another idea: make one copy's compare use a different constant spelling that folds to the same but... no.

What about a different but equivalent instruction with a REG_EQUAL note? No.

OK, think about what actually differs between the two streams in the target: both copies exist, meaning the original compiled source produced different RTL. The original source was probably written differently, e.g. case 1's tail used `if (p->unk1C < 0x10) goto TAIL; goto HITSTUN;` and case 3 used something like `if (p->unk1C >= 0x10) goto HITSTUN; goto TAIL;`? That would produce slti/beq vs slti/bne — different opcodes. Target has beqz (from the diff: target `beqz v0,a20`). Both copies in target: let me look at the target asm to see if the two copies have identical instructions. From the diff at target[107:115]: lw v0,28(s0); nop; addiu v0,v0,1; sw v0,28(s0); slti v0,v0,16; beqz v0,a20; nop; j a70. And the first copy (merged mine) at 103: bnez v0,9a4... hmm.

Let me dump the target and mine fully to compare. dt.sh prints the whole diff; let me capture with tail large into a file? Output >40 lines → use run.sh. But easier: use dt.sh and redirect to a file under my dir, then read ranges.

Actually the real question: how do the two target copies differ, if at all? If they're byte-identical, the RTL must have differed in a way that vanished. If they differ, we can mimic.

Let me dump the target function from build baseline. Use objdump? There's hdump.sh for headers. For a TU, tools/cc1_dumps_tu.sh. Simpler: the diff output gives mine vs target. Let me capture full output to a file.

Plan: `.run/P40/T11/bin/dt.sh $d $d/w1.c 400 > $d/diff1.txt` then read the file ranges (it's text, under 20k? maybe ~200 lines). Then examine.

Wait — "One action per command" mostly about results.tsv fixes. Fine.

Let me do it.
