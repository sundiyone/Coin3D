#ifndef COIN_GLUE_INTERNAL_WGL_H
#define COIN_GLUE_INTERNAL_WGL_H

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#ifndef COIN_INTERNAL
#error this is a private header file
#endif

#include <Inventor/C/glue/gl.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void * coin_wgl_getprocaddress(const cc_glglue * glue, const char * fname);

void * wglglue_context_create_offscreen(unsigned int width, unsigned int height, bool texture = true);
bool wglglue_context_make_current(void * ctx);
void wglglue_context_reinstate_previous(void * ctx);
void wglglue_context_destruct(void * ctx);

void wglglue_context_bind_pbuffer(void * ctx);
void wglglue_context_release_pbuffer(void * ctx);
bool wglglue_context_pbuffer_is_bound(void * ctx);
bool wglglue_context_can_render_to_texture(void * ctx);

bool wglglue_context_pbuffer_max(void * ctx, unsigned int * lims);

/* This abomination is needed to support SoOffscreenRenderer::getDC(). */
const void * wglglue_context_win32_HDC(void * ctx);
void wglglue_copy_to_bitmap_win32_HDC(void * ctx);

void wglglue_cleanup(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !COIN_GLUE_INTERNAL_WGL_H */
