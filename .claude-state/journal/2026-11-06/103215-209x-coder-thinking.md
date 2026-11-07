---
ts: 2026-11-06T17:32:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hUFfErhNw69lc1hHpiVu
---
y1: 8 (slightly worse). y2/y3: 7.

Time: 6.3 min. Let me think about the preference mechanism concretely, because fixing it is the key.

The global dump: "75 preferences: 3" (v1). This is qty_phys_sugg — from combine_regs: when a pseudo is set from a hard reg or from another pseudo that dies. For the shift insns, combine_regs(r1=75? r0=77?) may tie.

Let me look at the target's pinned build: what's 75's preference there? With the pin, 75 is fixed ($2) so no suggestion matters.

Lever-free, the preference v1... Let me find where reg 3 comes from. The two shift sources: 77 (angle) and 147 (load). In the final asm: angle is in a0 (4), the load in v0 (2). If the preference were from 77, it'd be 4; from 147, 2. It's 3. So neither.

Maybe the preference comes from the *store* `(set (mem) (subreg:HI 151))`? No, that's 151.

Hmm, maybe 75 has a preference for reg 3 because of the *second* shift's source 147 which is tied to... 147 = zero_extend of the load (146); 147 might be in v1? The final asm shows `lhu $2,242($16)` then `sll $3,$2,16`: 147 = $2 = v0. Hmm.

Wait, maybe the asm I read is from the *dump* (nd.s) of the nopin body — yes. And the greg dump's "75 preferences: 3" — let me double check that this dump corresponds to nopin (tag nd). Yes.

Reg 3 = v1. Hmm.

Let me look at the actual `;; 75 preferences` semantics in global-alloc: `qty_phys_sugg` is a HARD_REG_SET of suggested registers. "preferences: 3" prints the count? Let me check the dump code: in global.c, it prints ";; %d preferences: " followed by the reg numbers. So "75 preferences: 3" means ONE preference, register 3.

OK so 75 prefers v1. Where from? combine_regs with a hard reg v1: some insn sets 75 from a value in v1 or copies. The `(set (reg 75) (ashift (reg 77) 16))` — combine_regs is called with usedreg=77, setreg=75? If 77 dies at the insn, it ties 75 to 77's qty (a pseudo-pseudo tie), not a hard reg. Unless 77 is in v1 by then? No, local-alloc runs before global; 77 is a pseudo.

Hmm, wait: local-alloc could have tied 75 and 77 into the same qty (both in the then arm, 77 dies at 396). Then the qty has both pseudos. 77 (angle) is also used at `p[0x79] = angle` (before) — so 77's live range... angle is used in the store and the shift. The store is `(set (mem) (subreg (reg angle)))`. 77 dies at the shift.

If 75 and 77 are in one qty, they share a register. Then the qty is a *global* one? 75 crosses blocks; 77 is in the then-arm block only. Mixing...

The preference for v1 might come from another copy in the qty (e.g., a hard reg copy).

This is very deep. Let me try empirical knobs around angle:
- Make angle's use in the store different: `p[0x79] = angle;` → `p[0x79] = (u16)angle;` (same).
- Use a second variable for the shift: `sh16 = angle2 << 16;` where angle2 = angle? adds a copy.

Actually, here's a cleaner idea: make the *shift* use a value that's already in v0 — e.g., use the *call result* directly:
```
angle = func_80029D3C(cmp79);
p[0x79] = angle;
if (r[0x49] == 5) {
    sh16 = angle << 16;
}
```
What if we compute sh16 BEFORE the store, from the call result? e.g.:
```
angle = func_80029D3C(cmp79);
if (r[0x49] == 5) {
    sh16 = angle << 16;
}
p[0x79] = angle;
```
This changes the instruction order (the store after the branch) — the target has the store before the branch. But sched1 might move it? The store is in a different block (before the branch vs inside the then arm).

Hmm.

Let me check the time budget: 6.6 min. I'll continue ~10 more min then decide.

Let me try a few more targeted variants:
z1: `sh16 = angle;` in the then arm... no.
z2: In the then arm, `sh16 = (s32)((u16)angle << 16);` — a zero-extend of angle (the load path is lhu → zero-extended). The target's first arm uses a0 (sll a0). A zero-extend would add andi — bad.
z3: Move the `p[0x79] = angle;` store after the if (both paths)? changes order.
z4: Use `r[0x49] == 5 ? (sh16 = angle << 16) : ...` no.

Let me try z3 and a variant where the shift's operand is `p[0x79]` in both arms (x1 tried, 7).

Actually, let me look at what makes 75 prefer v1: maybe the `sh v0,242(s0)` store after the shift... no.

Let me try: change the store expression to use a temp explicitly so 151's reg differs:
`p[0x79] = (u16)((s32)((sh16 >> 16) + (s32)((u32)sh16 >> 31)) >> 1);` — same.

Let me try declaring `angle` differently or making the call result stored via a variable... 

Actually, maybe try: `sh16 = angle << 16;` → `sh16 = (s32)((u32)angle << 16);` (x2, 7).

Hmm. Let me look at the *preference* in the pinned build to see if it's the same (v1): dump the orig (pinned) with hdump and check "75 preferences". If the pinned build also says preference 3, then the preference is intrinsic and the pin overrides it — meaning lever-free we'd need to break the preference.

Let me do that: hdump orig.c and grep 75 preferences.
