/* -*- mode: C; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: expandtab:ts=8:sw=4:softtabstop=4:
#include "test.h"

int main(void) {
    int r;
    toku_lock_tree* lt  = NULL;
    toku_ltm*       mgr = NULL;
    uint32_t max_locks = 1000;
    uint64_t max_lock_memory = max_locks*64;

    r = toku_ltm_create(&mgr, max_locks, max_lock_memory, dbpanic);
    CKERR(r);
    r = toku_ltm_open(mgr);
    CKERR(r);
    
    {
        r = toku_lt_create(&lt, mgr, dbcmp);
        CKERR(r);
        assert(lt);
        r = toku_lt_close(lt);
        CKERR(r);
        lt = NULL;
    }

    r = toku_ltm_close(mgr);
    CKERR(r);
    mgr = NULL;

    return 0;
}
