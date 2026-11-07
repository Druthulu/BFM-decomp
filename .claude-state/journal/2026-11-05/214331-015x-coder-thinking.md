---
ts: 2026-11-06T04:43:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QMD4G3r3F7tJpuIz27jj
---
Candidate (lever-free) uses v1 for subu and v0 for lbu; the target uses v0 for both subu and lbu, v1 for... Let's see target. Get target asm from build object. Which build object? The scorer compares with build/. Let's find build object for ov_SC07_010. But easier: the diff says target:

```
lbu v0,0(a0)
subu v0,v0,a1
bgez v0,...
nop
move v0,zero
sb v0,0(a0)
lbu v0,1(a0)
subu v0,v0,a1
...
```

So target: the subtraction result reuses the loaded register v0 (the lbu destination), and the store is immediately after the if (delay slot? Actually target has 22 ins vs mine 20). Mine: lbu v0; subu v1; bgez; move v1; sb v1; ... The difference is register allocation: mine assigns the result to v1 (because v0 is reused by the next lbu, and it schedules the next load early). Target keeps result in v0 and reloads after store.

The barriers in orig force... let me check orig asm to see what barrier achieved. Original with barrier scores 0. What does orig look like? Probably orig uses v0 for result and the barrier prevents scheduling the next lbu above the sb.

So the barrier prevents sched1 from hoisting the next lbu above the sb, which would require result to be a different reg. Actually more precisely: without barrier, sched1 hoists lbu p[1] above sb p[0] (they're independent since different addresses... but they might alias! p[0] and p[1] are different bytes of same object; gcc doesn't know they don't alias, but with -O2 and no alias info, a store to (a0) may alias load (a0+1)? They are different offsets, non-overlapping, so alias analysis says no conflict). sched1 hoists the load.

Crack ideas (lever-free, real C):
1. Force a data dependency so the next load can't be hoisted: e.g., compute address via a pointer that depends on the store? Not allowed as identity launder.
2. Change the computation so cse/combine differs.
3. Make the three statements a loop — then loop structure prevents scheduling? A loop over i=0..2: `for (i=0;i<3;i++){v=p[i]-a1; if(v<0)v=0; p[i]=v;}`. That could produce exactly the target with v0 reuse? Let's try. Actually loop would generate an induction variable and compare, extra insns; target is straight-line 22 insns, so a loop unrolled by gcc? gcc 2.7.2 doesn't unroll by default at -O2. So loop is out.
4. Use distinct temp names? The issue is register allocation. In target, each statement's result register = same as load register (v0). In mine, result gets v1 because sched1 hoisted next load into v0.

What if we make the load and the subu more tightly coupled: e.g., write `p[0] = (p[0] - a1) < 0 ? 0 : p[0] - a1;` — that would load twice maybe. Or use `v0 = p[0]; if ((v0 -= a1) < 0) v0 = 0; p[0] = v0;` — same.

Alternatively, write the store through a volatile pointer? volatile would be a barrier-like lever — the kinds list says "barrier" kind = asm memory barrier. Volatile is arguably another lever kind ("no new lever of any kind"). So no volatile.

What about ordering: the target's stores happen immediately. In mine the load hoisting is due to sched1 seeing no dependence between sb a0 and lbu a0+1. If the store value depended on the address? No.

Real C move: make the three operations into three separate calls? No.

Idea: pointer reuse with an incrementing pointer: 
```
u8 *p = a0;
s32 v;
v = *p - a1; if (v<0) v=0; *p = v;
p++;
v = *p - a1; ...
```
That's equivalent; does it change scheduling? The address for the second load is p+1 where p is a temp — still independent.

Hmm. The key difference is register assignment of the result: target reuses v0 (same as loaded byte), i.e., the value of the loaded byte is overwritten. Mine's v0 is occupied by the hoisted next load. So if we prevent hoisting, local-alloc would put result in v0.

How to prevent sched1 hoisting a load above a store in plain C? Make the store's address expression depend on the loaded value? No, that changes codegen.

Actually, maybe make the second load use the same pointer p but after storing p[0], and give a dependency: e.g., compute the second byte as `p[1] - a1` where p itself is reassigned? `p = p + 1;` between statements — this creates a new pseudo; the load address depends on p (new), which is derived from old p... still no dependence on the store.

Alternative: use the stored value in the next computation in a way that cancels out? Identity launder not allowed.

Another approach: `if (v0 < 0) v0 = 0;` vs `if (v0 >= 0) {} else v0 = 0;`? Probably same.

What about writing the if differently: `v0 = p[0] - a1; if (v0 < 0) { v0 = 0; } p[0] = v0;` identical.

Let's inspect the original (with barrier) asm to know exactly what target is. Let me get orig candidate asm.

Actually the target from diff (right column) is:

```
0: lbu v0,0(a0)
1: subu v0,v0,a1
2: bgez v0,+...
3: nop
4: move v0,zero
5: sb v0,0(a0)
6: lbu v0,1(a0)
7: subu v0,v0,a1
8: bgez v0
9: nop
10: move v0,zero
11: sb v0,1(a0)
12: lbu v0,2(a0)
13: subu v0,v0,a1
14: bgez v0
15: nop
16: move v0,zero
17: sb v0,2(a0)
```
18 ins? but target says 22 ins. Wait the function has prologue? No, leaf. Hmm 22 ins includes maybe nops inserted. The diff line numbers go up to 22. Let's count: 3 groups of (lbu, subu, bgez, nop, move, sb) = 18; plus 3 nops after each lbu? The diff shows target insn 3 is nop, 4 move. Actually target listing: insn 2 subu, 3 bgez, 4 nop, 5 move, 6 sb, 7 lbu, 8 subu, 9 bgez, 10 nop, 11 move, 12 sb, 13 lbu, 14 subu, 15 bgez, 16 nop, 17 move, 18 sb, then jr ra, nop? Actually sb in delay slot. So 22 total with nops? The diff references up to 22.

Let me just dump the target from build. Find the object for ov_SC07_010.
