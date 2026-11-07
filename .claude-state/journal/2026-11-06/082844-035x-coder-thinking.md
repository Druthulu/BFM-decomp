---
ts: 2026-11-06T15:28:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vyJteHBTmKZJxNcpmBXC
---
This is deep. Rather than reverse-engineering, empirical search is better. Let me batch-test candidate spellings quickly. I'll write variants that change the flags/raw structure:

b1: `flags = call(); raw = flags;` (copy direction swapped)
b2: `flags = raw & 0xE000;`
b3: `flags = raw & 0xFFFF;`
b4: introduce a third local for the test: `s32 t; raw = call(); flags = raw; t = raw; if ((t & 0x6000)...)`
b5: `flags = raw; raw = raw | 0;`? folds.
b6: put `raw = 0;` (dead-reset) right after the copy and make the first test use a saved copy `t`:
```
raw = call();
flags = raw;
t = raw;
raw = 0;
if ((t & 0x6000) != 0x2000) ...
```
Hmm, t is a local copy of raw used at the andi — but cse merges t with raw before the reset. The reset breaks raw's class, so t (already merged? merge happened at the copy) — if t ≡ raw and raw is reset, t's value is still valid (t holds the old value), but cse's qty for t is the old value class... invalidate(raw) removes raw from the table but t remains with the old qty. Then the andi on t reads t's reg. And flags ≡ t ≡ raw old value. Hmm, all merged into one qty anyway.

b7: use the dead-reset on a *different* variable to break the class: the cse equivalence class for the call result. `raw = 0` invalidates raw's qty.

Hmm wait, actually why didn't a6 work? a6 = `raw = 0;` after the first if. Because the andi's operand had already been canon'd to the merged reg during cse1 processing of that block.

What if the dead-reset is placed between the copy and the andi, and the andi uses a separate variable assigned before the reset?

```
raw = call();
flags = raw;
t = raw;       // local copy
raw = 0;       // dead-reset
if ((t & 0x6000) != 0x2000) ...
```
cse processing in order: 
- `raw = call` → raw new qty.
- `flags = raw` → flags joins raw's qty (first=raw).
- `t = raw` → t joins raw's qty.
- `raw = 0` → invalidate(raw): removes the qty from the table? `invalidate` removes entries mentioning raw. flags and t keep their qty (which was raw's qty, now without raw).
- andi t → canon_reg(t) = qty_first_reg of that qty. After invalidate, qty_first_reg is recomputed? The qty still has flags and t; first may be flags or t.

Ugh, fragile.

Let me step back and consider: maybe the target's first andi on $v0 can be achieved by making the *call result* itself the tested value without a variable — e.g. use the expression `((s32 (*)(s32))func_8012CBA4)(a0)` twice? No.

Alternatively: what if `raw` and `flags` are made different *modes* so cse won't merge them: insert_regs checks `qty_mode[qty] != GET_MODE(x)` → no merge if modes differ. `flags` as `s16`? Then `flags = raw` truncates — changes codegen (target has full word). Unless... the value fits in s16? It doesn't necessarily (call result).

Hmm, what about `HImode` only for the *test*: `if (((s16)raw & 0x6000)...` no, mask is 0x6000 which fits s16? 0x6000 = 24576, as s16 that's negative. Meh.

What about making the *first* test use a different mask expression that cse can't relate: the target's first andi is `andi v0,v0,0x6000` and the second `andi v1,s1,0x6000`. Same mask, different regs.

Alternative idea: keep the launder's effect via the *value* being stored/reloaded from a local variable (memory). `s32 flags; ... *(s32*)&flags = raw;` — non-volatile memory round trip: gcc may optimize it into a register if it can prove no aliasing... it usually keeps the store/load (it doesn't do SRA on locals with address taken? gcc 2.7.2 does not do SRA for address-taken locals, so the store/load stay). But that changes codegen (extra sw/lw). Unless the target has them — it doesn't.

OK here's another thought: maybe the crack used in similar cases is to make `flags` be a *different variable that survives the calls anyway*: e.g., since `flags` only matters after the calls, we can assign it *inside* both arms of the first if:

```
raw = call();
if ((raw & 0x6000) != 0x2000) {
    flags = raw;
    ...calls...
} else {
    flags = raw;
}
```
Then cse: in the then-arm, `flags = raw` at the top; the andi is before the copy → stays on raw. In the else-arm, flags = raw. At the join, flags is live. Would cse merge flags with raw? In the then-arm, after `flags = raw`, raw is used by the calls? raw isn't used after the copy in that arm (the calls use s0). So flags ≡ raw, but raw dies. The qty gets flags. Across the join, flags is defined in both arms with the same value.

But this puts a `move s1,v0` at the top of each arm, whereas the target has one move right after the call. Also the else arm's copy. Hmm, that would be 2 moves. Not target.

What about assigning flags *before* the if but through a different expression: `flags = raw | (raw & 0);` folds.

Hmm, let me look at the actual orig RTL to see what the asm produces, then think about the minimal real-C thing that produces the same RTL. The asm insn is: `(insn (set (reg:SI flags) (asm_operands:SI (""))) (use (reg:SI flags)))` — an opaque set.

Real C that produces an opaque set of the same value... a volatile read of the variable itself? `*(volatile s32*)&flags` — address taken → memory.

What about a *function call* that returns its argument? Not available.

Hmm, what about the "do-while(0) 2nd set" trick: `do { flags = raw; } while (0);` was a2 = no change. Because cse still merges within.

What about the trick from func_8018FB5C: "the re-tie does 2 jobs: 2nd SET of the pinned $16 pseudo (kills sched1 birth boost) AND a zero-width RTL insn between the birth and the call arg setup". A zero-width RTL insn... `do {} while (0)` with nothing? A do-while with an empty body produces no insns (maybe a NOTE). The "2nd SET" was `vol = vol | 0x3000;`.

For flags, a 2nd set that's value-preserving and free... `flags = raw & 0xE000` costs an andi unless folded. Let's just TEST b2/b3 — maybe combine folds it and the result is exactly right. Cheap.

Also try: `flags = raw & 0xFFFFE000 | (raw & 0x1FFF)`? Not needed.

Let me add variants b1..b4 and test.
