#include "common.h"

extern void _SsSeqPlay(s16 seq_no, s16 play_mode);

void _SsSndPlay(s16 vabid, s16 prog) {
    _SsSeqPlay(vabid, prog);
}
