---
ts: 2026-11-06T09:54:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t6HKERzGEothw9mDCWh1
---
Baseline is score 0. But the body contains a pin and keepalive; the kinds are keepalive,pin. I need a lever-free body that scores 0.

The pin is `register s32 rv __asm__("$2")` — that's a register-asm pin. The keepalive is `__asm__("" :: "r"(rv))`.

Lever-free = none of the row kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind.

So I need real C to get rv into $2 and keep it alive (i.e. the value must be returned). Since the function is declared void, the target probably has `jr ra` after computing v0. Hmm.

Options: make the function return s32? No signature change allowed ("no signature or decl change outside the body (callers stay as they are)"). Signature change is off-limits. But moves.md line 10: `launder | func_80186874 | WALL flow-unused-result — flow: void fn computes rv=1/0 into v0 never used; flow deletes both sets; only s32 return keeps it (sig change)`.

Line 28: `keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)`.

Hmm — but here the function is declared void in src. Actually wait, can we change the return type in the body? The definition line `void func_8017F1F0(...)` — is that "outside the body"? The body is lines between braces. The brief says "no signature or decl change outside the body (callers stay as they are)". The declaration is on the line with the function name — arguably the signature. Changing void to s32 would be a signature change. Not allowed.

But maybe target actually computes v0 because the function's return value is used by callers? Callers are `extern void func_8017F1F0(...)` and call it as a statement. Hmm.

Let's look at what the target assembly is. Let me check the diff tail with more lines and inspect the actual target instructions. Let me run dt.sh with larger tail to see diff, and use hdump/objdump maybe.

Actually delever_search compares mine vs target. If I remove pin and keepalive, what does the score become? Let's just try: write win.c as a plain version with a local s32 rv and no asm. But flow may delete unused stores since void function. Actually the stores are to local variable rv which is never used → dead code elimination. The pin makes rv a hard register so it's "used"? Actually with register asm, flow keeps? And keepalive marks it used.

The target: probably the function does compute v0 values and return them. Let's check the actual target object disassembly. Is there a target binary in the item dir? The tu file points to src file. delever_search compares with the function in build/. Let me look at delever_search.py usage/help.
