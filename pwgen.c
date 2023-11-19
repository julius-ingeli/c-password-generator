// compile with: gcc pwgen.c -o pwgen -lssl -lcrypto


#include <stdio.h>
#include <string.h>
#include <openssl/rand.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <stdlib.h>
#endif


int main() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    while(1){
        char pw_lenIn[7];
        printf("Enter password length:");
        fgets(pw_lenIn,7,stdin);
        int pw_len = atoi(pw_lenIn);

        unsigned char password[pw_len + 1];
        

        

        if (RAND_bytes(password, pw_len)) {
            for (int i = 0; i < pw_len; i++) {
                password[i] = charset[password[i] % (sizeof(charset) - 1)];
            }
            password[pw_len] = '\0';
            printf("Generated password: %s\n", password);

    #ifdef _WIN32
            const size_t len = strlen(password) + 1;
            HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
            memcpy(GlobalLock(hMem), password, len);
            GlobalUnlock(hMem);
            OpenClipboard(0);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hMem);
            CloseClipboard();
        
    #else
            //check xclip installation
            int result = system("xclip -version > /dev/null 2>&1");
            if (result != 0) {
                printf("xclip is not installed. Attempting to install...\n");
                result = system("sudo apt-get install xclip -y");

                if (result == 0) {
                    printf("xclip installed successfully.\n");
                }  
                else {
                    printf("Failed to install xclip.\n");
                }
            }
            char cmd[64];
            sprintf(cmd, "echo %s | xclip -selection clipboard", password);
            system(cmd);
            
    #endif
        printf("Generate a new password? Y/N\n");
        char repIn[4];
        fgets(repIn,4,stdin);
        if(repIn[0] == 'N' || repIn[0] == 'n'){
            break;
        }
        } 
        else{
            fprintf(stderr, "Error generating random bytes.\n");
        }
    }
    return 0;
}
