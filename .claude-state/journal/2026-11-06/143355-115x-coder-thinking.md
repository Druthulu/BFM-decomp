---
ts: 2026-11-06T21:33:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CkgkwEmSjwR6eLe1xDrE
---
nu16 changes the modulo to `andi v0,0xfffc` (because n is u16, the modulo-by-4 is done differently: n>>2<<2 on a u16 becomes &0xfffc). That's a different instruction sequence (andi vs sra/sll). So nu16 is structurally different (wrong), even though count matches. Not the crack.

So the type change breaks the modulo. No good.

Hmm. The pin is genuinely load-bearing. Let me reconsider.

Actually, wait. Let me reconsider the target's modulo sequence:
```
81c bgez v0,828; 820 move s0,v0
824 addiu s0,v0,3
828 sra s0,s0,2
82c sll s0,s0,2
830 subu s0,v0,s0
```
This is the signed modulo: n=q; if(q<0)n=q+3; n>>=2; n<<=2; q-n. Note the branch `bgez` with delay slot `move s0,v0`. So it IS a branch (not if-converted). n crosses the branch (defined in both arms) → global-alloc. n's register: s0 (callee-saved) in target.

Mine: n in v1. Same branch structure. The only difference is the reg.

So this is purely a register allocation choice. Without the pin, global-alloc gives v1. To get s0, we need n to be callee-saved, which requires crossing a call OR higher priority.

Hmm, but n crosses the `bgez` branch (2 blocks), not a call. Global-alloc assigns caller-saved if possible (no save/restore). v1 is free. So v1.

The pin is the only way. Unless... the target's n is s0 because it's coalesced with the compiler-generated modulo's s0 pseudo. The compiler-generated `%0x1000` temp is s0 (crosses the rand). If n's pseudo were merged with that... 

Actually, here's an idea: write the velocity modulo using the SAME pattern as the radius modulo, i.e., compute it as `rand() % 4` but keep the result in a variable that's used across a call. Hmm.

Alternatively — maybe the crack is to compute BOTH velocities with a shared temp that crosses a call.

Let me look at the broader structure. The function has:
- radius = rand() % (r*3>>9)  [compiler modulo, s0]
- vel X: q=rand(); n=q;...; m=(q-n)<<16; if(rand&1)m=-m
- vel Z: same
- vel Y: -0xC0000 - ((rand()%9)<<16)

In target, s0 is used for the radius modulo AND the vel X/Z modulo temp AND m. So s0 is a general scratch across the function. The pin made n=s0, and it's reused.

Without the pin, the radius modulo uses s0 (crosses call), but the vel modulo uses v1 (local). 

To make the vel modulo use s0, make it cross a call. The `if (rand()&1)` call — the sll is in the delay slot (before the call). What if the value m crosses the call? It does: m is used in `if(...) m=-m` after the rand. So m crosses the rand! But m is in s0 in mine too (line 74 sll s0). So m is s0. But n (q-n temp) is v1.

The target coalesces n into s0 (the same reg as m). Why? Because n = q-n is immediately shifted into m. In target, `subu s0,v0,s0` writes n into s0 (same as m). In mine, `subu v0,v0,v1` writes to v0, then `sll s0,v0` moves to s0.

So the difference is the destination of the subu: target s0, mine v0. The compiler could coalesce n and m, but chose not to.

This is a local-alloc/global-alloc coalescing decision. The pin forces n=s0, so the subu writes s0.

Real-C: write `m = q - n; m = m << 16;` so the subu writes m directly? But `m = q - n` — the compiler computes into a temp then assigns m. It might coalesce. Let me test: `n = q - n; m = n << 16;` (win3) = 12, no change. Hmm.

What about `m = q - n; m <<= 16;` — the subu result into m, then shift. Let me test.

Actually win3 was `n = q - n; m = n << 16;`. The subu result went to v0 (not m). Let me try `m = q - n; m = m << 16;` (variant J).

Let me test J and also `m = (q - n); if(...) m=-m; m <<= 16;` (f was similar, 18).

Let me test J.
