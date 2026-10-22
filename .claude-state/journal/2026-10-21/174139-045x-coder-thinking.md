---
ts: 2026-10-21T23:41:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_aC7V18TZTd0a0hrmUH5M
---
Now we have data. The global allocnos (r74, r75, r78, and r76/r77 are local):

- r74: pri 5000, refs 6, live 24, crosses 6 calls
- r75: pri 4615, refs 6, live 26, crosses 6 calls
- r78: pri 3636, refs 4, live 22, crosses 4 calls
- r76: local s0, refs 3, live 7, crosses 2 calls
- r77: local s1, refs 3, live 10, crosses 2 calls
- r73: local s0, refs 2, live 7, crosses 1 call

Global order: 74 75 78 → r74 gets s0, r75 gets s1, r78 gets s2.

Wait, only 3 globals? But the function uses s0..s4 = 5 callee-saved. So 2 of them are locals (r76→s0? no...). Hmm, the table says r76 hard s0 and r77 hard s1 — but r74 and r75 are "-" (global, hard reg assigned by global alloc). So the mapping is confusing: the "hard" column for globals is "-" by design (per the tool docstring).

So: globals r74, r75, r78 get the 3 global callee-saved regs (s0, s1, s2), and locals r76, r77 get s3, s4.

From the assembly: c=$16(s0), d=$17(s1), a=$18(s2), b=$19(s3), e=$20(s4).

So globals (r74,r75,r78) = c, d, a in some order; locals r76→s3=b, r77→s4=e.

Priority order: r74 (5000) → s0 = c; r75 (4615) → s1 = d; r78 (3636) → s2 = a.

Hmm wait, but which is which? Let me confirm by matching refs/live:
- c: refs? c = a+0x2F; c used in 291B4(c) and 291A0(c,e). Hmm.
- Let's use "crosses N calls":
  - a: live across calls — a is set at entry, used at the very end (291C8(a, ...)). It crosses calls: 291B4(d), 291A0(d,291B4(c)), 291A0(c,e), 291DC(b), 291DC(a), 291C8(b,...) = 6 calls. → r74 (crosses 6 calls, refs 6, live 24) = a!
  - b: set early, used at 291C8(b,...) at the end → also crosses 6 calls. refs 6, live 26 → r75 = b.
  - e: e = 291B4(d)&0xff; used in 291A0(c,e); then e=291DC(b); used in 291C8(a,(s16)e). Crosses 4 calls (291A0(d,291B4(c)), 291A0(c,e)... let's count: after e is set (call 1 done), the calls after that are: 291B4(c) [1], 291A0(c,e) [2], 291DC(b) [3], 291DC(a) [4], 291C8(b,...) [5], 291C8(a,...) [6]. Hmm that's 6. But "crosses 4 calls" for r78.
  
  Let me instead count for c: c = a+0x2F is set AFTER the first call (291B4(d)) and before 291B4(c). c is used in 291B4(c) and 291A0(c,e). It crosses: 291B4(c) [1], 291A0(d, 291B4(c)) [2], 291A0(c,e) [3] = 3 calls. Hmm.
  
  d: d = b+0x2F set before 291B4(d), used in 291B4(d) and 291A0(d,...). Crosses 291B4(d)[1], 291B4(c)[2], 291A0(d,..)[3] = 3 calls.

Hmm, none has 4. Let me reconsider: "crosses 4 calls" might count differently.

Let's use refs: r74 refs 6, r75 refs 6, r78 refs 4.
- a: reads/writes: a=param_2 (1), a=(s16)a (2), a=a*2+0x14 (3), 291C8(a,...) (4). = 4? Hmm, maybe the initial a=param_2 gets coalesced with the param.
- Actually gcc's REG_N_REFS counts the pseudo's references after flow.

Let me instead map by live length:
- r74: live 24, crosses 6 calls, refs 6
- r75: live 26, crosses 6 calls, refs 6
- r78: live 22, crosses 4 calls, refs 4

And the local ones: r76 refs 3 live 7 crosses 2 calls → b (b used in 3 places: d=b+0x2F, b=b*2+0x14, 291C8(b,...)); r77 refs 3 live 10 crosses 2 calls → e (e: 291B4(d)&0xff, 291A0(c,e), e=291DC(b), 291C8(a,(s16)e) = 4 refs...). Hmm.

Hmm, b: b is live from `b=(s16)param_1` to `b=b*2+0x14` (after 3 calls) — crosses 2 calls (291B4(d), 291B4(c)/291A0...). live 7. r76 live 7, refs 3, crosses 2 calls. OK r76 = b. ✓ (b got s3 in asm ✓)
r77 = e (s4) ✓.

So globals: r74, r75, r78 = c, d, a in order s0, s1, s2.
- r74 (s0) = c: pri 5000 = floor(log2 6)*6/live*1e4 = 2*6/live*1e4 → 12/live*1e4 = 5000 → live = 24. ✓ r74 live 24. And crosses 6 calls: c crosses... hmm.

Hmm, so r74 live=24, refs=6. Which variable has live 24 and 6 refs?

Let's compute live lengths from the assembly (insn count):
The function body (excluding prologue/epilogue) in my build:
```
move $16,$5      ; a = param_2  (a: s2=$18)
sll $4,$4,16
sra $19,$4,16    ; b = (s16)param_1 (b: s3=$19)
addu $17,$19,47  ; d = b+0x2F (d: s1=$17)
move $4,$17
jal 291B4
andi $20,$2,0xff ; e = v0&0xff (e: s4=$20)
sll $16,$16,16
sra $18,$16,16   ; a = (s16)a
addu $16,$18,47  ; c = a+0x2F (c: s0=$16)
jal 291B4
move $4,$17
jal 291A0
move $4,$16
jal 291A0
sll $2,$19,1
addu $19,$2,20   ; b*2+0x14
jal 291DC
move $20,$2       ; e = 291DC(b)
sll $2,$18,1
addu $18,$2,20   ; a*2+0x14
jal 291DC
move $4,$19
sll $2,$2,16
sra $5,$2,16
jal 291C8
move $4,$18
sll $5,$20,16
sra $5,$5,16
jal 291C8
```
Live ranges:
- a ($18): from `move $16,$5` (or entry) to `addu $18,$2,20` — long! ~ 25 insns.
- b ($19): from `sra $19,$4,16` to `addu $19,$2,20` — ~ 20 insns.
- c ($16): from `addu $16,$18,47` to `move $4,$16` (the 291A0(c,e) call) — ~8 insns.
- d ($17): from `addu $17,$19,47` to `move $4,$17` (291A0(d,..)) — ~12 insns.
- e ($20): from `andi $20,$2,0xff` to `sll $5,$20,16` — ~15 insns.

Hmm, so a and b have the longest live ranges but got s2/s3, while c,d (short) got s0/s1. That's consistent with priority = refs/live: shorter live = higher priority!

pri = floor(log2(refs)) * refs / live * 1e4.
- c: refs 6? live 24?? That contradicts my estimate.

Hmm, maybe I mismapped. Let me reconsider: maybe r74 (live 24, refs 6, crosses 6 calls) = a, r75 (live 26, refs 6) = b, r78 (live 22, refs 4, crosses 4 calls) = ... hmm but a and b are locals in the asm? No: a=$18=s2, b=$19=s3. s2 and s3 — hmm! Maybe s2 and s3 are the globals and s0/s1 are locals!

Local allocation happens first (local-alloc assigns to $16-$23 etc.?) Actually in gcc 2.7, local-alloc assigns locals to registers, and global-alloc handles the globals. But the alloc_table says r76 hard s0, r77 hard s1 — those are the LOCAL ones assigned s0 and s1! And r73 hard s0 as well?! r73 hard s0 too. Hmm, r73 hard s0 and r76 hard s0 — conflict. So "hard" for locals is the local-alloc choice which may be later overridden by global-alloc.

OK so: locals r73, r76, r77 got local-alloc picks; globals r74, r75, r78 got the final s0/s1/s2 (or s2/s3/s4?).

Hmm. Let's think about gcc 2.7 order: local allocation (local-alloc) runs first, then global allocation (global-alloc) assigns the globals to registers, possibly overriding local choices. Actually in gcc 2.7 the flow is: local-alloc (allocate local pseudos), then global-alloc (allocate globals). Hmm, actually it's: flow → local-alloc → global-alloc → reload.

Hmm, but then "hard reg" printed for r76 = s0 could be its final home.

The assembly: c=$16(s0), d=$17(s1), a=$18(s2), b=$19(s3), e=$20(s4).

globals are r74, r75, r78 (3 of them) and locals r73, r76, r77 (3 of them). But there are 5 variables needing callee-saved: a,b,c,d,e.

Which are globals? A variable live across a call must be global (in gcc, locals can't live across calls... actually locals CAN be allocated to call-saved regs if they don't cross calls). r73 crosses 1 call, r76 crosses 2 calls, r77 crosses 2 calls. Hmm, but a call-crossing pseudo must be global in gcc 2.7? Actually no: in gcc 2.7, local-alloc only allocates pseudos that don't cross calls; those crossing calls are left to global-alloc.

So r73, r76, r77 (crossing 1 or 2 calls) crossing calls means they should be global too... but they're listed as locals with hard regs.

Hmm, "crosses N calls" in the table might be from the .greg dump's allocno info.

OK, I'm over-analyzing. Let me get the actual mapping from the .greg dump itself: it has "allocno" preferences and maybe the final assignment. Let me look at the .greg section for our function and grep for r7x entries with their hard regs.

Let me print the .greg section forfunc_801415C0.
