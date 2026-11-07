---
ts: 2026-11-06T15:04:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fz71GA4XndLsPiaKAT2k
---
This deep dive is expensive. Let me instead just experiment with candidates. The scoring is fast.

Candidates to try:
A) s0 s16 declaration.
B) init s0 in a do-while(0).
C) `a0 = s0 * 1024;`
D) give s0 a 2nd set: `s0 = s0 & 0;` (probably folds, but cheap).
E) 2nd set with `s0 = (s32)(u16)s0;` (value-preserving cast).
F) move `a0 = s0 << 10;` above `s2 = ...` and `s1 = ...`? const-prop unaffected.
G) use `s32 a0v` different variable.
H) `a0 = s0; a0 = a0 << 10;` (split shift) — cse might fold still.
I) `a0 = (s0 << 10) + (s1 - s1);`? folds.
J) Set s0 via a volatile-free opaque: read `s0 = ((Unkstruct_800B5CB8*)s1)->unk70 & 0;` → folds to 0 probably (x&0 = 0). 
K) `s0 = ((Unkstruct_800B5CB8*)s1)->unk70 * 0;` → folds.
L) `s0 = (s1 == s1) ? 0 : 1;` folds.
M) `s0 = 0; if (s1) s0 = 0;` — cse may see both 0 and keep known value 0. Probably folds.
N) `s0 = 0; if (s1) s0 = s0 + 1; else ...` no.

Hmm, what about giving s0 an initial value that is *not* constant but zero at runtime because of the loop: e.g. initialize s0 from `s2` where s2 = (s32)D_8019B538 then subtract it: `s0 = s2 - s2` folds.

Let me think about the moves that worked on similar "const fold" issues:
- line 97: "loop counter declared s16 + t0--; while (t0 >= 0) (HImode add: no SImode copy class, sll reads v0)" — the HImode add avoided a copy class.
- line 48: "$0 zr pin dropped, flag declared s16: HImode flag=1 test not folded by cse" — declaring s16 prevented cse from folding a test!

That's promising: s16/HImode values are not folded by cse the same way. Let's test: declare s0 as `s16`. Then `s0 = 0; a0 = s0 << 10;` — gcc would do HImode set, then sign-extend for shift. Since s0 is s16 in a register (HImode), `s0 << 10` promotes to int: the compiler emits sign extension? In 2.7.2, a HImode pseudo used in SImode requires conversion; cse might fold const. But the move line 48 says cse did NOT fold an HImode compare. Worth trying.

But careful: the loop uses `s0 = s0 + 1` (HImode add would be addiu with no overflow check?) and `s0 < 4`. Target has addiu s0,s0,1 and slti v0,s0,4 — works for HImode too but needs extension for `s0 << 1` and `s0 << 10`? Actually if s0 is s16, `s0 << 1` needs sign-extension of s0 to 32-bit: the register already holds sign-extended value? In 2.7.2, HImode pseudo in a register is assumed... hmm, this may add shifts.

Let me just test a batch with sc.sh. I'll write candidate files and score.

Actually, another thought: maybe declare `s0` as `u16`. Then s0 = 0, and `a0 = s0 << 10` — u16 promotes to int (zero-extend). Might still fold.

Let me test:
c2: s16 s0
c3: u16 s0
c4: do{ s0=0; }while(0)
c5: s0 = 0; s0 = s0 & 0;
c6: a0 = s0 * 0x400;

Let me write these by copying orig.c and editing.

Actually careful: the `register s32 a0` pins etc. remain.

Let me use sed to create variants? Better write each with a script. I'll create a small python script to generate variants from orig.c by string replacement.

Let me look at orig.c exactly first.
