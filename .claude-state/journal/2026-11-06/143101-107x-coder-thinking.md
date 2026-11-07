---
ts: 2026-11-06T21:31:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2JRA15HQXoQKnJW1ya3y
---
Mine at line 72: `subu v0,v0,v1` — the result goes to v0 (not s0). Then line 74 `sll s0,v0,0x10` — v0 → s0. So mine computes q-n into v0, then shifts into s0. Target computes q-n into s0 (subu s0,v0,s0), then shifts s0. 

So the difference: mine's `n` is in v1, and `q-n` result in v0; target's n in s0, `q-n` in s0.

So n is the pinned variable. Without the pin, n → v1.

n is a block-local temp (not crossing calls). Why does target put it in s0? Because the pin. The pin is NOT redundant.

Hmm. But wait, the compiler-generated `% 0x1000` modulo — what reg does it use in mine? Let me look at lines 55-67 of mine. The diff starts at 68, so 55-67 match target. Target's first modulo (77c-790) uses s0. So mine also uses s0 for that! Because that modulo's temp crosses the rand call.

So mine uses s0 for the compiler-generated modulo (crosses call) but v1 for the manual n. The manual n is block-local → v1.

To make the manual n go to s0 without a pin, we need it to cross a call. OR we need the compiler to coalesce n with the s0 pseudo from the earlier modulo. 

Idea: reuse the same variable/pseudo. The compiler-generated `% 0x1000` temp is internal. If we write the radius modulo using an explicit variable too, maybe they share s0? Hmm.

Alternative: make n cross a call by moving the `<<16` or the `-m` after the rand. Actually, the source is `m = (q - n) << 16; if ((rand() & 1) == 0) m = -m;`. If we write `m = q - n; if ((rand()&1)==0) m = -m; m <<= 16;` then m (q-n) crosses the rand → callee-saved. And target computes subu before rand, sll after rand! Let me check target: 830 subu s0,v0,s0; 834 jal rand; 838 sll s0,s0,0x10. YES — target computes q-n (subu) before rand, shifts after. So writing:
```
m = (q - n);
if ((rand() & 1) == 0) m = -m;
m = m << 16;
```
would give: subu m; rand; negu; sll. And m crosses the rand → callee-saved. But target's negu is on s0 and sll after. Let me see target: 838 sll s0,0x10; 83c andi v0,v0,1; 840 bnez; 844 nop; 848 negu s0,s0. So the order is: sll (m<<16) BEFORE the bnez/negu. So target: subu, rand, sll, then negu. So m = (q-n)<<16 is computed after the rand (sll at 838), then negated. So the value crossing the rand is (q-n), and then <<16, then negate.

If I write `m = q - n; if (rand()&1)==0) m = -m; m <<= 16;` → subu, rand, negu, sll. That's negu then sll (opposite order from target sll then negu). But -(m<<16) == (-m)<<16, so the compiler might reorder. Hmm.

Actually, the source `m = (q - n) << 16; if ((rand() & 1) == 0) m = -m;` gives: subu, sll (before rand?), then rand, negu. Target has subu, rand, sll, negu — so the sll was scheduled after the rand (sched1 hoisting the rand earlier). 

Hmm. The pin isn't about this.

Let me focus: I need n in s0. Since n is block-local, the only real-C way is to make it cross a call or coalesce with a callee-saved value.

Idea: introduce a dummy use of n after a rand call. But that changes code.

Idea: compute the modulo using a helper that spans the call. E.g., use `q % 4` but assign to a variable that's used after the rand:
```
q = rand();
n = q % 4;
if ((rand() & 1) == 0) n = -n;
m = n << 16;
```
Now n = q%4, crosses the rand (used after), → callee-saved. And the modulo `q % 4` generates sra/sll/subu with a temp; n holds the result. Target: subu s0 = q - (q/4*4) = q%4, then sll s0,0x10 after rand, then negu. Let me check target: 830 subu s0,v0,s0 (s0 = q%4); 834 rand; 838 sll s0,0x10; 848 negu s0. So yes! n = q%4 is in s0 across the rand.

But in the target, the sequence is:
```
828 sra s0,s0,2
82c sll s0,s0,2
830 subu s0,v0,s0    # s0 = q - (q/4)*4 = q%4
834 jal rand
838 sll s0,s0,0x10   # n << 16
...
848 negu s0,s0
```
So the variable in s0 is q%4 (call it n), computed via the manual sequence. Then <<16 after rand, then negu.

So the source could be:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
n = q - n;          // n = q % 4
if ((rand() & 1) == 0) n = -n;   // hmm
m = n << 16;
```
But target negates AFTER the <<16 (negu s0 after sll). If the source is `if (rand()&1)==0) n=-n; m=n<<16;`, the order would be negu then sll. Target is sll then negu. So the source must be `m = n << 16; if ((rand()&1)==0) m = -m;` with n = q%4. Then m = n<<16 crosses the rand (computed after? no, m = n<<16 before the rand in source order, but sched moved it after). Hmm.

Actually target: 830 subu s0 (n=q%4); 834 rand; 838 sll s0 (m = n<<16); 848 negu. So the sll happens after the rand. In source order, `m = n << 16;` is before `rand()`. Sched1/sched2 moved the sll after the rand? Or the compiler computed n first, called rand, then shifted. 

If I write:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
n = q - n;            // n = q % 4  (q-n)
m = n << 16;
if ((rand() & 1) == 0) m = -m;
```
This is semantically the same as the original `m = (q-n)<<16`. And n crosses the rand (n used in `m = n<<16` which is before the rand... hmm, n dead before rand).

Wait, the original already computes m = (q-n)<<16 before the rand. So n is dead before the rand. The value crossing the rand is m. In target, m is in s0 (callee-saved) — correct, because m crosses the rand (m used in the if after rand). So m must be callee-saved. And the intermediate q%4 (n) is ALSO in s0 because it's coalesced with m (n = m>>16, same register).

So the crossing variable is m, which forces s0. In mine, m is in... line 74 `sll s0,v0,0x10` → m in s0! So mine ALSO has m in s0 (crossing the rand). The difference is only that mine's n (q%4) is in v1, while target's n is in s0 (coalesced with m).

So the issue: mine computes q-n into v0 (line 72 `subu v0,v0,v1`), then shifts v0 into s0 (line 74). Target computes q-n directly into s0 (subu s0,v0,s0), then shifts s0 in place. So target's m and n are the SAME register (s0); mine's n (v1) is separate and the result goes to v0 then s0.

Why? Because target's `n = q - n` writes to s0 (same as m). In C, `m = (q - n) << 16` — the compiler could compute `q-n` into the same reg as m. Target does subu s0,s0 then sll s0. Mine does subu v0,v0,v1 then sll s0,v0. So mine's n is a separate pseudo (v1) and the result v0 then m s0.

This is a coalescing difference. The pin forced n into s0, making `q - n` reuse s0.

Real-C to coalesce: write `n = q - n; m = n << 16;` (separate statements). Then n (q%4) is used in `m = n << 16`, so the compiler may keep n in the same reg as m. Let me test:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
n = q - n;      // split!
m = n << 16;
if ((rand() & 1) == 0) m = -m;
```
This is the "split into its own statement" move (like the pv mask split). Let me test this for both sites.

Actually, `m = (q - n) << 16;` vs `n = q - n; m = n << 16;` — the latter splits the computation, giving n a 2nd live set. Let me test.

Let me build win3 with this split (keeping the manual n, removing the pin).

The source currently:
```
    m = (q - n) << 16;
```
Change to:
```
    n = q - n;
    m = n << 16;
```
for both sites. Let me test.
