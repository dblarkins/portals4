#include "config.h"

#include "ppe.h"

int
ni_init_impl( ptl_ppe_t *ctx, ptl_cqe_niinit_t *cmd )
{
    int ret;
    ptl_cqe_t *send_entry;
    ret = ptl_cq_entry_alloc(ctx->cq_h, &send_entry);
    if (ret < 0) {
        perror("ptl_cq_entry_alloc");
        return -1;
    }   
                
    send_entry->base.type = PTLACK;
    send_entry->ack.retval_ptr = cmd->retval_ptr;
    send_entry->ack.retval = PTL_OK;
                
    ret = ptl_cq_entry_send(ctx->cq_h, cmd->ni_handle.s.code,
                                       send_entry, sizeof(ptl_cqe_t));
    if (ret < 0) {          
        perror("ptl_cq_entry_send");
        return -1;
    }
    return 0;
}

int 
ni_fini_impl( ptl_ppe_t *ctx, ptl_cqe_nifini_t *cmd )
{
    int ret;
    ptl_cqe_t *send_entry;
    ret = ptl_cq_entry_alloc(ctx->cq_h, &send_entry);
    if (ret < 0) {
        perror("ptl_cq_entry_alloc");
        return -1;
    }

    send_entry->base.type = PTLACK;
    send_entry->ack.retval_ptr = cmd->retval_ptr;
    send_entry->ack.retval = PTL_OK;

    ret = ptl_cq_entry_send( ctx->cq_h, cmd->ni_handle.s.code,
                                        send_entry, sizeof(ptl_cqe_t));
    if (ret < 0) {
        perror("ptl_cq_entry_send");
        return -1;
    }
    return 0;
}