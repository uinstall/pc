#include <stdio.h>

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], faults = 0;
    
    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    // Input page reference string
    printf("Enter page reference string: ");
    for (int i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames array
    for (int i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    // Page replacement algorithm
    for (int i = 0; i < no_of_pages; ++i) {
        int flag1 = 0, flag2 = 0, flag3 = 0, pos, max;

        // Check if the page is already in a frame
        for (int j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        // If the page is not in a frame, find an empty frame
        if (flag1 == 0) {
            for (int j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }

        // If all frames are occupied, replace the page using the optimal page replacement algorithm
        if (flag2 == 0) {
            flag3 = 0;

            // Calculate the distance of each page in frames to its next occurrence
            for (int j = 0; j < no_of_frames; ++j) {
                temp[j] = -1;

                for (int k = i + 1; k < no_of_pages; ++k) {
                    if (frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            // Find the position of the page with the maximum distance
            for (int j = 0; j < no_of_frames; ++j) {
                if (temp[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            // If all pages have a next occurrence, find the page with the maximum distance
            if (flag3 == 0) {
                max = temp[0];
                pos = 0;

                for (int j = 1; j < no_of_frames; ++j) {
                    if (temp[j] > max) {
                        max = temp[j];s
                        pos = j;
                    }
                }
            }

            // Replace the page in the selected frame
            frames[pos] = pages[i];
            faults++;
        }

        // Display current state of frames
        printf("\n");
        for (int j = 0; j < no_of_frames; ++j) {
            printf("%d\t", frames[j]);
        }
    }

    // Display total page faults
    printf("\n\nTotal Page Faults = %d", faults);
    
    return 0;
}

