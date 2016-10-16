#if defined(USE_GLUT)
#else



--------------------------------------

bzip2 -> DirectReader.cpp
DirectReader.obj : error LNK2001: unresolved external symbol _BZ2_bzReadClose@8
DirectReader.obj : error LNK2001: unresolved external symbol _BZ2_bzReadGetUnused@16
DirectReader.obj : error LNK2001: unresolved external symbol _BZ2_bzRead@16
DirectReader.obj : error LNK2001: unresolved external symbol _BZ2_bzReadOpen@24

zlib -> libpng
libpng.lib(png.obj) : error LNK2001: unresolved external symbol _crc32
libpng.lib(png.obj) : error LNK2001: unresolved external symbol _inflateReset
libpng.lib(pngrutil.obj) : error LNK2001: unresolved external symbol _inflateReset
libpng.lib(pngread.obj) : error LNK2001: unresolved external symbol _inflateInit_
libpng.lib(pngread.obj) : error LNK2001: unresolved external symbol _inflate
libpng.lib(pngrutil.obj) : error LNK2001: unresolved external symbol _inflate
libpng.lib(pngread.obj) : error LNK2001: unresolved external symbol _inflateEnd

libpng -> SDL_image
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_sig_cmp
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_set_strip_16
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_set_read_fn
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_set_packing
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_set_gray_to_rgb
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_set_expand
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_read_update_info
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_read_info
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_read_image
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_get_valid
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_get_tRNS
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_get_io_ptr
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_get_IHDR
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_destroy_read_struct
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_create_read_struct
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _png_create_info_struct

jpeg -> SDL_image
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_std_error
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_start_decompress
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_resync_to_restart
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_read_scanlines
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_read_header
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_finish_decompress
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_destroy_decompress
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_CreateDecompress
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _jpeg_calc_output_dimensions

freetype -> SDL_ttf
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Init_FreeType
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Set_Pixel_Sizes
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_MulFix
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Set_Char_Size
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Open_Face
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Done_Face
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Render_Glyph
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Outline_Transform
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Load_Glyph
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Get_Char_Index
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Get_Kerning
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _FT_Done_FreeType

SDL_ttf -> FontInfo.cpp, ONScripterLabel.cpp, ONScripterLabel_text.cpp
FontInfo.obj : error LNK2001: unresolved external symbol _TTF_OpenFont
ONScripterLabel.obj : error LNK2001: unresolved external symbol _TTF_Init
ONScripterLabel.obj : error LNK2001: unresolved external symbol _TTF_GlyphMetrics
ONScripterLabel_text.obj : error LNK2001: unresolved external symbol _TTF_GlyphMetrics
ONScripterLabel_text.obj : error LNK2001: unresolved external symbol _TTF_RenderGlyph_Shaded
ONScripterLabel_text.obj : error LNK2001: unresolved external symbol _TTF_FontAscent

SDL_image -> Layer.cpp, ONScripterLabel.cpp, ONScripterLabel_image.cpp
Layer.obj : error LNK2001: unresolved external symbol _IMG_LoadJPG_RW
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _IMG_LoadJPG_RW
Layer.obj : error LNK2001: unresolved external symbol _IMG_Load_RW
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _IMG_Load_RW
ONScripterLabel.obj : error LNK2001: unresolved external symbol _IMG_Load



SDL -> SDL_image, SDL_ttf, 
	ONScripterLabel_command, ONScripterLabel_image, ONScripterLabel_text, ONScripterLabel, 
	ONScripterLabel_animation, ONScripterLabel_effect, ONScripterLabel_event,  
	ONScripterLabel_sound, ONScripterLabel_file2, ONScripterLabel_rmenu
	AnimationInfo, Layer, SDL_win32_main
SDL_image.lib(IMG_tga.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_pcx.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_lbm.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_xv.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_xpm.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_image.lib(IMG_pnm.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_FreeSurface
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_FreeSurface
ONScripterLabel_text.obj : error LNK2001: unresolved external symbol _SDL_FreeSurface
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _SDL_FreeSurface
AnimationInfo.obj : error LNK2001: unresolved external symbol _SDL_FreeSurface
Layer.obj : error LNK2001: unresolved external symbol _SDL_FreeSurface
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_FreeSurface
ONScripterLabel_animation.obj : error LNK2001: unresolved external symbol _SDL_FreeSurface
ONScripterLabel_effect.obj : error LNK2001: unresolved external symbol _SDL_UnlockSurface
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_UnlockSurface
AnimationInfo.obj : error LNK2001: unresolved external symbol _SDL_UnlockSurface
Layer.obj : error LNK2001: unresolved external symbol _SDL_UnlockSurface
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_UnlockSurface
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_UnlockSurface
ONScripterLabel_effect.obj : error LNK2001: unresolved external symbol _SDL_LockSurface
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_LockSurface
AnimationInfo.obj : error LNK2001: unresolved external symbol _SDL_LockSurface
Layer.obj : error LNK2001: unresolved external symbol _SDL_LockSurface
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_LockSurface
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_LockSurface
SDL_image.lib(IMG_lbm.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_gif.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_tga.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_xpm.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_pnm.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_pcx.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_image.lib(IMG_xv.obj) : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
AnimationInfo.obj : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
Layer.obj : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_CreateRGBSurface
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _SDL_FillRect
Layer.obj : error LNK2001: unresolved external symbol _SDL_FillRect
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_FillRect
ONScripterLabel_effect.obj : error LNK2001: unresolved external symbol _SDL_FillRect
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_FillRect
Layer.obj : error LNK2001: unresolved external symbol _SDL_MapRGB
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _SDL_MapRGB
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_UpperBlit
ONScripterLabel_text.obj : error LNK2001: unresolved external symbol _SDL_UpperBlit
Layer.obj : error LNK2001: unresolved external symbol _SDL_UpperBlit
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_UpperBlit
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_UpperBlit
ONScripterLabel_effect.obj : error LNK2001: unresolved external symbol _SDL_UpperBlit
Layer.obj : error LNK2001: unresolved external symbol _SDL_ConvertSurface
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_ConvertSurface
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_ConvertSurface
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_ConvertSurface
Layer.obj : error LNK2001: unresolved external symbol _SDL_RWFromMem
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_RWFromMem
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_WM_SetCaption
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_WM_SetCaption
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_WM_SetCaption
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_SetVideoMode
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_GetVideoInfo
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_WM_SetIcon
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_GetWMInfo
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_GetWMInfo
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_EnableUNICODE
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_InitSubSystem
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_GetError
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_GetError
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_GetError
SDL_win32_main.obj : error LNK2001: unresolved external symbol _SDL_GetError
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _SDL_GetError
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_Init
SDL_win32_main.obj : error LNK2001: unresolved external symbol _SDL_Init
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_Quit
SDL_win32_main.obj : error LNK2001: unresolved external symbol _SDL_Quit
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_GetTicks
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_GetTicks
ONScripterLabel_effect.obj : error LNK2001: unresolved external symbol _SDL_GetTicks
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_GetTicks
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_CDClose
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_CDStatus
ONScripterLabel_sound.obj : error LNK2001: unresolved external symbol _SDL_CDStatus
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_CDOpen
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_CDNumDrives
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_SetAlpha
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_SetAlpha
ONScripterLabel_file2.obj : error LNK2001: unresolved external symbol _SDL_SetAlpha
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_UpdateRect
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_UpdateRect
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_UpdateRect
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_UpdateRects
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_PeepEvents
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_PeepEvents
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_PumpEvents
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_GetMouseState
ONScripterLabel.obj : error LNK2001: unresolved external symbol _SDL_CDStop
ONScripterLabel_sound.obj : error LNK2001: unresolved external symbol _SDL_CDStop
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_SaveBMP_RW
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_RWFromFile
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _SDL_RWFromFile
SDL_image.lib(IMG.obj) : error LNK2001: unresolved external symbol _SDL_RWFromFile
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_PollEvent
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_PollEvent
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_AddTimer
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_AddTimer
ONScripterLabel_sound.obj : error LNK2001: unresolved external symbol _SDL_AddTimer
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_WarpMouse
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_WarpMouse
ONScripterLabel_rmenu.obj : error LNK2001: unresolved external symbol _SDL_WarpMouse
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_ShowCursor
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_WM_IconifyWindow
ONScripterLabel_command.obj : error LNK2001: unresolved external symbol _SDL_MapRGBA
ONScripterLabel_effect.obj : error LNK2001: unresolved external symbol _SDL_MapRGBA
ONScripterLabel_image.obj : error LNK2001: unresolved external symbol _SDL_MapRGBA
ONScripterLabel_effect.obj : error LNK2001: unresolved external symbol _SDL_Delay
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_Delay
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_PushEvent
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_RemoveTimer
ONScripterLabel_event.obj : error LNK2001: unresolved external symbol _SDL_WaitEvent
ONScripterLabel_sound.obj : error LNK2001: unresolved external symbol _SDL_CDPlayTracks
SDL_win32_main.obj : error LNK2001: unresolved external symbol _SDL_SetModuleHandle
SDL_win32_main.obj : error LNK2001: unresolved external symbol _SDL_strlcpy
SDL_win32_main.obj : error LNK2001: unresolved external symbol _SDL_strlcat
SDL_image.lib(IMG_lbm.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_gif.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_tga.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_xpm.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_pnm.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_pcx.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_jpg.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_xv.obj) : error LNK2001: unresolved external symbol _SDL_SetError
SDL_image.lib(IMG_gif.obj) : error LNK2001: unresolved external symbol _SDL_SetColorKey
SDL_image.lib(IMG_tga.obj) : error LNK2001: unresolved external symbol _SDL_SetColorKey
SDL_ttf.lib(SDL_ttf.obj) : error LNK2001: unresolved external symbol _SDL_SetColorKey
SDL_image.lib(IMG_xpm.obj) : error LNK2001: unresolved external symbol _SDL_SetColorKey
SDL_image.lib(IMG_png.obj) : error LNK2001: unresolved external symbol _SDL_SetColorKey
SDL_image.lib(IMG_lbm.obj) : error LNK2001: unresolved external symbol _SDL_SetColorKey
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_ReadLE16
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_ReadLE32
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_Error
SDL_image.lib(IMG_bmp.obj) : error LNK2001: unresolved external symbol _SDL_ClearError


--------------------------------------


SDL_FreeSurface
SDL_UnlockSurface
SDL_LockSurface
SDL_CreateRGBSurface
SDL_ConvertSurface
SDL_FillRect
SDL_UpperBlit
SDL_SetVideoMode
SDL_GetVideoInfo
SDL_UpdateRect
SDL_SaveBMP_RW
SDL_MapRGBA
SDL_MapRGB
SDL_SetColorKey
SDL_SetAlpha

SDL_GetMouseState
SDL_WarpMouse
SDL_ShowCursor

SDL_RWFromMem
SDL_RWFromFile

SDL_Delay
SDL_RemoveTimer
SDL_AddTimer

SDL_PushEvent
SDL_WaitEvent
SDL_PollEvent
SDL_PeepEvents
SDL_PumpEvents

SDL_WM_SetCaption
SDL_WM_SetIcon
SDL_WM_IconifyWindow

SDL_GetWMInfo
SDL_EnableUNICODE
SDL_InitSubSystem
SDL_Init
SDL_Quit
SDL_GetTicks
SDL_GetError
SDL_Error(*)
SDL_ClearError(*)
SDL_SetError(*)
SDL_SetModuleHandle(*)
SDL_strlcpy(*)
SDL_strlcat(*)
SDL_ReadLE16(*)
SDL_ReadLE32(*)

SDL_CDClose
SDL_CDStatus
SDL_CDOpen
SDL_CDNumDrives
SDL_CDStop
SDL_CDPlayTracks


