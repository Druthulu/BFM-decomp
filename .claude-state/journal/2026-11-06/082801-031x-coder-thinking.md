---
ts: 2026-11-06T15:28:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MHMhNWsXZsmnxmazzFjl
---
canon_reg uses `qty_first_reg[reg_qty[regno]]` — the first reg of the quantity. When a copy is seen, cse merges quantities. So which reg is "first" depends on insertion order.

In `insert_regs` for a reg, if the reg is already in a quantity, it adds to that quantity. The copy `(set flags raw)`: cse processes... hmm.

Rather than reverse-engineer, let me try: what if I swap the source order so the first test comes before the copy?

Target order: move s1,v0 (copy) at 1f04, then andi v0,v0 at 1f08. The copy precedes the test in the *machine code*, but in RTL the copy could be born anywhere; sched1 places it. Source order matters for sched1.

Idea: source `flags = raw;` after the first if? Then machine order might differ. Let's test a variant where the copy is moved after the first if — but then flags would be defined after the if, and used later. The move `s1,v0` would appear after the if. Target has it before. Not good.

Alternative idea: use a different C construct for the copy that gcc treats as a distinct value: e.g. `flags = raw + 0;`? folds. `flags = raw | 0;`? folds. `flags = (s32)(u32)raw;`? folds.

Hmm, what about `flags = raw & 0xE000;`? Then the second if's `flags & 0x8000` → combine folds to `raw & 0x8000`? Let's test — the codegen might be exactly `andi v1,s1,0x8000`... wait, the target's andis are on s1, so flags must be s1 and raw v0. If combine folds `flags & 0x8000` to `raw & 0x8000`, that would read v0 — wrong.

Let me try instead: make the *first test* use a value that cse won't rewrite. What if the first test is on `flags` and the later uses are on `raw`? Then flags (first test) would be... no, we need the first test on the call-return pseudo.

Hmm, hold on. Let's reconsider: maybe the real distinction is which pseudo is *local* (dies early) vs *global*. In the target, $v0 = the call result used at the andi (local, dies), $s1 = copy surviving calls (global). If cse merges them, the merged pseudo must be global ($s1) and both uses on $s1 — that's mine. The target keeps them separate only because the copy is opaque.

What real C can make a value opaque? A memory round trip through a volatile or a function call... but the "barrier" kind is a lever.

Wait — what about the "dead-reset" applied to the *source*: `raw = call(); flags = raw;` then LATER `raw = 0;`. cse's canon: at the andi (which reads raw), the qty of raw is merged with flags. The first reg in the qty is whichever got inserted first: raw was inserted first (it's assigned before flags). Hmm, but the merge direction: when cse processes `(set flags raw)`, it does `insert_regs(dest)` and `insert_regs(src)`; the src (raw) already has a qty; dest (flags) may get merged into raw's qty or vice versa.

Actually, wait. Maybe the merge isn't cse's canon_reg at all but the register allocator coalescing. Let me test: what if the andi use is written before the copy in source?

```
raw = call();
if ((raw & 0x6000) != 0x2000) {
   flags = raw;   // hmm, need flags defined in both paths
```

Hmm.

Alternatively, make `flags` the *first* assignment and `raw` the copy:
```
flags = call();
raw = flags;
if ((raw & 0x6000) != 0x2000) {...}
```
Then maybe canon keeps raw's use as raw (since raw was assigned later?). Let's just test a few permutations empirically. Cheap.

Also try: `flags = raw;` with the first test using a *third* variable `raw2 = raw;`? Hmm.

Actually here's a cleaner idea based on the target RTL: maybe the target's structure is exactly the source's, and the launder is only needed because cse unifies. The moves list shows for func_8017E178-like cases the crack was often "real 2nd set" of the variable. Here, a real 2nd set of *flags* that is value-preserving: flags ∈ {call result}. The only uses mask 0xE000. So `flags = raw & 0xFFFF;` is NOT value-preserving in general but is *observably* preserving given the uses. But the codegen would add an andi unless folded.

Wait, actually, what about this: since cse merges the qty, a second set of *raw* after the merge point but before the andi? No.

Hmm, what about using a different type for flags: `u32 flags`? Same mode.

What about `s32 flags` but assigning via a union? No.

Let me look at the actual RTL with cc1 dumps for the orig (with asm) vs a1. That will show exactly where the merge happens. Use cc1_dumps_tu.sh with a scratch TU: copy the real TU and replace the function body.

That's expensive but decisive. Actually, let me first try a batch of cheap variants (5 min). Variants:

b1: swap assignment: `flags = call(); raw = flags;` — but the cast call. Actually the call is `((s32 (*)(s32))func_8012CBA4)(a0)`.
b2: `flags = raw & 0xE000;`
b3: keep `flags = raw;` and change the first test to use a separate local: `s32 t = raw; if ((t & 0x6000) != 0x2000)` — t is a copy used once; cse merges t with raw, both local... then flags is separate? cse would merge all three into one qty. Hmm.
b4: reorder: put the first `if` before `flags = raw`? But target's move is before the andi in machine order. sched1 could still place it. Source:
```
raw = call();
if ((raw & 0x6000) != 0x2000) { calls... }
flags = raw;
m = flags & 0x8000;
```
Then flags = raw after the if; raw dead; cse merges → one global pseudo (live from call across calls to second if) → andi on s1. Not target.

b5: dead-reset of raw *before* the copy, using the first test on the call directly:
```
raw = call();
if ((raw & 0x6000) != 0x2000) {...}
raw = 0;          // dead reset kills the qty
flags = raw;      // NO, flags would be 0
```
No.

b6: two calls? no.

Let me think about the target's actual RTL: two pseudos, the first (raw) used only at the andi, the second (flags) = copy of raw used later. The copy `move s1,v0` exists. For gcc to keep a copy, the source reg must be live at/after the copy? No: raw is used at the andi which is AFTER the copy in machine order. So raw and flags are simultaneously live (raw until the andi, flags from the copy onward) — that's why two regs. In C, `raw` is live until the andi and `flags` from the copy. So they're genuinely two live ranges, but cse replaces the *use* of raw at the andi with flags, making raw die at the copy. Then the copy is dead → deleted? But mine still has `move s1,v0`. Hmm, mine: `move s1,v0; andi v1,s1,0x6000` — the move is needed to get v0 into s1. So the merged pseudo (s1) is defined by the copy and used at the andi. The call result v0 is the "source".

So in mine, cse turned `raw`'s use into flags, making raw's live range end at the copy. That's a cse canon_reg rewrite of the andi operand.

To prevent: cse must not consider raw ≡ flags at the andi. The equivalence comes from the copy insn. What if the copy insn is *after* the andi in the RTL (source order)? Then at the andi there's no equivalence yet, so raw stays. And the copy `flags = raw` after the andi — but then flags' value is raw which is still live at that point. Target's machine order has the move before the andi, but sched1 can move the copy earlier if there's no dependency... The copy depends on v0 (the call result) and the andi also depends on v0; sched1 could hoist the copy. Actually the target's move at 1f04 is before the andi at 1f08, and it's a copy — sched1 likely placed it there because the source order had it after but sched1 hoisted? Unlikely; sched1 tends to keep order for dependent insns.

But note: in target, `move s1,v0` at 1f04, `andi v0,v0` at 1f08 — both read v0, independent of each other. So sched1 could reorder.

Try b4': source:
```
raw = call();
if ((raw & 0x6000) != 0x2000) { ...calls... }
flags = raw;
```
Wait, that changes semantics? No — flags = raw is the same value; moving it after the if is fine as long as raw isn't modified in the if (it isn't).

Then: cse at the andi: raw has no equivalence yet → andi stays on raw ($v0). Then after the if, `flags = raw`: raw is still live (dies here), flags takes over for the later uses. cse merges at the copy, but the andi is before → stays raw. The merged qty's first reg: raw. Uses after → canon to raw? If canon rewrites flags' uses to raw, we get one pseudo live from call across calls → s1 and the andi on s1 again? Hmm, but the andi insn is processed before the copy, so it's already fixed. The later uses would be rewritten to raw (the first reg in the qty) → the qty spans the call to the second if → global s1, and raw's def is the call → move s1,v0 at the copy... 

Hmm, this is what mine looks like but with the andi order changed. Actually mine has andi on s1 = the merged reg. If the andi is processed before the copy, it stays on v0. The move still happens (the merged reg is s1 defined by the copy). So we'd get exactly: `move s1,v0; andi v0,v0,0x6000` — but the move would be after the if in source, i.e., after the calls. In target, the move is right after the call. sched1 might sink/hoist... The target's move at 1f04 is in the delay-slot region.

Actually wait — re-read target: 
```
1efc: jal call
1f00: sw s1,68(sp)     delay slot
1f04: move s1,v0
1f08: andi v0,v0,0x6000
1f0c: li v1,8192
1f10: beq v0,v1, 1f48
1f14: andi v0,s1,0x8000   delay slot
```
So the copy is right after the call, before the test. In C source with the copy after the if, sched1 would have to hoist the copy above the branch — impossible (the branch is a jump). So no.

Alternative: keep the copy at the top but make cse's canon prefer raw. canon_reg returns `qty_first_reg`. The qty's first reg is determined by insert_regs. Let me read insert_regs around line 1007.
