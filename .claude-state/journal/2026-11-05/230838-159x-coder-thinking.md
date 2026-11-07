---
ts: 2026-11-06T06:08:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y1xdvWPya5tN3dKa4PjA
---
p1's asm:
```
286c addiu sp,-56
2870 sw s0,40(sp)
2874 move s0,a0        ← s0 = a0
2878 sw ra,48(sp)
287c jal func_8012C1B8
2880 sw s1,44(sp)
2884 move s1,s0        ← s1 = s0  (a copy!)
```
So gcc copies s0 to s1! Why? Because the source has TWO variables: `s0` and... hmm, p1 removed pa0. But the copy `move s1,s0` exists.

Hmm — maybe the source's `s0` variable is copied because of the `(s32)a0` initialization and... no.

Wait: the source is `void func_8017EF9C(void *a0) { s32 loc[5]; s32 s0; s0 = (s32)a0; ... }`. gcc would keep s0 in a register. Why two copies (a0→s0→s1)?

Maybe gcc's global alloc decided: the variable s0 (used across calls) → $16 (s0) and another pseudo (the `a0` parameter) → $17? Hmm.

Actually, `move s0,a0` then `move s1,s0` — maybe the second is for a different variable: `s0` in the source is one variable, but the compiler may have split it into two pseudos (one for the a0 value, one for the "s0" used later). Hmm.

Wait — maybe the launder's removal isn't complete: the code still has `s32 pa0;`? No, I removed it.

Hmm, let me look at the source again: `s0 = (s32)a0;` — the function parameter a0 is `void *` and s0 is `s32`. So there's a cast. The RTL: s0 = (s32)a0.

Then the calls use `(s32 *)s0` etc.

Why the extra copy to s1? Let me look at the RTL... Actually, maybe it's the `loc[5]` array: `func_8012B14C(s0, (s32)&loc[0]);` — no.

Hmm, let me compare with the target: the target has only `move s0,a0` (no s1). So in the target (with pins), there's one variable.

In p1, there's an extra copy — maybe because the variable `s0` is used both as a pointer and as an int? Hmm.

Actually — I bet the extra copy comes from `pa0`! I removed the pa0 variable, but the code still references `s0`... no.

Let me look at the RTL to find the two pseudos. Actually, let me first try the simpler experiment: remove the *pins* only (keep the launder) and see.

n3 = orig with pins removed only (launder kept).

Let me also look at whether the extra `move s1,s0` is from the `s0 = (s32)a0` cast creating two pseudos.

Hmm, in the orig (pinned), the RTL has s0 as a hard reg ($16), so `s0 = (s32)a0` is `set (reg:SI 16) (reg:SI 4 a0)`. And pa0 = s0 is a copy to a normal pseudo. In the target, pa0 is in... the target's last block uses `move a0,s0` at 292c and `lh a1,112(a0)` and `sw v0,88(a0)` — so pa0 is in a0! Yes: the launder's pa0 got $4 (a0), and the calls use `move a0,s0` (s0 = $16).

So in the target: s0 = $16, pa0 = $4 (a0). The launder's copy s0→pa0 is the `move a0,s0` at 292c!

Hmm, and in the target the last block's code uses a0 (pa0) after `move a0,s0`.

So the launder is NOT removable as a no-op: pa0 is a separate variable that gcc allocates to a0. Without it (using s0 directly), the code uses `move a0,s0` before each call — which the target also has!

Wait, the target has `move a0,s0` before each call (288c, 28fc, 292c). Those are the call-argument setups (passing s0 to the calls). In mine (p1), the calls use `move a0,s1`? Let me check the later part.

Hmm, p1's asm at 2894: `move a0,s0` — same as target. Let me see the rest.

The difference so far: the prologue. Target: `sw s0,40; sw ra,44; jal; move s0,a0`. Mine: `sw s0,40; move s0,a0; sw ra,48; jal; sw s1,44; move s1,s0`.

So mine has an extra s1 copy and a bigger frame. The `move s1,s0` is a copy of the pointer to another register — used where? Probably in the last block (pa0's role). So gcc still has a second variable (the pa0 from... wait, I removed it).

Hold on — maybe my replacement didn't remove the pa0 *declaration*; let me check p1.c's last block. Earlier I saw:
```
        s32 v0, v1;
        v1 = (s32)&D_80184CCC[0];
        ...
        *(s32 *)(s0 + 0x58) = v0;
```
The declaration `s32 pa0;` was inside the `old` string I replaced, so it's gone. Good.

Then why s1? Let me look at the RTL/gre dumps. Let me dump p1.

Actually, maybe it's the `loc[5]` array or the `v0, v1` inner variables. Hmm.

Let me dump p1's TU and look at the greg allocnos.
