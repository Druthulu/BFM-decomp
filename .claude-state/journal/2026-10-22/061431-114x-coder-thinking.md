---
ts: 2026-10-22T12:14:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_MzH817dHqXBPpOWkCXVi
---
Item 5 (q07, score 16): the residual is a REGISTER ALLOCATION difference (v1 vs v0) and some instruction ordering. The structure is nearly identical! The target uses v0/a1/v1 differently.

Hmm, the diff is mostly register transposition (v1->v0 x2). The count is exact (111 = 111).

Interesting: the target's:
```
26: lw v0,108(s1)
27: ...
28: lhu v0,6(v0)     <- hmm, "lhu v0,6(v0)"? that's reading from v0 which was loaded... odd
29: lui v1,0x0
30: addiu v1,v1,0
31: sh v0,0(v1)
32: lw v0,108(s1)
```
vs mine:
```
26: lw v1,108(s1)
28: lhu v0,6(v1)
29: lui at,0x0
30: sh v0,0(at)
31: lw v1,108(s1)
```
So the target uses `lui v1` for the address D_80190048 (in v1) while mine uses `at`. And the target's `lw v0,108(s1)` where mine has `lw v1,108(s1)`.

So the differences are register allocations and the `lui/addiu` vs `lui at` spelling.

Hmm, "lui at,0x0 / sh v0,0(at)" — mine uses the `at` register for the address; the target uses v1 (a general register). That's because in the target, `p10` (the pointer) is kept in a register (v1) across the asm, whereas in mine it's rematerialized into `at`.

Hmm, and the target has an extra `lw v0,108(s1)` at 32 (mine doesn't have it there).

So the target has MORE loads of unk6C (108(s1)) — 3 of them? Let me count: target 26, 32, 38 = 3 loads; mine 26, 31, 38 = 3 loads. OK same count, different placement.

The differences are register-allocation-ish. Hmm, this needs the p10 re-tie's effect (the p10 pointer kept in a register).

Since q07 changed the 2nd `o = unk6C` load's spelling and got 111 ins exact, let me try more variations around it.

**IDEA for item 5**: the `p10` pointer should be kept in a register (v1) across the store. In mine it's rematerialized (lui at). To keep it in a register, p10 must be LIVE across the `*p10 = v6` store and the subsequent `*(u16 *)((u8*)p10+0x10) = g5e` store. Hmm, in the target:
```
29: lui v1,0x0
30: addiu v1,v1,0
31: sh v0,0(v1)     <- *p10 = v6
32: lw v0,108(s1)
33: ...
34: lhu v0,10(v0)
...
39: lw v0,108(s1)
40: lui a1,0x0
41: lhu a1,0(a1)
42: lhu v0,14(v0)
43: lui at,0x0
44: sh v0,0(at)      <- hmm, sh v0,0(at)?
45: sh a1,16(v1)     <- *(u16*)(p10+0x10) = g5e
```
So the target keeps p10 in v1 across the whole thing, and uses `at` for D_8019004C's address.

In mine:
```
29: lui at,0x0
30: sh v0,0(at)
...
42: lui at,0x0
43: sh v0,16(at)
```
So mine rematerializes the address into `at` each time. The target keeps p10 in v1.

**=> The p10 re-tie (the asm) is what keeps p10 in a register!** Without it, GCC rematerializes the address.

So: to keep p10 in a register, p10 must be "used" in a way that requires it to be in a register — e.g., if `p10` is used AFTER a call (the call clobbers at), then p10 must be in a callee-saved register... but the target has it in v1 (a caller-saved reg!). Hmm, and the target's v1 survives... hmm, there's no call between.

Hmm, in mine, GCC chose to rematerialize p10 (a "rematerializable" address) because the address is a constant symbol → reload can rematerialize it. The target keeps it in v1.

**How to keep an address in a register in plain C?** Per the cookbook: "A named derived pointer `q = p - k` that cse keeps as a REGISTER address (find_best_addr, cse.c:2656-2721) — the `la` lever." and "§153 — THE ADDRESS-REMATERIALISATION LAUNDER: a third zero-emission asm lever".

So the ASM re-tie on p10 prevents the rematerialization! And the plain-C equivalent: **make the address non-rematerializable**, e.g. by making it a derived pointer: `p10 = &D_80190048;` → the address is a constant symbol → rematerializable. If we write `p10 = (u16 *)&D_80190048 + 0;` hmm, or `p10 = &D_80190048; p10 = p10;` (q04 — tried, 39).

Hmm! q04 (p10 = p10) gave 39 — no change. Hmm.

What about making the pointer's value NOT a simple symbol address:
```c
p10 = &D_80190048;
```
vs
```c
p10 = (u16 *)((u8 *)&D_80190048 + 0);
```
vs
```c
p10 = &D_80190048[0];   /* an array element address */
```
Hmm, if D_80190048 is declared as an array, `&D_80190048[0]` might be a different RTL (still a symbol ref).

Hmm, the "address rematerialisation" happens in reload: if the pseudo's value is a symbol address that fits, reload rematerializes it at each use.

To prevent: make the pointer's value something reload can't rematerialize, e.g. a symbol + a variable offset: `p10 = (u16 *)((u8 *)&D_80190048 + k)` with k a runtime value... but then the code changes.

Hmm, OR: **use the pointer more times** (more refs → reload keeps it in a register). In the target, p10 is used twice (`*p10 = v6` and `*(u16*)((u8*)p10+0x10) = g5e`) — 2 uses. In mine, also 2 uses. Hmm.

Hmm, in the target the address is materialized ONCE (lui v1 + addiu v1,v1,0) and used twice. In mine, materialized twice (lui at twice). So the target's p10 is a REGISTER, mine's is rematerialized.

The asm re-tie is what makes p10 a register in the target.

Hmm, so how do we keep a pointer in a register in plain C? The cookbook says: "a named derived pointer q = p - k that cse keeps as a REGISTER address (find_best_addr)" — so a DERIVED pointer (p - k) is kept as a register! Because its value isn't a simple symbol.

**So: make p10 a derived pointer!** E.g.:
```c
p10 = (u16 *)((u8 *)&D_80190048 + 0);   /* still a symbol+0 → foldable */
```
Hmm. What about:
```c
p10 = &D_80190048;
```
→
```c
{ u16 *base = &D_80190048; p10 = base; }
```
Hmm, same.

What about `p10 = (u16 *)((u8 *)p10_base + 0x0)` where p10_base is a copy? Hmm.

Hmm, what about deriving it from another pointer:
```c
p10 = (u16 *)((u8 *)&D_80190048 - 0);
```
GCC folds -0.

Hmm. What about:
```c
p10 = (u16 *)&D_80190048[0];
```
Hmm, D_80190048 is probably `u16 D_80190048[]` or a s16. Let me check its type. If it's an array, `&D_80190048[0]` gives the same address but as an array element → the RTL might be `(plus (symbol_ref D) (const_int 0))` → hmm.

Hmm, actually the current RTL for `p10 = &D_80190048;` is probably `(set (reg) (symbol_ref D_80190048))` — a pure symbol. Then reload rematerializes it as lui+addiu.

For a DERIVED pointer (e.g. `q = p - 4` where p is a symbol), the RTL is `(set (reg) (plus (symbol_ref D) (const_int -4)))` → reload can't rematerialize it as a simple lui/addiu? It can (lui + addiu -4). Hmm.

Hmm, so what makes the target keep p10 in v1? Hmm, the asm: `__asm__ __volatile__("" : "=r"(p10) : "0"(p10) : "memory");` — the asm's output is p10 → p10 must be in a register, and since the asm is volatile with a memory clobber, GCC must keep p10 in a register ACROSS the asm (the asm could clobber memory but not registers other than its output). So p10 (in v1) is live across the asm → reload can't rematerialize it → it gets a register.

In plain C, without the asm, p10's live range is just the two uses → reload rematerializes.

**To keep p10 in a register in plain C: make p10 live across something that forces a register.** Hmm — a call! If there were a call between the two uses, p10 would need a callee-saved register (not v1). Hmm.

Hmm, what if the asm's memory clobber is the key (a barrier)? Then the STORE `*p10 = v6` can't be moved across... hmm.

OK — the target also has a specific order: `sh v0,0(v1)` (the store to p10) then `lw v0,108(s1)` — the store happens BEFORE the next load. In mine, the store `sh v0,0(at)` is at 30 and then `lw v1,108(s1)` at 31. Same order.

Hmm, so the difference is just: the address register (v1 vs at) and the extra `lw v0,108(s1)` at 32 vs 31 (ordering).

Let me look at the target's sequence 26-33 vs mine 26-32:
target:
```
26: lw v0,108(s1)
27: ? (not shown)
28: lhu v0,6(v0)
29: lui v1,0x0
30: addiu v1,v1,0
31: sh v0,0(v1)
32: lw v0,108(s1)
33: ? 
34: lhu v0,10(v0)
```
mine:
```
26: lw v1,108(s1)
27: ?
28: lhu v0,6(v1)
29: lui at,0x0
30: sh v0,0(at)
31: lw v1,108(s1)
32: ?
33: lhu v0,10(v1)
```
So mine is missing the `addiu` (the `at` address is lui-only + the store uses `sh v0,0(at)`? hmm, that means the address is just `lui at,0x0` + `sh v0,0(at)` — that's a symbol at offset 0. And the target has lui+addiu (the symbol + 0).

Hmm, mine's `lui at,0x0; sh v0,0(at)` — the symbol D_80190048 is at address 0x80190048, so `lui at,0x8019` + `ori/addiu at,at,0x48`. Hmm, the disassembly shows `lui at,0x0` with a relocation (the objdump shows 0x0 for the symbol). So the addend is in the relocation. So mine has lui at + sh v0,0(at) = 2 instructions, and the target has lui v1 + addiu v1,v1,0 + sh = 3 instructions??

Hmm, but the counts are equal (111 = 111). So there's a compensating difference elsewhere. Looking at the diff: "replace mine[28:32] target[28:33]" → mine has 4 insns (28-31) and the target has 5 (28-32). And "delete mine[53:55] target[55:55]" → mine has 2 extra at 53-54.

So the target has an extra addiu (the address materialized as lui+addiu into a REGISTER) while mine has 2 extra at the end (lui at + sh). So mine has the D_8019004C store at the END with a lui at, and the target has it earlier.

OK. The residual is a register-allocation/scheduling difference. Getting this to 0 requires the p10 pointer to live in a register (v1).

**IDEA: make p10's live range longer in plain C.** E.g., use p10 a THIRD time somewhere later (e.g. in the tail). Hmm, that changes the code.

**IDEA: make the address of p10 non-rematerializable.** The cookbook: "A named derived pointer q = p - k that cse keeps as a REGISTER address". So:
```c
u16 *q = (u16 *)((u8 *)&D_80190048 + 0);
p10 = q;
```
Hmm, q is a copy → GCC would fold.

What about deriving from a pointer that's already in a register:
```c
p10 = (u16 *)((u8 *)&D_80190048 - 0);
```
GCC folds -0 → the same symbol.

Hmm, what about:
```c
p10 = &D_80190048;
```
where D_80190048 is declared as an ARRAY? Then `&D_80190048` is the array address; hmm.

Let me check D_80190048's declaration. If it's `extern u16 D_80190048[]`, then `&D_80190048` is a pointer to the array. And `*p10 = v6` would store to the array's first element. Hmm.

Alternatively: what if the pointer is derived from ANOTHER pointer in the TU, e.g. `p10 = (u16 *)((u8 *)&D_80190048 + (s32)(char)0);` — folds.

Hmm. **What about making p10's value depend on a runtime value that is 0?** Like `p10 = (u16 *)((u8 *)&D_80190048 + (o & 0))`? Folds.

Hmm, what about `p10 = (u16 *)((u8 *)&D_80190048 + 0) + 0;`? Folds.

OK — what about using the "3 quantities" trick: local-alloc's BIRTH order. The target has p10 in v1 and the constant D_8019004C's address in `at`. Hmm.

**TIME CHECK**: 07:45. I've got item 5 at score 16 (111 exact), item 3 at 41 (101 exact), item 1 at 6 (89 exact), item 4 at 14 (237 exact), item 2 at 2 (200 exact).

None are MATCHes yet. I need to decide: keep pushing or wrap up with WALLs?

The deliverable requires exactly one results.tsv row per item, with MATCH or PARTIAL (score 0) or WALL. Given the residual distances, a MATCH is plausible but not quick.

Let me push a bit more on the most promising: item 1 (score 6) — the missing load in the case0 arm. And item 5 (score 16).

Hmm, for item 1, the missing load: **IDEA**: what if `e` gets a 2nd definition in the case0 arm (like the asm did in case1)? E.g., in case0:
```c
e = ((Unkstruct_800B5CB8 *)s0)->unk20;
e = e;      /* second set — like the asm's */
```
Hmm, but the asm was in case1. If the asm were in case0, the case0 load would stay and case1's would sink. Hmm — but we need BOTH.

**IDEA**: give `e` a second set in BOTH arms:
case0: `e = unk20; e = e;`
case1: `e = unk20; e = e;`
Hmm, if `e = e` is a no-op that GCC removes, no effect. But if it survives, e gets 2 sets in each arm → maybe the loads stay!

Let me test that. Cheap.

Also for item 1:
- `e` as a `u16`/`s16`? Hmm, e holds an address.
- the `e` load moved before the call.

Let me do a final round for item 1 with 8 variants:
x01: s16 v1 + `e = e;` in case0 AND case1 (2 edits)
x02: s16 v1 + `e = e;` in case1 only
x03: s16 v1 + `e = e;` in case0 only
x04: s16 v1 + the e load before the func_8001C810 call in both arms (2 edits)
x05: s16 v1 + the case0/case1 blocks swapped
x06: s16 v1 + `e` declared `s32 e;` → `u32 e;`
x07: s16 v1 + the shared block's `t` in place
x08: s16 v1 + the `e` load via `*(s32*)((u8*)s0+0x20)` in BOTH arms (2 edits)

Let me do this round and then wrap up.

For item 3 and 5, I need more tries too. Let me do a combined round: item 1 (8), item 3 (8 more), item 5 (8 more). That's 24 files + edits.

Hmm, time and context. Let me do:
- Round for item 1: 8 variants.
- Round for item 3: 8 variants (z14-z21).
- Round for item 5: 8 variants (q14-q21).

Then score all, then write up.

Item 3's new variants (based on z02/z03/z06's success at 41):
The z02 diff showed the residual: register transpositions (a2/a3/t0) and the `move` instructions. The target has `move a2,v0` etc. — the moves for xa/xb! So the copies ARE materializing in the target but not in mine (or with different registers).

Hmm, z02's residual:
```
67  nop        | move a2,v0
68  subu v0,a1,v1 | subu v0,v0,v1
69  bgez v0,5348 | bltz v0,5344
70  subu a2,a1,v1 | move a1,v1
71  subu a2,v1,a1 | j 5348
72  lh a1,18(sp) | subu a3,a2,a1
73  --          | subu a3,a1,a2
74  --          | lh v0,18(sp)
```
So the target has extra `move` instructions (move a2,v0; move a1,v1) that mine lacks → the copies xa=a and xb=b are NOT materialized in mine even with u16 xa.

Hmm, and the target has `bltz v0` vs mine's `bgez v0` — a branch inversion!

Hmm, interesting: the target's structure is `if (a - b >= 0) {...} else {...}` → the target computes `subu v0,v0,v1` then `bltz v0` → i.e., the condition is inverted: `if (a - b < 0) { else-arm } else { if-arm }`.

So the target's C might be:
```c
if (a - b < 0) {
    xb = b;
    d1 = xb - xa;
} else {
    xb = b;
    d1 = xa - xb;
}
```
Hmm! Or the compiler inverted the condition. GCC 2.7's jump.c does invert branches. Hmm.

Let me look at the target more carefully. Hmm, the diff is confusing. Let me consider: the target has `move a2,v0` then `subu v0,v0,v1` then `bltz v0` then `move a1,v1` then `j` then `subu a3,a2,a1` / `subu a3,a1,a2`.

So the target's arms:
- if-arm: `move a3,a2` ... `subu a3,a2,a1` (d1 = xa - xb)
- else-arm: `move a1,v1` ... `subu a3,a1,a2` (d1 = xb - xa)
And the condition: `bltz v0` where v0 = a-b.

So the target: if (a-b < 0) → the else-arm (d1 = xb - xa) else → the if-arm (d1 = xa - xb). That matches the source `if (a - b >= 0) {d1 = xa-xb} else {d1 = xb-xa}` with the branch INVERTED by GCC (bltz jumps to the else-arm).

Mine: `bgez v0` (jump to the if-arm) — GCC chose the opposite polarity.

Hmm! So the branch polarity differs. That suggests the source order of the arms differs: maybe the target's source is:
```c
if (a - b < 0) {
    xb = b;
    d1 = xb - xa;
} else {
    xb = b;
    d1 = xa - xb;
}
```
i.e., the arms SWAPPED! Then GCC's branch would be `bgez`... hmm, no: with the arms swapped, GCC would emit `bltz` to skip... hmm.

Hmm, GCC's jump.c "invert" pass: it prefers a `bgez` (branch-if-≥0) over `bltz`? GCC's `invert_jump` prefers... Hmm.

Let me just TRY the swapped arms for item 3! That's a concrete, cheap test:
```c
if (a - b < 0) {
    xb = b;
    d1 = xb - xa;
} else {
    xb = b;
    d1 = xa - xb;
}
```
And also the swapped variant with `>= 0` inverted.

**AH, and the "move" instructions!** The target has `move a2,v0` and `move a1,v1` — those are the xa/xb copies! `move a2,v0` = xa = a (a's value in v0 → xa in a2). And `move a1,v1` = xb = b.

So in the target, the copies ARE materialized (2 moves). In mine they're not (or they're in different regs).

So item 3 needs BOTH: the copies materialized AND the branch polarity.

The copies: `xa = a;` where a is in v0 → `move a2,v0`. To materialize, xa and a must be in different registers → xa must be live when a is redefined. Hmm! In the source, `a` is redefined at "a = sxy[2].vy" AFTER the first block. So during the first block, a and xa overlap.

Hmm, so why doesn't GCC materialize? Because cse merges xa ≡ a (make_regs_eqv).

**The u16 trick (z02) gave 41 with 101 ins** — so the count became exact (101 = 101). Hmm, that's a good sign: the u16 xa added an instruction (the andi for the truncation?) — hmm, 100 → 101.

Hmm, so u16 xa changed the code but the residual is still register transpositions.

Let me try for item 3:
- the arms swapped (the `>= 0` / `< 0` inversion)
- `xa` as u16 AND the arms swapped
- `xb` as u16 AND `xa` as u16 (z06 was that → 41)
- `xa` as u16 + `d1 = xa - b` (z10 was 48)
- `xa` as u16 + `d1 = b - xa`

Let me do a round of 8 for item 3:
z14: `xa` u16 + arms swapped
z15: `xa` s16 + arms swapped
z16: `xa` u16 + `xb` u16 + arms swapped
z17: `xa` u16 + `d1 = xa - b` / `d1 = b - xa` (2 edits)
z18: `xa` u16 + `if (a >= b)` in the if arm only
z19: `xa` u16 + the `d1`/`d2` decl as s32
z20: `xa` u16 + `a = sxy[1].vy;` → `a = (s16)sxy[1].vy;`
z21: `xa` u16 + `xa = a;` → `xa = (s32)a;`

OK. And item 5's new variants (8):
q14: q07 + `p10` kept in a register: use p10 a third time? hmm. Let me do q07 + `p10 = p10;` (second set).
q15: q07 + `*(u16 *)((u8 *)p10 + 0x10) = D_80126B5E;` (drop the g5e temp)
q16: q07 + the 1st `o = unk6C` via the char* spelling
q17: q07 + `v6` as u16 → hmm, it is u16.
q18: q07 + `*p10 = v6;` → `*(u16 *)p10 = v6;`
q19: q07 + the `p10` decl → `void *p10;`? then `*p10 = v6` breaks.
q20: q07 + the `state` decl as s32
q21: q07 + `p10 = (u16 *)&D_80190048;`

OK. Let me now create the files and edits. To save time, let me create 24 files (8+8+8) in one message, then the edits in 2 messages, then 3 sc.sh calls.

Hmm, that's a lot of message content. Let me trim to 6 per item = 18 files.

Actually, let me be efficient: I'll do ONE more round of 8 for item 1 (the closest at 6), 8 for item 3, 8 for item 5. Let me write it.

Time: 07:50. Let me go fast.
