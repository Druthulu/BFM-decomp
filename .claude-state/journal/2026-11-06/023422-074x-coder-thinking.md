---
ts: 2026-11-06T09:34:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_I1VspaHym5JiQOP1Hav5
---
All 2. The single diff: `move a0,s0` position and `sh zero,392` base.

Let me think about the sched1 mechanism. With the keepalive, the asm use of s0 is after the 0x188 store. sched1 doesn't hoist the copy above the store because... let me dump and compare (orig vs keepalive-free) the sched1 dumps to see.

Actually, let me try a real-C move that creates a genuine use of s0 after the 0x188 store: what if the 0x188 store and the +0x44 RMW are *combined* into a statement that uses s0 once? No.

Wait — here's a thought: what if the *order* of the two independent stores is swapped in the source? I.e., write the +0x44 RMW *before* the 0x188 store:
```
*(u32*)(s0+0x44) = *(u32*)(s0+0x44) & ~4;
*(u16*)(s0+0x188) = 0;
func_801553C0(s0);
```
Then the target order would be RMW then 0x188 store — but the target has the 0x188 store at 37 and the RMW at 39-43. So no.

Hmm, but maybe the compiler would reorder them? The target has store first. If the source has RMW first, sched1 might move the store up? Unlikely (sched1 is within an EBB and respects dependencies; independent stores can be reordered).

Let me look at the target more carefully: 36 `sw zero,388(s0)` (the else branch of the inner if: `*(s32*)(s0+0x184) = 0`), 37 `sh zero,392(s0)` (the 0x188 store after the join), 38 `move a0,s0`, 39 `lw v0,68(a0)` ...

So the join block: 0x188 store, copy, RMW, call. The copy at 38 is between the store and the RMW.

In mine: copy at 37, store at 40 (using a0), RMW at 38-43.

Interesting: in mine the store is at 40, after the copy at 37 and after the `li v1,-5` at 39. So sched1 placed the copy first (birth) and then the store.

With the keepalive, sched1 kept the store first. The asm creates a scheduling barrier? An asm with a register operand doesn't create a barrier, but the USE of s0 after the store means the copy (a0=s0) could still be hoisted. Hmm, but the asm might act as a scheduling barrier in sched1 (asm insns are not scheduled across?).

Actually — the keepalive asm is at source position after the 0x188 store and before the RMW. In the RTL, it's an insn between them. sched1 treats ASM_INPUT/ASM_OPERANDS as... `sched.c` won't move other insns across an asm? There's a rule: asm insns have a scheduling type; an asm with no outputs may be treated as a barrier if it's volatile? Our keepalive is `__asm__("" :: "r"(s0))` (not volatile). Hmm.

Let me just look at the sched dump for both. But time: item 3 started 02:32:49. Budget 20-30 min. Let me think about the real-C angle more.

The key difference is just the position of the arg copy. Real C could force the copy to be later by making the RMW's base *not* s0 but a value that's computed from s0 after the store... e.g., `*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;` uses s0. The compiler copies s0→a0 and uses a0. Why does it copy at all? Because the call needs a0 = s0. The copy is inserted by sched1/local-alloc as an argument copy.

If the RMW used a *different* expression, e.g., a pointer variable that the compiler keeps in s0... 

What if we pass the call argument from a variable that is not s0, e.g.:
```
s32 s0 = *(s32 *)(s1 + 0x4C);
...
func_801553C0(s0);
```
The copy a0=s0 is needed. What if the call were the *first* use of s0 after the store, i.e., the RMW moved after the call? Target: RMW before the call (39-43, call at 42 with the sw in the delay slot). Actually the `sw v0,68(a0)` is in the call's delay slot (43). So the RMW's store is scheduled into the delay slot. Interesting.

What if we move the RMW *after* the call in source? Then the store couldn't be in the delay slot before the call. No.

Hmm, what if the RMW were written as a post-increment-ish? No.

Let me try the dump to see if it's sched1 or local-alloc. Dump orig and win, diff the .sched files around the join.

Actually, a cheaper test: does the diff persist if we disable scheduling? Can't.

Let me try a few more C shapes:
u1: `s0` used in the store via a cast: `*(u16 *)(s0 + 0x188) = 0;` -> `*(u16 *)((s32)s0 + 0x188) = 0;` (same).
u2: put the store after the RMW but before the call (t3 tried: 2).
u3: `func_801553C0(s0);` -> `func_801553C0(s1 ? s0 : s0);` no.
u4: introduce a genuine use of s0 after the store: e.g., compute the RMW address as `(u32 *)(s0 + 0x44)` stored in a variable declared before... 
u5: make the call take `*(s32*)(s1+0x4C)` directly: `func_801553C0(*(s32 *)(s1 + 0x4C));` — reload from memory; target uses s0. no.
u6: move the 0x188 store *earlier*, before the inner if? Target has it after the join (both branches converge). If moved before the inner if, the order changes (target 37 after 36). Actually the target's 0x188 store is after the if/else join. Hmm, but wait: the else branch's store at 36 is `sw zero,388(s0)`; the join's store at 37. What if the source's 0x188 store were at the top of the if-body (before the inner if)? Then the target would have sh at insn 15-ish, not 37. No.

u7: The v44 variable: in the inner if, `(v44 = *(u32*)(s0+0x44)) & 0x400` — v44 is declared at the top of the if-body. Maybe using v44 for the RMW: `*(u32*)(s0+0x44) = v44 & 0xFFFFFFFB;` — but v44 was loaded before the inner if and may be stale if the if-body modified it (`*(u32*)(s0+0x44) = v44 | 0x10;`). Semantically different? If the inner if took the true branch, +0x44 = v44|0x10; the RMW would then use the stale v44 — different behavior. Not allowed.

u8: use a `u32 *p = (u32 *)s0;` for the RMW: `p[0x11] &= ~4;` — the compiler may keep p in s0? Let me try.

u9: use `s0` in a volatile-ish way? No.

Let me dump to understand first — it's worth it. Dump win (keepalive-free) and orig (with) sched dumps and diff the relevant region. Outdir under shard dir, delete after.
