---
ts: 2026-11-06T10:23:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_inpHqxsf8BnlICVioL9O
---
The two-statement shift form always shifts the caller-saved regs (score 22). The single-expression form gives score 2 (only the sign-ext temp).

Hmm. The two-statement form removes the temp, which perturbs the caller-saved allocation. The single-expression form keeps the temp (v1), which is the only diff.

Can I make the single-expression form's temp get s0? The temp is a local qty (born after the call). local-alloc gives it v1. If I could make it get s0...

Actually — what if the sign-extension temp is *forced* to reuse div's register by writing the sign-extension as a copy through a variable? Hmm.

Wait, here's an idea: what if I write `div = (s16)div;` but the compiler's sign-extend pattern uses `(set (reg temp) (ashift (reg div) 16))` + `(set (reg div) (ashiftrt (reg temp) 16))`. If I could make `temp` and `div` the same qty... 

What if div is declared `register`? Then gcc might allocate it earlier. Hmm, tried `register` for item 2 (no change).

Alternatively, use a `s16` intermediate: 
```
s16 dt;
...
dt = div;       // hmm, changes code
```

Hmm. What if the sign-extension is written as `div = (s16)div;` where div is `s32` but the RTL is `(set (reg div) (sign_extend (subreg (reg div) 0)))`. The MIPS expander emits:
```
(set (reg temp) (ashift (reg div) (const_int 16)))
(set (reg div) (ashiftrt (reg temp) (const_int 16)))
```
The temp is a new pseudo. local-alloc gives it v1. 

If I could make the temp cross a call (so it'd get a callee-saved reg)... no.

Hmm, what if I move the sign-extension BEFORE the call? Then the temp's live range... but the target has it after the call.

Wait — actually, maybe the target's in-place `sll s0,s0,16; sra s0,s0,16` is NOT from a sign-extension pattern but from `div` being a hard reg (the pin). But the ORIGINAL (Square) source wouldn't have a pin. Hmm. Unless the original used a `register` variable? Or the original's `div` was a parameter that gcc kept in a hard reg?

Hmm. Actually, maybe the original's in-place shift comes from `div = div << 16; div = div >> 16;` (in-place shifts) with the caller-saved allocation matching. The two-statement form gives in-place shifts. The caller-saved shift is the remaining issue. Let me look at i1's diff to see if the caller-saved shift is fixable by statement reordering.

i1 = h1 + two-statement shift. Score 22, REG-caller. Let me diff.
