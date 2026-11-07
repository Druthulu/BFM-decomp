---
ts: 2026-11-06T21:23:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HgtIVzQT0Y18JXRn3U9d
---
Line 191 is a great lead: "the 12 launders on v -> six 'v = (s16)v;' real 2nd sets (v is a sign-extended s16, so the cast is a no-op); six sets buy the same ref count the 12 empty asms did".

And line 198: "DEAD-RESET CSE-BREAKER (§373): pb=&buf; call(pb); pb=0; before every site; cse's &buf address class breaks, so all 6 sites rematerialise addiu aN,sp,56 and no callee-saved reg parks the address".

So for the `ap` launder (ap = buf, force rematerialization), the crack is a dead-reset: `ap = buf; ...; ap = 0;`. Wait, but here the target does NOT rematerialize ap (target uses addiu sp,16 inline). Hmm, actually the dead-reset breaks the cse class so the address rematerializes per site. That's what target does (addiu a0,sp,16 per call). So for ap, use a dead-reset after each use!

But the tp launder is the opposite: target KEEPS tp in a register (s0), and the launder forces that. So the tp launder needs a real 2nd set to keep it in a reg, not a dead-reset.

Wait, let me re-read: the launder on tp: `tp = D_801274F0; asm(tp);`. Without it, tp rematerializes (mine). Target keeps it in s0. So the launder makes tp non-rematerializable. To crack: make tp's value non-constant or raise its refs.

For a constant symbol address, moves line 235/185/334 show WALLs (cse-const-addr, reload-rematerialise) — these are the known hard cases where the target keeps a const address in a reg. But line 24 shows a MATCH pattern? No, line 24 is a WALL.

Hmm. So the tp launder (keep const symbol ptr in reg) is a known WALL class: cse-const-addr / reload-rematerialise / greg-const-ptr-priority.

But wait — maybe the crack is a dead-reset that makes it rematerialize consistently? No, target keeps it in a reg, so rematerialization is wrong.

Actually, let me reconsider. Maybe the target keeps tp in s0 because of the *pin* on base ($18) shifting register allocation, and the tp launder. With both levers, the allocation gives tp s0. Without, tp rematerializes.

Is there a real-C way to force tp into a callee-saved reg? If tp has enough refs and isn't rematerializable. The 2nd set raises refs.

The move "v = (s16)v;" real 2nd set: for tp, `tp = (s32)tp;`? That's an identity cast (s32 to s32), no-op — but does it create a 2nd set? A cast to the same type is a no-op expression; the compiler might drop it. `(s32)tp` where tp is s32 → same type, no conversion, likely dropped.

What if tp is declared as `u32 tp` and we do `tp = (u32)tp;`? Same type, dropped.

What if tp is `s32` and we do `tp = (s32)(u32)tp;`? Same width, no-op.

Hmm. The v cast worked because v was sign-extended s16 and `(s16)v` truncates (a real subreg operation that combine may keep as a no-op but counts as a set). For tp (s32), a cast to s16 would truncate the address (wrong value).

What about `tp = (s32)(s16)tp;`? Truncates — wrong.

Hmm. What if tp is a pointer and we cast: `tp = (s32)(u8 *)tp;`? pointer to s32, no-op.

Let me think about the C0414 dead-reset for tp: `tp = 0;` after each use. This would break the cse class and force rematerialization — the opposite of what we want (target keeps it).

Wait, actually, maybe I'm misreading the target. Let me re-examine: target `lh a0,-8(s0)`. Is s0 really tp? Let me check the target.s to see where s0 is set. Let me look at target.s around the epilogue.

Actually, maybe s0 is NOT tp but `buf` or something, and target's tp is rematerialized differently. Let me read target.s.

Hmm, this is getting long. Let me reconsider the budget: item 3 is complex (2 levers). I've spent ~15 min. Let me look at target.s to confirm the s0 identity, then decide.

Actually, let me reconsider the whole thing: the p_only (pin removed, launders kept) = 206 ins, score 23 (REG-callee). So with launders, count is right. The pin removal only shifts callee-saved regs. If I could crack the pin with real C AND replace the launders with real 2nd sets...

For the tp launder: the target keeps tp in s0. But maybe with the pin removed, the allocation changes. Let me check p_only's diff: it's score 23 REG-callee with 206 ins. Let me see which regs.

Let me read p_only diff.
