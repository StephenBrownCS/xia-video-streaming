xia-video-streaming
===================

Video Streaming applications for the eXpressive Internet Architecture

    Created by Ben Bramble, Stephen Brown, and Big Buck Bunny May 2013

This directory must be located adjacent to the xia-core directory
    For example. our directory structure looks something like this:
        xia/
            xia-core/
            xia-video-streaming/
    
    This is because our makefiles use some link dependencies based on the 
    xia-core folder.
    
    Also, the content server is currently hard-coded to use the video in 
    xia-core's web demo (Big Buck Bunny).

Contents
    client/
        Contains the video client, for use in streaming the video and playing it
        Contains the makefile and should be run directly out of that directory
        
        It borrows from the example chunk client example from XIA, but expands 
        in a lot of ways, including handling failover and multi-threading.
        
        The main class is VideoClient
        
    demoVideo/
        This is a video demonstrating our project
        Not for use in testing streaming functionality!
        
    plogg/
        This is the original video application created by Chris Doublee
        (who is not affiliated with this project in any way)
        It just plays ogg video files and is useful for assessing the state of 
        your machine for video-readiness.
        
        This player is discussed on Chris's blog, the Bluish Coder

    server/
        This contains both the CID Directory Server and the Content Server
        Originally they were united as one application, but we decided to 
        split them up since they actually do quite different things. They 
        both borrow heavily from the XIA video server example
        
    xsockconf/
        This directory includes our network topology files. To run our network,
        you must type "make" in that directory. It will copy xsock files into 
        each of the client and server directories (since those executables will 
        need those files in the same directory).
        
Third Party Library Dependencies (for Client)
        libncursesw5-dev
        gettext
        xmlto
        autoconf
        autogen
        
        alsa-lib
        alsa-plugins
        
        libogg
        libtheora
        libvorbis
        SDL
        libsydneyaudio
        
Limitations
    Network-level failover last known to work with XIA revision pushed on April 5, 2013.
    It is known to NOT work with the revision posted on April 11, 2013.
    
    Must be located in the directory path specified above.
    
    Cannot currently support more than 2 Content Servers running, due to limitation 
    of 4 fallback paths in DAG.
    
Other Resources
    See our demo video and paper, included in this same repository.
    See the extensive READMEs located in the client and server directories.

        