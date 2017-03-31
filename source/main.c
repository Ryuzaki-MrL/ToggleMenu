#include <stdio.h>
#include <string.h>
#include <3ds.h>

int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    cfguInit();

    u8 titleID[0x8];
    u8 homemenuID[] = {0x02, 0x98, 0x00, 0x00, 0x30, 0x00, 0x04, 0x00};
    u8 testmenuID[] = {0x02, 0x81, 0x00, 0x00, 0x30, 0x00, 0x04, 0x00};

    CFG_GetConfigInfoBlk4(0x8, 0x00110001, titleID);
    bool isHomeMenu = !memcmp(titleID, testmenuID, 0x8);

    if (isHomeMenu) CFG_SetConfigInfoBlk8(0x8, 0x00110001, homemenuID);
    else CFG_SetConfigInfoBlk8(0x8, 0x00110001, testmenuID);

    CFG_UpdateConfigNANDSavegame();
    // CFG_GetConfigInfoBlk4(0x8, 0x00110001, titleID);
    // printf("Changed menu to: %#018llx", *(u64*(titleID)));
    // printf("Current menu: %s menu", isHomeMenu ? "test" : "home");

    hidScanInput();
    if (!hidKeysHeld()) APT_HardwareResetAsync();

    cfguExit();
    gfxExit();
    return 0;
}
