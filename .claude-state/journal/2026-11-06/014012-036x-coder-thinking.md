---
ts: 2026-11-06T08:40:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9NwoSS0P3T7InDPcDaCr
---
There's a second Register-72 line at the end: "Register 72 used 5 times across 46 insns; crosses 3 calls" — that's the .greg (global) summary, meaning r72 is a GLOBAL allocno (crosses calls!). Indeed, the a0 copy is live across... "crosses 3 calls" — the function has 1 call, but the TU-level? Hmm, this dump is the whole TU; the .greg section for the function may be later. Wait line 214 in this range (offset 23786+213 = 23999) — that's still within the lreg dump? Hmm, the lreg dump includes the global alloc summary too? "Register 72 used 5 times across 46 insns; crosses 3 calls" — that's from global.c's dump (.greg), but we're in .lreg? The line range 23786-24060 may include the end of lreg and start of greg? No — the .lreg file is the local-alloc dump. Hmm, but alloc_table read both dumps. Whatever: the important line: r72 crosses 3 calls and is a global allocno.

"crosses 3 calls" in a 1-call function? Odd — maybe counted over the whole TU? No, per function. Perhaps the calls are the ones in the RTL for the whole TU... The dumps are TU-wide, and the function section boundary may be followed by other functions. Actually line 214 relative to 23786 = 24000; the function's RTL might end there and next is another function. Let me not worry.

Key: r72 is a global allocno (crosses the call func_8012C51C — live across the call, yes: it's used at the call as a1 arg, so it's live *at* the call, and after? "crosses" might mean live across). Global alloc assigns it; local-alloc assigned the others. So the conflict: global-alloc allocates r72 after local-alloc assigned caller regs to t0..t4, leaving a3 (or a2).

In target, r72 got a2. How? If local-alloc assigned t3 to a3 instead of a2. Local-alloc's own ordering among t0..t4: r75,r76,r77 tie at 4000; tie broken by qty number order (lower qty first?) → r75 a0, r76 a1, r77 a2. To make r77 (t3) get a3, another local pseudo must take a2 first: e.g., if t0's live length dropped so its pri > 4000 and it took a2? t0 (r74) pri 2000 (live 10). If t0's live length were 4: 2*2/4 = 5000 > 4000, then order: r78 (t4, 10000) v0, t0 (5000) v1? or a0? Order of hard regs tried: GR_REGS in order v0,v1,a0,a1,a2,a3,t0.. — t0 would get v1 (first free after v0). Hmm, then t1 a0, t2 a1, t3 a2 — still a2.

We need t3 → a3. That requires a2 taken by something allocated before t3. Candidates: the a0 copy (global, allocated after local) no. Another local pseudo: t0 could take a2 if v0,v1,a0,a1 taken before it... no.

Alternatively t3's priority drops below t2's? No, they're all 4000, order by qty: r75 < r76 < r77.

Hmm wait, maybe in target local-alloc assigned t3 to a3 because the *preference* of t3's load? Local-alloc tries preferred registers first (copy preferences). The load's destination has no preference.

Alternatively: in target the pseudo numbering/order differs: t3 might be r76 (lower qty) and t2 r77? If source declares/loads in a different order... The qty numbers are assigned by RTL generation order. If t3 were created before t2, then t3 gets a2 and t2 a3 — no, we want t3 a3.

Wait, maybe in target the a0 copy is not global but local: if r72 is local, local-alloc allocates it in priority order too: 3703 → after the 4000s, so it'd get a3 still.

Hmm, unless in target the a0 copy is created EARLIER in qty order than t3 and... no, allocation order is by priority, not qty.

Let me directly look at the target-achieving w2 dump to see which pseudo got which reg and why. In w2 (off keepalive), alloc table: r72 a2 pri 3333, r77 a3 pri 1666. And r79 a0 2857. Let me read w2's lreg register summary section.
