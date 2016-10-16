/* -*- C++ -*-
 *
 *  ONScripterLabel_effect.cpp - Effect executer of ONScripter-EN
 *
 *  Copyright (c) 2001-2009 Ogapee. All rights reserved.
 *  (original ONScripter, of which this is a fork).
 *
 *  ogapee@aqua.dti2.ne.jp
 *
 *  Copyright (c) 2008-2011 "Uncle" Mion Sonozaki
 *
 *  UncleMion@gmail.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>
 *  or write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *  Contains emulation of Takashi Toyama's "cascade.dll", "whirl.dll",
 *  "trvswave.dll", and "breakup.dll" NScripter plugin effects.
 *  Added by Mion, Summer 2008.
 */

#ifdef _MSC_VER
#pragma warning(disable:4244)
#endif

#include "ONScripterLabel.h"

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#define EFFECT_STRIPE_WIDTH (16 * screen_ratio1 / screen_ratio2)
#define EFFECT_STRIPE_CURTAIN_WIDTH (24 * screen_ratio1 / screen_ratio2)
#define EFFECT_QUAKE_AMP (12 * screen_ratio1 / screen_ratio2)

static char *dll, *params; //for dll-based effects

void ONScripterLabel::buildSinTable()
{
    if (!sin_table) {
        //integer-based trig table, scaled up by TRIG_FACTOR
        sin_table = new int[TRIG_TABLE_SIZE];
        for (int i=0; i<TRIG_TABLE_SIZE; i++) {
            sin_table[i] = (int)(sin((float) i * M_PI * 2 / TRIG_TABLE_SIZE) *
                                 TRIG_FACTOR);
        }
    }
}

void ONScripterLabel::buildCosTable()
{
    if (!cos_table) {
        //integer-based trig table, scaled up by TRIG_FACTOR
        cos_table = new int[TRIG_TABLE_SIZE];
        for (int i=0; i<TRIG_TABLE_SIZE; i++) {
            cos_table[i] = (int)(cos((float) i * M_PI * 2 / TRIG_TABLE_SIZE) *
                                 TRIG_FACTOR);
        }
    }
}

bool ONScripterLabel::setEffect( EffectLink *effect, bool generate_effect_dst, bool update_backup_surface )
{
    if ( effect->effect == 0 ) return true;

    if (update_backup_surface)
        refreshSurface(backup_surface, &dirty_rect.bounding_box, REFRESH_NORMAL_MODE);
    
    int effect_no = effect->effect;

    SDL_BlitSurface( accumulation_surface, NULL, effect_src_surface, NULL );

    if (generate_effect_dst){
        int refresh_mode = refreshMode();
        if (update_backup_surface && refresh_mode == REFRESH_NORMAL_MODE){
            SDL_BlitSurface( backup_surface, &dirty_rect.bounding_box, effect_dst_surface, &dirty_rect.bounding_box );
        }
        else{
            if (effect_no == 1)
                refreshSurface( effect_dst_surface, &dirty_rect.bounding_box, refresh_mode );
            else
                refreshSurface( effect_dst_surface, NULL, refresh_mode );
        }
    }
    
    effect_counter = 0;
    effect_start_time_old = SDL_GetTicks();
    effect_duration = effect->duration;
    if (ctrl_pressed_status || skip_mode & SKIP_NORMAL) {
        // shorten the duration of effects while skipping
        if ( effect_cut_flag ) {
            effect_duration = 0;
            return false; //don't parse effects if effectcut skip
        } else if (effect_duration > 100) {
            effect_duration = effect_duration / 10;
        } else if (effect_duration > 10) {
            effect_duration = 10;
        } else {
            effect_duration = 1;
        }
    } else if (effectspeed == EFFECTSPEED_INSTANT) {
        effect_duration = 0;
        return false; //don't parse effects if instant speed
    } else if (effectspeed == EFFECTSPEED_QUICKER) {
        effect_duration = effect_duration / 2;
        if (effect_duration <= 0)
            effect_duration = 1;
    }

    /* Load mask image */
    if ( effect_no == 15 || effect_no == 18 ){
        if ( !effect->anim.image_surface ){
            parseTaggedString( &effect->anim, true );
#ifdef RCA_SCALE
            setupAnimationInfo( &effect->anim, NULL, scr_stretch_x, scr_stretch_y );
#else
            setupAnimationInfo( &effect->anim );
#endif
        }
    }
    if ( effect_no == 11 || effect_no == 12 || effect_no == 13 || effect_no == 14 ||
         effect_no == 16 || effect_no == 17 )
        dirty_rect.fill( screen_width, screen_height );

    dll = params = NULL;
    if (effect_no == CUSTOM_EFFECT_NO - 1) { // dll-based
        dll = effect->anim.image_name;
        if (dll != NULL) { //just in case no dll is given
            if (debug_level > 0)
                printf("dll effect: Got dll/params '%s'\n", dll);

            params = dll;
            while (*params != 0 && *params != '/') params++;
            if (*params == '/') params++;

            if (!strncmp(dll, "whirl.dll", 9)) {
                buildSinTable();
                buildCosTable();
                buildWhirlTable();
                dirty_rect.fill( screen_width, screen_height );
            }
            else if (!strncmp(dll, "trvswave.dll", 12)) {
                buildSinTable();
                dirty_rect.fill( screen_width, screen_height );
            }
            else if (!strncmp(dll, "breakup.dll", 11)) {
                initBreakup(params);
                dirty_rect.fill( screen_width, screen_height );
            }
            else {
                dirty_rect.fill( screen_width, screen_height );
            }
        }
    }

    return false;
}

bool ONScripterLabel::doEffect( EffectLink *effect, bool clear_dirty_region )
{
    bool first_time = (effect_counter == 0);

    effect_start_time = SDL_GetTicks();

    effect_timer_resolution = effect_start_time - effect_start_time_old;
    effect_start_time_old = effect_start_time;

    int effect_no = effect->effect;
    if (first_time) {
        if ( (effect_cut_flag &&
              ( ctrl_pressed_status || skip_mode & SKIP_NORMAL )) ||
             (effectspeed == EFFECTSPEED_INSTANT) )
            effect_no = 1;
    }

    skip_effect = false;

    int i;
    int width, width2;
    int height, height2;
    SDL_Rect src_rect={0, 0, screen_width, screen_height};
    SDL_Rect dst_rect={0, 0, screen_width, screen_height};

    /* ---------------------------------------- */
    /* Execute effect */
    if (debug_level > 0 && first_time)
        printf("Effect number %d, %d ms\n", effect_no, effect_duration );

    bool not_implemented = false;
    switch ( effect_no ){
      case 0: // Instant display
      case 1: // Instant display
        //drawEffect( &src_rect, &src_rect, effect_dst_surface );
        break;

      case 2: // Left shutter
        width = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=0 ; i<screen_width/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = i * EFFECT_STRIPE_WIDTH;
            src_rect.y = 0;
            src_rect.w = width;
            src_rect.h = screen_height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 3: // Right shutter
        width = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=1 ; i<=screen_width/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = i * EFFECT_STRIPE_WIDTH - width - 1;
            src_rect.y = 0;
            src_rect.w = width;
            src_rect.h = screen_height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 4: // Top shutter
        height = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=0 ; i<screen_height/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = 0;
            src_rect.y = i * EFFECT_STRIPE_WIDTH;
            src_rect.w = screen_width;
            src_rect.h = height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 5: // Bottom shutter
        height = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=1 ; i<=screen_height/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = 0;
            src_rect.y = i * EFFECT_STRIPE_WIDTH - height - 1;
            src_rect.w = screen_width;
            src_rect.h = height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 6: // Left curtain
        width = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_width/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            width2 = width - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_width;
            if ( width2 >= 0 ){
                src_rect.x = i * EFFECT_STRIPE_CURTAIN_WIDTH;
                src_rect.y = 0;
                src_rect.w = width2;
                src_rect.h = screen_height;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      case 7: // Right curtain
        width = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_width/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            width2 = width - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_width;
            if ( width2 >= 0 ){
                if ( width2 > EFFECT_STRIPE_CURTAIN_WIDTH ) width2 = EFFECT_STRIPE_CURTAIN_WIDTH;
                src_rect.x = screen_width - i * EFFECT_STRIPE_CURTAIN_WIDTH - width2;
                src_rect.y = 0;
                src_rect.w = width2;
                src_rect.h = screen_height;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      case 8: // Top curtain
        height = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_height/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            height2 = height - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_height;
            if ( height2 >= 0 ){
                src_rect.x = 0;
                src_rect.y = i * EFFECT_STRIPE_CURTAIN_WIDTH;
                src_rect.w = screen_width;
                src_rect.h = height2;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      case 9: // Bottom curtain
        height = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_height/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            height2 = height - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_height;
            if ( height2 >= 0 ){
                src_rect.x = 0;
                src_rect.y = screen_height - i * EFFECT_STRIPE_CURTAIN_WIDTH - height2;
                src_rect.w = screen_width;
                src_rect.h = height2;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      default:
        not_implemented = true;
        if (first_time) {
            snprintf(script_h.errbuf, MAX_ERRBUF_LEN,
                     "effect No. %d not implemented; substituting crossfade",
                     effect_no);
            errorAndCont(script_h.errbuf);
        }

      case 10: // Cross fade
        height = 256 * effect_counter / effect_duration;
        alphaMaskBlend( NULL, ALPHA_BLEND_CONST, height, &dirty_rect.bounding_box );
        break;

      case 11: // Left scroll
        width = screen_width * effect_counter / effect_duration;
        src_rect.x = 0;
        dst_rect.x = width;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width - width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);

        src_rect.x = screen_width - width - 1;
        dst_rect.x = 0;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 12: // Right scroll
        width = screen_width * effect_counter / effect_duration;
        src_rect.x = width;
        dst_rect.x = 0;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width - width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);

        src_rect.x = 0;
        dst_rect.x = screen_width - width - 1;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 13: // Top scroll
        width = screen_height * effect_counter / effect_duration;
        src_rect.x = dst_rect.x = 0;
        src_rect.y = 0;
        dst_rect.y = width;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = screen_height - width;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);

        src_rect.x = dst_rect.x = 0;
        src_rect.y = screen_height - width - 1;
        dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = width;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 14: // Bottom scroll
        width = screen_height * effect_counter / effect_duration;
        src_rect.x = dst_rect.x = 0;
        src_rect.y = width;
        dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = screen_height - width;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);

        src_rect.x = dst_rect.x = 0;
        src_rect.y = 0;
        dst_rect.y = screen_height - width - 1;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = width;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 15: // Fade with mask
        alphaMaskBlend( effect->anim.image_surface, ALPHA_BLEND_FADE_MASK, 256 * effect_counter / effect_duration, &dirty_rect.bounding_box );
        break;

      case 16: // Mosaic out
        generateMosaic( effect_src_surface, 5 - 6 * effect_counter / effect_duration );
        break;

      case 17: // Mosaic in
        generateMosaic( effect_dst_surface, 6 * effect_counter / effect_duration );
        break;

      case 18: // Cross fade with mask
        alphaMaskBlend( effect->anim.image_surface, ALPHA_BLEND_CROSSFADE_MASK, 256 * effect_counter * 2 / effect_duration, &dirty_rect.bounding_box );
        break;

      case (CUSTOM_EFFECT_NO + 0 ): // quakey
        if ( effect_timer_resolution > effect_duration / 4 / effect->no )
            effect_timer_resolution = effect_duration / 4 / effect->no;
        dst_rect.x = 0;
        dst_rect.y = (Sint16)(sin(M_PI * 2.0 * effect->no * effect_counter / effect_duration) *
                              EFFECT_QUAKE_AMP * effect->no * (effect_duration -  effect_counter) / effect_duration);
        SDL_FillRect( accumulation_surface, NULL, SDL_MapRGBA( accumulation_surface->format, 0, 0, 0, 0xff ) );
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case (CUSTOM_EFFECT_NO + 1 ): // quakex
        if ( effect_timer_resolution > effect_duration / 4 / effect->no )
            effect_timer_resolution = effect_duration / 4 / effect->no;
        dst_rect.x = (Sint16)(sin(M_PI * 2.0 * effect->no * effect_counter / effect_duration) *
                              EFFECT_QUAKE_AMP * effect->no * (effect_duration -  effect_counter) / effect_duration);
        dst_rect.y = 0;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case (CUSTOM_EFFECT_NO + 2 ): // quake
        dst_rect.x = effect->no*((int)(3.0*rand()/(RAND_MAX+1.0)) - 1) * 2;
        dst_rect.y = effect->no*((int)(3.0*rand()/(RAND_MAX+1.0)) - 1) * 2;
        SDL_FillRect( accumulation_surface, NULL, SDL_MapRGBA( accumulation_surface->format, 0, 0, 0, 0xff ) );
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case (CUSTOM_EFFECT_NO + 3 ): // flushout
        if (effect_counter > 0){
            width = 30 * effect_counter / effect_duration;
            height = 30 * (effect_counter + effect_timer_resolution) / effect_duration;
            if (height > width){
                doFlushout(height);
                alphaMaskBlend( NULL, ALPHA_BLEND_CONST, effect_counter * 256 / effect_duration, &dirty_rect.bounding_box, effect_tmp_surface );
            }
        }
        break;

      case (CUSTOM_EFFECT_NO - 1): // dll-based
        if (dll != NULL) {
            if (!strncmp(dll, "cascade.dll", 11)) {
                effectCascade(params, effect_duration);
            } else if (!strncmp(dll, "whirl.dll", 9)) {
                effectWhirl(params, effect_duration);
            } else if (!strncmp(dll, "trvswave.dll", 12)) {
                effectTrvswave(params, effect_duration);
            } else if (!strncmp(dll, "breakup.dll", 11)) {
                effectBreakup(params, effect_duration);
            } else {
                not_implemented = true;
                if (first_time) {
                    snprintf(script_h.errbuf, MAX_ERRBUF_LEN,
                             "dll effect '%s' (%d) not implemented; substituting crossfade",
                             dll, effect_no);
                    errorAndCont(script_h.errbuf);
                }
            }
        } else { //just in case no dll is given
            not_implemented = true;
            if (first_time) {
                snprintf(script_h.errbuf, MAX_ERRBUF_LEN,
                         "no dll provided for effect %d; substituting crossfade",
                         effect_no);
                errorAndCont(script_h.errbuf);
            }
        }
        if (not_implemented) {
            // do crossfade
            height = 256 * effect_counter / effect_duration;
            alphaMaskBlend( NULL, ALPHA_BLEND_CONST, height, &dirty_rect.bounding_box );
        }
        break;
    }

    SDL_Delay(1);

    if (debug_level > 1)
        printf("\teffect count %d / dur %d\n", effect_counter, effect_duration);

    effect_counter += effect_timer_resolution;
    if ( effect_counter < effect_duration && effect_no != 1 ){
        if ( effect_no != 0 ) flush( REFRESH_NONE_MODE, NULL, false );

        event_mode = IDLE_EVENT_MODE;
        event_mode |= WAIT_NO_ANIM_MODE;
        if (effectskip_flag) {
            event_mode |= WAIT_INPUT_MODE;
        }
        waitEvent(0);
        event_mode &= ~(WAIT_NO_ANIM_MODE | WAIT_INPUT_MODE);

        if (effectskip_flag && skip_effect)
            effect_counter = effect_duration;

        return true;
    }
    else {
        //last call
        SDL_BlitSurface(effect_dst_surface, &dirty_rect.bounding_box,
                        accumulation_surface, &dirty_rect.bounding_box);

        if (effect_no != 0)
            flush(REFRESH_NONE_MODE, NULL, clear_dirty_region);
        if (effect_no == 1)
            effect_counter = 0;
        else if ((effect_no == (CUSTOM_EFFECT_NO - 1)) && (dll != NULL)){
            dll = params = NULL;
        }

        display_mode &= ~DISPLAY_MODE_UPDATED;

        event_mode = IDLE_EVENT_MODE;
        if (!first_time){
            event_mode = WAIT_TIMER_MODE;
            if ( ctrl_pressed_status || (skip_mode & SKIP_TO_WAIT) )
                waitEvent(1); //allow a moment to detect ctrl unpress, if any
            else
                waitEvent(effect_blank);
        }
        else if (effect_no > 1)
            waitEvent(0); // to detect possibly important events

        return false;
    }
}

void ONScripterLabel::drawEffect(SDL_Rect *dst_rect, SDL_Rect *src_rect, SDL_Surface *surface)
{
    SDL_Rect clipped_rect;
    if (AnimationInfo::doClipping(dst_rect, &dirty_rect.bounding_box, &clipped_rect)) return;
    if (src_rect != dst_rect){
        src_rect->x += clipped_rect.x;
        src_rect->y += clipped_rect.y;
        src_rect->w = clipped_rect.w;
        src_rect->h = clipped_rect.h;
    }

    SDL_BlitSurface(surface, src_rect, accumulation_surface, dst_rect);
}

void ONScripterLabel::generateMosaic( SDL_Surface *src_surface, int level )
{
    int i, j, ii, jj;
    int width = 160;
    for ( i=0 ; i<level ; i++ ) width >>= 1;

#ifdef BPP16
    int total_width = accumulation_surface->pitch / 2;
#else
    int total_width = accumulation_surface->pitch / 4;
#endif
    SDL_LockSurface( src_surface );
    SDL_LockSurface( accumulation_surface );
    ONSBuf *src_buffer = (ONSBuf *)src_surface->pixels;

    for ( i=screen_height-1 ; i>=0 ; i-=width ){
        for ( j=0 ; j<screen_width ; j+=width ){
            ONSBuf p = src_buffer[ i*total_width+j ];
            ONSBuf *dst_buffer = (ONSBuf *)accumulation_surface->pixels + i*total_width + j;

            int height2 = width;
            if (i+1-width < 0) height2 = i+1;
            int width2 = width;
            if (j+width > screen_width) width2 = screen_width - j;
            for ( ii=height2 ; ii!=0 ; ii-- ){
                for ( jj=width2 ; jj!=0 ; jj-- ){
                    *dst_buffer++ = p;
                }
                dst_buffer -= total_width + width2;
            }
        }
    }

    SDL_UnlockSurface( accumulation_surface );
    SDL_UnlockSurface( src_surface );
}

// An interesting builtin effect... this causes a semi-transparent
// time-lapse expansion of the image, producing a sort of "hyperspace" effect
void ONScripterLabel::doFlushout( int level )
{
    int i, j, ii, jj;

#ifdef BPP16
    int total_width = accumulation_surface->pitch / 2;
#else
    int total_width = accumulation_surface->pitch / 4;
#endif
    SDL_LockSurface( effect_src_surface );
    SDL_LockSurface( accumulation_surface );
    ONSBuf *src_buffer = (ONSBuf *)effect_src_surface->pixels;

    ONSBuf *dst_buffer = (ONSBuf *)accumulation_surface->pixels;
    const int factor = 32;
    const int maxlevel = 30;
    level += factor - maxlevel;
    const int y_offset = screen_height*level/factor/2;
    const int x_offset = screen_width*level/factor/2;
    for ( i=0 ; i<screen_height ; i++ ){
        ii = i*(factor-level)/factor + y_offset;
        for ( j=0 ; j<screen_width ; j++ ){
            jj = j*(factor-level)/factor + x_offset;
            *dst_buffer++ = src_buffer[ ii*total_width+jj ];
        }
    }

    SDL_UnlockSurface( accumulation_surface );
    SDL_UnlockSurface( effect_src_surface );
    alphaMaskBlend( NULL, ALPHA_BLEND_CONST, 64, &dirty_rect.bounding_box, effect_tmp_surface, accumulation_surface, effect_tmp_surface );
}

//
// Emulation of Takashi Toyama's "cascade.dll" NScripter plugin effect
//
void ONScripterLabel::effectCascade( char *params, int duration )
{
    enum {
        //some constants for cascade
        CASCADE_DIR   = 1,
        CASCADE_LR    = 2,
        CASCADE_UP    = 0,
        CASCADE_DOWN  = 1,
        CASCADE_LEFT  = 2,
        CASCADE_RIGHT = 3,
        CASCADE_CROSS = 4,
        CASCADE_IN    = 8
    };

    SDL_Surface *src_surface, *dst_surface;
    SDL_Rect src_rect={0, 0, screen_width, screen_height};
    SDL_Rect dst_rect={0, 0, screen_width, screen_height};
    int mode, width, start, end;
 
    if (params[0] == 'u')
        mode = CASCADE_UP;
    else if (params[0] == 'd')
        mode = CASCADE_DOWN;
    else if (params[0] == 'r')
        mode = CASCADE_RIGHT;
    else
        mode = CASCADE_LEFT;

    if (params[1] == 'i')
        mode |= CASCADE_IN;
    else if (params[1] == 'x')
        mode |= CASCADE_IN | CASCADE_CROSS;

    if (mode & CASCADE_IN)
        src_surface = effect_dst_surface;
    else
        src_surface = effect_src_surface;
    if (mode & CASCADE_CROSS)
        dst_surface = effect_tmp_surface;
    else
        dst_surface = accumulation_surface;

    if (effect_counter == 0)
        effect_tmp = 0;

    if (mode & CASCADE_LR) {
        // moves left-right
        width = screen_width * effect_counter / duration;
        if (!(mode & CASCADE_IN))
            width = screen_width - width;

        src_rect.y = dst_rect.y = 0;
        src_rect.h = dst_rect.h = screen_height;
        src_rect.w = dst_rect.w = 1;
        if ((mode & CASCADE_CROSS) && (width > 0)) {
            // need to cascade-out the src
            if (mode & CASCADE_DIR) {
                // moves right
                start = 0;
                end = width;
                dst_rect.x = end;
            } else {
                // moves left
                start = screen_width - width;
                end = screen_width;
                dst_rect.x = start;
            }
            src_rect.x = 0;
            SDL_BlitSurface(effect_src_surface, &dst_rect, accumulation_surface, &src_rect);
            for (int i=start; i<end; i++) {
                dst_rect.x = i;
                SDL_BlitSurface(accumulation_surface, &src_rect, effect_src_surface, &dst_rect);
            }
        }
        if (mode & CASCADE_DIR) {
            // moves right
            start = width;
            end = screen_width;
            src_rect.x = start;
        } else {
            // moves left
            start = 0;
            end = screen_width - width;
            src_rect.x = end;
        }
        for (int i=start; i<end; i++) {
            dst_rect.x = i;
            SDL_BlitSurface(src_surface, &src_rect, dst_surface, &dst_rect);
        }
        if ((mode & CASCADE_IN) && (width > 0)) {
            if (mode & CASCADE_DIR)
                src_rect.x = effect_tmp;
            else
                src_rect.x = screen_width - width;
            dst_rect.x = src_rect.x;
            src_rect.w = dst_rect.w = width - effect_tmp;
            SDL_BlitSurface(src_surface, &src_rect, dst_surface, &dst_rect);
            effect_tmp = width;
        }
    } else {
        // moves up-down
        width = screen_height * effect_counter / duration;
        if (!(mode & CASCADE_IN))
            width = screen_height - width;

        src_rect.x = dst_rect.x = 0;
        src_rect.h = dst_rect.h = 1;
        src_rect.w = dst_rect.w = screen_width;
        if ((mode & CASCADE_CROSS) && (width > 0)) {
            // need to cascade-out the src
            if (mode & CASCADE_DIR) {
                // moves down
                start = 0;
                end = width;
                dst_rect.y = end;
            } else {
                // moves up
                start = screen_height - width;
                end = screen_height;
                dst_rect.y = start;
            }
            src_rect.y = 0;
            SDL_BlitSurface(effect_src_surface, &dst_rect, accumulation_surface, &src_rect);
            for (int i=start; i<end; i++) {
                dst_rect.y = i;
                SDL_BlitSurface(accumulation_surface, &src_rect, effect_src_surface, &dst_rect);
            }
        }
        if (mode & CASCADE_DIR) {
            // moves down
            start = width;
            end = screen_height;
            src_rect.y = start;
        } else {
            // moves up
            start = 0;
            end = screen_height - width;
            src_rect.y = end;
        }
        for (int i=start; i<end; i++) {
            dst_rect.y = i;
            SDL_BlitSurface(src_surface, &src_rect, dst_surface, &dst_rect);
        }
        if ((mode & CASCADE_IN) && (width > 0)) {
            if (mode & CASCADE_DIR)
                src_rect.y = effect_tmp;
            else
                src_rect.y = screen_height - width;
            dst_rect.y = src_rect.y;
            src_rect.h = dst_rect.h = width - effect_tmp;
            SDL_BlitSurface(src_surface, &src_rect, dst_surface, &dst_rect);
            effect_tmp = width;
        }
    }
    if (mode & CASCADE_CROSS) {
        // do crossfade
        width = 256 * effect_counter / duration;
        alphaMaskBlend( NULL, ALPHA_BLEND_CONST, width, &dirty_rect.bounding_box, NULL, dst_surface );
    }
}

//
// Emulation of Takashi Toyama's "trvswave.dll" NScripter plugin effect
//
void ONScripterLabel::effectTrvswave( char *params, int duration )
{
    enum {
        //some constants for trvswave
        TRVSWAVE_AMPLITUDE   = 9,
        TRVSWAVE_WVLEN_END   = 32,
        TRVSWAVE_WVLEN_START = 256
    };

    SDL_Rect src_rect={0, 0, screen_width, 1};
    SDL_Rect dst_rect={0, 0, screen_width, 1};
    int ampl, wvlen;
    int y_offset = -screen_height / 2;
    int width = 256 * effect_counter / duration;
    alphaMaskBlend( NULL, ALPHA_BLEND_CONST, width, &dirty_rect.bounding_box, NULL, NULL, effect_tmp_surface );
    if (effect_counter * 2 < duration) {
        ampl = TRVSWAVE_AMPLITUDE * 2 * effect_counter / duration;
        wvlen = (Sint16)(1.0/(((1.0/TRVSWAVE_WVLEN_END - 1.0/TRVSWAVE_WVLEN_START) * 2 * effect_counter / duration) + (1.0/TRVSWAVE_WVLEN_START)));
    } else {
        ampl = TRVSWAVE_AMPLITUDE * 2 * (duration - effect_counter) / duration;
        wvlen = (Sint16)(1.0/(((1.0/TRVSWAVE_WVLEN_END - 1.0/TRVSWAVE_WVLEN_START) * 2 * (duration - effect_counter) / duration) + (1.0/TRVSWAVE_WVLEN_START)));
    }
    SDL_FillRect( accumulation_surface, NULL, SDL_MapRGBA( accumulation_surface->format, 0, 0, 0, 0xff ) );
    for (int i=0; i<screen_height; i++) {
        int theta = TRIG_TABLE_SIZE * y_offset / wvlen;
        while (theta < 0) theta += TRIG_TABLE_SIZE;
        theta %= TRIG_TABLE_SIZE;
        dst_rect.x = (Sint16)(ampl * sin_table[theta] / TRIG_FACTOR);
        //dst_rect.x = (Sint16)(ampl * sin(M_PI * 2.0 * y_offset / wvlen));
        SDL_BlitSurface(effect_tmp_surface, &src_rect, accumulation_surface, &dst_rect);
        ++src_rect.y;
        ++dst_rect.y;
        ++y_offset;
    }
}

//
// Emulation of Takashi Toyama's "whirl.dll" NScripter plugin effect
//
#define CENTER_X (screen_width/2)
#define CENTER_Y (screen_height/2)

void ONScripterLabel::buildWhirlTable()
{
    if (whirl_table) return;

    whirl_table = new int[screen_height * screen_width];
    int *dst_buffer = whirl_table;

    for ( int i=0 ; i<screen_height ; ++i ){
        for ( int j=0; j<screen_width ; ++j, ++dst_buffer ){
            int x = j - CENTER_X, y = i - CENTER_Y;
            // actual x = x + 0.5, actual y = y + 0.5;
            // (x+0.5)^2 + (y+0.5)^2 = x^2 + x + 0.25 + y^2 + y + 0.25
            *dst_buffer = (int)(sqrt((float)(x * x + x + y * y + y) + 0.5) * 4);
        }
    }
}

void ONScripterLabel::effectWhirl( char *params, int duration )
{
//#define OMEGA (M_PI / 64)

    int direction = (params[0] == 'r') ? -1 : 1;

    int t = (effect_counter * (TRIG_TABLE_SIZE/4) / duration) %
            TRIG_TABLE_SIZE;
    int rad_amp = (sin_table[t] + cos_table[t] - TRIG_FACTOR) *
                  (TRIG_TABLE_SIZE/2) / TRIG_FACTOR;
    int rad_base = ((TRIG_FACTOR - cos_table[t]) *
                    TRIG_TABLE_SIZE / TRIG_FACTOR) + rad_amp;
    //float t = (float) effect_counter * M_PI / (duration * 2);
    //float one_minus_cos = 1 - cos(t);
    //float rad_amp = M_PI * (sin(t) - one_minus_cos);
    //float rad_base = M_PI * 2 * one_minus_cos + rad_amp;

    int width = 256 * effect_counter / duration;
    alphaMaskBlend( NULL, ALPHA_BLEND_CONST, width, &dirty_rect.bounding_box,
                    NULL, NULL, effect_tmp_surface );

    SDL_LockSurface( effect_tmp_surface );
    SDL_LockSurface( accumulation_surface );
    ONSBuf *src_buffer = (ONSBuf *)effect_tmp_surface->pixels;
    ONSBuf *dst_buffer = (ONSBuf *)accumulation_surface->pixels;
    int *whirl_buffer = whirl_table;

    for ( int i=0 ; i<screen_height ; ++i ){
        for ( int j=0 ; j<screen_width ; ++j, ++dst_buffer, ++whirl_buffer ){
            int ii=i, jj=j;
            // actual x = x + 0.5, actual y = y + 0.5
            int x = j - CENTER_X, y = i - CENTER_Y;
            //whirl factor
            int theta = *whirl_buffer;
            while (theta < 0) theta += TRIG_TABLE_SIZE;
            theta %= TRIG_TABLE_SIZE;
            theta = ((rad_amp * sin_table[theta] / TRIG_FACTOR) + rad_base) *
                    direction;
            //float theta = direction * (rad_base + rad_amp * 
            //                           sin(sqrt(x * x + y * y) * OMEGA));

            //perform rotation
            while (theta < 0) theta += TRIG_TABLE_SIZE;
            theta %= TRIG_TABLE_SIZE;
            //working on x+0.5, hence (2x+1)/2
            jj = (((x + x + 1) * cos_table[theta] -
                   (y + y + 1) * sin_table[theta])/TRIG_FACTOR - 1)/2 +
                 CENTER_X;
            ii = (((x + x + 1) * sin_table[theta] +
                   (y + y + 1) * cos_table[theta])/TRIG_FACTOR - 1)/2 +
                 CENTER_Y;
            //jj = (int) (x * cos_theta - y * sin_theta + CENTER_X);
            //ii = (int) (x * sin_theta + y * cos_theta + CENTER_Y);
            if (jj < 0) jj = 0;
            if (jj >= screen_width) jj = screen_width-1;
            if (ii < 0) ii = 0;
            if (ii >= screen_height) ii = screen_height-1;

            // change pixel value!
            *dst_buffer = *(src_buffer + screen_width * ii + jj);
        }
    }

    SDL_UnlockSurface( accumulation_surface );
    SDL_UnlockSurface( effect_tmp_surface );
}

//
// Emulation of Takashi Toyama's "breakup.dll" NScripter plugin effect
//
#define BREAKUP_CELLWIDTH 24
#define BREAKUP_CELLFORMS 16
#define BREAKUP_MAX_CELL_X ((screen_width + BREAKUP_CELLWIDTH - 1)/BREAKUP_CELLWIDTH)
#define BREAKUP_MAX_CELL_Y ((screen_height + BREAKUP_CELLWIDTH - 1)/BREAKUP_CELLWIDTH)
#define BREAKUP_MAX_CELLS (BREAKUP_MAX_CELL_X * BREAKUP_MAX_CELL_Y)
#define BREAKUP_DIRECTIONS 8
#define BREAKUP_MOVE_FRAMES 40
#define BREAKUP_STILL_STATE (BREAKUP_CELLFORMS - BREAKUP_CELLWIDTH/2)

#define BREAKUP_MODE_LOWER  1
#define BREAKUP_MODE_LEFT   2
#define BREAKUP_MODE_PILEUP 4
#define BREAKUP_MODE_JUMBLE 8

const int breakup_disp_x[BREAKUP_DIRECTIONS] = { -7,-7,-5,-4,-2,1,3,5 }; 
const int breakup_disp_y[BREAKUP_DIRECTIONS] = {  0, 2, 4, 6, 7,7,6,5 }; 
int n_cell_x, n_cell_y, n_cell_diags, n_cells, tot_frames, last_frame;
int breakup_mode;
SDL_Rect breakup_window;  // window of _cells_, not pixels

void ONScripterLabel::buildBreakupCellforms()
{
// build the 32x32 mask for each cellform
    if (breakup_cellforms) return;

    int w = BREAKUP_CELLWIDTH * BREAKUP_CELLFORMS;
    int h = BREAKUP_CELLWIDTH;
    breakup_cellforms = new bool[w*h];

    for (int n=0, rad2=1; n<BREAKUP_CELLFORMS; n++, rad2=(n+1)*(n+1)) {
        for (int x=0, xd=-BREAKUP_CELLWIDTH/2; x<BREAKUP_CELLWIDTH; x++, xd++) {
            for (int y=0, yd=-BREAKUP_CELLWIDTH/2; y<BREAKUP_CELLWIDTH; y++, yd++) {
                if (((xd * xd + xd + yd * yd + yd)*2 + 1) < 2*rad2)
                    breakup_cellforms[y*w + n*BREAKUP_CELLWIDTH + x] = true;
                else
                    breakup_cellforms[y*w + n*BREAKUP_CELLWIDTH + x] = false;
            }
        }
    }
}

void ONScripterLabel::buildBreakupMask()
{
// build the cell area mask for the breakup effect
    int w = BREAKUP_CELLWIDTH * BREAKUP_MAX_CELL_X;
    int h = BREAKUP_CELLWIDTH * BREAKUP_MAX_CELL_Y;
    if (! breakup_mask) {
        breakup_mask = new bool[w*h];
    }

    SDL_LockSurface( effect_src_surface );
    SDL_LockSurface( effect_dst_surface );
    ONSBuf *buffer1 = (ONSBuf *)effect_src_surface->pixels;
    ONSBuf *buffer2 = (ONSBuf *)effect_dst_surface->pixels;
    SDL_PixelFormat *fmt = effect_dst_surface->format;
    int surf_w = effect_src_surface->w;
    int surf_h = effect_src_surface->h;
    int x1=w, y1=-1, x2=0, y2=0;
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            if ((j >= surf_w) || (i >= surf_h)) {
                breakup_mask[i*w+j] = false;
                continue;
            }
            ONSBuf pix1 = buffer1[i*surf_w+j];
            ONSBuf pix2 = buffer2[i*surf_w+j];
            int pix1c = ((pix1 & fmt->Bmask) >> fmt->Bshift) << fmt->Bloss;
            int pix2c = ((pix2 & fmt->Bmask) >> fmt->Bshift) << fmt->Bloss;
            breakup_mask[i*w+j] = true;
            if (abs(pix1c - pix2c) > 8) {
                if (y1 < 0) y1 = i;
                if (j < x1) x1 = j;
                if (j > x2) x2 = j;
                y2 = i;
                continue;
            }
            pix1c = ((pix1 & fmt->Gmask) >> fmt->Gshift) << fmt->Gloss;
            pix2c = ((pix2 & fmt->Gmask) >> fmt->Gshift) << fmt->Gloss;
            if (abs(pix1c - pix2c) > 8) {
                if (y1 < 0) y1 = i;
                if (j < x1) x1 = j;
                if (j > x2) x2 = j;
                y2 = i;
                continue;
            }
            pix1c = ((pix1 & fmt->Rmask) >> fmt->Rshift) << fmt->Rloss;
            pix2c = ((pix2 & fmt->Rmask) >> fmt->Rshift) << fmt->Rloss;
            if (abs(pix1c - pix2c) > 8) {
                if (y1 < 0) y1 = i;
                if (j < x1) x1 = j;
                if (j > x2) x2 = j;
                y2 = i;
                continue;
            }
            pix1c = ((pix1 & fmt->Amask) >> fmt->Ashift) << fmt->Aloss;
            pix2c = ((pix2 & fmt->Amask) >> fmt->Ashift) << fmt->Aloss;
            if (abs(pix1c - pix2c) > 8) {
                if (y1 < 0) y1 = i;
                if (j < x1) x1 = j;
                if (j > x2) x2 = j;
                y2 = i;
                continue;
            }
            breakup_mask[i*w+j] = false;
        }
    }
    if (breakup_mode & BREAKUP_MODE_LEFT)
        x1 = 0;
    else
        x2 = surf_w-1;
    if (breakup_mode & BREAKUP_MODE_LOWER)
        y2 = surf_h-1;
    else
        y1 = 0;
    breakup_window.x = x1 / BREAKUP_CELLWIDTH;
    breakup_window.y = y1 / BREAKUP_CELLWIDTH;
    breakup_window.w = x2/BREAKUP_CELLWIDTH - breakup_window.x + 1;
    breakup_window.h = y2/BREAKUP_CELLWIDTH - breakup_window.y + 1;

    SDL_UnlockSurface( effect_dst_surface );
    SDL_UnlockSurface( effect_src_surface );
}

void ONScripterLabel::initBreakup( char *params )
{
    buildBreakupCellforms();

    breakup_mode = 0;
    if (params[0] == 'l')
        breakup_mode |= BREAKUP_MODE_LOWER;
    if (params[1] == 'l')
        breakup_mode |= BREAKUP_MODE_LEFT;
    if ((params[2] >= 'A') && (params[2] <= 'Z'))
        breakup_mode |= BREAKUP_MODE_JUMBLE;
    if ((params[2] == 'p') || (params[2] == 'P'))
        breakup_mode |= BREAKUP_MODE_PILEUP;

    if (!breakup_cells)
        breakup_cells = new BreakupCell[BREAKUP_MAX_CELLS];
    buildBreakupMask();
    n_cell_x = breakup_window.w;
    n_cell_y = breakup_window.h;
    n_cell_diags = n_cell_x + n_cell_y;
    n_cells = n_cell_x * n_cell_y;
    tot_frames = BREAKUP_MOVE_FRAMES + n_cell_diags + BREAKUP_CELLFORMS - BREAKUP_CELLWIDTH/2 + 1;
    last_frame = 0;

    int n = 0, dir = 1, i = 0, diag_n = 0;
    for (i=0; i<n_cell_x; i++) {
        int state = BREAKUP_MOVE_FRAMES + BREAKUP_STILL_STATE + diag_n;
        if (breakup_mode & BREAKUP_MODE_PILEUP)
            state = 0 - diag_n;
        for (int j=i, k=0; (j>=0) && (k<n_cell_y); j--, k++) {
            breakup_cells[n].cell_x = j + breakup_window.x;
            breakup_cells[n].cell_y = k + breakup_window.y;
            if (!(breakup_mode & BREAKUP_MODE_LEFT))
                breakup_cells[n].cell_x = breakup_window.x + breakup_window.w - j - 1;
            if (breakup_mode & BREAKUP_MODE_LOWER)
                breakup_cells[n].cell_y = breakup_window.y + breakup_window.h - k - 1;
            breakup_cells[n].dir = dir;
            breakup_cells[n].state = state;
            breakup_cells[n].radius = 0;
            ++dir &= (BREAKUP_DIRECTIONS-1);
            ++n;
        }
        ++diag_n;
    }
#ifdef _MSC_VER
	{
#endif
    for (int i=1; i<n_cell_y; i++) {
        int state = BREAKUP_MOVE_FRAMES + BREAKUP_STILL_STATE + diag_n;
        if (breakup_mode & BREAKUP_MODE_PILEUP)
            state = 0 - diag_n;
        for (int j=n_cell_x-1, k=i; (k<n_cell_y) && (j>=0); j--, k++) {
            breakup_cells[n].cell_x = j + breakup_window.x;
            breakup_cells[n].cell_y = k + breakup_window.y;
            if (!(breakup_mode & BREAKUP_MODE_LEFT))
                breakup_cells[n].cell_x = breakup_window.x + n_cell_x - j - 1;
            if (breakup_mode & BREAKUP_MODE_LOWER)
                breakup_cells[n].cell_y = breakup_window.y + n_cell_y - k - 1;
            breakup_cells[n].dir = dir;
            breakup_cells[n].state = state;
            breakup_cells[n].radius = 0;
            ++dir &= (BREAKUP_DIRECTIONS-1);
            ++n;
        }
        ++diag_n;
    }
#ifdef _MSC_VER
	}
#endif
}

void ONScripterLabel::effectBreakup( char *params, int duration )
{
    int x_dir = -1;
    int y_dir = -1;

    int frame = tot_frames * effect_counter / duration;
    int frame_diff = frame - last_frame;
    if (frame_diff == 0) 
        return;

    SDL_Surface *bg = effect_dst_surface;
    SDL_Surface *chr = effect_src_surface;
    last_frame += frame_diff;
    frame_diff = -frame_diff;
    if (breakup_mode & BREAKUP_MODE_PILEUP) {
        bg = effect_src_surface;
        chr = effect_dst_surface;
        frame_diff = -frame_diff;
        x_dir = -x_dir;
        y_dir = -y_dir;
    }
    SDL_BlitSurface(bg, NULL, accumulation_surface, NULL);
    SDL_Surface *dst = accumulation_surface;

    if (breakup_mode & BREAKUP_MODE_JUMBLE) {
        x_dir = -x_dir;
        y_dir = -y_dir;
    }
    if (!(breakup_mode & BREAKUP_MODE_LEFT)) {
        x_dir = -x_dir;
    }
    if (breakup_mode & BREAKUP_MODE_LOWER) {
        y_dir = -y_dir;
    }

    SDL_LockSurface( chr );
    SDL_LockSurface( dst );
    ONSBuf *chr_buf = (ONSBuf *)chr->pixels;
    ONSBuf *buffer  = (ONSBuf *)dst->pixels;
    bool *msk_buf = breakup_cellforms;

    for (int n=0; n<n_cells; ++n) {
        SDL_Rect rect = { breakup_cells[n].cell_x * BREAKUP_CELLWIDTH,
                          breakup_cells[n].cell_y * BREAKUP_CELLWIDTH, 
                          BREAKUP_CELLWIDTH, BREAKUP_CELLWIDTH };
        breakup_cells[n].state += frame_diff;
        if (breakup_cells[n].state >= (BREAKUP_MOVE_FRAMES + BREAKUP_STILL_STATE)) {
            for (int i=0; i<BREAKUP_CELLWIDTH; ++i) {
                for (int j=0; j<BREAKUP_CELLWIDTH; ++j) {
                    int x = rect.x + j;
                    int y = rect.y + i;
                    if ((x < 0) || (x >= dst->w) || (x >= chr->w) ||
                        (y < 0) || (y >= dst->h) || (y >= chr->h))
                        continue;
                    if ( breakup_mask[y*BREAKUP_CELLWIDTH*BREAKUP_MAX_CELL_X + x] )
                        buffer[y*dst->w + x] = chr_buf[y*chr->w + x];
                }
            }
        }
        else if (breakup_cells[n].state >= BREAKUP_MOVE_FRAMES) {
            breakup_cells[n].radius = breakup_cells[n].state - (BREAKUP_MOVE_FRAMES*3/4) + 1;
            for (int i=0; i<BREAKUP_CELLWIDTH; i++) {
                for (int j=0; j<BREAKUP_CELLWIDTH; j++) {
                    int x = rect.x + j;
                    int y = rect.y + i;
                    if ((x < 0) || (x >= dst->w) || (x >= chr->w) ||
                        (y < 0) || (y >= dst->h) || (y >= chr->h))
                        continue;
                    int msk_off = BREAKUP_CELLWIDTH*breakup_cells[n].radius;
                    if ( msk_buf[BREAKUP_CELLWIDTH * BREAKUP_CELLFORMS * i + msk_off + j] &&
                         breakup_mask[y*BREAKUP_CELLWIDTH*BREAKUP_MAX_CELL_X + x] )
                        buffer[y*dst->w + x] = chr_buf[y*chr->w + x];
                }
            }
        }
        else if (breakup_cells[n].state >= 0) {
            int state = breakup_cells[n].state;
            int disp_x = x_dir * breakup_disp_x[breakup_cells[n].dir] * (state-BREAKUP_MOVE_FRAMES);
            int disp_y = y_dir * breakup_disp_y[breakup_cells[n].dir] * (BREAKUP_MOVE_FRAMES-state);

            breakup_cells[n].radius = 0;
            if (breakup_cells[n].state >= (BREAKUP_MOVE_FRAMES/2))
                breakup_cells[n].radius = (breakup_cells[n].state/2) - (BREAKUP_MOVE_FRAMES/4) + 1;
            for (int i=0; i<BREAKUP_CELLWIDTH; i++) {
                for (int j=0; j<BREAKUP_CELLWIDTH; j++) {
                    int x = disp_x + rect.x + j;
                    int y = disp_y + rect.y + i;
                    if ((x < 0) || (x >= dst->w) ||
                        (y < 0) || (y >= dst->h))
                        continue;
                    if (((rect.x+j)<0) || ((rect.x+j) >= chr->w) ||
                        ((rect.y+i)<0) || ((rect.y+i) >= chr->h))
                        continue;
                    int msk_off = BREAKUP_CELLWIDTH*breakup_cells[n].radius;
                    if ( msk_buf[BREAKUP_CELLWIDTH * BREAKUP_CELLFORMS * i + msk_off + j] &&
                         breakup_mask[(rect.y+i)*BREAKUP_CELLWIDTH*BREAKUP_MAX_CELL_X + rect.x + j] )
                        buffer[y*dst->w + x] =
                            chr_buf[(rect.y+i)*chr->w + rect.x + j];
                }
            }
        }
    }

    SDL_UnlockSurface( accumulation_surface );
    SDL_UnlockSurface( chr );
}
