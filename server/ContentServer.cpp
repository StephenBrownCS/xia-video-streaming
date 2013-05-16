
/*
    Content Server
        Simply reads in a file (hard-coded to be the video in xia-core), 
        uploads it to its cache slice, then either quits or waits for a time 
        before removing the content.
    
        
        The client only supports ogg video files
        
    Limitations
        Attempting to specify TTL for the content cache didn't work in our testing
        That is why we sleep for some period of time before removing the content
        ourselves.
        
        You will need to change the path for VIDEO_NAME, depending on where 
        the video is that you wish to upload.

*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Xsocket.h"
#include "Utility.h"

#define DEBUG


#define CHUNKSIZE (1024)
#define SNAME "www_s.video.com.xia"

using namespace std;

//GLOBAL CONFIGURATION OPTIONS
string VIDEO_NAME = "../../xia-core/applications/demo/web_demo/resources/video.ogv";

/*
** upload the video file as content chunks
** if shouldTakeDownContent is true, will take down the content after a period 
** of time specified by periodToSleep
*/
int uploadContent(const char *fname, bool shouldTakeDownContent, int periodToSleep);


//***************************************************************************
//******                    MAIN METHOD                                 *****
//***************************************************************************

int main(int argc, char *argv[])
{
    printHostInformation();
    
    int periodToSleep = 0;
    bool shouldTakeDownContent = false;
    if (argc > 1){
        shouldTakeDownContent = true;
        periodToSleep = atoi(argv[1]);
    }
    
    // put the video file into the content cache
    if (uploadContent(VIDEO_NAME.c_str(), shouldTakeDownContent, periodToSleep) != 0){
        die(-1, "Unable to upload the video %s\n", VIDEO_NAME.c_str());
    }
    return 0;
}


int uploadContent(const char *fname, bool shouldTakeDownContent, int periodToSleep)
{
    int count;

    // Open file and allocate cache slice
    string fileName(fname);
    say("Loading video file: " + fileName);
    say("Allocating cache slice", LVL_DEBUG);
    ChunkContext *ctx = XallocCacheSlice(POLICY_DEFAULT, 0, 20000000);
    if (ctx == NULL)
        die(-2, "Unable to initilize the chunking system\n");

    // Upload file to cache slice
    say("Putting the file...", LVL_DEBUG);
    ChunkInfo *info;
    if ((count = XputFile(ctx, fname, CHUNKSIZE, &info)) < 0)
        die(-3, "unable to process the video file\n");

    // Display how many chunks we just read in
    ostringstream ss;
    ss << count;
    say("Put " + ss.str() + " chunks\n");

	//Print out the CIDs for the CidDirectoryServer to read and send out
	ofstream outfile("CIDs_BigBuckBunny.txt");
   	for (int i = 0; i < count; i++) {
        string CID = "CID:";
        CID += info[i].cid;
		outfile << CID << endl;
    }
	outfile.close();

    // If the user has specified that we take down the content after some 
    // number of seconds sleep for some period of time, then clear the 
    // content cache

    if(shouldTakeDownContent){
        sleep(periodToSleep);
    
        say("Removing CIDs from Cache", LVL_INFO);
        for (int i = 0; i < count; i++) {
            XremoveChunk(ctx, info[i].cid);
        }
    }

    XfreeChunkInfo(info);

    // close the connection to the cache slice, but becase it is set to retain,
    // the content will stay available in the cache
    XfreeCacheSlice(ctx);
    
    return 0;
}



