#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "boost_bitrate.h"

void _ZN19GlassRacingChnlMenu7timeOutEv(void* this) {

	if (!timeOut && !getInstance){

		timeOut = dlsym (RTLD_NEXT, "_ZN19GlassRacingChnlMenu7timeOutEv");
		if (timeOut == 0){
			if(!guiLib){guiLib = dlopen("/system/lib/libtp1801_gui.so", 1);}
			timeOut = dlsym (guiLib, "_ZN19GlassRacingChnlMenu7timeOutEv");
			if (timeOut == 0)
			{
				printf("dlsym: %s\n", dlerror());
				return;
			}
		}

		getInstance = dlsym (RTLD_NEXT, "_ZN17GlassUserSettings11getInstanceEv");
		if (getInstance == 0){
			if(!guiLib){guiLib = dlopen("/system/lib/libtp1801_gui.so", 1);}
			getInstance = dlsym (guiLib, "_ZN17GlassUserSettings11getInstanceEv");
			if (getInstance == 0)
			{
				printf("dlsym: %s\n", dlerror());
				return;
			}
		}
	}

	if(!instance_bb)instance_bb = getInstance();

	if(instance_bb){
		gs_gui_config_bb = (__gs_gui_config *)*(uint32_t *)((int)instance_bb + 0xe4);
	
		gs_link_stat_t link = GS_LINK_STAT_UKNOWN;
		gs_gui_config_bb->gs_modem_get_link_state_wrap(gs_gui_config_bb->gs_info, &link);
		
		if(link != GS_LINK_STAT_NORMAL){
			clock_gettime(CLOCK_MONOTONIC, &start_bb);
		}

		clock_gettime(CLOCK_MONOTONIC, &now_bb);
		
		//GlassRacingChnlMenu::timeOut timeouts 1/s. Send the cmd every second for 15 seconds.	
		if((link == GS_LINK_STAT_NORMAL) && !started_bb){
			if((now_bb.tv_sec - start_bb.tv_sec) > 15)started_bb = true;
			gs_gui_config_bb->gs_modem_set_bandwidth_mode(gs_gui_config_bb->gs_info, 6);
			printf("Launching 30/60Mbit mode...\n");
		}
		else if((link == GS_LINK_STAT_LOST) && started_bb){
			started_bb = false;
			printf("LINK LOST!\n");
		}

	}
	
	timeOut(this);
	return;
}
