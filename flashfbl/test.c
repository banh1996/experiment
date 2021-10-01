#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
    char fota_state_file[] = "fotastate.txt\n";
    char temp_str[128];
    
    sprintf(temp_str, "%s", argv[1]);
    strcat(temp_str, fota_state_file);
    sprintf(fota_state_file, "%s", temp_str);
    printf("%s %ld", fota_state_file, strlen(fota_state_file));

    return 0;
}
