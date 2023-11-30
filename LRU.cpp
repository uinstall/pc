#include<stdio.h>

// Function to find the index of the least recently used page
int findLRU(int time[], int n) 
{
    int pos = 0;
    for(int i = 1; i < n; ++i) {
        if(time[i] < time[pos]) {
            pos = i;
        }
    }
    return pos;
}

int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], faults = 0;

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    // Input reference string
    printf("Enter reference string: ");
    for(int i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames and time arrays
    for(int i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    // Page replacement algorithm
    for(int i = 0; i < no_of_pages; ++i) {
        int flag1 = 0, flag2 = 0;

        // Check if page is already in frame
        for(int j = 0; j < no_of_frames; ++j) 
		{
            if(frames[j] == pages[i]) 
			{
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }


        // If page is not in frame, replace a page
        if(flag1 == 0) {
            for(int j = 0; j < no_of_frames; ++j) {
                if(frames[j] == -1) {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }
        
        

        // If all frames are occupied, replace the LRU page
        if(flag2 == 0) {
            int pos = findLRU(time, no_of_frames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Display current state of frames
        for(int j = 0; j < no_of_frames; ++j) {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }

    // Display total page faults
    printf("\nTotal Page Faults = %d", faults);

    return 0;
}

