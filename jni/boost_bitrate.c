#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "boost_bitrate.h"

int32_t _ZN19GlassRacingChnlMenu7timeOutEv (void* this) {	
	
	int32_t ret_ = 0;
	
	if (!timeOut && !getInstance){
		
		timeOut = dlsym (RTLD_NEXT, "_ZN19GlassRacingChnlMenu7timeOutEv");
		if (timeOut == 0){
			guiLib = dlopen("/system/lib/libtp1801_gui.so", 1);
			timeOut = dlsym (guiLib, "_ZN19GlassRacingChnlMenu7timeOutEv");
			if (timeOut == 0)
			{
				printf("dlsym: %s\n", dlerror());
				return 0;
			}
		}
		
		getInstance = dlsym (RTLD_NEXT, "_ZN17GlassUserSettings11getInstanceEv");
		if (getInstance == 0){
			if(!guiLib){guiLib = dlopen("/system/lib/libtp1801_gui.so", 1);}
			getInstance = dlsym (guiLib, "_ZN17GlassUserSettings11getInstanceEv");
			if (getInstance == 0)
			{
				printf("dlsym: %s\n", dlerror());
				return 0;
			}
		}
	}	

	uint32_t inst = getInstance();

	uint32_t *gs_gui_config = (uint32_t *)*(uint32_t *)((int)inst + 0xe4);
	uint32_t *gs_info = (uint32_t *)*(uint32_t *)((int)gs_gui_config + 0x4c);

	gs_link_stat_t link = GS_LINK_STAT_UKNOWN;
	gs_link_stat_t *link_state = &link;	

	gs_modem_get_link_state_wrap = (void *)*(int32_t *)((int)gs_gui_config + 0x228);
	gs_modem_set_bandwidth_mode = (void *)*(uint32_t *)((int)gs_gui_config + 0x2AC);
	
	gs_modem_get_link_state_wrap(gs_info, link_state);
		
	if(((link == GS_LINK_STAT_NORMAL) || (link == GS_LINK_STAT_WEAK)) && !started){
		started = true;
		sleep(10);
		gs_modem_set_bandwidth_mode(gs_info, 6);
		printf("Launch 30/60Mbit mode...\n");
	}
	else if(((link == GS_LINK_STAT_LOST) || (link == GS_LINK_STAT_UKNOWN)) && started){
		started = false;
		printf("LINK LOST!\n");	
	}
	
	
	ret_ = timeOut(this);		
	
	return ret_;	
}
