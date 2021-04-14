//
//  main.cpp
//  System-Info
//
//  Created by Jackson Fortner on 4/9/21.
//

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/sysctl.h>

using namespace std;

int GetSystemTotalMemory() {
    int mib[] = {CTL_HW, HW_MEMSIZE};
    int64_t value = 0;
    size_t length = sizeof(value);
    
    if ((sysctl(mib, 2, &value, &length, NULL, 0)) == -1) return -1;
    
    return (int)(value / 1048576);
}

char *GetSystemModel() {
    int mib[] = {CTL_HW, HW_MODEL};

    char *model;
    size_t model_size;
    if (sysctl(mib, 2, NULL, &model_size, NULL, 0) == 0) {
        model = (char*) malloc(model_size);
    
        if (sysctl(mib, 2, model, &model_size, NULL, 0) == 0) {
            return model;
        }
    }

    return NULL;
}

int main(int argc, const char * argv[]) {
    int total_memory = GetSystemTotalMemory();
    char *system_model = GetSystemModel();

    cout << "[*] Printing system info...." << endl;
    cout << "   [+] System Model:          : " << system_model << endl;
    cout << "   [+] Total Memory Installed : " << total_memory << "mb" << endl;
    
    return 0;
}
