---
ts: 2026-10-22T00:48:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_5HkBfuqXG4pXmgi5C2Pj
---
I see the target:
```
260: jal func_8018CC40     ; func_80029124(m, 1)
264: sw v0,4(s2)          ; delay: D_801E79D8.unk0C = ...
268: jal func_8018CC40     ; func_800D0FE0(slot)
26c: move a0,s0           ; delay: a0 = s0 (for the NEXT call?)
270: li v0,2
274: j 2c8
278: sh v0,-8(s2)         ; D_801E79D8.unk00 = 2
27c: move a0,s0           ; the else branch
280: addiu v0,a2,-20      ; d = rb - 0x14
...
298: jal func_8018CC40     ; func_800D0F0C(sc)
29c: sw v0,0(s3)
```
Hmm, so `move a0,s0` at 26c is in the delay slot of the jal at 268 (the call to func_800D0FE0 with a0 = slot?). Hmm, s0 holds `slot`?

Hmm, wait: at 27c (the else branch) there's another `move a0,s0`. So `move a0,s0` appears twice in the target: at 26c (delay slot) and 27c.

And the diff said: mine has `move a0,s0` at 58 and the target at 52. So the *first* `move a0,s0` is at a different position.

Hmm, since s0 = slot (a local kept in a callee-saved reg), the `move a0,s0` is the a0 setup for the call `func_800D0FE0(slot)`.

In the target: the call at 268 has its delay slot = `move a0,s0` (so a0 is set in the delay slot of the *previous* call — the scheduler moved it). In mine, the `move a0,s0` is at 58 (later — probably in the delay slot of the jal at 268 as well but the order differs...).

The diff: "insert mine[52:52] target[52:53]: 52 -- | move a0,s0" and "delete mine[58:59] target[59:59]: 58 move a0,s0 | --". So the target has it at 52 and mine at 58. Hmm, so in the target the `move a0,s0` is 6 instructions earlier.

Let me see the full context. Let me look at the target's asm from the start (the log has 86 lines; the head is missing). Let me read the log file.

Actually, the diff is about the *position* of one instruction — a scheduling artifact. The "statement order" move might fix it: e.g. moving the `func_800D0FE0(slot)` call earlier/later in the source, or the `D_801E79D8.unk00 = 2;` assignment.

Given the target:
```
25c: li a1,1
260: jal func_80029124        ; func_80029124(m, 1)
264: sw v0,4(s2)              ; delay: D_801E79D8.unk0C = (&D_801E3D74)[id]
268: jal func_800D0FE0        ; func_800D0FE0(slot)
26c: move a0,s0               ; delay
270: li v0,2
274: j 2c8
278: sh v0,-8(s2)             ; delay of the j: D_801E79D8.unk00 = 2
```
So the source order is:
```
D_801E79D8.unk08 = (&D_801E3D60)[id];
D_801E79D8.unk0C = (&D_801E3D74)[id];
func_80029124(m, 1);
func_800D0FE0(slot);
D_801E79D8.unk00 = 2;
```
The scheduler placed `move a0,s0` (the a0 setup for func_800D0FE0) in the delay slot of the *previous* call (jal at 268)?? Hmm, the delay slot of the jal at 268 executes *after* the call — so `move a0,s0` after the call at 268 would be the setup for the *next* call. Hmm, but the next call is at 298 (in the else branch, a different path). Hmm, no: 26c is the delay slot of the jal at 268, and the next instruction (270) is `li v0,2`. So the `move a0,s0` at 26c is the a0 setup for the call at 268 — placed in the *delay slot* of the call at 268? No! The delay slot of a jal executes after the call target is computed but before the call's effect. So the `move a0,s0` at 26c IS the a0 setup for the call at 268 — it's in the delay slot of the *previous* jal (260). Yes! The delay slot of the jal at 260 holds the instruction after it in the *program order*, which the scheduler moved.

OK whatever. The point: the difference is a scheduling position. The "statement order" move could help: e.g. moving `func_800D0FE0(slot)` before `func_80029124(m, 1)`? That changes the semantics (the call order) — the game's asm has a specific order. Hmm, the *source* order determines the call order, so I can't swap them.

Hmm, so the difference is in *where* the `move a0,s0` is placed relative to other instructions — a scheduler decision influenced by the source.

Hmm, what differs in my variant? v07_swp0 = the "statement swap" variant (the statement after the asm swapped with the asm). The launder is on `sc`:
```
sc = slot;
__asm__("" : "=r"(sc) : "0"(sc));
d = rb - 0x14;
D_801E79D8.unk04 = (&D_801E3EA4)[d >> 1];
((void (*)(s32))func_800D0F0C)(sc);
D_801E79D8.unk00 = 1;
```
Hmm, and v09_idt0 (the identity `sc = sc;`) also scored 2.

The remaining difference is in the *other* branch (the `flags & 0x4000` branch) — the `move a0,s0` position. Hmm! So the launder (in the else branch) affects the scheduling in the *then* branch? That seems odd. Unless the difference is caused by the *removal* of the launder (the register allocation changed → different scheduling).

Hmm, the `move a0,s0`: s0 holds `slot`? Let me think: in the target, s0 = slot (kept in a callee-saved reg). Hmm, but `slot` is used in both branches (func_800D0FE0(slot) in the then branch and sc = slot in the else branch).

So s0 = slot. The `move a0,s0` sets a0 = slot for the call func_800D0FE0(slot).

In the target, the `move a0,s0` is at 26c (the delay slot of the jal at 260 = func_80029124's call) — i.e. scheduled early. In mine, it's at 58 (later, probably in the delay slot of the jal at 268).

Hmm, the scheduler moved it earlier in the target. Why? Because in the target, the register allocation/scheduling differed (the launder's effect on sc → $4, d → $2, etc.).

Hmm, this is the "sched1/sched2" territory. The score is 2 (one instruction misplaced). Since the *pins* (register $2/$4/$6) stay in my variant (only the launder was removed), the allocation is mostly the same.

Hmm! Wait. Maybe the launder's removal changed something subtle. Let me look at the *plain* variant's score for this item: the log showed only v07_swp0 (2), v09_idt0 (2), v03_cast0s16 (8), v08_init0 (24). And v01_plain? It wasn't in the list... hmm, the list showed 2, 2, 8, 24, and then the 999s. Hmm, v01_plain must have scored 2 as well (it would be listed first). The output was truncated (head -46). Let me re-score this item to see the full list.

Let me also try more variants for it: the cast on sc (`sc = (s16)sc;` → hmm, sc is a register-pinned variable; a cast might break the pin), statement reorderings, etc.

Let me re-score the item and look at the full list.
