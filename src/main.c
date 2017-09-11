////////////////////////////////////////
// { sprite animation using buffer swap demo } { 1.0.0 }
// Author:Lesquivemeau
// License:MIT
// Description:Shows a little fox sleeping
////////////////////////////////////////

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers */
#include <stdlib.h>
#include <graphx.h>

/*Definitions*/
#define lcd_vramArray
#define SPR_HEIGHT 35 //Taille de l'image (hauteur)
#define SPR_WIDTH 40 //Taille de l'image (largeur)
/* Other available headers: stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h */
#include "logo_gfx.h" //on inclus le fichier header qui correspond à l'image convertie
/* Put function prototypes here */

/*Variables*/

/* Put all your code here */
void main(void)
{
    int SIZE = LCD_HEIGHT/SPR_HEIGHT; //Cette varialble correspond au facteur d'agrandissement de l'image (vertical mais aussi horizontal, j'utilise la mème valeur pour ne pas déformer l'image, et je me base sur la hauteur car l'écran de la calculatrice est plus large que haut, ça évite de dépasser des bords, LCD_HEIGHT est égal à la hauteur de l'écran, et LCD_WIDTH la largeur
    int offset = LCD_WIDTH-SPR_WIDTH*SIZE; //Cette variable définis l'espace total entre l'image et le bord de l'écran, on va s'en servir pour centrer l'image
    int x = offset/2; //Celle-ci est simplement la position de l'image (coin superieur gauche de l'image donc) une fois centrée
    uint8_t seconds = 0;
    bool anim;
    anim = true;
    gfx_Begin();
    gfx_SetDrawBuffer(); //On initialise le buffer
    gfx_FillScreen(255); //on remplis l'écran de blanc
    gfx_SetPalette(logo_gfx_pal, sizeof_logo_gfx_pal, 0); //Change la palette de couleur pour correspondre à l'image
    gfx_ScaledTransparentSprite_NoClip(fox_0, x, 0,SIZE,SIZE); //Dessiner le sprite dans le buffer
    gfx_SwapDraw();
    gfx_ScaledTransparentSprite_NoClip(fox_1, x, 0,SIZE,SIZE); //Dessiner le sprite dans le buffer
    do{
        boot_GetTime(&seconds,NULL,NULL);
        if(seconds%2 == 0 && anim) {
        gfx_SwapDraw();
        anim = false;
        }
        else if(seconds%2!=0) {
        anim = true;
        }
    }while (!os_GetCSC());
    gfx_End();
}

/*Functions*/