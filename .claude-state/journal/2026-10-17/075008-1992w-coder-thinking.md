---
ts: 2026-10-17T13:50:08.009Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm thinking that rematerialization typically kicks in under register pressure or when a spill register is held, but here s0 is free, so that path wouldn't trigger naturally. I'm wondering whether the pseudo avoids getting a register at all, and considering how REG_EQUIV constants crossing a call interact with local-alloc's update_equiv_regs logic and REG_EQUAL notes.

Looking at the allocation priority formula in global.c, I'm checking whether r177, set once from a constant source, would qualify for REG_EQUIV treatment, and tracing how its priority computation (based on refs, live length, and size) determines whether it keeps a hard register through reload. The key question is whether s0 just happens to be free in this function when r177 is allocated, versus other functions where s0 might already be occupied, which would explain the difference in behavior.

Target holds r=0x30 in s0 across a call between two multiplications, so I need to figure out why the address pseudo would conflict with s0 in that case but not in the current build -- possibly something else is kept live across those calls in the target, or local-alloc's update_equiv_regs treats the cheap constant pseudo differently when deciding whether to actually allocate a hard register for it.

I'm also wondering if the original code passed the address as a pointer argument in a way CSE couldn't prove equivalent between the two calls, maybe through a different static reference, or if expand_call's handling of constant arguments in gcc 2.7's calls.c treats this case specially when the argument register is already assigned.

I notice the generated rtl shows a symbolic value loaded into one register then moved to the hard argument register—possibly the mips movsi expander forcing symbolic constants through a pseudo before the hard register. I should check whether the specific function at that address actually takes any arguments, or whether its assembly reveals the pattern needed to confirm rematerialization is happening there.

Thinking about pressure: I can't add new code, so I need to figure out how to prevent CSE from merging the two address pseudos without modifying anything. If I reassign the register holding the symbolic address between the two calls, CSE might treat the second set as redundant since it holds the same value already—so that approach doesn't break the live range either. I need a different value in between to force a real redefinition.

I'm running low on time for this section, so I should decide quickly whether to pursue the legitimate route of splitting the two calls into separate statements rather than fighting CSE directly.

Checking whether CSE's basic-block length limit could explain the behavior, but that doesn't seem to fit either. I'm now wondering if a CALL_INSN with a constant call pattern might be the relevant mechanism.

I try redeclaring D_800AF648 as an extern struct and passing a member address instead, hoping CSE treats it as equal, but that doesn't pan out. Making the register bare or volatile also fails to produce the right instruction sequence, since volatile forces a stack load that doesn't match the expected bytes. I'm starting to suspect the real explanation involves a missing parameter pin on registers $4-$7, though it's still unclear.

I try array-decay declarations and macros wrapping both calls with a shared pointer variable, but each attempt collapses to the same CSE outcome. I'm accepting this as a wall for pin4 — the best score achievable while that pin is present is zero, so it's not a lever-free solution.
