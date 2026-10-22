---
ts: 2026-10-22T00:21:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_6kiu7I1rGEd3o1HYjrwS
---
A2's residue (score 5):
- ins 29-31: the ORDER of the two loads is swapped! Mine: `lbu a0,108(s0)` (the c6c load) then `lw v0,-72(s0)` (the q-0x48 load). The target: `lw a0,-72(s0)` (the q-0x48 load) FIRST, then `lbu v0,108(s0)` (the c6c load) — and the registers are swapped too ($4 vs $2).
- ins 35-36: `beqz a0` vs `beqz v0` — the test of the loaded value (the q-0x48 load) — the register differs.
- ins 63: `lhu v1,0(s0)` vs `lhu v1,-2(s0)` — an OFFSET difference (the base register for the q-relative access: mine uses s0 = p, the target uses q?) hmm: `-2(s0)` vs `0(s0)` → the target's s0 = q (so q-2) and mine's s0 = p (so p+0)? Hmm, `*(u16 *)q` = q+0 vs p+0x54 ✗. Hmm, mine[63] `lhu v1,0(s0)` vs target `lhu v1,-2(s0)`: the target's s0 = q+2? Hmm, the source has `*(u16 *)q` and `*(u16 *)(q - 0x4)`. Hmm.

Wait: the source's `*(u16 *)q` (in `*(u16 *)p * 4`? no). Let me look: the source has `*(u16 *)p` and `*(u16 *)(q + 0x1E)`, `*(u16 *)(q - 0x4E)`, `*(u16 *)(q - 0x4)`, `*(u16 *)(q - 0x4A)`, `*(u16 *)q`, `*(u16 *)(q - 0x46)`.

mine[63] `lhu v1,0(s0)` = `*(u16*)q` with s0 = q ✓; target `lhu v1,-2(s0)` = `*(u16*)(q-2)`?? Hmm, that doesn't match the source ✗. Hmm, unless the target's s0 = q+2 (i.e. the target's q = p + 0x54 and s0 = q... hmm).

Hmm, whatever: the register/base difference is a knock-on effect.

The core residue in A2: the order of two loads (the `*(s32 *)(q - 0x48)` load and the `c6c` load) and their registers ($2 vs $4).

In the target:
```
29 lw a0,-72(s0)     ; the q-0x48 load → $4
30 nop
31 lbu v0,108(s0)    ; the c6c load → $2
32 nop
33 ...
35 beqz v0
36 sw a0,-20(s0)
```
In mine:
```
29 lbu a0,108(s0)    ; the c6c load → $4
30 nop
31 lw v0,-72(s0)     ; the q-0x48 load → $2
...
35 beqz a0
36 sw v0,-20(s0)
```
So the source order of these two statements is swapped in the compiled output — a sched1 ordering difference! In the source:
```c
            c6c = *(u8 *)(q + 0x6C);
            *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
            tbl = D_8011DB08;
            *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
```
The `*(s32 *)(q - 0x48)` load is the last statement; the c6c load is earlier. The ROM has the q-0x48 load FIRST (ins 29) then the c6c load (ins 31) → so the ROM's scheduler moved the q-0x48 load earlier (sched1 hoisting) ✓, while mine keeps the source order.

So a lever: make gcc hoist the `*(s32 *)(q - 0x48)` load before the c6c load. sched1's hoisting depends on the block structure/priority.

Hmm, and the register assignment: the target has the q-0x48 load in $4 and the c6c load in $2 (the ROM's c6c is pinned to $2 ✓ — in A2 I dropped the c6c pin).

So: A2 + the c6c pin = the original (all pins) = 0 presumably. To reach a PARTIAL, I need the c6c load to land in $2 lever-free.

In A2 (c6c unpinned), c6c got $4 and the q-0x48 load got $2 — swapped relative to the target.

The local-alloc order in that block: the ROM has c6c ($2, the first reg) and the q-0x48 temp ($4). Mine has the q-0x48 temp ($2) and c6c ($4).

So in the target, c6c (a user variable, low allocno) gets $2 ✓ (birth order); in mine, the q-0x48 temp (a compiler temp, higher allocno?) gets $2 ✗.

Hmm, the q-0x48 load temp is used immediately (the store) → live 1-2 → high priority (pri 10000) → wins the tie ✓. And c6c: 1 set + 1 use → pri 10000 too → tie → the lower allocno wins. The user variable c6c has a LOW allocno (created in the front end) ✓ → c6c should win ✗ (observed: the temp won).

Hmm! Unless the q-0x48 temp's live is 1 → pri = 1*2/1 = 20000 > c6c's 10000 ✓✓ → the temp wins $2 ✓ (observed).

So to flip: the q-0x48 temp's live must be ≥ 2 (so its pri = 10000) and then the tie-break by allocno gives c6c ✓.

How to lengthen the q-0x48 temp's live range? By using it later, e.g.:
```c
            *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
```
The load's value is used by the store immediately ✗ (live 1).

Hmm, what if the source is:
```c
            t = *(s32 *)(q - 0x48);
            *(s32 *)(q - 0x14) = t;
```
→ the temp `t` is a user variable (low allocno) → hmm, then t and c6c tie and c6c (declared first?) wins ✓ or t wins ✗.

Hmm, what if the load's value is used in a way that extends its life, e.g. the store is separated:
```c
            *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
            tbl = D_8011DB08;
            *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
```
Hmm.

Since the ROM's order has the q-0x48 load BEFORE the c6c load (ins 29 vs 31), and the c6c load's result is tested at ins 35 — the two loads are independent, so the scheduler picked an order.

In mine, the order follows the source (c6c first). To get the ROM's order, the source order might need to change: e.g. move the `*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);` statement EARLIER in the source (before the c6c load)!

Let me try that (statement-order move ✓ in the catalog):
```c
            func_8017869C((s32)p);
            *(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50);
            *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
            c6c = *(u8 *)(q + 0x6C);
            *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
            tbl = D_8011DB08;
            ...
```
Hmm, but that changes the order of the STORES too (the q-0x14 store would come before the q-0x18 store) — the ROM's store order: ins 36 `sw a0,-20(s0)` (the q-0x14 store) hmm, and the q-0x18 store is elsewhere. Since the stores are to different addresses, the order matters for the bytes ✗ risky.

Hmm. But actually the ROM's ins 29-36 region:
```
29 lw a0,-72(s0)     ; the q-0x48 load
31 lbu v0,108(s0)    ; the c6c load
35 beqz v0
36 sw a0,-20(s0)     ; the q-0x14 store
```
So in the ROM, the q-0x48 load AND its store are separated by the c6c load and the test — i.e. the store's value (in $4) is live across the c6c load ✓ (live ≥ 3) → pri = 1*2/3 = 6666 < c6c's 10000 ✓✓ → c6c wins $2 ✓✓✓.

So in the ROM, the q-0x48 value is live across the branch (the store is after the test) → a lower priority ✓.

In mine (A2), the q-0x48 load is at ins 31 and its store at ins 36 → also live across ✗ hmm. Hmm, mine[35] `beqz a0` and mine[36] `sw v0,-20(s0)` → so mine's q-0x48 value (in $2) is live from ins 31 to 36 ✓ (live ~3-4) → pri 6666 → and c6c (in $4) → pri 10000 → so c6c should have won $2 ✗ (observed: c6c in $4).

Hmm, contradiction. So my priority model isn't matching. Ugh.

Let me try the practical approach: try source-order variants and see if the score drops. Cheap: 2-3 variants.

V-a: move the `*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);` statement before the c6c load.
V-b: keep the order but use a temp for the q-0x48 value:
```c
            t = *(s32 *)(q - 0x48);
            c6c = *(u8 *)(q + 0x6C);
            ...
            *(s32 *)(q - 0x14) = t;
```
Hmm, that changes the code (an extra copy?) ✗.

Let me try V-a with the q+tbl pins kept (A2 base) — if it reaches 0 → PARTIAL:pin (2 pins left) ✓.

Hmm, wait. Let me reconsider: A2 = q ($16) + tbl ($3) pins kept, c6c's dropped → 5. If V-a gives 0 → PARTIAL:pin (with q and tbl kept). That's a valid PARTIAL result ✓ (the kinds still kept: pin).

Hmm, but is a PARTIAL with 2 of 3 pins kept valuable? The brief allows it: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)".

Let me try V-a and V-b (both on the A2 base).

Actually, also worth trying: A2 + the c6c pin dropped but with `c6c` declared as `u8` (a width change → the HImode copy might change the allocation) ✓ (C0505: widths).

Let me write V-a (statement order) and V-c (c6c as u8) and scorethem.
