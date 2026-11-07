---
ts: 2026-11-06T14:34:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qwcF9RkOip5luqYaBpR3
---
In block 3, the scheduling: the ready list at T-18 has 52 (1) and 55 (7f000001), and 55 is launched before 52. 55 is likely the a1 la (or a call). Hmm. The ref_count for insn 55 is 1.

Actually, the target block 3 order: let me map. The block 3 insns 43-107 include the whole `if (unk94 == 15)` body. The scheduling order (from the dump) is: 107, 106, 102, 100, 98, 96, 91, 88, 96... wait it's confusing.

The key: the a1 la (insn 45 or 47?) is launched at T-21/T-22 (late in the block). Hmm, the target order has a1 early. Let me map insn numbers to the RTL.

Actually, the scheduled order from the dump: T-1: 107, T-2: 106, T-3: 102, T-4: 100, T-5: 98, T-6: 96, T-7: 91, T-8: 88, T-9: 79, T-10: 77, T-11: 74, T-12: 72, T-13: 69, T-14: 66, T-15: 60, T-16: 60?, T-17: 57, T-18: 55, T-19: 52, T-20: 49, T-21: 47, T-22: 45.

Wait, this is the order of LAUNCHING (backwards?). The scheduler emits insns in this order. So the final order is: 45, 47, 49, 52, 55, 57, 60, 63, 66, 69, 72, 74, 77, 79, 88, 91, 96, 98, 100, 102, 106, 107. So insn 45 is first, 47 second, etc.

The target asm order (after sched1): `move $4,$16` (a0=s0), `la $5,D_8019DC34` (a1), `#APP`, `li $2,-655360`, `li $16,4`, ... So insn 45 = move a0=s0, insn 47 = la a1, etc.

Now, without the keepalive, the la sinks to position 31. The keepalive is insn 49? Its ref_count 16? Hmm.

Actually, the scheduling dump shows the a1 la (insn 47?) launched at T-21. And insn 45 at T-22. So the order is 45, 47, 49, 52, ... 

Hmm wait, the T numbering is reverse (T-1 is last). So launched last = T-1 (107), and T-22 (45) launched first. So the final order: 45 first, then 47, then 49, ..., 107 last. Yes.

So in the ORIG (with keepalive), the a1 la (insn 47) is scheduled second (after 45 = move a0). Good.

Without the keepalive, the a1 la would be scheduled later. Why? Because the keepalive asm creates a dependency: the asm uses a1, so the la must come before the asm. The asm has priority 1 and is scheduled... hmm, the asm is scheduled at some position, forcing the la before it.

Let me figure out: which insn is the keepalive? It's an asm with priority 1 and ref_count 1. Probably insn 49 (ref_count 16? no). Hmm.

Let me look at the RTL insn numbers. In the .rtl or .lreg dump, find the asm_operands insn and the a1 la. Let me grep the .sched dump's block 3 insn list... Actually the .sched dump doesn't list the insns, just numbers.

Let me look at the .lreg dump (post-sched) for the function to see the order. Or the .rtl dump (pre-sched) to see insn numbers.

Actually, the key insight: the keepalive asm pins the la early. To replace it with real C, I need a real use of a1 that's scheduled early.

Hmm, what if I make a1's value used by an earlier real instruction? The target's early instructions after the la: `li $2,-655360` (v0), `li $16,4` (s0), `sw $2,20($4)` (store), `la $2,D_8019DAFC`, `li $3,0x40000000`, `or $2,$2,$3`, `li $3,0x20000000`, `or $2,$2,$3`, `la $6,D_8019DC3C` (a2), `li $7,0x20` (a3), `sh $16,2($4)`, call.

If I use a1 in one of these, e.g., compute `v0` from a1... no.

Wait, what about the a2 computation `a2 = (s32)&D_8019DC3C;`? It's at position 29-30 in the target (after the or's). Hmm.

Let me look at this from the "what did the original source look like" angle. The function:
```
if (unk94 == 15) {
    func_8012B1B4(s0, &D_8019DC18);
    a0 = s0;
    a1 = (s32)&D_8019DC34;
    v0 = 0xFFF60000;
    s0 = 4;
    a0->unk14 = v0;
    v0 = &D_8019DAFC | 0x40000000 | 0x20000000;
    a2 = (s32)&D_8019DC3C;
    a3 = 0x20;
    a0->unk2 = s0;
    a0->unk58 = v0;
    if (func_8012D5E4(a0, a1, a2, a3) == 1) D_80126B96 = s0;
    func_8002D4C8(0xA9D, 0);
}
```
The target order of the OR's: `la $2,D_8019DAFC; li $3,0x40000000; or; li $3,0x20000000; or`. 

Hmm, what if the original source had `a1` used earlier, e.g., `a1` assigned and then a store through a1? No.

Let me try a different lever: move the `a1 = (s32)&D_8019DC34;` assignment BEFORE the `func_8012B1B4` call, so it's computed even earlier? The target has it after the call. Hmm.

What if I move it before `a0 = s0;`? Tested (v2), still 4. Let me check v2's actual order — maybe it moved but not to the right place.

Let me look at v2's diff.

Actually, all score 4 with the same ORDER diff presumably. Let me check v1/v2 diffs to see if the position changed.

Hmm, let me reconsider. Maybe the real-C crack is to use a1 in the `v0` OR chain in a way that folds. For example:
```
v0 = (s32)&D_8019DAFC;
v1 = 0x40000000;
v0 = v0 | v1;
```
What if I write `v0 = (s32)&D_8019DAFC | (a1 & 0x40000000)`? No, that changes semantics.

Hmm.

What if the a1 address is computed as part of a real store: the target's `sw $2,20($4)` stores v0 to a0->unk14. What if a1's address is used as a base for something? No.

Let me look at the .rtl dump to see the actual insn 45-55 and identify the asm. Let me grep the .rtl dump for the function's asm_operands and the la.

Actually, let me look at the lreg dump (post-sched) for the function to see the final order and register assignment, and identify insn 45/47/49. The .lreg dump's RTL is post-sched. Let me find func_80183130 in .lreg and read the first ~40 insns.

Hmm, this is a lot. Let me consider the time. It's ~08:05. I've spent ~10 min on this item. Let me give it another 10-15 min.

Let me try the C0414 dead-reset trick: 
```
a1 = (s32)&D_8019DC34;
a1 = 0;   // dead reset? but a1 is used later at the call, so setting a1=0 would change it!
```
No.

What about a "use" of a1 that's a real store but dead? E.g., `*(s32 *)a1 = *(s32 *)a1;`? That's a memory access (side effect, not deleted) and changes code. No.

Hmm.

Let me look at the actual problem: the la sinks because sched1 schedules it late. The keepalive asm forces it early. What real instruction could force the la early without being extra?

Idea: Make the `a0 = s0;` and `a1 = ...;` into a single expression that the compiler emits as move+la. E.g., `a0 = s0, a1 = (s32)&D_8019DC34;` — a comma expression. That's the same two assignments.

Idea: pass a1 to a function call that's already there? The call func_8012B1B4 takes (s0, &D_8019DC18). No.

Wait — what if the original source had the a1 assignment BEFORE the func_8012B1B4 call, and a1 was used as... no.

Let me look at the surrounding function's caller? No.

Let me try the do-while(0) around a larger region to prevent sinking. C0535 says do-while(0) splits cse1's EBB. Let me try wrapping the assignments `a0 = s0; a1 = ...;` and the following `v0 = ...` in a do-while(0)? Hmm.

Actually, let me reconsider: maybe the ORDER issue is from sched1, and the do-while(0) affects sched1's LUID ordering. Let me test wrapping the a1 assignment together with the NEXT statement in a do-while(0):
```
do { a1 = (s32)&D_8019DC34; v0 = 0xFFF60000; } while (0);
```
Hmm.

Or wrap the whole early section in do-while(0)? 

Let me look at what the C0535 example did: `do { r = p + i; } while (0);` — just the copy, and the following store was outside. And it worked for sched1 birth order. So wrapping just the a1 assignment should work... but v1 tested that and got 4. Hmm, maybe v1's do-while(0) didn't create the split because there was no following related statement.

Wait, in C0535, the do-while(0) was around TWO copies. Let me re-read: "wrap the two copy statements in `do { ... } while (0);`". So the do-while(0) was around two copies, and the effect was to keep their birth order. 

Let me try wrapping `a0 = s0; a1 = (s32)&D_8019DC34;` in a do-while(0):
```
do { a0 = s0; a1 = (s32)&D_8019DC34; } while (0);
```
Let me test that (v4).

Also, let me test moving the a1 assignment before the func_8012B1B4 call but after `a0 = s0`... can't, a0=s0 is after the call.

Hmm, wait: the source order is:
```
func_8012B1B4(s0, &D_8019DC18);
a0 = s0;
a1 = &D_8019DC34;
v0 = 0xFFF60000;
...
```
What if I move `a1 = &D_8019DC34;` to BEFORE the func_8012B1B4 call? Then it's computed before the call. The target has it after the call (`move $4,$16; la $5,...`). So that would be too early. But sched1 might sink it back to after the call? Unlikely.

Let me test v4 (do-while around both) and v5 (a1 assignment moved before the call).

Actually, let me first look at the sched1 dump for the c1 (no keepalive) to understand what changes. I need a scratch TU dump. Let me create the scratch TU setup for ov_SC04_004.

Let me check the TU's includes.
