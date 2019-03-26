//  Milan Patel CS3377.0W1
//  main.c
//  Assignment 2
//
//  Created by Milan Patel on 3/2/19.
//  Copyright © 2019 Milan Patel. All rights reserved.
//
#include <ftw.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// Static variables which update as counters
static int directoryCounter = 0;
static int fileCounter = 0;
static int byteCounter = 0;

// Display function which increase counters
static int display(const char *fPath, const struct stat *sb, int typeFlag, struct FTW *ftwbuf){
    // If file
    if(typeFlag == FTW_F){
        // Increment counters
        byteCounter = byteCounter + (intmax_t)sb->st_size;
        fileCounter++;
    }
    // If directory
    if(typeFlag == FTW_D){
        // Increment counter
        directoryCounter++;
    }
    return 0;
}
// Main function
int main(int argc, char * argv[]) {
    // Flag variable
    int flag = 0;
    
    // Argument check and exit
    if(argc > 2 && strchr(argv[1], 'p') != NULL){
        flag |= FTW_PHYS;
    }
    if(argc > 2 && strchr(argv[1], 'd') != NULL){
        flag |= FTW_DEPTH;
    }
    if(nftw((argc < 2) ? "." : argv[1], display, 20, flag) == -1){
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    // Print counters and exit successfully
    printf("%3d \n", fileCounter);
    printf("%3d \n", directoryCounter);
    printf("%3d \n", byteCounter);
    exit(EXIT_SUCCESS);
    
    
}
