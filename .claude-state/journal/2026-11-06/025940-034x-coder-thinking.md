---
ts: 2026-11-06T09:59:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_918er9u8wxrIqsEHqweX
---
136 includers each. So MATCH requires score 0 on every includer (136 each!). That's a lot of compiles, but the helper handles one includer at a time; and `dt.sh` with a header TU probably tests all includers? Let me check: dt.sh calls delever_search --try with tu=header. In _score_file, `recs = recs_for(tu, ...)` and `rec = recs[0]` — only the FIRST includer! So dt.sh only tests includer 0 for a header. Hmm. But the brief says "header item (src/shared/ov/*.h): MATCH only if score 0 on every includer (tryinc.py k = 0..n-1)".

So I need to test all 136 includers with tryinc.py. That's 136 compiles per candidate — slow (~35ms each? plus overhead maybe 0.5s each → ~1 min). Manageable but not for many candidates.

Hmm, wait. Actually the dedup.us.yaml says "ONE source: instantiated by #include at each member's site". The h_exact hash suggests all includers must match. But maybe the score is the same for all includers if the function is identical... not necessarily (register allocation depends on surrounding code? No — each function compiles independently; but the TU's other functions could affect? No, codegen per function is independent). Actually the score for the same function body should be identical across includers unless something differs (e.g., macros/inline). Hmm, but the whole-object comparison differs. Wait, the score is about the *function's instructions*, which should be the same. But "score 0" for --try is based on the function's instruction comparison. So likely one includer suffices to know the score... but the brief insists on all.

Hmm, but actually the reason to check all includers: the header is textually included, and the function's codegen could differ if the includer's context differs (e.g., different definitions of macros, different types). Let's just test all at the end for the winner.

Let me start with item 2. Remove the pin and keepalive.

Let me write win.c for item 2.

Actually, let me first test a few quick candidates on includer 0 with dt.sh, then verify the winner on all 136.

Item 2 body (lever-free attempt):
```c
extern s32 ratan2(s32 a0, s32 a1);
s32 func_8012BA10(s32 arg0, s32 arg1) {
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    s32 d;
    s32 s1ang;
    s32 u5; s32 u6; s32 iVar4; s32 q; s32 t;
    d = arg1;
    s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    u5 = (ratan2(...) - 0x400) & 0xFFF;
    d = (s16)d;
    ...
}
```
Note the body file: does it include the `extern s32 ratan2` line? The definition span probably starts at the function definition line, not the extern above. Let me check: `s32 func_8012BA10(...)` is the def. The `extern s32 ratan2` is a separate declaration (outside the def span). So the body file should start at the function definition. But including the extern line is harmless? It would be inserted at the definition's position; the original extern line remains. Duplicate extern is fine. But body_span starts at the def line, so my file's content replaces from there; if I include the extern in my file it's duplicated (harmless). Better to match the span: just the function definition.

Hmm, but careful: the scratch replaces raw[ls[line-1] : ls[end]]. So whatever I put replaces the def. Let me include just the def.

Let me create item 2 win.c.

Actually first, let me see the residual of the lever-free version via --explain for each header. --explain takes TU FN; for a header it uses recs[0]. Let me run --explain on item 2.
