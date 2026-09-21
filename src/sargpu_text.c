/* SarGPU text module. Compiled through sargpu.c; do not compile separately. */
/* Bundled stb_truetype configuration (public domain/MIT). */
#ifndef __INTELLISENSE__
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif
static double mr_tt_fmod(double x,double y){return x-(long long)(x/y)*y;}
static double mr_tt_acos(double x){double negate=x<0?-1.0:1.0;if(x<0)x=-x;double r=-0.0187293;r=r*x+0.0742610;r=r*x-0.2121144;r=r*x+1.5707288;r=r*sqrtf((float)(1.0-x));return negate<0?3.141592653589793-r:r;}
static double mr_tt_pow(double x,double y){if(x<=0)return 0;if(y>0.32&&y<0.34){double r=x>1?x:1;for(int i=0;i<12;i++)r=(2*r+x/(r*r))/3;return r;}return x;}
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_malloc(x,u) ((void)(u),MemAlloc((unsigned int)(x)))
#define STBTT_free(x,u) ((void)(u),MemFree(x))
#define STBTT_assert(x) ((void)0)
#define STBTT_strlen(x) ((int)TextLength(x))
#define STBTT_memcpy memcpy
#define STBTT_memset memset
#define STBTT_ifloor(x) ((int)__builtin_floor(x))
#define STBTT_iceil(x) ((int)__builtin_ceil(x))
#define STBTT_sqrt(x) sqrtf((float)(x))
#define STBTT_pow(x,y) mr_tt_pow((x),(y))
#define STBTT_fmod(x,y) mr_tt_fmod((x),(y))
#define STBTT_cos(x) cosf((float)(x))
#define STBTT_acos(x) mr_tt_acos(x)
#define STBTT_fabs(x) ((x)<0?-(x):(x))
#include "external/stb_truetype.h"

#undef STB_TRUETYPE_IMPLEMENTATION
#undef STBTT_STATIC
#undef STBTT_malloc
#undef STBTT_free
#undef STBTT_assert
#undef STBTT_strlen
#undef STBTT_memcpy
#undef STBTT_memset
#undef STBTT_ifloor
#undef STBTT_iceil
#undef STBTT_sqrt
#undef STBTT_pow
#undef STBTT_fmod
#undef STBTT_cos
#undef STBTT_acos
#undef STBTT_fabs
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif /* __INTELLISENSE__ */
/* End stb_truetype configuration. */


/* Original 5x7 font. Lowercase maps to uppercase; unsupported characters use ?. */
static const unsigned char mr_font[][7]={
    {14,17,19,21,25,17,14},{4,12,4,4,4,4,14},{14,17,1,2,4,8,31},{30,1,1,14,1,1,30},
    {2,6,10,18,31,2,2},{31,16,16,30,1,1,30},{14,16,16,30,17,17,14},{31,1,2,4,8,8,8},
    {14,17,17,14,17,17,14},{14,17,17,15,1,1,14},
    {14,17,17,31,17,17,17},{30,17,17,30,17,17,30},{14,17,16,16,16,17,14},{30,17,17,17,17,17,30},
    {31,16,16,30,16,16,31},{31,16,16,30,16,16,16},{14,17,16,23,17,17,15},{17,17,17,31,17,17,17},
    {14,4,4,4,4,4,14},{7,2,2,2,2,18,12},{17,18,20,24,20,18,17},{16,16,16,16,16,16,31},
    {17,27,21,21,17,17,17},{17,25,21,19,17,17,17},{14,17,17,17,17,17,14},{30,17,17,30,16,16,16},
    {14,17,17,17,21,18,13},{30,17,17,30,20,18,17},{15,16,16,14,1,1,30},{31,4,4,4,4,4,4},
    {17,17,17,17,17,17,14},{17,17,17,17,17,10,4},{17,17,17,21,21,21,10},{17,17,10,4,10,17,17},
    {17,17,10,4,4,4,4},{31,1,2,4,8,16,31},
    {0,0,4,0,4,0,0},{0,0,0,0,0,6,6},{0,0,0,31,0,0,0},{1,2,2,4,8,8,16},
    {0,4,4,31,4,4,0},{14,17,1,2,4,0,4},{4,4,4,4,4,0,4},
    {0,0,0,0,6,4,8},{24,25,2,4,8,19,3},{12,18,20,8,21,18,13},
    {2,4,8,8,8,4,2},{8,4,2,2,2,4,8},{0,0,31,0,31,0,0},
    {2,4,8,16,8,4,2},{8,4,2,1,2,4,8},{0,0,0,0,0,0,31},
    {4,4,4,4,4,4,4},{4,4,0,0,0,0,0},{10,31,10,10,31,10,0}
};
static int mr_builtin_glyph(unsigned char c){
    if(c>='a'&&c<='z')c-=32;if(c>='0'&&c<='9')return c-'0';if(c>='A'&&c<='Z')return c-'A'+10;
    switch(c){case ':':return 36;case '.':return 37;case '-':return 38;case '/':return 39;case '+':return 40;case '!':return 42;case ',':return 43;case '%':return 44;case '&':return 45;case '(':return 46;case ')':return 47;case '=':return 48;case '<':return 49;case '>':return 50;case '_':return 51;case '|':return 52;case '\'':return 53;case '#':return 54;default:return 41;}
}
void DrawText(const char *text,int x,int y,int fontSize,Color color) {
    if (!text || fontSize<=0) return;
    float scale=fontSize/7.0f,px=(float)x,py=(float)y;
    for (;*text;text++) {
        unsigned char c=(unsigned char)*text;
        if (c=='\n') { px=(float)x; py+=fontSize+scale*2; continue; }
        int index=mr_builtin_glyph(c);
        if (c!=' ') for (int row=0;row<7;row++) for (int col=0;col<5;col++)
            if (mr_font[index][row] & (1<<(4-col))) mr_quad(px+col*scale,py+row*scale,scale,scale,color,mr.white);
        px+=scale*6;
    }
}
int MeasureText(const char *text,int fontSize) {
    if (!text || fontSize<=0) return 0;
    int line=0,longest=0;
    for (;*text;text++) {
        if (*text=='\n') { if (line>longest) longest=line; line=0; }
        else line++;
    }
    if (line>longest) longest=line;
    return (int)(longest*(fontSize/7.0f)*6.0f+0.5f);
}
static int mr_text_line_spacing;
Font GetFontDefault(void) { return (Font){7,0,0,{mr.white,1,1,1,7},NULL,NULL}; }
bool IsFontValid(Font font) { return font.baseSize>0 && ((font.glyphCount==0&&font.texture.id==mr.white)||(font.glyphCount>0&&font.recs&&font.glyphs&&IsTextureValid(font.texture))); }
GlyphInfo *LoadFontData(const unsigned char *data,int dataSize,int fontSize,int *codepoints,int count,int type){
    if(!data||dataSize<=0||fontSize<=0)return NULL;if(count<=0)count=95;int offset=stbtt_GetFontOffsetForIndex(data,0);stbtt_fontinfo info;if(offset<0||!stbtt_InitFont(&info,data,offset))return NULL;
    GlyphInfo *glyphs=MemAlloc((unsigned int)count*sizeof *glyphs);if(!glyphs)return NULL;memset(glyphs,0,(size_t)count*sizeof *glyphs);float scale=stbtt_ScaleForPixelHeight(&info,(float)fontSize);int ascent=0;stbtt_GetFontVMetrics(&info,&ascent,NULL,NULL);
    for(int i=0;i<count;i++){int cp=codepoints?codepoints[i]:32+i,w=0,h=0,xoff=0,yoff=0,advance=0,bearing=0;unsigned char *alpha=NULL;if(type==FONT_SDF)alpha=stbtt_GetCodepointSDF(&info,scale,cp,4,128,64.0f,&w,&h,&xoff,&yoff);else alpha=stbtt_GetCodepointBitmap(&info,0,scale,cp,&w,&h,&xoff,&yoff);stbtt_GetCodepointHMetrics(&info,cp,&advance,&bearing);(void)bearing;glyphs[i]=(GlyphInfo){cp,xoff,(int)(ascent*scale)+yoff,(int)(advance*scale+0.5f),(Image){0}};
        if(w>0&&h>0&&alpha){Color *pixels=MemAlloc((unsigned int)((size_t)w*h*4));if(!pixels){if(type==FONT_SDF)stbtt_FreeSDF(alpha,NULL);else stbtt_FreeBitmap(alpha,NULL);UnloadFontData(glyphs,count);return NULL;}for(int p=0;p<w*h;p++){unsigned char a=alpha[p];if(type==FONT_BITMAP)a=a<80?0:255;pixels[p]=(Color){255,255,255,a};}glyphs[i].image=(Image){pixels,w,h,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};}
        if(alpha){if(type==FONT_SDF)stbtt_FreeSDF(alpha,NULL);else stbtt_FreeBitmap(alpha,NULL);}
    }return glyphs;
}
void UnloadFontData(GlyphInfo *glyphs,int count){if(!glyphs)return;for(int i=0;i<count;i++)if(IsImageValid(glyphs[i].image))UnloadImage(glyphs[i].image);MemFree(glyphs);}
Image GenImageFontAtlas(const GlyphInfo *glyphs,Rectangle **glyphRecs,int count,int fontSize,int padding,int packMethod){
    (void)fontSize;if(glyphRecs)*glyphRecs=NULL;if(!glyphs||count<=0||padding<0)return(Image){0};int side=64;long long area=0;for(int i=0;i<count;i++)area+=(long long)(glyphs[i].image.width+padding*2)*(glyphs[i].image.height+padding*2);while(side<4096&&(long long)side*side<area*2)side*=2;Rectangle *recs=MemAlloc((unsigned int)count*sizeof *recs);int *order=MemAlloc((unsigned int)count*sizeof *order);if(!recs||!order){MemFree(recs);MemFree(order);return(Image){0};}for(int i=0;i<count;i++)order[i]=i;if(packMethod!=0)for(int i=1;i<count;i++){int value=order[i],j=i-1;while(j>=0&&glyphs[order[j]].image.height<glyphs[value].image.height){order[j+1]=order[j];j--;}order[j+1]=value;}Image atlas={0};
    for(;side<=4096;side*=2){atlas=GenImageColor(side,side,BLANK);if(!atlas.data)break;int x=padding,y=padding,row=0;bool fits=true;for(int i=0;i<count;i++){int index=order[i],w=glyphs[index].image.width,h=glyphs[index].image.height;if(x+w+padding>side){x=padding;y+=row+padding;row=0;}if(y+h+padding>side){fits=false;break;}recs[index]=(Rectangle){(float)x,(float)y,(float)w,(float)h};if(w>0&&h>0)for(int py=0;py<h;py++)memcpy((Color*)atlas.data+(size_t)(y+py)*side+x,(Color*)glyphs[index].image.data+(size_t)py*w,(size_t)w*4);x+=w+padding;if(h>row)row=h;}if(fits){MemFree(order);if(glyphRecs)*glyphRecs=recs;else MemFree(recs);return atlas;}UnloadImage(atlas);atlas=(Image){0};}
    MemFree(order);MemFree(recs);return(Image){0};
}
Font LoadFontFromMemory(const char *fileType,const unsigned char *data,int dataSize,int fontSize,int *codepoints,int count) {
    (void)fileType;if(count<=0)count=95;GlyphInfo *glyphs=LoadFontData(data,dataSize,fontSize,codepoints,count,FONT_DEFAULT);if(!glyphs)return(Font){0};Rectangle *recs=NULL;Image atlas=GenImageFontAtlas(glyphs,&recs,count,fontSize,2,0);if(!IsImageValid(atlas)){UnloadFontData(glyphs,count);return(Font){0};}Texture2D texture=LoadTextureFromImage(atlas);UnloadImage(atlas);if(!IsTextureValid(texture)){MemFree(recs);UnloadFontData(glyphs,count);return(Font){0};}return(Font){fontSize,count,2,texture,recs,glyphs};
}
Font LoadFontFromImage(Image image,Color key,int firstChar){
    if(!IsImageValid(image))return(Font){0};Color *pixels=image.data;int charSpacing=0,lineSpacing=0;bool found=false;for(int y=0;y<image.height&&!found;y++)for(int x=0;x<image.width;x++)if(!ColorIsEqual(pixels[(size_t)y*image.width+x],key)){charSpacing=x;lineSpacing=y;found=true;break;}if(!found||charSpacing<=0||lineSpacing<=0)return(Font){0};int glyphHeight=0;while(lineSpacing+glyphHeight<image.height&&!ColorIsEqual(pixels[(size_t)(lineSpacing+glyphHeight)*image.width+charSpacing],key))glyphHeight++;if(glyphHeight<=0)return(Font){0};int count=0;for(int y=lineSpacing;y+glyphHeight<=image.height;y+=glyphHeight+lineSpacing){int x=charSpacing;while(x<image.width&&!ColorIsEqual(pixels[(size_t)y*image.width+x],key)){count++;while(x<image.width&&!ColorIsEqual(pixels[(size_t)y*image.width+x],key))x++;x+=charSpacing;}}if(count<=0)return(Font){0};Rectangle *recs=MemAlloc((unsigned int)count*sizeof *recs);GlyphInfo *glyphs=MemAlloc((unsigned int)count*sizeof *glyphs);if(!recs||!glyphs){MemFree(recs);MemFree(glyphs);return(Font){0};}memset(glyphs,0,(size_t)count*sizeof *glyphs);int index=0;for(int y=lineSpacing;y+glyphHeight<=image.height&&index<count;y+=glyphHeight+lineSpacing){int x=charSpacing;while(x<image.width&&!ColorIsEqual(pixels[(size_t)y*image.width+x],key)&&index<count){int start=x;while(x<image.width&&!ColorIsEqual(pixels[(size_t)y*image.width+x],key))x++;recs[index]=(Rectangle){(float)start,(float)y,(float)(x-start),(float)glyphHeight};glyphs[index]=(GlyphInfo){firstChar+index,0,0,0,ImageFromImage(image,recs[index])};index++;x+=charSpacing;}}Image atlas=ImageCopy(image);ImageColorReplace(&atlas,key,BLANK);Texture2D texture=LoadTextureFromImage(atlas);UnloadImage(atlas);if(!IsTextureValid(texture)){MemFree(recs);UnloadFontData(glyphs,count);return(Font){0};}return(Font){glyphHeight,count,0,texture,recs,glyphs};
}
Font LoadFontEx(const char *fileName,int fontSize,int *codepoints,int count){int size=0;unsigned char*data=LoadFileData(fileName,&size);if(!data)return(Font){0};Font font=LoadFontFromMemory(GetFileExtension(fileName),data,size,fontSize,codepoints,count);UnloadFileData(data);return font;}
Font LoadFont(const char *fileName){return LoadFontEx(fileName,32,NULL,0);}
static void mr_font_write_int(MRWriteBuffer *out,int value){if(value<0){mr_image_write(out,"-",1);value=-value;}mr_write_uint(out,(unsigned)value);}
static void mr_font_write_text(MRWriteBuffer *out,const char *value){mr_image_write(out,(void*)value,(int)TextLength(value));}
bool ExportFontAsCode(Font font,const char *fileName){
    if(!IsFontValid(font)||font.glyphCount<=0||!fileName)return false;Image atlas=LoadImageFromTexture(font.texture);if(!IsImageValid(atlas))return false;MRWriteBuffer out={0};mr_font_write_text(&out,"/* SarGPU font data */\n#include \"sargpu.h\"\n\n#define FONT_BASE_SIZE ");mr_write_uint(&out,(unsigned)font.baseSize);mr_font_write_text(&out,"\n#define FONT_GLYPH_COUNT ");mr_write_uint(&out,(unsigned)font.glyphCount);mr_font_write_text(&out,"\n#define FONT_ATLAS_WIDTH ");mr_write_uint(&out,(unsigned)atlas.width);mr_font_write_text(&out,"\n#define FONT_ATLAS_HEIGHT ");mr_write_uint(&out,(unsigned)atlas.height);mr_font_write_text(&out,"\n#define FONT_GLYPH_PADDING ");mr_write_uint(&out,(unsigned)font.glyphPadding);mr_font_write_text(&out,"\nstatic const Rectangle FONT_RECS[] = {\n");
    for(int i=0;i<font.glyphCount;i++){mr_font_write_text(&out,"    { ");mr_write_uint(&out,(unsigned)font.recs[i].x);mr_font_write_text(&out,", ");mr_write_uint(&out,(unsigned)font.recs[i].y);mr_font_write_text(&out,", ");mr_write_uint(&out,(unsigned)font.recs[i].width);mr_font_write_text(&out,", ");mr_write_uint(&out,(unsigned)font.recs[i].height);mr_font_write_text(&out," },\n");}mr_font_write_text(&out,"};\nstatic const int FONT_GLYPHS[][4] = {\n");
    for(int i=0;i<font.glyphCount;i++){GlyphInfo g=font.glyphs[i];mr_font_write_text(&out,"    { ");mr_font_write_int(&out,g.value);mr_font_write_text(&out,", ");mr_font_write_int(&out,g.offsetX);mr_font_write_text(&out,", ");mr_font_write_int(&out,g.offsetY);mr_font_write_text(&out,", ");mr_font_write_int(&out,g.advanceX);mr_font_write_text(&out," },\n");}mr_font_write_text(&out,"};\nstatic const unsigned char FONT_ATLAS_RGBA[] = {\n");size_t bytes=(size_t)atlas.width*atlas.height*4;const char hex[]="0123456789abcdef";unsigned char *p=atlas.data;for(size_t i=0;i<bytes;i++){char value[5]={'0','x',hex[p[i]>>4],hex[p[i]&15],','};mr_image_write(&out,value,5);if((i&15)==15)mr_font_write_text(&out,"\n");}mr_font_write_text(&out,"\n};\n");bool ok=!out.failed&&SaveFileData(fileName,out.data,out.size);MemFree(out.data);UnloadImage(atlas);return ok;
}
void UnloadFont(Font font){if(font.glyphCount<=0)return;UnloadTexture(font.texture);MemFree(font.recs);UnloadFontData(font.glyphs,font.glyphCount);}
int GetGlyphIndex(Font font,int codepoint){if(!font.glyphs)return 0;int fallback=0;for(int i=0;i<font.glyphCount;i++){if(font.glyphs[i].value==codepoint)return i;if(font.glyphs[i].value=='?')fallback=i;}return fallback;}
GlyphInfo GetGlyphInfo(Font font,int codepoint){return font.glyphs&&font.glyphCount>0?font.glyphs[GetGlyphIndex(font,codepoint)]:(GlyphInfo){0};}
Rectangle GetGlyphAtlasRec(Font font,int codepoint){return font.recs&&font.glyphCount>0?font.recs[GetGlyphIndex(font,codepoint)]:(Rectangle){0};}
static void mr_draw_custom_text(Font font,const char *text,Vector2 position,Vector2 origin,float rotation,float size,float spacing,Color tint){if(!text||!IsFontValid(font)||size<=0)return;float angle=rotation*MR_DEG2RAD,c=cosf(angle),s=sinf(angle);if(font.glyphCount==0){float scale=size/7.0f,x=0,y=0;Texture2D white={mr.white,1,1,1,7};while(*text){unsigned char ch=(unsigned char)*text++;if(ch=='\n'){x=0;y+=size+(mr_text_line_spacing>0?mr_text_line_spacing:size*.5f);continue;}int index=mr_builtin_glyph(ch);if(ch!=' ')for(int row=0;row<7;row++)for(int col=0;col<5;col++)if(mr_font[index][row]&(1<<(4-col))){float lx=x+col*scale-origin.x,ly=y+row*scale-origin.y;Rectangle dst={position.x+lx*c-ly*s,position.y+lx*s+ly*c,scale,scale};DrawTexturePro(white,(Rectangle){0,0,1,1},dst,(Vector2){0},rotation,tint);}x+=scale*6+spacing;}return;}float scale=size/font.baseSize,x=0,y=0;while(*text){int bytes=0,cp=GetCodepoint(text,&bytes);if(bytes<1)bytes=1;text+=bytes;if(cp=='\n'){x=0;y+=size+(mr_text_line_spacing>0?mr_text_line_spacing:size*.5f);continue;}int index=GetGlyphIndex(font,cp);GlyphInfo glyph=font.glyphs[index];Rectangle src=font.recs[index];float lx=x+glyph.offsetX*scale-origin.x,ly=y+glyph.offsetY*scale-origin.y;Rectangle dst={position.x+lx*c-ly*s,position.y+lx*s+ly*c,src.width*scale,src.height*scale};if(src.width>0&&src.height>0)DrawTexturePro(font.texture,src,dst,(Vector2){0},rotation,tint);x+=(glyph.advanceX?glyph.advanceX:(int)src.width)*scale+spacing;}}
void DrawTextEx(Font font,const char *text,Vector2 position,float size,float spacing,Color tint){mr_draw_custom_text(font,text,position,(Vector2){0},0,size,spacing,tint);}
void DrawTextPro(Font font,const char *text,Vector2 position,Vector2 origin,float rotation,float size,float spacing,Color tint){mr_draw_custom_text(font,text,position,origin,rotation,size,spacing,tint);}
void DrawTextCodepoint(Font font,int codepoint,Vector2 position,float size,Color tint){int bytes=0;const char*text=CodepointToUTF8(codepoint,&bytes);DrawTextEx(font,text,position,size,0,tint);}
void DrawTextCodepoints(Font font,const int*points,int count,Vector2 position,float size,float spacing,Color tint){if(!points)return;float x=position.x;for(int i=0;i<count;i++){DrawTextCodepoint(font,points[i],(Vector2){x,position.y},size,tint);GlyphInfo glyph=GetGlyphInfo(font,points[i]);x+=(glyph.advanceX?glyph.advanceX:font.baseSize)*size/font.baseSize+spacing;}}
Vector2 MeasureTextEx(Font font,const char*text,float size,float spacing){if(!text||size<=0)return(Vector2){0};if(font.glyphCount==0)return(Vector2){(float)MeasureText(text,(int)size),size};float scale=size/font.baseSize,x=0,maxX=0,y=size;while(*text){int bytes=0,cp=GetCodepoint(text,&bytes);if(bytes<1)bytes=1;text+=bytes;if(cp=='\n'){if(x>maxX)maxX=x;x=0;y+=size+(mr_text_line_spacing>0?mr_text_line_spacing:size*.5f);continue;}GlyphInfo glyph=GetGlyphInfo(font,cp);x+=(glyph.advanceX?glyph.advanceX:font.baseSize)*scale+spacing;}if(x>maxX)maxX=x;if(maxX>0)maxX-=spacing;return(Vector2){maxX,y};}
void SetTextLineSpacing(int spacing){mr_text_line_spacing=spacing>0?spacing:0;}
static float mr_clamp01(float value) { return value<0 ? 0 : value>1 ? 1 : value; }
static unsigned char mr_byte(float value) {
    if (value<0) value=0; if (value>255) value=255;
    return (unsigned char)(value+0.5f);
}
bool ColorIsEqual(Color a,Color b) { return a.r==b.r && a.g==b.g && a.b==b.b && a.a==b.a; }
Color Fade(Color color,float alpha) { color.a=mr_byte(mr_clamp01(alpha)*255); return color; }
int ColorToInt(Color c) { return (int)(((unsigned int)c.r<<24)|((unsigned int)c.g<<16)|((unsigned int)c.b<<8)|c.a); }
Vector4 ColorNormalize(Color c) { return (Vector4){c.r/255.0f,c.g/255.0f,c.b/255.0f,c.a/255.0f}; }
Color ColorFromNormalized(Vector4 n) { return (Color){mr_byte(n.x*255),mr_byte(n.y*255),mr_byte(n.z*255),mr_byte(n.w*255)}; }
Vector3 ColorToHSV(Color c) {
    float r=c.r/255.0f,g=c.g/255.0f,b=c.b/255.0f;
    float max=mr_max(r,mr_max(g,b)),min=mr_min(r,mr_min(g,b)),delta=max-min,h=0;
    if (delta>0.000001f) {
        if (max==r) { h=60*(g-b)/delta; if (h<0) h+=360; }
        else if (max==g) h=60*((b-r)/delta+2);
        else h=60*((r-g)/delta+4);
    }
    return (Vector3){h,max>0 ? delta/max : 0,max};
}
Color ColorFromHSV(float hue,float saturation,float value) {
    while (hue<0) hue+=360; while (hue>=360) hue-=360;
    saturation=mr_clamp01(saturation); value=mr_clamp01(value);
    float chroma=value*saturation,x=chroma*(1-((int)(hue/60)%2 ? (hue/60-(int)(hue/60)) : 1-(hue/60-(int)(hue/60)))),m=value-chroma;
    float r=0,g=0,b=0;
    int sector=(int)(hue/60);
    if (sector==0) { r=chroma; g=x; } else if (sector==1) { r=x; g=chroma; }
    else if (sector==2) { g=chroma; b=x; } else if (sector==3) { g=x; b=chroma; }
    else if (sector==4) { r=x; b=chroma; } else { r=chroma; b=x; }
    return (Color){mr_byte((r+m)*255),mr_byte((g+m)*255),mr_byte((b+m)*255),255};
}
Color ColorTint(Color c,Color tint) { return (Color){(unsigned char)(c.r*tint.r/255),(unsigned char)(c.g*tint.g/255),(unsigned char)(c.b*tint.b/255),(unsigned char)(c.a*tint.a/255)}; }
Color ColorBrightness(Color c,float factor) {
    factor=factor<-1 ? -1 : factor>1 ? 1 : factor;
    if (factor<0) { c.r=mr_byte(c.r*(1+factor)); c.g=mr_byte(c.g*(1+factor)); c.b=mr_byte(c.b*(1+factor)); }
    else { c.r=mr_byte(c.r+(255-c.r)*factor); c.g=mr_byte(c.g+(255-c.g)*factor); c.b=mr_byte(c.b+(255-c.b)*factor); }
    return c;
}
Color ColorContrast(Color c,float contrast) {
    contrast=contrast<-1 ? -1 : contrast>1 ? 1 : contrast;
    float f=(1+contrast)*(1+contrast);
    c.r=mr_byte((((c.r/255.0f)-0.5f)*f+0.5f)*255);
    c.g=mr_byte((((c.g/255.0f)-0.5f)*f+0.5f)*255);
    c.b=mr_byte((((c.b/255.0f)-0.5f)*f+0.5f)*255); return c;
}
Color ColorAlpha(Color color,float alpha) { return Fade(color,alpha); }
Color ColorAlphaBlend(Color dst,Color src,Color tint) {
    src=ColorTint(src,tint); float a=src.a/255.0f,da=dst.a/255.0f,outA=a+da*(1-a);
    if (outA<=0) return BLANK;
    return (Color){mr_byte((src.r*a+dst.r*da*(1-a))/outA),mr_byte((src.g*a+dst.g*da*(1-a))/outA),
        mr_byte((src.b*a+dst.b*da*(1-a))/outA),mr_byte(outA*255)};
}
Color ColorLerp(Color a,Color b,float factor) {
    factor=mr_clamp01(factor); return (Color){mr_byte(a.r+(b.r-a.r)*factor),mr_byte(a.g+(b.g-a.g)*factor),
        mr_byte(a.b+(b.b-a.b)*factor),mr_byte(a.a+(b.a-a.a)*factor)};
}
Color GetColor(unsigned int value) { return (Color){value>>24,value>>16,value>>8,value}; }
int GetCodepointNext(const char *text,int *size) {
    if (size) *size=0; if (!text || !*text) return 0;
    const unsigned char *s=(const unsigned char *)text; int cp=0,length=1;
    if (s[0]<0x80) cp=s[0];
    else if ((s[0]&0xe0)==0xc0 && (s[1]&0xc0)==0x80) { cp=((s[0]&31)<<6)|(s[1]&63); length=2; if (cp<0x80) cp='?'; }
    else if ((s[0]&0xf0)==0xe0 && (s[1]&0xc0)==0x80 && (s[2]&0xc0)==0x80) { cp=((s[0]&15)<<12)|((s[1]&63)<<6)|(s[2]&63); length=3; if (cp<0x800 || (cp>=0xd800 && cp<=0xdfff)) cp='?'; }
    else if ((s[0]&0xf8)==0xf0 && (s[1]&0xc0)==0x80 && (s[2]&0xc0)==0x80 && (s[3]&0xc0)==0x80) { cp=((s[0]&7)<<18)|((s[1]&63)<<12)|((s[2]&63)<<6)|(s[3]&63); length=4; if (cp<0x10000 || cp>0x10ffff) cp='?'; }
    else cp='?';
    if (size) *size=length; return cp;
}
int GetCodepoint(const char *text,int *size) { return GetCodepointNext(text,size); }
int GetCodepointPrevious(const char *text,int *size) {
    if (size) *size=0; if (!text) return 0;
    int length=1; while (length<4 && (((const unsigned char *)text)[-length]&0xc0)==0x80) length++;
    int decoded=0,actual=0; decoded=GetCodepointNext(text-length,&actual);
    if (size) *size=length; return actual==length ? decoded : '?';
}
const char *CodepointToUTF8(int cp,int *size) {
    static char text[5]; int n=0;
    if (cp<0 || cp>0x10ffff || (cp>=0xd800 && cp<=0xdfff)) cp='?';
    if (cp<=0x7f) text[n++]=(char)cp;
    else if (cp<=0x7ff) { text[n++]=(char)(0xc0|(cp>>6)); text[n++]=(char)(0x80|(cp&63)); }
    else if (cp<=0xffff) { text[n++]=(char)(0xe0|(cp>>12)); text[n++]=(char)(0x80|((cp>>6)&63)); text[n++]=(char)(0x80|(cp&63)); }
    else { text[n++]=(char)(0xf0|(cp>>18)); text[n++]=(char)(0x80|((cp>>12)&63)); text[n++]=(char)(0x80|((cp>>6)&63)); text[n++]=(char)(0x80|(cp&63)); }
    text[n]=0; if (size) *size=n; return text;
}
int GetCodepointCount(const char *text) { int count=0,size; if (!text) return 0; while (*text) { GetCodepointNext(text,&size); text+=size; count++; } return count; }
int *LoadCodepoints(const char *text,int *count) {
    int total=GetCodepointCount(text); if (count) *count=total;
    if (!total) return NULL; int *result=MemAlloc((unsigned int)total*sizeof *result); if (!result) { if (count) *count=0; return NULL; }
    for (int i=0,size;i<total;i++) { result[i]=GetCodepointNext(text,&size); text+=size; } return result;
}
void UnloadCodepoints(int *codepoints) { MemFree(codepoints); }
char *LoadUTF8(const int *codepoints,int length) {
    if (!codepoints || length<=0) return NULL; char *out=MemAlloc((unsigned int)length*4+1); if (!out) return NULL;
    int position=0; for (int i=0;i<length;i++) { int size; const char *encoded=CodepointToUTF8(codepoints[i],&size); memcpy(out+position,encoded,(size_t)size); position+=size; }
    out[position]=0; return out;
}
void UnloadUTF8(char *text) { MemFree(text); }
#include <stdarg.h>

#define MR_TEXTFORMAT_BUFFERS 4
#define MR_TEXTFORMAT_BUFFER_SIZE 1024
static char mr_textformat_buffers[MR_TEXTFORMAT_BUFFERS][MR_TEXTFORMAT_BUFFER_SIZE];
static int mr_textformat_index;

#if defined(__wasm__)
static void mr_format_char(char *out,int *length,char value){if(*length<MR_TEXTFORMAT_BUFFER_SIZE-1)out[(*length)++]=value;}
static void mr_format_repeat(char *out,int *length,char value,int count){while(count-->0)mr_format_char(out,length,value);}
static int mr_format_unsigned(char *out,unsigned long long value,unsigned int base,bool upper){
    char reverse[65];int count=0;if(value==0)reverse[count++]='0';
    while(value&&count<(int)sizeof reverse){unsigned int digit=(unsigned int)(value%base);reverse[count++]=(char)(digit<10?'0'+digit:(upper?'A':'a')+digit-10);value/=base;}
    for(int i=0;i<count;i++)out[i]=reverse[count-i-1];return count;
}
static int mr_format_float(char *out,double value,int precision){
    int length=0;if(precision<0)precision=6;if(precision>18)precision=18;
    if(value!=value){out[0]='n';out[1]='a';out[2]='n';return 3;}
    if(value<0){out[length++]='-';value=-value;}
    if(value>18446744073709551615.0){out[length++]='i';out[length++]='n';out[length++]='f';return length;}
    double rounding=0.5;for(int i=0;i<precision;i++)rounding*=0.1;value+=rounding;
    unsigned long long whole=(unsigned long long)value;char digits[65];int count=mr_format_unsigned(digits,whole,10,false);
    for(int i=0;i<count;i++)out[length++]=digits[i];
    if(precision>0){out[length++]='.';double fraction=value-(double)whole;for(int i=0;i<precision;i++){fraction*=10.0;int digit=(int)fraction;if(digit<0)digit=0;if(digit>9)digit=9;out[length++]=(char)('0'+digit);fraction-=digit;}}
    return length;
}
static void mr_web_text_format(char *out,const char *format,va_list args){
    int length=0;while(format&&*format){if(*format!='%'){mr_format_char(out,&length,*format++);continue;}format++;if(*format=='%'){mr_format_char(out,&length,'%');format++;continue;}
        bool left=false,plus=false,space=false,zero=false,prefix=false;for(bool flags=true;flags;)switch(*format){case '-':left=true;format++;break;case '+':plus=true;format++;break;case ' ':space=true;format++;break;case '0':zero=true;format++;break;case '#':prefix=true;format++;break;default:flags=false;break;}
        int width=0;if(*format=='*'){width=va_arg(args,int);format++;if(width<0){left=true;width=-width;}}else while(*format>='0'&&*format<='9')width=width*10+*format++-'0';
        int precision=-1;if(*format=='.'){format++;precision=0;if(*format=='*'){precision=va_arg(args,int);format++;}else while(*format>='0'&&*format<='9')precision=precision*10+*format++-'0';}
        int size=0;if(*format=='h'){format++;size=-1;if(*format=='h'){format++;size=-2;}}else if(*format=='l'){format++;size=1;if(*format=='l'){format++;size=2;}}else if(*format=='z'||*format=='t'){format++;size=1;}else if(*format=='j'){format++;size=2;}
        char type=*format?*format++:0,temp[96];int count=0;const char *valueText=NULL;char sign=0;char prefixText[2];int prefixCount=0;
        if(type=='s'){valueText=va_arg(args,const char*);if(!valueText)valueText="(null)";count=(int)TextLength(valueText);if(precision>=0&&count>precision)count=precision;}
        else if(type=='c'){temp[0]=(char)va_arg(args,int);valueText=temp;count=1;}
        else if(type=='d'||type=='i'){long long value=size>=2?va_arg(args,long long):(size==1?va_arg(args,long):va_arg(args,int));bool negative=value<0;unsigned long long magnitude=negative?(unsigned long long)(-(value+1))+1:(unsigned long long)value;count=mr_format_unsigned(temp,magnitude,10,false);valueText=temp;sign=negative?'-':(plus?'+':(space?' ':0));}
        else if(type=='u'||type=='x'||type=='X'||type=='o'){unsigned long long value=size>=2?va_arg(args,unsigned long long):(size==1?va_arg(args,unsigned long):va_arg(args,unsigned int));unsigned int base=type=='o'?8:(type=='u'?10:16);count=mr_format_unsigned(temp,value,base,type=='X');valueText=temp;if(prefix&&value){if(base==8){prefixText[0]='0';prefixCount=1;}else if(base==16){prefixText[0]='0';prefixText[1]=type=='X'?'X':'x';prefixCount=2;}}}
        else if(type=='p'){unsigned long long value=(unsigned long long)(uintptr_t)va_arg(args,void*);count=mr_format_unsigned(temp,value,16,false);valueText=temp;prefixText[0]='0';prefixText[1]='x';prefixCount=2;}
        else if(type=='f'||type=='F'){count=mr_format_float(temp,va_arg(args,double),precision);valueText=temp;if(temp[0]=='-'){sign='-';valueText++;count--;}else sign=plus?'+':(space?' ':0);}
        else {mr_format_char(out,&length,'%');if(type)mr_format_char(out,&length,type);continue;}
        int zeros=0;if(precision>count&&(type!='s'&&type!='c'&&type!='f'&&type!='F'))zeros=precision-count;int total=count+zeros+prefixCount+(sign?1:0);int padding=width>total?width-total:0;
        if(!left&&!zero)mr_format_repeat(out,&length,' ',padding);if(sign)mr_format_char(out,&length,sign);for(int i=0;i<prefixCount;i++)mr_format_char(out,&length,prefixText[i]);if(!left&&zero)mr_format_repeat(out,&length,'0',padding);mr_format_repeat(out,&length,'0',zeros);for(int i=0;i<count;i++)mr_format_char(out,&length,valueText[i]);if(left)mr_format_repeat(out,&length,' ',padding);
    }out[length]=0;
}
#endif

const char *TextFormat(const char *text,...){
    char *buffer=mr_textformat_buffers[mr_textformat_index];mr_textformat_index=(mr_textformat_index+1)%MR_TEXTFORMAT_BUFFERS;
    va_list args;va_start(args,text);
#if defined(__wasm__)
    mr_web_text_format(buffer,text,args);
#else
    vsnprintf(buffer,MR_TEXTFORMAT_BUFFER_SIZE,text?text:"",args);buffer[MR_TEXTFORMAT_BUFFER_SIZE-1]=0;
#endif
    va_end(args);return buffer;
}

unsigned int TextLength(const char *text) { unsigned int n=0; if (text) while (text[n]) n++; return n; }
int TextCopy(char *dst,const char *src) { int n=0; if (!dst || !src) return 0; do { dst[n]=src[n]; } while (src[n++]); return n-1; }
bool TextIsEqual(const char *a,const char *b) { if (!a || !b) return a==b; while (*a && *a==*b) { a++; b++; } return *a==*b; }
const char *TextSubtext(const char *text,int position,int length) {
    static char out[1024]; int source=(int)TextLength(text); if (position<0) position=0; if (position>source) position=source;
    if (length<0) length=0; if (length>source-position) length=source-position; if (length>1023) length=1023;
    for (int i=0;i<length;i++) out[i]=text[position+i]; out[length]=0; return out;
}
void TextAppend(char *text,const char *append,int *position) { if (!text || !append || !position) return; while (*append) text[(*position)++]=*append++; text[*position]=0; }
int TextFindIndex(const char *text,const char *find) {
    if (!text || !find) return -1; if (!*find) return 0;
    for (int i=0;text[i];i++) { int j=0; while (find[j] && text[i+j]==find[j]) j++; if (!find[j]) return i; } return -1;
}
static const char *mr_text_case(const char *text,bool upper) {
    static char out[1024]; int i=0; if (!text) { out[0]=0; return out; }
    for (;text[i] && i<1023;i++) { char c=text[i]; if (upper && c>='a'&&c<='z') c-=32; if (!upper&&c>='A'&&c<='Z') c+=32; out[i]=c; }
    out[i]=0; return out;
}
const char *TextToUpper(const char *text) { return mr_text_case(text,true); }
const char *TextToLower(const char *text) { return mr_text_case(text,false); }
int TextToInteger(const char *text) { int sign=1,value=0; if (!text) return 0; while (*text==' '||*text=='\t') text++; if (*text=='-') { sign=-1; text++; } else if (*text=='+') text++; while (*text>='0'&&*text<='9') value=value*10+*text++-'0'; return value*sign; }
float TextToFloat(const char *text) {
    if (!text) return 0; while (*text==' '||*text=='\t') text++; float sign=1,value=0,scale=0.1f; if (*text=='-') { sign=-1; text++; } else if (*text=='+') text++;
    while (*text>='0'&&*text<='9') value=value*10+*text++-'0'; if (*text=='.') { text++; while (*text>='0'&&*text<='9') { value+=(*text++-'0')*scale; scale*=0.1f; } } return value*sign;
}
void DrawFPS(int x,int y) {
    static double sampleStart;
    static unsigned int sampleFrames,displayed;
    double now=GetTime();
    if (sampleStart==0) {
        sampleStart=now;
        displayed=mr.dt>0.00001f ? (unsigned int)(1.0f/mr.dt+0.5f) : 0;
    }
    sampleFrames++;
    double elapsed=now-sampleStart;
    if (elapsed>=0.5) {
        displayed=(unsigned int)(sampleFrames/elapsed+0.5);
        sampleFrames=0; sampleStart=now;
    }
    char text[24],digits[12]; int n=0,i=0;
    unsigned int fps=displayed;
    do { digits[n++]=(char)('0'+fps%10); fps/=10; } while (fps);
    while (n) text[i++]=digits[--n];
    text[i++]=' '; text[i++]='F'; text[i++]='P'; text[i++]='S'; text[i]=0;
    DrawText(text,x,y,14,GREEN);
}
