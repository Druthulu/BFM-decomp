/* guess_CallActorEventHandler — shared body (overlay slot 0x80128158, h_exact 2c9ae3cd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_CallActorEventHandler: looks the id in a1 up in the object's id table (+0xBC) and calls the handler found with the object; returns 1 if one ran
 * Confidence medium, xref chain: K&R: calls guess_LookupIdValue(*(a0 + 0xBC)) with its own a1 left in place, then fp(a0); guess_HandleActorEventDefault passes 0x11
 * Names ledger: config/names.tsv guess_CallActorEventHandler */
s32 guess_CallActorEventHandler(a0)
    int a0;
{
    s32 (*fp)(int) = (s32 (*)(int))guess_LookupIdValue(*(s32 *)((u8 *)a0 + 0xBC));
    if (fp != 0) {
        fp(a0);
        return 1;
    }
    return 0;
}
