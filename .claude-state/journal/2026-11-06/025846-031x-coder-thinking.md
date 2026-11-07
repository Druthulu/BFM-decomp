---
ts: 2026-11-06T09:58:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i5zAHsGekZwykPB2dR5L
---
`mnem` includes operands (the regex captures the rest of the line after the opcode). So "move a0,s0" is full. Good, so mine really has `nop` and no `move a0,s0`.

Hmm, but then how is the arg passed? Unless in mine, `s0` (the local var) was allocated to a0 ($4)! Let me check: mine line 2 `move s0,a0` — that's `move` to the register holding s0. If s0 were a0, the compiler would optimize away `move a0,a0`? It wouldn't emit it. But it did emit `move s0,a0`, so s0 != a0.

Wait, maybe the disassembly at line 2 shows `move s0,a0` where "s0" is the literal register name $16. Yes.

So mine's final call: no a0 setup. Could the compiler have decided func_80146C3C takes the arg in a0 from... hold on, maybe mine's line 74 jal is a different call and the `move a0,s0` is at line 73? Let me re-read dump lines 69-80:
```
69  lw v0,28(s0)
70  nop
71  addiu v0,v0,1
72  j 924
73  sw v0,28(s0)
74  jal 0 <func_800CCB20>
75  nop   | move a0,s0
76  lw ra,20(sp)
```
So mine at 74 jal with nop delay, and no move a0,s0 anywhere. That's weird.

OH WAIT. Maybe the two streams aren't aligned by index the way I assume — SequenceMatcher aligned them, but my dump prints by index i side by side. If mine has one fewer instruction before, everything after shifts. But both are 81 insns. The diff earlier said "replace mine[75:76] target[75:76]" so it's index 75. And mine[74:75] equal. So mine truly lacks move a0,s0.

Unless the arg is passed via `a0` already equal to s0's value because... the compiler knows s0 == arg0 and arg0 is in a0, but a0 got clobbered. Hmm, unless the clobber at line 15 is into a different reg in mine. Line 15 mine `lw a0,8(a1)` — yes a0 clobbered.

This suggests mine's code is actually WRONG (semantically) or the disassembler shows `nop` where the target has `move`. But scoring says score 7 with only register diffs, so the instruction words match except regs. If mine had no move, it'd be a semantic difference but the *shape* matches (both are 81 insns, and the "replace mine[75:76]" is a register-field diff: nop has word 0, move a0,s0 has word 0x00008021... those are very different words, but masked_word zeroes register fields; nop=0, move=0x00008021 & mask... opcode differs (move is addu with rs=0,rt=0? `move a0,s0` = addu a0,s0,zero = word 0x02008021? Actually move dst,src = addu dst,src,zero. Masked word keeps opcode/funct/shamt, zeroes reg fields → 0x00000021 (funct=0x21 addu, rs=0,rt=0,rd=0). nop = 0x00000000 (sll 0,0,0, funct 0). Different. So it IS a real mismatch of 1.

Hmm so where's the arg? Let me just look at mine's raw disassembly around the call via --keep and objdump. But maybe the compiler passed s0 in a0 because... let me reconsider: maybe `move a0,s0` in target is actually the delay-slot fill of the `jal`, and in mine the same move appears as part of a different insn. Wait, if mine has no move at all, then mine is semantically broken — but this is a candidate body; the scorer only compares shape, not semantics. It's possible the lever-free body genuinely produces broken code if s0 isn't a0. No — GCC wouldn't drop the arg.

Let me look more carefully: maybe mine's line 73 `sw v0,28(s0)` is in the delay slot of `j 924`, and mine's line 74 jal... Hmm.

Let me just dump with raw words to be sure. Let me modify dumpbody to print word hex too, and re-run. Actually simpler: run with --keep and objdump. Let me use the --keep path.

Actually, let me reconsider. The `((void (*)(s32))func_80146C3C)(s0)` — this is an indirect-ish call via a cast. In GCC 2.7.2, `func_80146C3C` is declared `extern void func_80146C3C(u8 *a0);`. The cast makes it a call with return type void and arg s32. The arg is s0.

In the target, `move a0,s0` in delay slot. In mine, maybe the call is emitted as `jal func_80146C3C` with a0 set by... `move a0,s0` at line 73?? No.

I need the raw. Let me update dumpbody to print the word.

Actually — the mnem for `move a0,s0`: if s0 is the variable name for the pseudo in $16, disassembly prints `move a0,s0`. If mine's s0 variable were allocated to $4 (a0), then the arg setup `move a0,<a0>` would be a no-op and removed → nop delay slot! And line 2 `move s0,a0` would be `move a0,a0`... but it shows `move s0,a0` (dst s0). Hmm, unless mine's arg0->s0 move is to $16 but the variable is named by register.

Wait, `move s0,a0` — this is the prologue `s0 = (s32)arg0`. dst=$16, src=$4. If the variable s0 were in $4, this would be `move a0,a0`, which GCC wouldn't emit. So s0 is in $16.

I'm confused; let me just get raw words.
