---
ts: 2026-11-06T09:07:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zbLp1Z4szm2VDLmwaRuI
---
~130 includers each. Testing all includers for every candidate is expensive. tryinc.py k tests one includer at a time. Hmm, but MATCH for header = score 0 on every includer. The body is identical across includers presumably; the differences come from the TU context (other functions/constants). Typically a body scoring 0 in one includer scores 0 in most; but must verify all.

Let me check how many includers exactly: count items in that binaries list. Let me just run tryinc.py 0 and see what it prints (it prints k/len).

First approach note. Let me write it now.

The plan: For each header, remove the keepalive asm and find real-C spelling that keeps the target allocation. Item 1: keepalive forces `pm` (param_2 & 0xffff) into $3. Item 2: three keepalives: bVar1 at line 47, iVar7/t at 58, fc at 64. Item 3: s0 at line 27.

Let me start with item 1. Copy orig.c, nopin? The brief mentions nopin.c in FRESH. Let's copy orig.c from src (body only, as delever_search --body expects a body definition?). Let me check what --body expects: "write a lever-free body of func in G25x/<dir>/win.c (bare definition)". So win.c is a bare function definition.

Let me copy the def from header into orig.c. Then make a first candidate win.c = orig minus keepalive.

Actually, let me look at an existing worked example for a header item to see the format.
