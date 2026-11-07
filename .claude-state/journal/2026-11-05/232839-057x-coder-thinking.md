---
ts: 2026-11-06T06:28:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ctan8pHR2wKmbAtqoOmn
---
Wait — I should not waste too much. Also the `s32 otz = RotTransPers4` replacement inside the do-while would conflict with the loop-2 use of otz. Let me simplify: drop that variant.

Actually, let me reconsider the whole approach once more before burning tries.

Hmm, here's a thought I haven't tried: **`otz` used in the `if (i != 11)` condition of the SAME iteration**? No.

Another: what if the raw value is stored into `q`'s unused field? no.

OK here's a NEW idea that might be the actual crack: **make the second call's argument a *different variable* that is assigned from otz and live across the call**... no.

Hmm, what about **`otz` being used by the func_8012E28C call in the NEXT iteration**? no.

Let me just run the sweep (limited) and then wall.

Actually, let me simplify the sweep script — remove the risky variants. Let me rewrite it.

Actually, hold on. Let me think about the problem ONE more time, from the "what C code would produce this target" angle. 

The target:
```
otz = RotTransPers4(...);
otz = func_801823D4(otz, -0x1A);
```
compiles to:
```
jal RotTransPers4
move s1,v0
move a0,s1
jal func_801823D4
li a1,-26
move s1,v0
```
For gcc to emit `move s1,v0` + `move a0,s1`, the RTL must be (set otz v0) and (set a0 otz) NOT combined. Combine folds when otz dies. 

What if otz is ALSO used in the *next* iteration's `if (i != 11)`? No.

What if otz is a **parameter**? no.

Hmm, what if otz's type is such that the assignment from v0 is a SUBREG copy that combine can't fold? E.g. if `otz` is a `s32` but the call returns `s16`... then the extension. 

BUT: what if otz is `s16` and the *arg* is passed as `(s32)otz` where the extension... hmm, `func_801823D4(otz, -0x1A)` with otz s16 → the value is promoted to int (s32) → sign extension = sll/sra. Two insns. But what if the extension can be folded because the value is known non-negative? No.

What if otz is `u16` → andi 1 insn. Target has none.

What if otz is `u8`? andi 0xff.

No good.

OK, so the ONLY way is an extra RTL insn. The target has no extra insn — because the asm is zero bytes but still an RTL insn.

Wait... unless! What if we can produce a **zero-byte RTL insn** in plain C? Like a `(note)`? Hmm.

What about a **`do { } while (0)` that survives as a LOOP_BEG/LOOP_END note pair**? In w1 it didn't prevent the fold. Because notes don't split blocks.

What about a **`__label__`/statement expression**? no.

OK. Let me check one thing: is it possible that a *different placement* of the empty do-while (e.g., inside the do-while that wraps the call, after the call) creates a block boundary that survives? The w2 do-while's body is the call; the loop's end is right after the call. If the empty do-while is placed *inside* the loop after the call, the loop body would be `{ call; do{}while(0); }` — same.

Hmm, what if the empty do-while is placed between the call and the func_801823D4 call — w1, no effect.

OK — I'm confident this is a wall. Let me do the sweep to satisfy the bar, then record.

Actually, wait! Let me reconsider ONE thing: the `-0x1A` argument. What if `func_801823D4(otz, -0x1A)` were split into two statements:
```
s32 d = -0x1A;
otz = func_801823D4(otz, d);
```
That changes the arg setup (li a1 in the delay slot might move). Not helpful.

And what about `otz = func_801823D4(otz, -0x1A)` where the *call* is a different function (an alias)? no.

FINE. Sweep.

Actually, let me reconsider the value of continuing: maybe a smarter move is to check whether the OTHER items have the same launder pattern; if the family is uniform, all 5 will wall on the same thing. Let me check item 3 (func_80183534, 96 ins) quickly — look at its launder/pin.

Let me first run the sweep for item 1 (cheap, one command), and in parallel look at item 3's source.

Let me rewrite sweep.py to be safe.
