---
ts: 2026-11-06T09:55:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BpxprvmkxqkKAUQ9krWd
---
Interesting! Only one instruction difference: target has `move v0,s0` at position 46 that mine lacks. And the score is COUNT (not a diff of content). So the target has one extra `move v0,s0` at 46.

Hmm. That `move v0,s0` is the keepalive effect presumably: rv = (s32)a0 where a0 is in s0; keepalive keeps rv live → `move v0,s0`. Wait but the pin made rv=$2=v0. So the keepalive forced a `move v0,s0` (rv = (s32)a0, rv in $2). Without the pin, `rv = (s32)a0;` would be a copy to a pseudo which is dead → deleted. And with pin it's `move v0,s0`.

But wait — the original with pin+keepalive scored 0. Without the pin, if I keep the keepalive... no, keepalive is a lever, forbidden.

So I need real C that produces `move v0,s0` at instruction 46. Interesting: `move v0,s0` — moving a0 (in s0) to v0 (return register). The function returns void. Hmm, why would target have a move to v0? Maybe the original C actually returned something, or had a value used.

Actually wait: this is a jr_ function in ov_SC06_014 — it's a "jr" (jump-related) override. The target may have `move v0,s0` because the original code did something like `return a0;`? But signature is void per src. Hmm, but the signature in src is our declaration; the target asm is the truth.

Actually hold on: the note in orig says the pin $2 was "NEEDED DIFFERS (P36 rung B t8_tus2)". So the pin + keepalive were added to make this exact instruction.

Let's think: `move v0,s0` where s0 = a0. In the original source maybe the function returns a0 (a pointer). But our signature is void and callers ignore. The delever tool compares the whole function object. If we change return type, that's a signature change — forbidden ("no signature or decl change outside the body"). Hmm, but the brief says "no signature or decl change outside the body (callers stay as they are)". So we can't change the return type.

So we need a `move v0,s0` in the body via real C. A `move v0,s0` is generated when a value is assigned to a variable that lands in v0 and the source is in s0. Since v0 is caller-saved and a0 is in s0 (saved), the compiler would need a reason.

Wait — but which instruction is 46? Let me look at the actual assembly of the target. Let me dump the target function. There's probably a way: the bank. Let me check delever_search for how to dump, or use hdump.sh. Actually the diff shows target[46:47] = move v0,s0. Let me get more context — maybe use the tool with a bigger tail or check if there's a dump option.

Actually maybe simplest: look at the function's assembly. Since the function is in build/, I could objdump. But the brief says use tools. Let me check if there's a way via delever_search.py. Let me look at its --help.

Actually, let's reason: the orig scored 0 with pin+keepalive. The pin makes rv = $2 = v0. `rv = (s32)a0;` then asm uses rv → `move v0,s0`. Without pin, `s32 rv; rv=(s32)a0;` dead → removed.

What real C gives `move v0,s0` at the end? Perhaps the source had:
```c
a0 = ...? 
```
Hmm.

Alternatively: maybe the real C returns a0 through a void function's implicit... no.

Wait: maybe `move v0,s0` isn't at the end. Instruction 46 out of 52. Let me find the target listing. The delever tool probably can output the target disassembly. Let me check its help.
