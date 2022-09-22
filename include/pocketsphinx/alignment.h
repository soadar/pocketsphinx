/* -*- c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* ====================================================================
 * Copyright (c) 2010 Carnegie Mellon University.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * This work was supported in part by funding from the Defense Advanced 
 * Research Projects Agency and the National Science Foundation of the 
 * United States of America, and the CMU Sphinx Speech Consortium.
 *
 * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND 
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */

/**
 * @file ps_alignment.h Multi-level alignment structure
 */

#ifndef __PS_ALIGNMENT_H__
#define __PS_ALIGNMENT_H__

#include <pocketsphinx/prim_type.h>

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

#define PS_ALIGNMENT_NONE ((uint16)0xffff)

struct ps_alignment_entry_s {
    union {
        int32 wid;
        struct {
            uint16 ssid;
            uint16 cipid;
            uint16 tmatid;
        } pid;
        uint16 senid;
    } id;
    int16 start;
    int16 duration;
    int32 score;
    uint16 parent;
    uint16 child;
};

typedef struct ps_alignment_entry_s ps_alignment_entry_t;

typedef struct ps_alignment_s ps_alignment_t;

typedef struct ps_alignment_iter_s ps_alignment_iter_t;

/**
 * Retain an alighment
 */
ps_alignment_t *ps_alignment_retain(ps_alignment_t *al);

/**
 * Release an alignment
 */
int ps_alignment_free(ps_alignment_t *al);

/**
 * Iterate over the alignment starting at the first word.
 */
ps_alignment_iter_t *ps_alignment_words(ps_alignment_t *al);

/**
 * Iterate over the alignment starting at the first phone.
 */
ps_alignment_iter_t *ps_alignment_phones(ps_alignment_t *al);

/**
 * Iterate over the alignment starting at the first state.
 */
ps_alignment_iter_t *ps_alignment_states(ps_alignment_t *al);

/**
 * Get the alignment entry pointed to by an iterator.
 *
 * The iterator retains ownership of this so don't try to free it.
 */
ps_alignment_entry_t *ps_alignment_iter_get(ps_alignment_iter_t *itor);

/**
 * Move alignment iterator to given index.
 */
ps_alignment_iter_t *ps_alignment_iter_goto(ps_alignment_iter_t *itor, int pos);

/**
 * Move an alignment iterator forward.
 *
 * If the end of the alignment is reached, this will free the iterator
 * and return NULL.
 */
ps_alignment_iter_t *ps_alignment_iter_next(ps_alignment_iter_t *itor);

/**
 * Move an alignment iterator back.
 *
 * If the start of the alignment is reached, this will free the iterator
 * and return NULL.
 */
ps_alignment_iter_t *ps_alignment_iter_prev(ps_alignment_iter_t *itor);

/**
 * Get a new iterator starting at the parent of the current node.
 *
 * If there is no parent node, NULL is returned.
 */
ps_alignment_iter_t *ps_alignment_iter_up(ps_alignment_iter_t *itor);
/**
 * Get a new iterator starting at the first child of the current node.
 *
 * If there is no child node, NULL is returned.
 */
ps_alignment_iter_t *ps_alignment_iter_down(ps_alignment_iter_t *itor);

/**
 * Release an iterator before completing all iterations.
 */
int ps_alignment_iter_free(ps_alignment_iter_t *itor);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __PS_ALIGNMENT_H__ */
