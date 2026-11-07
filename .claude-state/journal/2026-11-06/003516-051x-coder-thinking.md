---
ts: 2026-11-06T07:35:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qP7AvzqP5lMbYC198htc
---
Still "too many arguments". So even with `extern void func_800CAF84();` the compiler rejects 1 arg. That means GCC 2.7 in this project's flags treats `()` as `(void)`? That would be C++-ish. Or the compile flags include `-Wstrict-prototypes`? No, it's an error.

Wait, maybe the issue is the K&R definition at line 88: `void func_800CAF84(arg0) void *arg0; {`. In GCC 2.7, the function's type after a K&R definition with a parameter list is a *prototype* with one arg of type void*. Then `extern void func_800CAF84();` (unprototyped) is compatible. Calling with an s32 arg is compatible (no prototype → default promotions). So should be fine.

Unless the `--try --body` scratch TU puts the body at a place where a `(void)` prototype from a *later* declaration applies? In C, a declaration later in the file doesn't affect earlier code.

Hmm, "too many arguments" at line 266 — let me actually inspect the scratch TU. I can force a compile failure and the scratch is restored, but maybe with `--keep` the TU stays? Let me check: oracle.compile_obj writes to write_path (the real TU) then delever_search restores it in `finally`. So no.

Alternative: I can copy the TU to my shard, insert my body manually, and compile it with the project's compiler? That's complex.

Let me reconsider: maybe the tool's --body mode *keeps* the original local extern declaration because it extracts the body from the file by line range? No — it says FILE holds the function's definition only, and it replaces the definition.

Wait, maybe the error line 266 is not the call but the `extern` line in the *scratch*: if the scratch TU has the ORIGINAL `extern void func_800CAF84(void);` at line 253 AND my body at 254+... no.

Let me look at how --try --body splices. Search delever_search for "--body".
