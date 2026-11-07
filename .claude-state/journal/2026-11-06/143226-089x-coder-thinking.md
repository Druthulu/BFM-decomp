---
ts: 2026-11-06T21:32:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_d9t6GKDLAixT5XxQEraS
---
v18 also scores 0! v18 wraps the then-block in `do { ... } while (0)` (with the keepalive dropped). Interesting — the do-while(0) splits the block (C0535) and changes scheduling.

But wait: the constraint says `do{}while(0)` only with `// !FAKE: do-while`. Hmm, "no `do{}while(0)` only with `// !FAKE: do-while`" — the constraint reads: "no `register` vars, no `__asm__`; `do{}while(0)` only with `// !FAKE: do-while`". So a do-while(0) is allowed if annotated with `// !FAKE: do-while`. Hmm, but that annotation marks it as a fake/lever... The brief's MOVES+ mentions C0535 (do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item) as a valid move.

Anyway, v03 is cleaner (no do-while): it hoists `a = arg0` before the inner if. v03 uses the pin ($4), which is allowed (not a row kind). v03 has no keepalive and no asm beyond the pin.

Wait — v03 still contains `register void *a __asm__("$4")` — a pin. The kinds row is "keepalive", so the pin may stay. But the "Lever-free = ... no pin" phrase... The CONSTRAINTS section is explicit: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". The pin was already in the def (orig.c), so it may stay. MATCH = keepalive gone. v03 satisfies that.

Hmm, but is the pin really "another kind"? The item's kinds row says "keepalive" only, so yes.

But wait — there's a subtlety: is the pin `$4` maybe considered part of the keepalive lever? No, the kinds file says keepalive.

Now, which is better: v03 or v18? v03 keeps the pin; v18 also keeps the pin (v18 is BASE with the do-while). Both score 0 on includer 0.

Let me also check whether a variant without the pin scores 0 (cleaner): v02 (no pin, no a) = 3. What about a no-pin variant with `a` hoisted (like v03 but `void *a`)? That was w5 = 3. So the pin is needed.

Hmm, actually let me try v03 without the pin: `void *a; ... a = arg0;` before the if. Not generated. Let me test it: it would probably score 3 (the move coalesces). The pin is load-bearing for the copy to exist at all (a0).

So v03 is the win: pin kept (allowed), keepalive gone (the row kind).

Wait, but the task says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

Hmm, this sentence lists "no pin" as part of lever-free. But then the kinds row for this item is "keepalive" and the CONSTRAINTS say "levers of other kinds the def already had (pins under other causes) may stay". There's a tension. The PARTIAL definition says "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". If win.c keeps a pin and scores 0, and the row kind is keepalive, then the result would be MATCH (the row kind is gone) — with an extra note that the pin (a non-row lever) stays.

Hmm, but the brief also says: "a win.c that keeps all row kinds is a WALL, whatever it scores". The row kinds = {keepalive}. v03 keeps no row kind → MATCH.

I'm fairly confident: MATCH with the pin retained. Let me also double check by looking at what other items in this shard did... e.g., moves.md line 47 "pin | func_8017FBCC | WALL combine-copy-merge — ... only v0+$0 keeps it". And line 288: "keepalive | func_80180054..." etc.

Also line 290 in moves.md: "keepalive | func_801896EC | MATCH: fold ..." etc.

Hmm, but there's a risk the expert considers the pin a lever that should be removed too. The item's kinds row is authoritative: "keepalive". The brief's INTERFACES: "result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". And CONSTRAINTS: "MATCH = the kinds in <dir>/kinds gone".

v03: kinds gone (keepalive gone), scores 0 on includer 0. Need all includers.

Let me wait for the all-inc check. Meanwhile, let me prepare the notes and think about whether v03's win.c should be the final.

Let me look at v03's assembly to confirm it matches the target exactly.

Let me run dt on v03 with more output (via tryinc, but I want the asm). Let me use the dump approach? Simpler: the score 0 means byte-identical, so no need.

Let me check the background job's progress.
