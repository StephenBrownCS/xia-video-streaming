// Copyright (C) 2009 Chris Double. All Rights Reserved.
// The original author of this code can be contacted at: chris.double@double.co.nz
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// DEVELOPERS AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//


/*
    This class is adapted from Chris Double's Plogg ogg player. The only real 
    changes we made were to separate his file into a .h and cpp file and to 
    rename his main class to "PloggOggDecoder". We also removed the main method.
    
    This makes the Plogg Ogg Decoder reusable in different applications.
    
    Known Issues:
        In one of our VM's we were never able to get video to work. Instead, 
        it would always be audio-only with a black window with a few green 
        pixels in the upper left.
        
        We determined that this was not an issue in the code. It either must be 
        a third-party library that was not correctly installed or a limitation of 
        running the VM in virtual box on a Macbook Pro late 2008 model running 
        Snow Leopard. We couldn't get a simple barebones SDL example to work on 
        that machine either.
*/

#ifndef __PLOG_OGG_DECODER_H__
#define __PLOG_OGG_DECODER_H__

#include<istream>
#include<map>
#include <ogg/ogg.h> // for ogg_int64_t

extern "C" {
	#include <sydney_audio.h>
}

// Forward References
class OggStream;
class SDL_Surface;
class SDL_Overlay;

typedef std::map<int, OggStream*> StreamMap; 

class PloggOggDecoder{
public:
  StreamMap mStreams;  
  SDL_Surface* mSurface;
  SDL_Overlay* mOverlay;
  sa_stream_t* mAudio;
  ogg_int64_t  mGranulepos;

public:
	PloggOggDecoder();
	~PloggOggDecoder();
  	void play(std::istream& stream);

private:
  bool handle_theora_header(OggStream* stream, ogg_packet* packet);
  bool handle_vorbis_header(OggStream* stream, ogg_packet* packet);
  void read_headers(std::istream& stream, ogg_sync_state* state);

  bool read_page(std::istream& stream, ogg_sync_state* state, ogg_page* page);
  bool read_packet(std::istream& is, ogg_sync_state* state, OggStream* stream, ogg_packet* packet);
  void handle_theora_data(OggStream* stream, ogg_packet* packet);
};


#endif
