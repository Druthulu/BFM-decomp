---
ts: 2026-11-06T03:51:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BgCfuINgo5q3dLTjAa37
---
Score 0! Both. Wait, "score 0 (OTHER)" — score 0 = MATCH. Let me confirm with dt.sh which prints the full result.

c6 and c7 both score 0. Great. But is do-while a lever? The brief allows `do{}while(0)` only with `// !FAKE: do-while` annotation. It's a real C construct and allowed. However — the do-while here is around a statement that doesn't change value; is it a "fake" control flow? The brief explicitly permits it with annotation. And C0535 says do-while splits cse1 EBB, a legitimate technique. So it counts.

But wait: does a `do{}while(0)` count as "no new lever of any kind"? The constraints say "`do{}while(0)` only with `// !FAKE: do-while`", so it's allowed. Good.

c7 is simpler (wraps only the zero store). Let me verify c7 with dt.sh and check the diff is clean.

Actually both score 0. Let me pick c7 (minimal). But consider: does c7 leave the zero store inside a do-while that also alters something else? Let me verify score 0 with dt.sh output.

Then, check that c7 has no barrier/launder/pin. It has none. 

Let me confirm and then write win.c = c7. Also I should double-check the body compiles as a full TU replacement — dt.sh already did that.

Let me run dt.sh c7.
