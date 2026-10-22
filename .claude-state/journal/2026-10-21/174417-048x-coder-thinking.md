---
ts: 2026-10-21T23:44:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_J36SovcJxLSHSoDhOTGK
---
Globals: 74, 75, 78 (3 regs to allocate). Hard regs used include 16,17,18,19,20 (s0..s4).

The .greg dump also has ";; N preferences:" lines per allocno in some versions. Let me get those. My gsec filter only prints lines starting with ";;" — the preferences lines are like ";; 74 preferences: 4 16". They weren't printed... The output shows only 7 lines. So no preferences lines (gcc prints them only when there are copy preferences).

Now: which global is which variable? Let's find out from the .lreg dump (local allocation) or from the final assembly.

From the assembly: c=$16(s0), d=$17(s1), a=$18(s2), b=$19(s3), e=$20(s4).
Globals get 3 of these; the other 2 are locals. But locals can't cross calls... yet a and b cross calls. Hmm — unless in gcc 2.7 "local" pseudos CAN cross calls if they're assigned to callee-saved regs (local-alloc in gcc 2.7 does handle locals that don't cross calls only).

Hmm, actually gcc 2.7's local-alloc: "allocate_local_regions" — it allocates locals that fit in the local regs. Pseudo-regs that cross calls are turned into "global" by `make_global_reg`? Actually in gcc 2.7, `local_alloc` calls `make_global_reg` for regs that cross calls.

Let me determine the mapping empirically differently: I'll use the alloc_table's "hard" column:
- r76 → s0
- r77 → s1
- r73 → s0

Conflict! r73 and r76 both "s0". These hard-reg columns come from the .lreg dump (local-alloc's choice), then global-alloc may override.

Alternatively, from alloc_table: r74, r75, r78 are globals (pri 5000, 4615, 3636) — the order line says "3 regs to allocate: 74 75 78" meaning they're allocated in that order → r74 gets the first available callee-saved reg, r75 the next, r78 the next.

Available callee-saved: s0..s7 (16..23), minus those used by locals (r73, r76, r77 which got local-alloc's s0, s1, and ?). Hard regs used: 16 17 18 19 20.

If locals took s0, s1 and one more (s3, s4?), then globals get... hmm, 5 callee-saved used by 5 variables: 3 globals + 2 locals? But the table lists 3 locals (r73, r76, r77) plus 3 globals = 6 pseudos, but only 5 variables (a,b,c,d,e). Plus the 6 "TIE" entries (r79, r81, r85, r87, r90, r92) which are call-arg copies (a0, a1, v0) — those are locals too.

So 6 locals + 3 globals = 9, minus 3 hard-reg ties (r79=a0, r85=v0, r92=a1) = 6 real: r73, r76, r77, r81(s0), r90(v0)... hmm confusing.

Let's simplify: the table shows
- r79 a0, r81 s0, r85 v0, r87 v0, r90 v0, r92 a1 (ties, 2 refs, 2 live) — these are call-arg setup pseudos (each is a copy of an argument into a0/a1/v0). r81 s0: that's a copy of s0 into a0 maybe.
- r74, r75, r78: globals
- r76, r77, r73: locals

5 variables (a,b,c,d,e) → 3 globals + 2 locals. Which 3 are globals? The globals have high live lengths (24, 26, 22) → a, b, and one of c/d/e with live 22. c and d have live ~8-12 in my count but REG_LIVE_LENGTH is in a different unit.

Hmm. But wait: c and d in the asm get $16 and $17 (s0,s1) — the LOWEST callee-saved regs. Globals are allocated FIRST (in gcc 2.7, global-alloc runs after local-alloc? or before?).

In gcc 2.7 the order in `allocate_numbers` (global.c) is: globals get allocated first? Actually gcc 2.7's flow: `rest_of_compilation` → ... → `local_alloc()` then `global_alloc()`. Hmm, actually in gcc 2.7: `flow_analysis` → `local_alloc` → `global_alloc` → `reload` → ...

Hmm, in gcc 2.7 global.c, `global_alloc()` first calls `allocate_numbers` for globals, then for locals. Actually `allocate_numbers` handles both global and local allocnos.

The order line "3 regs to allocate: 74 75 78" — these are the allocnos to be allocated in global-alloc. Then the local ones are separate.

OK let me take a totally different and more direct approach: instrument by dumping with the `.lreg` after global allocation? Or simply: make variants and observe the resulting assembly, using the alloc table as guidance.

Practical approach: I know the priority formula. Let me figure out which pseudo is which by using the priority formula with the observed numbers:
- pri 5000 = floor(log2(6)) * 6 / live * 1e4 = 2*6/live*1e4 → 12/live*1e4 = 5000 → live = 24. ✓ (r74: refs 6, live 24)
- pri 4615: refs 6, live 26 → 12/26*1e4 = 4615. ✓
- pri 3636: refs 4, live 22 → floor(log2 4)=2 → 2*4/22*1e4 = 3636. ✓
- r76: refs 3, live 7 → floor(log2 3)=1 → 3/7*1e4 = 4285 ✓
- r77: refs 3, live 10 → 3/10*1e4 = 3000 ✓
- r73: refs 2, live 7 → floor(log2 2)=1 → 2/7*1e4 = 2857 ✓

Great, formula confirmed: pri = floor(log2(refs)) * refs / live * 1e4.

Now assign to variables. Global order 74 (5000) → s0, 75 (4615) → s1, 78 (3636) → s2.

In the asm: s0=c, s1=d, s2=a. So:
- c: refs 6, live 24, crosses 6 calls
- d: refs 6, live 26, crosses 6 calls
- a: refs 4, live 22, crosses 4 calls

Hmm, that gives c live 24 > a live 22. But in the asm c's live range looks shorter than a's. Hmm, REG_LIVE_LENGTH may be measured in a different unit (e.g., insn count in the flow graph, which is the same order as my count). Let me recount from the asm:

Actually let me count live lengths precisely using the RTL insn numbers. From the .lreg dump earlier I could extract. Meh.

Alternatively: refs 6 for c? c is referenced: c = a+0x2F (1), 291B4(c) (2), 291A0(d,...) no, 291A0(c,e) (3). That's 3. Hmm, refs 6 doesn't fit.

Let me reconsider: maybe r74 = a (refs 6? a: a=param_2(1), a=(s16)a(2), a=a*2+0x14(3), 291C8(a,..)(4) = 4).

Hmm, refs 6 vs 4.

I'm not confident about the mapping. Let me get it precisely: I'll write a helper that, for the .lreg dump, extracts pseudo names → hard regs from the final RTL. Actually the simplest: the final .greg/rtl dump after global allocation shows `(reg:SI 18 s2)` for the pseudo. The alloc_table already prints "hard" for locals. For globals it prints "-" because the .greg dump is the INPUT to global allocation.

So to map globals to variables, I need the .lreg dump (which is printed AFTER global allocation? "lreg" = local register allocation... hmm, in gcc 2.7 the dump flags: -dl = "local register allocation", -dg = "global register allocation"). In gcc 2.7's global.c, the dump is printed at the START (input) and maybe also at the end.

Alternative: use the final RTL dump (c1.i.rtl) which is printed at the end of the compilation with all pseudos replaced by hard regs. But then I can't see pseudo names.

OK, alternative approach: use the `.s` assembly + my own reasoning, plus the priority numbers, and just do a targeted experiment: I need to change which variables are global vs local and their priorities.

Actually here's a cleaner idea: I know the final assignment from the asm:
c=$16(s0), d=$17(s1), a=$18(s2), b=$19(s3), e=$20(s4).

And I know the priority values: 5000, 4615, 3636 for globals; 4285, 3000, 2857 for locals (r76, r77, r73).

Local allocnos get their regs from local-alloc; global allocnos from global-alloc. In gcc 2.7, `global_alloc` → `allocate_numbers` handles BOTH global and local allocnos, but global allocnos are allocated first (they're the ones that cross calls).

Since the global order line lists only 74 75 78, and hard regs 16,17,18,19,20 are used, we have 3 globals + 2 locals-with-callee-saved (the other 2 of the 3 locals r73/r76/r77 must be in caller-saved regs or coalesced).

Hmm, r76 hard s0, r77 hard s1 — those are from the .lreg (local-alloc) input. Then global-alloc reassigned things.

Let me try yet another approach: just check the `-dg` output at the END. gcc 2.7's global.c has:

```c
  if (dump_file) {
    fprintf (dump_file, "\n;; Function %s\n", ...);
    ...
  }
```
Let me check if there are TWO ";; Function func_801415C0" sections in the .greg file (one at input, one at output). Let me count.

Let me use a helper to count occurrences.

Actually, I realize there might be a much better approach to this whole problem, given the constraint "no register vars, no __asm__".

KEY INSIGHT: The target uses a=s0,b=s1,c=s2,d=s3,e=s4 — all five in callee-saved regs, in the order a,b,c,d,e which equals declaration order. My candidate gives c,d,a,b,e.

Since priority = floor(log2 refs)*refs/live, and the winner is the max priority, I need to raise a's and b's priority above c's and d's.

But note: locals are allocated first in gcc 2.7?? If c,d are locals (allocated by local-alloc) and a,b,e are globals, then the split into locals/globals matters.

Hmm, from the asm: b=$19(s3) and e=$20(s4) — and r76→s0, r77→s1 in the lreg table with refs 3. b has refs 3! (b=(s16)param_1, d=b+0x2F, b=b*2+0x14, 291C8(b,...)) = 4 actually. e: e=291B4(d)&0xff, 291A0(c,e), e=291DC(b), 291C8(a,(s16)e) = 4.

Hmm refs 3 for r76/r77.

Let's consider: r73 (refs 2, live 7, crosses 1 call) → s0. Which variable has 2 refs and crosses 1 call? Hmm.

I'm burning time. Let me do something much more direct: EXPERIMENT. Try variants and look at the resulting allocation (from the .s asm of the dump, or better from delever_search's score/diff which shows register pairs).

But each experiment is a compile (~1-2 s). A sweep of 50 variants is fine.

Let me think about which knob to turn. The priority formula is floor(log2 refs)*refs/live.

For a global to beat another global, it needs higher floor(log2(refs))*refs/live.

Currently: globals are (refs 6, live 24) pri 5000 → s0; (refs 6, live 26) pri 4615 → s1; (refs 4, live 22) pri 3636 → s2.

And the asm says s0=c? Hmm, but if globals get s0,s1,s2 then the global variables are c,d,a and locals b,e get s3,s4.

So: c has refs 6, live 24; d has refs 6, live 26; a has refs 4, live 22.

Hmm, c refs 6? Let's recount c: 
- `c = a + 0x2F;` → 1 ref (write)
- `func_800291B4(c)` → read → 2
- `func_800291A0(c, e)` → read → 3
Also `func_800291A0(d, func_800291B4(c) & 0xFF)` — same c read.
Hmm 3.

Unless gcc counts the "e = func_800291B4(d) & 0xFF" and other things.

a refs 4: a=param_2, a=(s16)a, a=a*2+0x14, 291C8(a,..). That's 4 ✓ matches "refs 4"!
d refs: d=b+0x2F, 291B4(d), 291A0(d,...) = 3. Hmm.

c: 3, d: 3, a: 4, b: 4, e: 4.

But the table says locals r76 refs 3, r77 refs 3, r73 refs 2, and globals refs 6,6,4.

Hmm, refs 6 for two globals. Which vars have 6 refs? None by my count.

Unless REG_N_REFS includes the hard-reg references... 

I think I'm misreading which allocnos are global. "3 regs to allocate: 74 75 78" and then the table's "GR_REGS" vs "GR_REGS or none" note. r74/r75/r78 have "GR_REGS" in notes; r76/r77/r73 have "GR_REGS or none".

So r74, r75, r78 are definitely globals (cross calls).

OK: which 3 variables cross calls? All of a,b,c,d,e cross at least one call... Actually:
- a: set at entry, used at the end → crosses 6 calls ✓
- b: crosses 6 calls ✓ (b set early, used in 291C8(b,...) at the end)
- c: crosses 3 calls
- d: crosses 3 calls
- e: crosses 4 calls

Hmm: "crosses 6 calls" for r74 (refs 6) and r75 (refs 6); "crosses 4 calls" for r78 (refs 4).

If r74 and r75 = a and b, both crossing 6 calls and refs 6... 

So maybe: a refs 6? a = param_2 (1), a = (s16)a (2), a = a*2+0x14 (3), 291C8(a, (s16)e) (4). Plus the initial a=param_2 might be 2 refs (set + the copy). And in the asm, `move $16,$5` — a is copied from a1. So maybe a has more refs.

And e crosses 4 calls with refs 4: e = 291B4(d)&0xFF (1), 291A0(c,e) (2), e = 291DC(b) (3), 291C8(a,(s16)e) (4) ✓✓ refs 4, crosses 4 calls ✓.

So r78 (refs 4, live 22, crosses 4 calls) = e! And e got s2?? But the asm says e=$20(s4)!

Hmm, that contradicts. Unless globals got s3,s4,s2 in a different order... 

Ugh. Let's settle this: r74 (pri 5000) gets the first callee-saved reg available. If the globals are a, b, e (the three that cross the most calls) then they'd get s0,s1,s2 — but the asm says a=$18(s2), b=$19(s3), e=$20(s4).

Hmm! But wait: are $18,$19,$20 callee-saved? Yes s2,s3,s4. And $16,$17 = s0,s1.

So maybe global-alloc picked s2,s3,s4 for the globals because s0,s1 were already taken by locals (r76→s0, r77→s1 from local-alloc)! Yes! That makes sense: local-alloc ran first and assigned r76→s0, r77→s1 (and r73→s0?? hmm).

So: locals r76 (s0), r77 (s1) = c and d (the two that cross only 3 calls, but local-alloc can allocate a local to a callee-saved reg if it doesn't cross a call... but c and d DO cross calls).

Hmm, r76 "crosses 2 calls", r77 "crosses 2 calls". c crosses: 291B4(c) [call 1], 291A0(d, 291B4(c)) [call 2], 291A0(c,e) [call 3]. Hmm, 3 calls? Depends on counting: a pseudo "crosses" a call if it's live across it. c is set before call "291B4(c)". Is c live across that call? It's USED by that call, so it's live AT the call, not across. So c is live across: call 291A0(d, 291B4(c)) [the call after 291B4(c)] and call 291A0(c,e) → hmm, c is used in 291A0(c,e) so it's live up to it. So c crosses 1 call (291A0(d,291B4(c)))?

Ugh, "crosses N calls" definition unclear.

Let me just take the empirical route and use the .lreg hard-reg column:
- r76 → s0, r77 → s1 (locals)
- r73 → s0 (also local, but maybe reallocated)
And globals r74, r75, r78 got s2, s3, s4 (in order 74→s2, 75→s3, 78→s4)? That would mean: 74 = a ($18=s2), 75 = b ($19=s3), 78 = e ($20=s4).

Check: 74 pri 5000 = refs 6, live 24 → a. 75 pri 4615 = refs 6, live 26 → b. 78 pri 3636 = refs 4, live 22 → e. And locals r76→s0 = c, r77→s1 = d.

That's consistent with the asm! c=s0(r76), d=s1(r77), a=s2(r74), b=s3(r75), e=s4(r78). 

And r73 (refs 2, live 7, crosses 1 call) → s0: that's a call-arg copy pseudo? No, it has a hard reg. Hmm, r73 might be `a`... whatever.

Now the TARGET: a=s0, b=s1, c=s2, d=s3, e=s4.

So in the target, a and b are the LOWEST callee-saved regs. In my candidate, a and b are globals that got s2,s3 because locals c,d took s0,s1 first.

Priority: locals are allocated first by local-alloc; global-alloc then picks from what's left. Wait no — global-alloc allocates the GLOBALS, choosing among all callee-saved regs, but must avoid conflicts with the locals already assigned? In gcc 2.7, `allocate_numbers` handles global allocnos first with a preference order.

Actually in gcc 2.7 global.c `allocate_numbers`:
```c
  /* Allocate all the globals first, then the locals. */
```
Hmm. If globals were allocated first they'd get s0,s1,s2 and locals s3,s4. But the asm shows globals a,b,e in s2,s3,s4 and locals c,d in s0,s1. So LOCALS got s0,s1 first. That means local-alloc ran first and chose s0,s1 for c,d.

Hmm, but local-alloc doesn't allocate pseudos that cross calls... unless c and d don't cross calls in gcc's view.

OK so c and d are LOCALS (not crossing calls per gcc), and a, b, e are GLOBALS.

To get the target (a=s0, b=s1, c=s2, d=s3, e=s4), I need:
- a, b, e to be allocated to s0, s1, s4 — but locals are allocated first, taking s0,s1.

Hmm. Wait — if the target has a=s0,b=s1,c=s2,d=s3,e=s4, and locals c,d got s2,s3 while globals a,b,e got s0,s1,s4. So local-alloc picked s2,s3 for c,d, leaving s0,s1,s4 for globals. Hmm, but then global order: 74(a)→s0, 75(b)→s1, 78(e)→s4. That works if local-alloc gave c,d the regs s2,s3.

But in the target, c is s2 and d is s3, matching r76→s2, r77→s3. In my candidate r76→s0, r77→s1. So local-alloc's choice differs!

Why would local-alloc pick s2/s3 vs s0/s1 for the same locals? local-alloc picks the first free local register (from the local-alloc reg list). The local register list order in gcc 2.7 is: $16,$17,$18,$19,$20,$21,$22,$23, $30(fp), $31? Hmm, local-alloc's local_regs preference order.

Hmm, but the local regs available depend on which hard regs are already used by the function (hard regs used: 2 4 5 16 17 18 19 20 31). Hmm.

Hold on. Actually in the TARGET, the pinned version had a→$16, b→$17 forced. Then local-alloc would pick s2,s3 for c,d (since s0,s1 are taken by the pinned a,b) and global-alloc gives e→s4. That EXACTLY explains the target!

So the target's allocation is a natural consequence of a and b being pinned to $16/$17. To get it naturally, I need local-alloc to give c,d the regs $18,$19 (s2,s3) and global-alloc to give a,b,e $16,$17,$20.

So the lever: make local-alloc skip s0,s1 for c,d. Why does local-alloc prefer s0,s1? Because it takes the first free registers. If a and b were also locals... hmm.

Alternatively: make c and d GLOBALS too. Then global-alloc handles all 5 and picks by priority: the order would be by priority, and the target order is a,b,c,d,e. So I'd need priorities a>b>c>d>e.

Currently the globals are a,b,e with priorities 5000, 4615, 3636. If c,d became globals, their priorities would be refs 3-ish, live small → high priority (like 3/10*1e4=3000 to 3/7*1e4=4285). Hmm, r76 has refs 3, live 7 → pri 4285; r77 refs 3, live 10 → 3000. So if c and d were globals with pri 4285 and 3000, the global order would be: c(4285), a(5000), b(4615), d(3000), e(3636) → sorted by priority: a 5000 > c 4285 > b 4615? no: 5000 > 4615 > 4285 > 3636 > 3000 → order a, b, c, e, d. That gives a=s0,b=s1,c=s2,e=s3,d=s4. Target wants e=s4, d=s3.

Close! I need d's priority above e's. d: refs 3, live 10 → 3000. e: refs 4, live 22 → 3636.

To swap: increase d's refs or reduce d's live; decrease e's refs or increase e's live.

Hmm, but wait: making c,d global requires them to cross calls in gcc's view. c crosses the call 291A0(d, 291B4(c))? and d crosses 291B4(c)... 

Hmm, actually why is c a local? Because c is not live across a call? c is set before call 291B4(c) and used in that call → c is live AT the call, so gcc's local-alloc can allocate it to a call-saved reg? No — if it's live at a call it must be in a callee-saved reg. local-alloc handles locals live across calls by making them global.

Ugh, in gcc 2.7: `local_alloc` → for each local reg, if `REG_LIVE_LENGTH` spans a call, it's made global (`make_global_reg`). c IS live across the call 291A0(d, 291B4(c))? No: c is used as an argument to 291B4(c) which is inside the argument list of 291A0. So c is live up to 291B4(c) but the outer call 291A0 happens after → c is dead by then. So c does NOT cross a call → local ✓.

d: d is used in 291A0(d, ...) as first arg → d live up to that call. Before it, 291B4(c) call happens → d IS live across the 291B4(c) call. Hmm, then d should be global.

Hmm, but r77 (crosses 2 calls) is d? "crosses 2 calls" for r77. Hmm.

Whatever. Let me try the empirical approach: I want the final allocation to be a=s0,b=s1,c=s2,d=s3,e=s4.

Idea A: make c and d globals by extending their live ranges across calls (e.g., recompute them later). Then the global priority order determines the regs. Need order a,b,c,d,e by priority.

Currently priorities: a 5000 (refs 6, live 24), b 4615 (refs 6, live 26), e 3636 (refs 4, live 22), c 4285 (refs 3, live 7), d 3000 (refs 3, live 10).

If all five are globals: order by priority desc = a(5000), b(4615), c(4285), e(3636), d(3000) → a=s0, b=s1, c=s2, e=s3, d=s4. Need e and d swapped: e must have lower priority than d.

e: refs 4, live 22 → 3636. d: refs 3, live 10 → 3000.
To make d > e: d needs floor(log2(refs_d))*refs_d/live_d > 2*4/22.
- If d had refs 4: 2*4/live_d > 0.3636 → live_d < 22. d's live is 10 → pri = 2*4/10*1e4 = 8000 > 3636 ✓.
- So give d a 4th ref! E.g. use d twice more, or... hmm. Currently d's refs = 3: d=b+0x2F, 291B4(d), 291A0(d,...).

Hmm, and e's refs 4 → 3636. If e had refs 3 → 3*live... e live 22 → 3/22*1e4=1363 < d. Hmm.

Also b (refs 6, live 26 → 4615) vs c (refs 3, live 7 → 4285): b > c ✓. Good.
And a (5000) > b (4615) ✓.

So target order a,b,c,d,e requires: pri(a) > pri(b) > pri(c) > pri(d) > pri(e).

With: a=5000 (refs6/live24), b=4615 (refs6/live26), c=4285 (refs3/live7), d=3000 (refs3/live10), e=3636 (refs4/live22).

Need c > d: 4285 > 3000 ✓ (already). Need d > e: 3000 < 3636 ✗.

So I need to either raise d's priority above e's, or lower e's.

Raise d: give d more refs. d appears 3 times. If I restructure so d is used 4 times... but I can't add semantics. Hmm, "real C moves only" — I can restructure expressions.

Idea: instead of `d = b + 0x2F;` and using d twice, write d's uses inline: `func_800291B4(b + 0x2F)` and `func_800291A0(b + 0x2F, ...)`. Then d disappears as a variable! But the target needs `d` in s3 as a separate register (target has `addiu s3,s1,47` then `move a0,s3` — d materialized in s3). Hmm, if d is inlined, the addiu would compute into a0 directly: `addiu a0,s1,47`. The target has `addiu s3,s1,47; move a0,s3` — so d IS a separate variable in s3. So d must stay.

Alternatively lower e's priority: e refs 4, live 22. If e had refs 3 → 1363. Can I remove one ref of e? e is used: e = 291B4(d) & 0xFF; 291A0(c, e); e = 291DC(b); 291C8(a, (s16)e). 4 uses.

Hmm. Alternatively increase d's live length? No, that lowers priority.

Hmm, but hold on: maybe there's a much simpler route. Let me reconsider.

What if instead of making c,d globals, I keep them locals but make local-alloc choose s2,s3? The issue is local-alloc picks the first free local regs in its preference order. If s0,s1 were already used by *something else* (e.g., a and b as globals allocated before locals)...

In gcc 2.7's `allocate_numbers` (global.c), the order is: it processes GLOBAL allocnos first, then LOCAL ones? Let me check the gcc 2.7 source. Actually let me find gcc source on this machine — tools/bin/gcc-2.7.2-psx exists; maybe the source is around.

Let me look for gcc-2.7.2 source.

Actually, from the observed result: locals c,d got s0,s1 and globals a,b,e got s2,s3,s4. If globals were allocated first, they'd get s0,s1,s2. So either locals are allocated first, or the global allocation prefers regs not used by locals.

Hmm, in gcc 2.7 global.c `allocate_numbers`:
```c
  /* Allocate all the globals first ... */
```
Hmm. I recall gcc 2.7's global.c has a two-phase: first `global_alloc` allocates global regs, then `allocate_numbers` for locals? Actually there's `allocno_order` which sorts all allocnos (globals+locals) and then assigns.

In gcc 2.7, the function `allocate_numbers (reg, ...)` iterates over allocnos in a priority order; for each, it tries to find a reg. The ";; N regs to allocate: 74 75 78" line lists only globals. Then the order line for locals would be separate.

In gcc 2.7's global.c, there's:
```c
  /* Do global register allocation first.  */
  ...
  for (i = 0; i < n; i++) { ... allocate globals ... }
  /* Now allocate locals.  */
```
Hmm, but then globals would take s0,s1,s2.

Unless the local regs (allocated by local-alloc earlier) are marked as occupied. YES: local-alloc ran BEFORE global-alloc (in gcc 2.7 `rest_of_compilation`: `local_alloc ()` then `global_alloc ()`). local-alloc assigned c→s0, d→s1. Then global-alloc must avoid s0,s1 (they're taken by locals) → a→s2, b→s3, e→s4.

In the pinned original, local-alloc couldn't use s0/s1 (pinned to a,b) → c→s2, d→s3 → globals a,b (pinned) and e→s4.

So the target's natural equivalent: local-alloc should give c→s2, d→s3. That requires s0,s1 to be unavailable at local-alloc time. What makes local-alloc skip s0/s1? If a and b were ALSO locals (not globals) and got s0,s1 first! Then c,d get s2,s3.

So: if a and b are locals (not crossing calls), local-alloc would assign them... but a and b live across many calls, so they're globals.

Hmm. Alternatively: the ORDER of allocation within local-alloc. local-alloc allocates locals in some order; c and d are the only locals.

Hmm, so how can local-alloc avoid s0/s1?

Option: make c and d globals too, so that ALL FIVE are globals and global-alloc assigns them by priority. Then I need the priority order a,b,c,d,e. As computed, c(4285) > e(3636) > d(3000), giving a=s0,b=s1,c=s2,e=s3,d=s4. Need d>e.

Alternatively, adjust so that: c > d > e. 

d's refs: 3 → live 10 → 3000. e's refs 4 → live 22 → 3636.
Need floor(log2(r_d))*r_d/live_d > 2*4/22 = 0.3636.
With r_d=4: 2*4/live_d > 0.3636 → live_d < 22 → pri = 8/10*1e4 = 8000 ✓.
With r_d=3: 1*3/live_d > 0.3636 → live_d < 8.25 → live_d ≤ 8. Currently 10. If d's live dropped to 8 → 3/8*1e4 = 3750 > 3636 ✓ (barely).

Or lower e: e refs 3 → 1*3/22*1e4 = 1363. Need e to have 3 refs. Can I merge e's two uses? e is set twice: e = 291B4(d)&0xFF and e = 291DC(b). Two different values. The 4 refs: set1, use1 (291A0(c,e)), set2, use2 (291C8(a,(s16)e)). 

Hmm what if I use separate variables for the two e values? Then e1 and e2 each have 2 refs. But then there'd be an extra variable → extra register. Target has exactly 5 callee-saved used (s0-s4). Actually the target uses s0,s1,s2,s3,s4 — 5 regs. If I split e into e1,e2, there'd be 6 variables → 6 regs. Unless one of them is short-lived and in a caller-saved reg. e1 = 291B4(d)&0xFF is used in 291A0(c,e1) — crosses the call 291B4(c)... so it needs a callee-saved reg. Hmm, in the target e ($20=s4) holds both values (e is reused: `andi a1,v0,0xff` then later `move s4,v0`).

OK here's another thought: what if instead of restructuring, I change the *live length* of d by moving the assignment of d later or earlier? d's live is 10 currently. If I could make it ≤8, pri(d) = 3750 > 3636 = pri(e). 

d = b + 0x2F, used at 291B4(d) and 291A0(d, ...). The live range: from the assignment to the last use.

Alternatively, make e's live longer: e = 291B4(d)&0xFF is set early (before 291B4(c)) and used at 291A0(c,e). If e's first set were EARLIER (e.g., computed before d?), e's live would grow. But e depends on d which depends on b.

Hmm! What if I reorder so that `e = func_800291B4(d) & 0xFF;` comes right after `d = b + 0x2F;` — it already does.

What if e's live is longer because e is set even earlier? e = 291B4(d)&0xFF requires d. d = b+0x2F requires b. Hmm.

Alternatively: what if I make e's live longer by using the FIRST e value later? Not possible.

OK, let's think differently: what if the ordering a,b,c,d,e is achieved by priority with different refs:
- a: refs 6, live 24 → 5000
- b: refs 6, live 26 → 4615
- c: refs 3, live 7 → 4285
- d: refs 3, live 10 → 3000
- e: refs 4, live 22 → 3636

For order a,b,c,d,e I need pri(c) > pri(d) > pri(e) and pri(b) > pri(c).
pri(b)=4615 > pri(c)=4285 ✓ (barely!).
pri(c)=4285 > pri(d)=3000 ✓.
pri(d) needs > 3636.

d needs refs 4 (→8000) or live ≤ 8 (→3750).

d's refs: `d = b + 0x2F` (write=1), `291B4(d)` (read=2), `291A0(d, ...)` (read=3). To get 4 refs, I could write d's use twice more... but semantics.

Hmm! What about `d = b + 0x2F` written as `d = b; d += 0x2F;`? That adds a ref (read b, write d, read d, write d) → d gets 3 refs instead of 1. Let's see: currently `d = b + 0x2F` = 1 write of d. Splitting into `d = b; d += 0x2F;` gives d: write(1), read(2), write(3) → +2 refs → d refs = 5. But it also adds a live range.

Hmm, but careful: that changes the codegen: `addu d, b, 47` becomes `move d,b; addu d,d,47` → 2 instructions instead of 1! The target has `addiu s3,s1,47` (one instruction). So no.

Alternatively `d = b + 0x2F` → keep, but read d more: e.g. `e = func_800291B4(d) & 0xFF;` and `func_800291A0(d, ...)`. That's 2 reads. Plus the write = 3.

Could I write `func_800291A0(d, ...)` as `func_800291A0(d, d & 0xFF)`? No, changes semantics.

Hmm, what about d's live length: currently 10. d is set at `addu s1,s3,47` (mine: d=$17) and last used at `move $4,$17` before 291A0(d, ...). Live length in insns: from insn X to insn Y.

Hmm, what if I move the statement `d = b + 0x2F;` LATER (closer to its uses) — that shortens d's live range (good for priority: live smaller → pri higher). But d is needed by `e = func_800291B4(d) & 0xFF` which is the first call. Hmm, the first call is 291B4(d), so d must be set before it.

Alternatively, move `d = b + 0x2F` EARLIER? d = b + 0x2F could be computed before `b = (s16)param_1`? No.

Hmm, what about moving the FIRST call `e = func_800291B4(d) & 0xFF;` later? It's already before.

OK, alternative approach: lower e's priority by increasing e's live length. e's live currently 22. If e's live were 24+, pri(e) = 2*4/24*1e4 = 3333 < pri(d)=3000? No, 3333 > 3000. Need live_e > 26.67 → pri(e) < 3000. e's live 22 → need 27+. That's a long extension.

Alternatively make e have 5 refs → floor(log2 5)=2 → 2*5/live*1e4. With live 22 → 4545 > 4285(c). Hmm worse.

Make e have 8+ refs → floor(log2 8)=3 → 3*8/live. Worse.

Make e have 3 refs → 1*3/live*1e4 = 1363 with live 22 ✓ (need e to lose a ref).

e's 4 refs: two sets and two uses. Could I make one use not reference e? e.g. `func_800291C8(a, (s16)e)` — the (s16)e cast creates a copy... 

Hmm what about this: `func_800291A0(c, e)` — e used. `func_800291C8(a, (s16)e)` — e used.

What if I restructure to reuse: since the second e value is `(s16)func_800291DC(a)` in the other call... 

Wait, let me re-read the source:
```c
e = func_800291B4(d) & 0xFF;      // e1
...
func_800291A0(c, e);               // use e1
b = b * 2 + 0x14;
e = func_800291DC(b);              // e2
a = a * 2 + 0x14;
func_800291C8(b, (s16)func_800291DC(a));
func_800291C8(a, (s16)e);          // use e2
```

Hmm, so `e` is used with two different values → 4 refs.

OK. Let me step back and consider: maybe there's a completely different lever. What if a and b are NOT globals in the target? In the target (pinned), a→$16 and b→$17 are pinned hard regs. c→$18, d→$19, e→$20. That's just "the next three callee-saved regs after the pinned ones", which is what local-alloc would give... no wait, e is a global (crosses calls) so it got $20.

Hmm, in the pinned version: a,b pinned to $16,$17. local-alloc assigns c,d: c→$18, d→$19. global-alloc assigns e→$20.

In my candidate: local-alloc assigns c→$16, d→$17. global-alloc: a→$18, b→$19, e→$20.

Interesting: so local-alloc picks the first free callee-saved regs. In the target, $16/$17 are taken by the pins so c,d get $18,$19.

So the natural (unpinned) equivalent would be: local-alloc gives c,d the first free callee-saved regs ($16,$17) unless those are taken. So for c→$18, d→$19, a→$16, b→$17, e→$20, we need a and b to be allocated BEFORE c and d, i.e., a and b must be globals allocated before locals? But globals are allocated after local-alloc... 

Hmm, unless local-alloc's allocation ORDER within the locals matters: local-alloc allocates locals in order of their live range/priority. If a and b were locals too... but they cross calls.

Hmm, wait. What if a and b DON'T cross calls in gcc's view, i.e. if I restructure so that a and b are computed later (shorter live ranges)?

Look at the target asm again:
```
sw s1,20(sp)        <- save s1 (b)
sll s1,a0,0x10
sra s1,s1,0x10      <- b = (s16)param_1  (b in s1, from a0)
addiu s3,s1,47      <- d = b + 0x2F
move a0,s3
jal 291B4
andi a1,v0,0xff
move a0,s2          <- c in s2
jal 291B4
move a1,s4          <- e in s4
sll s1,s1,0x1
addiu s1,s1,20      <- b*2+0x14
jal 291DC
move a0,s1
move s4,v0          <- e = 291DC(b)
sll s0,s0,0x1       <- a*2+0x14 (a in s0, raw param_2 since entry)
addiu s0,s0,20
jal 291DC
move a0,s0
move a0,s2
move a0,s3
```
So in the target, `a` = param_2 is held in $16 from the function entry (never copied) — a is the raw parameter, and the `a = (s16)a` happens later.

In my candidate:
```
move $16,$5     <- a = param_2 (a in s2=$18)
sll $4,$4,16
sra $19,$4,16   <- b = (s16)param_1 (b in s3=$19)
```
So mine copies param_2 to a callee-saved reg early.

The target keeps param_2 in $16 directly (the callee-saved reg), i.e. gcc coalesced the parameter a1 with $16. In mine, `move $16,$5` copies it.

Hmm! That's a difference in how gcc handles the parameter: in the target, the parameter pseudo for param_2 was allocated $16 directly (a1 → $16 with a move at entry). Actually the target has no `move $16,$5` — hmm, but then param_2 comes in a1 and must be moved to $16 somewhere. Unless... 

Hold on, target insn 3 = `sw s1,20(sp)`, 4 = `sll s1,a0,0x10`. Where's the move of a1→s0? It must be before insn 3, i.e. in the prologue region (insns 0-2). Let me reconstruct the target prologue: probably:
```
addiu sp,-0x20
sw ra,0x1c(sp)
sw s0,0x10(sp)     <- insn 2?
move s0,a1         <- hmm
```
Actually the diff showed "replace mine[3:4] target[3:6]" with target[3]=sw s1,20(sp). So target[0..2] = 3 instructions before that. Those would be: addiu sp,-0x20; sw ra,0x1c(sp); sw s0,0x10(sp)? That's 3, but then where's the move a1→s0?

Hmm, maybe the target's `a` (param_2) is NOT in s0 initially. Let me re-read: target has `sll s0,s0,0x1` near the end — so s0 = a*2. And `sll s0,s0,0x10; sra s0,s0,0x10` at mine[15:17]/target[15:17] = the (s16)a cast.

So s0 holds a throughout. It must be set from a1 at entry. In the target's first 3 instructions: addiu sp, sw ra, sw s0 → then where's `move s0,a1`? Maybe the target's prologue is:
```
0: addiu sp,-0x20
1: sw ra,0x1c(sp)
2: sw s0,0x10(sp)
3: sw s1,20(sp)
4: sll s1,a0,0x10
```
Hmm, but `move s0,a1` is missing. Unless gcc put the move in the delay slot of something. Hmm, there are no branches before.

Wait, maybe the function's params are (param_1, param_2) = (a0, a1) and the target moves a1→s0 somewhere. Let me count target instructions: total 51. Let me get the full target disassembly properly rather than reconstructing from a diff.

Let me add a "tgt" mode to my sweep.py to dump the target function's instructions from the baseline object.

Actually, tools/asm_verbatim.py or tools/objdump... Let me check what's available: tools/asm-differ, tools/asm_verbatim.py. Also md.insns_from_object is in some module `md`. Let me find it.

Let me write a small helper using delever_search's imports to print the target insns.

In sweep.py I can do:
```python
import delever_search as ds
md = ds.md
recs = ds.recs_for(tu, by_src, inc)
base = ds.oracle.baseline_path(recs[0]["obj"])
insns = md.insns_from_object(str(base), fn)
for i in insns: print(i)
```
Let me check what insns_from_object returns (strings?).

Let me add that mode.
