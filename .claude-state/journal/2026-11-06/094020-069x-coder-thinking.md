---
ts: 2026-11-06T16:40:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Sb6u3l36QtqVRUuCZCNB
---
The template has doubled braces `{{` for the if blocks, but also `((Unkstruct...))` has single braces? No, those are parens. The issue: `{self}` fine, but `{{` inside... The error "unexpected '{' in field name" — maybe due to `}}` handling. Let me use a different approach: use placeholders like @DECL@, @INIT@, @SELF@ and str.replace.
