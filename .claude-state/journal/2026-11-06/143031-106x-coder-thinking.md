---
ts: 2026-11-06T21:30:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B7mcbGjcsRKYLVWLCsC5
---
win2: 119 ins (2 extra), score 18. The `q % 4` generates a slightly different sequence (2 extra). So not it.

The first site in win2 used v0/v1; the manual n version used v1. Hmm.

Let me think. The target's n is in s0 for BOTH sites (and the compiler-generated %0x1000). The pin forces n to s0. Without the pin, the manual n gets v1.

Why does the compiler choose s0 in target? Because n is pinned. Real C can't pin.

But maybe n lands in s0 if its live range crosses a call. Let me check: is n live across any call in the target? Looking at target: n (s0) is used at 77c-790 (first modulo), then 81c-830 (second), then 858-868 (third). Between these, there are rand() calls. Is n live across them? At 790, `subu s0,v0,s0` (n used), then `lw v1,32(s2)`... then the div... then `move a1,s0` at 7dc (uses s0 = n as the radius argument!). So n IS live across the call at 78c (rand) — s0 is set at 790 after the call though. Hmm.

Wait, at 78c there's a jal rand, then 790 subu s0,v0,s0. So s0 is used after the call but set after the call. n's value from before the call (s0 at 784-788) is used at 790 after the call → n crosses the call at 78c! Because `n = n>>12; n = n<<12;` happens BEFORE the call (784, 788), and `q - n` (subu) happens AFTER the call (790). Wait, the source: `func_8012B0B4(&sp10, rand() % 0x1000, rand() % (...))`. The first argument `rand() % 0x1000` — the compiler evaluates it, and the second `rand()` is a separate call. The modulo temp crosses the second rand() call? Let me see: 
```
778 bgez v0,784; 77c move s0,v0
780 addiu s0,v0,4095
784 sra s0,s0,0xc
788 sll s0,s0,0xc
78c jal rand          <- second rand
790 subu s0,v0,s0      <- q - n, n in s0 across the call!
```
YES! n (s0) is live across the rand() call at 78c. So n crosses a call → global-alloc MUST put it in a callee-saved reg → s0!

So in the target, the compiler-generated modulo for `rand() % 0x1000` uses a pseudo that crosses the next rand() call, forcing callee-saved s0. And the manual n sequences (2nd, 3rd) reuse the same s0 because... the pseudo is the same or allocation.

Wait, but the manual n sequences (2nd/3rd) are separate. In target they also use s0. Hmm. Maybe because the manual n and the compiler's modulo temp are the same pseudo (both derived from rand() results, same type). The compiler may reuse the register.

In MINE (pin removed), the manual n gets v1. Why doesn't the compiler-generated modulo force s0 and then n reuse it? Let me look at mine's full asm around the first modulo. In win.c (pin removed), the diff showed only the manual n sequences (68-72, 82-86) differ; the compiler-generated modulo (which crosses the call) presumably uses s0 already? Let me check.

Actually, in win.c the register pairs were "v1->s0 x14, v0->s0 x4" — so mine uses v1/v0 where target uses s0, in the manual n sequences. The compiler-generated modulo might already use s0 in both. So the issue is just the manual n.

So: if I write the manual modulo using the SAME pattern as the compiler's `%`, i.e., `q % 4`, the compiler generates the modulo but win2 gave 119 (2 extra) because the manual `%4` and the sign correction... hmm.

Wait, win2 replaced BOTH sites with `q % 4` and got 119 (2 extra). The extra 2 might be because `%4` uses `div`? No, %4 is sra/sll/subu (power of 2). Let me look at win2's diff head to see the 2 extra.

Actually, maybe the issue: the target's manual modulo and the compiler's %0x1000 share the same pseudo, so s0 is used. If I write `q % 4`, the compiler creates a NEW pseudo for each, maybe not sharing.

Let me look at win2's full diff.

Actually, let me reconsider: the cleanest crack might be to make `n` cross a call. In the manual sequence, if I move the `m = (q - n) << 16;` AFTER a rand() call, then n crosses it. But the source computes m before the next rand. Hmm.

Alternatively, the target's n in s0 is because the pin. Real-C to force callee-saved: make n live across a call. 

Idea: restructure the velocity computation to interleave: `q = rand(); n = ...; if ((rand() & 1) == 0) m = -m;` — n is dead before the rand. 

Hmm.

Let me look at the compiler-generated `% 0x1000` in mine (win.c): does it use s0? If yes, then n could reuse s0 if the compiler coalesces. Let me dump mine's asm and look.

Let me get mine's full asm around the modulo. Let me use --keep to get the object and objdump? Or just the diff. The diff showed the first differing line at 68. Let me see lines 55-95 of mine's asm via the diff head. Actually let me capture the full diff for win.c.

Let me just try a few real-C variants:
1. win3: keep manual n but add a use of n across the rand: reorder `m = (q - n) << 16;` to after `if ((rand() & 1) == 0)`? No, m is used in the if.
   Actually: `q = rand(); n=q; ...; m = (q-n)<<16; if ((rand()&1)==0) m=-m;` — m is computed before the rand. If I compute m after the rand: `q = rand(); n=...; int r = rand()&1; m=(q-n)<<16; if(r==0)m=-m;` — now n is live across the rand → callee-saved! But this changes the order of rand() calls? No, the rand for the sign is after the modulo; reordering the computation of m vs the rand is semantically fine (rand called same order). Let me test:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
if ((rand() & 1) == 0) m = -((q - n) << 16); else m = (q - n) << 16;
```
Hmm, that duplicates the expression. Or:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
t = rand() & 1;   // rand crosses n
m = (q - n) << 16;
if (t == 0) m = -m;
```
This makes n live across the rand (since m uses n after). That could force s0! And the code: target has the rand after m (m computed, then bgez on rand result). Hmm, target order:
```
81c bgez v0 (q)
820 move s0,v0
824 addiu s0,v0,3
828 sra s0,s0,2
82c sll s0,s0,2
830 subu s0,v0,s0   # m-ish
834 jal rand         # sign rand
838 sll s0,s0,0x10   # m <<= 16 AFTER the rand!
83c andi v0,v0,1
840 bnez v0,84c
844 nop
848 negu s0,s0
```
Interesting! Target computes `subu s0,v0,s0` (q-n) at 830, then calls rand at 834, then `sll s0,s0,0x10` (m<<16) AFTER the rand. So n is dead at 830 (q-n computed), and s0 holds (q-n) across the rand, then shifted. So s0 crosses the rand call! That's why s0 (callee-saved) is needed — the value (q-n) is live across rand().

In MINE (pin removed), the sequence might shift the `sll <<16` before the rand, so s0 doesn't cross. Let me check mine's asm.

So the C source `m = (q - n) << 16; if ((rand() & 1) == 0) m = -m;` — the compiler could compute m<<16 before or after the rand. Target computes q-n before, <<16 after (scheduling). In mine, maybe <<16 before the rand (so m is in s0/v1 across).

Hmm, this is sched1/sched2 ordering. The pin forced n into s0 which is callee-saved, and the value crosses the call.

Wait, but the manual n is dead at `q-n` (830), and the RESULT (q-n) is live across the rand. So the pseudo live across the call is the (q-n) value, not n. In target that's s0. In mine, it's v1 (caller-saved)?? But it crosses a call, so global-alloc MUST use callee-saved for it. Unless mine computes <<16 before the rand (so the crossing value is m, which is also callee-saved). Hmm.

Let me look at mine's asm. Let me capture win.c full diff.
