---
ts: 2026-10-22T01:03:01.437Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 8bd904fe-fbea-4565-a883-e61d65fe8209
usage: {input: 6, cacheRead: 340347, cacheWrite: 3029, output: 1434}
---

It's the third: cracking to remove register pins and inline asm. It isn't about structs, and it isn't for fun. One update first: the cookbook task T21 finished at 17:33. It added four new cookbook entries (C0530 to C0533) and either filed or ruled out the rest. T11 then picked up again with MiniMax.

**Why there are pins at all.** To reach 100% matched, every function had to compile to exactly the same bytes as the retail game. When plain C wouldn't quite produce those bytes, agents used "levers", which force the compiler's hand:
- **Register pins:** `register int x asm("$16")` tells the compiler which CPU register a variable must live in.
- **Inline asm:** raw machine instructions written straight into the C.
- **Compiler barriers:** tricks that stop the compiler from moving or merging code.

They work, but they're tech debt. A human reader sees assembly tricks instead of C, and the code only builds the same way on this exact compiler. The original programmers at Square wrote plain C. So for nearly every pinned function, some plain-C spelling exists that the compiler turns into the same bytes. It just wasn't found yet.

**What "cracking" means here.** Taking a function that already matches with levers and finding a lever-free C version that still compiles to identical bytes. Coders try different spellings: a different variable type, a different statement order, a variable reused instead of a new one. Each try is compiled and compared byte for byte until one matches with no levers. Today's feed shows one: G07's coder cracked `func_8003DF8C` by declaring two loop counters as `u16` instead of `int`. That changed how the compiler handled their copies, and the pin was no longer needed.

**Why "singleton".** Earlier tasks cleared the cheap cases:
- **T7** turned many pins into missing function parameters, which they really were.
- **T8** removed the levers that turned out not to be needed at all.
- **T9** cracked the 38 "head classes": groups where the same lever appears in many functions, so cracking one example fixed every copy.

What's left are singletons: functions whose lever appears nowhere else, about 400 of them. No fix carries over from another function, so each one has to be cracked by itself. That's why T11 is a "wave" of many coders working through batches of 8 to 10 functions.

**Why it matters.** The goal of this generation of phases is legible source: plain C with real types and names, not just matching bytes. The milestone you set for this phase is that every lever is either removed or has a recorded reason, the specific compiler behaviour that plain C can't reproduce (its "wall"). So every cracked function becomes clean C, and every function that won't crack gets its wall written down instead of staying a mystery. The struct work you're thinking of is separate. That was T2 to T5, and T17 comes later.

The queue was held while we talked, and I'm releasing it now.
