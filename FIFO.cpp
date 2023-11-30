#include <stdio.h>

int main() {
    // Define the incoming page reference stream
    int incomingStream[] = {4, 1, 2, 4, 5,1,3,4,2};
    
    // Initialize variables
    int pageFaults = 0;
    int frames = 3;
    int pages = sizeof(incomingStream) / sizeof(incomingStream[0]);

    // Display header for the table
    printf(" Incoming \tFrame 1 \tFrame 2 \tFrame 3\n");

    // Initialize array to track frames
    int temp[frames];
    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    // Process each page in the stream
    for (int m = 0; m < pages; m++) {
        // Check if the page is already in a frame
        int isPageInFrame = 0;
        for (int n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                isPageInFrame = 1;
                break;
            }
        }

        // Update page faults and frame information
        if (!isPageInFrame) 
		{
            pageFaults++;
            if (pageFaults <= frames) {
                temp[pageFaults - 1] = incomingStream[m];
            } else {
                temp[(pageFaults - 1) % frames] = incomingStream[m];
            }
        }

        // Display current state of frames
        printf("%d\t\t\t", incomingStream[m]);
        for (int n = 0; n < frames; n++) {
            printf("%d\t\t\t", (temp[n] != -1) ? temp[n] : -1);
        }
        printf("\n");
    }

    // Display total page faults
    printf("Total Page Faults:\t%d\n", pageFaults);

    return 0;
}

