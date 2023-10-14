#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

#define SW_IDENTITY "assignment-2"
#define DESIRED_LOGLEVEL LOG_DEBUG

void print_usage() {
    printf("Usage: writer <writefile> <writestr>\r\n");
}

int main(int argc, char** argv) {
    setlogmask(LOG_UPTO(DESIRED_LOGLEVEL));
    openlog(SW_IDENTITY, LOG_CONS | LOG_NDELAY | LOG_PID, LOG_USER);

    int returnValue = 0;    
    FILE* fPointer = NULL;
    
    //Check if arguments number is valid
    bool ok = (argc == 3);
    if(!ok) {
        print_usage();
        syslog(LOG_ERR, "Missing arguments, expected 3, found %d", argc);
        returnValue = 1;
    }
       
    if(ok) {       
        fPointer = fopen(argv[1], "w");
        ok = (fPointer != NULL);
        if(!ok) {
            printf("Error opening %s file: %s\r\n", argv[1], strerror(errno));
            syslog(LOG_ERR, "Error opening %s file: %s", argv[1], strerror(errno));
            returnValue = 1;
        }
    }
    
    if(ok) {
        size_t wrSize = strlen(argv[2]);
        size_t writtenData = fprintf(fPointer, "%s", argv[2]);
        
        ok = (wrSize == writtenData);
        if(!ok) {
            syslog(LOG_ERR, "Inconsistent write size: expected %lu, actual %lu\r\n", wrSize, writtenData);
            returnValue = 1;
        } else {
            syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
        }
    }
    
    if(fPointer != NULL) {
        int closeV = fclose(fPointer);
        ok = (closeV == 0);
        if(!ok) {
            printf("Failure closing %s file.\r\n", argv[1]);
            syslog(LOG_ERR, "Failure closing %s file.\r\n", argv[1]);
            returnValue = 1;
        }
    }
    return returnValue;
}
