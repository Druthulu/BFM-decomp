---
ts: 2026-11-06T21:42:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SWyAHWzFy4ixJ2M8CzDv
---
The launder is at `iv2c = iVar2; __asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));` followed by `one = 1; if (iv2c != one) uVar5 = 0;`.

The target asm (from notes): without launder, `iv2c = iVar2` folds into iVar2 (no `move v1,a0`). The launder forces iv2c into a fresh pseudo tied to iVar2's value? Actually "=r" with "0" constraint: output in same register as input — forces a copy to a new register? Hmm, it forces the value into a register, but the notes say it's anti-coalescing: it keeps `iv2c` in a distinct register (the move v1,a0 survives).

Wait — the note says "without it `iv2c = iVar2` folds into iVar2 (no `move v1,a0`)". So target has a `move v1,a0` and the launder creates it.

Real-C alternatives to create a copy that survives cse:
1. s16/s16-width temp: `int t2 = (short)iVar2; iv2c = t2;` — HImode copy escapes cse (per func_80182ED4). But the value iVar2 is compared with 1 and used as a flag; sign extension might be fine if iVar2 is 0/1? Actually iVar2 = t+1 or 1, t = param_2>>16 & 0xf, so iVar2 in 1..16. `(short)` copy is a no-op semantically but in RTL it's a sign_extend — could generate extra insns. In func_80182ED4, `tmp=(s16)t; u=tmp` produced `or v1,v0`? Hmm, they said the HImode copy escapes cse so `or v1,v0` survives. That's for a case where target has `or v1,v0` (move spelled or). 

Here the target's move is `move v1,a0`. A sign-extend of a value in a0 would be sll/sra unless combine proves it's already sign-extended. Risky but worth trying: maybe cse keeps the HImode copy and combine folds `(short)x` when x is known... no, it can't know.

2. do-while around the copy (C0535): `do { iv2c = iVar2; } while (0);` — an EBB split might prevent cse copy propagation? Actually cse propagates copies across blocks; a do-while makes a new basic block boundary, which could stop cse's copy propagation (cse works per extended basic block). That's promising! And the G31 notes say the launder's mechanism is anti-coalescing at cse. If `iv2c = iVar2` is in its own EBB, cse can't merge... hmm, but then the copy might still be optimized by combine/local-alloc coalescing later? The launder is an asm barrier, so the value is in a register at that point.

Wait, actually the mechanism: the copy `iv2c = iVar2` — for the move to survive, iv2c must be a distinct pseudo not coalesced with iVar2 by cse's copy propagation. cse replaces uses of iv2c with iVar2 when the copy reaches. If the copy is in a separate EBB (do-while), cse's copy table doesn't carry across... but the use is right after within the same block. Hmm, do-while splits the block so the copy is in block A and the use in block B; cse processes each EBB; the use in B won't see the copy from A (cse's copy table resets at block boundaries unless it's the same extended block). Then local-alloc might coalesce iv2c and iVar2 anyway if they don't conflict... but iv2c's live range is short and iVar2 continues to live after? If iVar2 is used later (it is: `r = (uint)(iVar2 << 3) | c6b`), then coalescing iv2c with iVar2 would extend... coalescing qty's only when one dies at the copy. iVar2 doesn't die at the copy, so no coalesce. Then the copy stays as a move. 

So `do { iv2c = iVar2; } while (0);` is a strong candidate. Let me test.

3. Another: make iv2c a different width var, or declare it at a different scope.

The notes say q1 = p1 + do-while on the uVar1 store. p1 has launder kept, score 2. So I take prev_win (q1) and replace the launder line with a real-C move.

Test candidates:
- w1: `do { iv2c = iVar2; } while (0);` replacing the asm line.
- w2: s16 temp: `iv2c = (short)iVar2;` (just the cast).
- w3: temp with s16: `{ short s = (short)iVar2; iv2c = s; }`... 

Header items: score on includer 0 first, then verify all 141.

Let me check the header file location and how tryinc works. `.run/P40/T10/tryinc.py <k> <header> <fn> <body>`. And prev_win.c is the body.

First: FRESH — orig.c from src header. The item dir has no orig.c either? ls showed fn, kinds, notes.md, prev_win.c, tu. So create orig.c = current header (the whole file? or the body?). tu = src/shared/ov/func_80177EA4.h — the header itself. For header items, orig.c likely the header content. Let me copy the header to orig.c (it's small, 2.4KB).

Then test w1 via tryinc.py 0.
