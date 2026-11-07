---
ts: 2026-11-06T12:26:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5wWxqXDR5USD4d2iktU1
---
Interesting! My c1 already has the `(s16)i` scaling in the loop (matching target) — that came from the orig code's `(s32)i << 1` with i s16. Good.

Differences:
1. beqz at 221c: mine fills delay slot with `move a0,s0` (fall-through); target has `addiu v0,s1,1` from the taken thread (and then the extra copy at 2234). Also mine's jal delay slot is `move a1,s3` in both. Target: at 2228 jal, delay 222c move a1,s3 — same.
2. Tail: mine has `sw s0,0(at)` at 22d4 (before lw v0,8(a1)); target has it at the very end 22ec. That's the sched2 store re-tie (memory barrier needed) — mine sinks the final store above? Wait mine: 
```
22cc: addiu s0,s0,40
22d0: lui at,0x0
22d4: sw s0,0(at)     ← store D_801151D0
22d8: lw v0,8(a1)     ← load D_800AE7B8[..].f4[2]
...
22e8: sw v0,8(a1)     ← store
```
Target:
```
22d0: addiu s0,s0,40
22d4: lw v0,8(a1)
22d8: lui v1,0xff00
22dc: and v0,v0,v1
22e0: or v0,v0,a0
22e4: sw v0,8(a1)
22e8: lui at,0x0
22ec: sw s0,0(at)
```
So target keeps the D_801151D0 store last; mine hoists it above the load. Hmm wait, mine hoisted the store ABOVE the load — sched2 hoisting a store above a load requires disambiguation. The comment said D_801151D0 is a plain scalar while D_800AE7B8[..] is mem/s, so sched2 hoists the final store above the RMW. The barrier "memory" re-ties them.

Lever-free options: make D_801151D0 mem-in-struct too, so sched2 won't move the store? Or make the tail store's address opaque in the same class. E.g., write the store through a pointer that aliases a struct: `((struct {...}*)&D_801151D0)->x = ...`? That changes MEM_IN_STRUCT_P → mem/s for both → then sched2 can't disambiguate and keeps order. That's a real C move (struct alias, like the D_801151D0 1-field struct alias used in G28x MATCHes!). The moves.md lines 320-323: "D_801151D0 1-field struct alias (MEM_IN_STRUCT store not hoisted)" — exactly this mechanism. 

So: `extern struct { s32 v; } S_801151D0;`? But the extern declaration is `extern s32 D_801151D0;` in the TU at block scope; the original function declares `extern s32 D_801151D0;` locally. I can change the local declaration to a 1-field struct alias with __asm__ label? Wait — `__asm__` label on a declaration is a symbol rename, not a codegen lever (like `aB9A02 __asm__("D_800B9A02")` in the worked example, accepted as not a lever). But the constraint says no `__asm__` at all? The brief says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." The kinds are barrier,keepalive,pin. Symbol-name asm aliases are not a codegen lever (worked example kept `aB9A02 __asm__("D_800B9A02")`). But the note in the worked example says "Kept the TU-idiom extern asm-label alias ... (symbol name, not a codegen lever; was in orig body)". Here orig body has `xf8017EF8C __asm__("func_8017EF64")` and `xf8017E1D4 __asm__("func_8017E1AC")` which are symbol renames for calls — keep them.

For D_801151D0 struct alias I need the symbol to be D_801151D0 with a struct type. Local: `extern struct S151D0 D_801151D0;` — but struct type must be defined; can define a local struct type inside the function (like Rec20 typedef is function-local). Yes:

```
struct S151D0 { s32 v; };
extern struct S151D0 D_801151D0;
...
((struct S151D0 *)&D_801151D0)...
```
Hmm, but D_801151D0 is declared in the TU as `extern s32 D_801151D0;`? Wait, is it? The function declares it locally; the comment says "D_800B9A02 (extern short, TU:2470/2472) ... are re-declared here at BLOCK scope in their exact TU shapes". D_801151D0 may only be declared locally in this function. Let me check the TU for other declarations of D_801151D0.

Then:
- `ot = (s32 *)D_801151D0;` → `ot = (s32 *)D_801151D0.v;`
- `D_801151D0 = (s32)ot;` → `D_801151D0.v = (s32)ot;`

That gives a MEM_IN_STRUCT store, and the load `D_800AE7B8[*pb].f4[2]` is mem/s → sched2 can't disambiguate → keeps order. That's the mechanism used in G28x.

3. The beqz delay slot: target has `addiu v0,s1,1` in the beqz delay and then again at 2234, with `move s1,v0` at 2238. Mine: beqz delay = `move a0,s0`, then at 2230 `addiu v0,s1,1`, 2234 `move s1,v0`. So the only difference is where the increment copy goes (delay slot vs after the call) and the branch target offset.

Lever-free way to get the taken-thread fill: reorg's fill_eager_delay_slots: it looks at the instruction after the delay slot (fall-through). If it's a "simple" insn it uses it. If the fall-through's first insn is not usable (e.g. it's a label target of other branches? or it sets a register that's live at the branch target?)...

Let me look at reorg.c fill_eager_delay_slots logic in gcc 2.7.2 to find conditions that make the fall-through ineligible. Key: `if (insn && (maybe_never || ...))`. Let me look at the source.

Actually a much simpler idea: restructure the source so the increment appears before the call in source order, i.e.:
```
do {
    s32 inc = i + 1;
    if (...) { call; }
    i = inc;
} while(...)
```
Hmm, then the increment is computed before the beqz — target has it in the delay slot of the beqz which is exactly "computed after the branch decision". Since reorg copies it into the delay slot from the taken thread, the C-level result is the same.

The barrier was at the head of the call arm to make the fall-through head ineligible. In reorg terms: fill_eager_delay_slots for the beqz: it tries insn = next after delay slot (the `move a0,s0`); eligible if `eligible_for_delay` and not a label. An empty asm (volatile) is not eligible (asm insns are not eligible), so it tried the taken thread.

Lever-free alternative to make the head ineligible: make the first instruction of the fall-through something not eligible for delay, e.g. a `jal`? No. Or make the fall-through start with a label that's a jump target (reorg's `stop_search_p`/`label` check). Hmm, the head of the then-arm is a label only if something jumps there.

Alternative: reorder so the fall-through head is the call setup but with the call in the delay... no.

Another approach: maybe restructure to `if (cond == 0) goto skip;` style? Hmm.

Alternatively swap the if arms: `if (*(s16*)... == 0) { } else { call }`? gcc would invert the branch. Target's shape: `lh; beqz v0, L; call`. If we write `if (x != 0) call;` we get `beqz` to the increment. If we write `if (x == 0) { i = i+1; panel += 0x20; continue; } call;` — messy.

Wait, maybe the increment copy in the delay slot arises naturally if the source has the increment BEFORE the if inside the loop? No: then the increment would be emitted before the lh.

Hmm, think about what reorg does: the branch is `beqz v0, .L2238`. Its delay slot insn (chosen by dbr scheduling in reorg after reload? no — delay slot filling in reorg). reorg fills from:
1. insn after delay slot (fall-through) if eligible and safe,
2. else the target's first insn (taken thread), if safe (steal_delay_slots).
The empty asm made (1) fail. Without it, reorg picked `move a0,s0`.

Lever-free: make the fall-through head ineligible for delay. What's eligible_for_delay? Let's read reorg.c. Things not eligible: insns that set a register used by the branch/jump target (needed for target), `jump_insn`, `insn` with REG_INC conflict, `insn` that is a `call_insn`? Actually calls are eligible in some cases (jal delay slots filled). Let me check the source: tools/reference/gcc-2.7.2/reorg.c.

Another angle: instead of fighting reorg, change the C so the target's shape emerges: perhaps write the increment as part of the if-arm's end? E.g.

```
if (x != 0) {
    call;
}
i = i + 1;
panel += 0x20;
```
The target has TWO copies of the increment (one in the delay slot, one after the call). That means the source had one increment, and reorg duplicated it (fill from taken thread "steals" the increment insn from the taken path — the taken path is `.L2238: move s1,v0` preceded by `addiu v0,s1,1`). Reorg stole the addiu into the delay slot and redirected the label forward one insn (to 2234's addiu? no...). Hmm, the note says "the target instead copies `addiu $v0,$s1,1` out of the TAKEN thread and redirects the label one insn forward (hence the increment appearing twice)". So reorg duplicated rather than moved (since the insn has a side effect on a reg used at the label... it kept both copies: one in the delay slot, one at the original place, and the label redirected past the first? The beqz target 0x1e4 = 2238? Wait target beqz at 221c jumps to 2238 (0x1e4 relative to 21... let me compute: 221c + 4 + 4*? beqz v0,2238 → target 2238 = `move s1,v0`. Hmm but then the second addiu at 2234 is skipped when branching! So taken path: 2238 move s1,v0 where v0 was set by the delay slot insn at 2220. Clever: the branch's delay slot executes on both paths; on the taken path v0=i+1 is used directly, skipping 2234's addiu. On the fall-through path the call clobbers v0, so 2234 recomputes i+1. That's reorg's "steal with duplicate".

So we need reorg to prefer the taken thread. What makes the fall-through ineligible? In reorg.c fill_eager_delay_slots:

Let me read the actual code.
