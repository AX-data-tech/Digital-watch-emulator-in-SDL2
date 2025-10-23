#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "draw.h"
#include "fsm.h"

// Define the cell colours
Sint16 cell_on[3] = {230, 0, 0};
Sint16 cell_off[3] = {0, 0, 0};

// Here is how we define the starting point of the LCD screen
#define STARTX 165
#define STARTY 400

// Define the cells
// A
Sint16 cell_AA_x[4] = {STARTX, STARTX + 100, STARTX + 80, STARTX + 20};
Sint16 cell_AA_y[4] = {STARTY, STARTY, STARTY + 20, STARTY + 20};
Sint16 cell_AB_x[4] = {STARTX + 100, STARTX + 100, STARTX + 80, STARTX + 80};
Sint16 cell_AB_y[4] = {STARTY, STARTY + 100, STARTY + 90, STARTY + 20};
Sint16 cell_AC_x[4] = {STARTX + 100, STARTX + 100, STARTX + 80, STARTX + 80};
Sint16 cell_AC_y[4] = {STARTY + 100, STARTY + 200, STARTY + 180, STARTY + 110};
Sint16 cell_AD_x[4] = {STARTX, STARTX + 20, STARTX + 80, STARTX + 100};
Sint16 cell_AD_y[4] = {STARTY + 200, STARTY + 180, STARTY + 180, STARTY + 200};
Sint16 cell_AE_x[4] = {STARTX, STARTX + 20, STARTX + 20, STARTX};
Sint16 cell_AE_y[4] = {STARTY + 100, STARTY + 110, STARTY + 180, STARTY + 200};
Sint16 cell_AF_x[4] = {STARTX, STARTX + 20, STARTX + 20, STARTX};
Sint16 cell_AF_y[4] = {STARTY, STARTY + 20, STARTY + 90, STARTY + 100};
Sint16 cell_AG_x[6] = {STARTX, STARTX + 20, STARTX + 80, STARTX + 100, STARTX + 80, STARTX + 20};
Sint16 cell_AG_y[6] = {STARTY + 100, STARTY + 90, STARTY + 90, STARTY + 100, STARTY + 110, STARTY + 110};
// B
Sint16 cell_BA_x[4] = {STARTX + 130,  STARTX + 230, STARTX + 210, STARTX + 150};
Sint16 cell_BA_y[4] = {STARTY, STARTY, STARTY + 20, STARTY + 20};
Sint16 cell_BB_x[4] = {STARTX + 230, STARTX + 230, STARTX + 210, STARTX + 210};
Sint16 cell_BB_y[4] = {STARTY, STARTY + 100, STARTY + 90, STARTY + 20};
Sint16 cell_BC_x[4] = {STARTX + 230, STARTX + 230, STARTX + 210, STARTX + 210};
Sint16 cell_BC_y[4] = {STARTY + 100, STARTY + 200, STARTY + 180, STARTY + 110};
Sint16 cell_BD_x[4] = {STARTX + 130, STARTX + 150, STARTX + 210, STARTX + 230};
Sint16 cell_BD_y[4] = {STARTY + 200, STARTY + 180, STARTY + 180, STARTY + 200};
Sint16 cell_BE_x[4] = {STARTX + 130, STARTX + 150, STARTX + 150, STARTX + 130};
Sint16 cell_BE_y[4] = {STARTY + 100, STARTY + 110, STARTY + 180, STARTY + 200};
Sint16 cell_BF_x[4] = {STARTX + 130, STARTX + 150, STARTX + 150, STARTX + 130};
Sint16 cell_BF_y[4] = {STARTY, STARTY + 20, STARTY + 90, STARTY + 100};
Sint16 cell_BG_x[6] = {STARTX + 130, STARTX + 150, STARTX + 210, STARTX + 230, STARTX + 210, STARTX + 150};
Sint16 cell_BG_y[6] = {STARTY + 100, STARTY + 90, STARTY + 90, STARTY + 100, STARTY + 110, STARTY + 110};
// C
Sint16 cell_CA_x[4] = {STARTX + 290,  STARTX + 390, STARTX + 370, STARTX + 310};
Sint16 cell_CA_y[4] = {STARTY, STARTY, STARTY + 20, STARTY + 20};
Sint16 cell_CB_x[4] = {STARTX + 390, STARTX + 390, STARTX + 370, STARTX + 370};
Sint16 cell_CB_y[4] = {STARTY, STARTY + 100, STARTY + 90, STARTY + 20};
Sint16 cell_CC_x[4] = {STARTX + 390, STARTX + 390, STARTX + 370, STARTX + 370};
Sint16 cell_CC_y[4] = {STARTY + 100, STARTY + 200, STARTY + 180, STARTY + 110};
Sint16 cell_CD_x[4] = {STARTX + 290, STARTX + 310, STARTX + 370, STARTX + 390};
Sint16 cell_CD_y[4] = {STARTY + 200, STARTY + 180, STARTY + 180, STARTY + 200};
Sint16 cell_CE_x[4] = {STARTX + 290, STARTX + 310, STARTX + 310, STARTX + 290};
Sint16 cell_CE_y[4] = {STARTY + 100, STARTY + 110, STARTY + 180, STARTY + 200};
Sint16 cell_CF_x[4] = {STARTX + 290, STARTX + 310, STARTX + 310, STARTX + 290};
Sint16 cell_CF_y[4] = {STARTY, STARTY + 20, STARTY + 90, STARTY + 100};
Sint16 cell_CG_x[6] = {STARTX + 290, STARTX + 310, STARTX + 370, STARTX + 390, STARTX + 370, STARTX + 310};
Sint16 cell_CG_y[6] = {STARTY + 100, STARTY + 90, STARTY + 90, STARTY + 100, STARTY + 110, STARTY + 110};
// D
Sint16 cell_DA_x[4] = {STARTX + 420, STARTX + 520, STARTX + 500, STARTX + 440};
Sint16 cell_DA_y[4] = {STARTY, STARTY, STARTY + 20, STARTY + 20};
Sint16 cell_DB_x[4] = {STARTX + 520, STARTX + 520, STARTX + 500, STARTX + 500};
Sint16 cell_DB_y[4] = {STARTY, STARTY + 100, STARTY + 90, STARTY + 20};
Sint16 cell_DC_x[4] = {STARTX + 520, STARTX + 520, STARTX + 500, STARTX + 500};
Sint16 cell_DC_y[4] = {STARTY + 100, STARTY + 200, STARTY + 180, STARTY + 110};
Sint16 cell_DD_x[4] = {STARTX + 420, STARTX + 440, STARTX + 500, STARTX + 520};
Sint16 cell_DD_y[4] = {STARTY + 200, STARTY + 180, STARTY + 180, STARTY + 200};
Sint16 cell_DE_x[4] = {STARTX + 420, STARTX + 440, STARTX + 440, STARTX + 420};
Sint16 cell_DE_y[4] = {STARTY + 100, STARTY + 110, STARTY + 180, STARTY + 200};
Sint16 cell_DF_x[4] = {STARTX + 420, STARTX + 440, STARTX + 440, STARTX + 420};
Sint16 cell_DF_y[4] = {STARTY, STARTY + 20, STARTY + 90, STARTY + 100};
Sint16 cell_DG_x[6] = {STARTX + 420, STARTX + 440, STARTX + 500, STARTX + 520, STARTX + 500, STARTX + 440};
Sint16 cell_DG_y[6] = {STARTY + 100, STARTY + 90, STARTY + 90, STARTY + 100, STARTY + 110, STARTY + 110};
// E
Sint16 cell_EA_x[4] = {STARTX + 550, STARTX + 600, STARTX + 590, STARTX + 560};
Sint16 cell_EA_y[4] = {STARTY + 100, STARTY + 100, STARTY + 110, STARTY + 110};
Sint16 cell_EB_x[4] = {STARTX + 600, STARTX + 600, STARTX + 590, STARTX + 590};
Sint16 cell_EB_y[4] = {STARTY + 100, STARTY + 150, STARTY + 145, STARTY + 110};
Sint16 cell_EC_x[4] = {STARTX + 600, STARTX + 600, STARTX + 590, STARTX + 590};
Sint16 cell_EC_y[4] = {STARTY + 150, STARTY + 200, STARTY + 190, STARTY + 155};
Sint16 cell_ED_x[4] = {STARTX + 550, STARTX + 560, STARTX + 590, STARTX + 600};
Sint16 cell_ED_y[4] = {STARTY + 200, STARTY + 190, STARTY + 190, STARTY + 200};
Sint16 cell_EE_x[4] = {STARTX + 550, STARTX + 560, STARTX + 560, STARTX + 550};
Sint16 cell_EE_y[4] = {STARTY + 150, STARTY + 155, STARTY + 190, STARTY + 200};
Sint16 cell_EF_x[4] = {STARTX + 550, STARTX + 560, STARTX + 560, STARTX + 550};
Sint16 cell_EF_y[4] = {STARTY + 100, STARTY + 110, STARTY + 145, STARTY + 150};
Sint16 cell_EG_x[6] = {STARTX + 550, STARTX + 560, STARTX + 590, STARTX + 600, STARTX + 590, STARTX + 560};
Sint16 cell_EG_y[6] = {STARTY + 150, STARTY + 145, STARTY + 145, STARTY + 150, STARTY + 155, STARTY + 155};
// F
Sint16 cell_FA_x[4] = {STARTX + 620, STARTX + 670, STARTX + 660, STARTX + 630};
Sint16 cell_FA_y[4] = {STARTY + 100, STARTY + 100, STARTY + 110, STARTY + 110};
Sint16 cell_FB_x[4] = {STARTX + 670, STARTX + 670, STARTX + 660, STARTX + 660};
Sint16 cell_FB_y[4] = {STARTY + 100, STARTY + 150, STARTY + 145, STARTY + 110};
Sint16 cell_FC_x[4] = {STARTX + 670, STARTX + 670, STARTX + 660, STARTX + 660};
Sint16 cell_FC_y[4] = {STARTY + 150, STARTY + 200, STARTY + 190, STARTY + 155};
Sint16 cell_FD_x[4] = {STARTX + 620, STARTX + 630, STARTX + 660, STARTX + 670};
Sint16 cell_FD_y[4] = {STARTY + 200, STARTY + 190, STARTY + 190, STARTY + 200};
Sint16 cell_FE_x[4] = {STARTX + 620, STARTX + 630, STARTX + 630, STARTX + 620};
Sint16 cell_FE_y[4] = {STARTY + 150, STARTY + 155, STARTY + 190, STARTY + 200};
Sint16 cell_FF_x[4] = {STARTX + 620, STARTX + 630, STARTX + 630, STARTX + 620};
Sint16 cell_FF_y[4] = {STARTY + 100, STARTY + 110, STARTY + 145, STARTY + 150};
Sint16 cell_FG_x[6] = {STARTX + 620, STARTX + 630, STARTX + 660, STARTX + 670, STARTX + 660, STARTX + 630};
Sint16 cell_FG_y[6] = {STARTY + 150, STARTY + 145, STARTY + 145, STARTY + 150, STARTY + 155, STARTY + 155};

// X1
Sint16 cell_X1_x[4] = {STARTX + 250, STARTX + 270, STARTX + 270, STARTX + 250};
Sint16 cell_X1_y[4] = {STARTY + 70, STARTY + 70, STARTY + 90, STARTY + 90};

// X2
Sint16 cell_X2_x[4] = {STARTX + 250, STARTX + 270, STARTX + 270, STARTX + 250};
Sint16 cell_X2_y[4] = {STARTY + 110, STARTY + 110, STARTY + 130, STARTY + 130};

// Drawing function
void c_draw(SDL_Renderer* ren, const FSM* clock)
{
	if (clock->mode == 0)
	{
		// Time mode
		switch(clock->time_hour)
		{
			case(0):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(1):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(2):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(3):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(4):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(5):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(6):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(7):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(8):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(9):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(10):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(11):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(12):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(13):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(14):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(15):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(16):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(17):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(18):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(19):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(20):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(21):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);

				break;

			case(22):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

			case(23):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);

				break;

		}

		// We will go digit by digit
		int firstmin = (clock->time_min - (clock->time_min % 10))/10;
		int seconmin = clock->time_min % 10;

		switch(firstmin)
		{
			case(0):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(1):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(2):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(3):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(4):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(5):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		switch(seconmin)
		{
			case(0):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(1):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(2):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(3):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(4):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(5):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(6):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(7):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(8):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(9):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		// We will go digit by digit
		int firstsec = (clock->time_sec - (clock->time_sec % 10))/10;
		int seconsec = clock->time_sec % 10;

		switch(firstsec)
		{
			case(0):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(1):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(2):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(3):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(4):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(5):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		switch(seconsec)
		{
			case(0):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(1):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(2):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(3):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(4):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(5):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(6):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(7):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;
			case(8):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
			case(9):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		// X1 and X2 are steadily illuminated in this mode
		filledPolygonRGBA(ren, cell_X1_x, cell_X1_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
		filledPolygonRGBA(ren, cell_X2_x, cell_X2_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);

	}

	if (clock->mode == 1)
	{
		// Stop watch mode
		int sw_min1;
		int sw_min2;
		int sw_sec1;
		int sw_sec2;
		int sw_milli1;
		int sw_milli2;

		// Calculate the digits
		sw_min1 = (clock->sw_min - (clock->sw_min % 10)) / 10;
		sw_min2 = clock->sw_min % 10;
		sw_sec1 = (clock->sw_sec - (clock->sw_sec % 10)) / 10;
		sw_sec2 = clock->sw_sec % 10;
		sw_milli1 = (clock->sw_milli - (clock->sw_milli % 10)) / 10;
		sw_milli2 = clock->sw_milli % 10;

		switch(sw_min1)
		{
			case(0):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(1):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(2):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(3):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(4):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(5):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(6):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(7):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(8):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(9):
				filledPolygonRGBA(ren, cell_AA_x, cell_AA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AB_x, cell_AB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AC_x, cell_AC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AD_x, cell_AD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AE_x, cell_AE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_AF_x, cell_AF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_AG_x, cell_AG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		switch(sw_min2)
		{
			case(0):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(1):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(2):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(3):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(4):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(5):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(6):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(7):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(8):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(9):
				filledPolygonRGBA(ren, cell_BA_x, cell_BA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BB_x, cell_BB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BC_x, cell_BC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BD_x, cell_BD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BE_x, cell_BE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_BF_x, cell_BF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_BG_x, cell_BG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		switch(sw_sec1)
		{
			case(0):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(1):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(2):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(3):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(4):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(5):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(6):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(7):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(8):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(9):
				filledPolygonRGBA(ren, cell_CA_x, cell_CA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CB_x, cell_CB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CC_x, cell_CC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CD_x, cell_CD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CE_x, cell_CE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_CF_x, cell_CF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_CG_x, cell_CG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		switch(sw_sec2)
		{
			case(0):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(1):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(2):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(3):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(4):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(5):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(6):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(7):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(8):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(9):
				filledPolygonRGBA(ren, cell_DA_x, cell_DA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DB_x, cell_DB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DC_x, cell_DC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DD_x, cell_DD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DE_x, cell_DE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_DF_x, cell_DF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_DG_x, cell_DG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		switch(sw_milli1)
		{
			case(0):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(1):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(2):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(3):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(4):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(5):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(6):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(7):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(8):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(9):
				filledPolygonRGBA(ren, cell_EA_x, cell_EA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EB_x, cell_EB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EC_x, cell_EC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_ED_x, cell_ED_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EE_x, cell_EE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_EF_x, cell_EF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_EG_x, cell_EG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		switch(sw_milli2)
		{
			case(0):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(1):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(2):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(3):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(4):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(5):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(6):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(7):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_off[0], cell_off[1], cell_off[2], 255);
				break;

			case(8):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;

			case(9):
				filledPolygonRGBA(ren, cell_FA_x, cell_FA_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FB_x, cell_FB_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FC_x, cell_FC_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FD_x, cell_FD_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FE_x, cell_FE_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
				filledPolygonRGBA(ren, cell_FF_x, cell_FF_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
				filledPolygonRGBA(ren, cell_FG_x, cell_FG_y, 6, cell_on[0], cell_on[1], cell_on[2], 255);
				break;
		}

		// X1 and X2 flash in this mode
		if (clock->sw_milli < 50)
		{
			filledPolygonRGBA(ren, cell_X1_x, cell_X1_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
			filledPolygonRGBA(ren, cell_X2_x, cell_X2_y, 4, cell_on[0], cell_on[1], cell_on[2], 255);
		}
		else
		{
			filledPolygonRGBA(ren, cell_X1_x, cell_X1_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
			filledPolygonRGBA(ren, cell_X2_x, cell_X2_y, 4, cell_off[0], cell_off[1], cell_off[2], 255);
		}

	}


	SDL_RenderPresent(ren);
}
