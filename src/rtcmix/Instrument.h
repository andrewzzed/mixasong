/* RTcmix  - Copyright (C) 2000  The RTcmix Development Team
   See ``AUTHORS'' for a list of contributors. See ``LICENSE'' for
   the license to this software and for a DISCLAIMER OF ALL WARRANTIES.
 */
#ifndef _INSTRUMENT_H_
#define _INSTRUMENT_H_ 1

#include <bus.h>
#include <buffers.h>
#include <sys/types.h>


class Instrument {
public:
   float          start;
   float          dur;
   int            cursamp;
   int            chunksamps;
   int            endsamp;
   int            nsamps;
   unsigned long  chunkstart;
   int            output_offset;

   int            sfile_on;        // a soundfile is open (for closing later)
   int            fdIndex;         // index into unix input file desc. table
   off_t          fileOffset;      // current offset in file for this inst

   double         inputsr;
   int            inputchans;
   int            outputchans;

   int            mytag;           // for note tagging/rtupdate() 

   BUFTYPE        *inbuf;          // private interleaved buffers
   BUFTYPE        *outbuf;

   BusSlot        *bus_config;

private:
   BUFTYPE        *obufptr;
   short          bufstatus[MAXBUS];
   short          needs_to_run;

public:
   Instrument();
   virtual ~Instrument();
   void set_bus_config(const char *);
   virtual int init(float *, short);
   virtual int run();

   void exec(BusType bus_type, int bus);
   int rtaddout(BUFTYPE samps[]);  // replacement for old rtaddout
   void addout(BusType bus_type, int bus);

   float getstart();
   float getdur();
   int getendsamp();
   void setendsamp(int);
   void setchunk(int);
   void set_output_offset(int);
   void setchunkstart(int);  // FIXME:  get rid of this soon DJT
private:
   void gone();                    // decrements reference to input soundfile

};


// some prototypes that probably don't belong here
void heapify(Instrument *);
void heapSched(Instrument *);
int rtsetoutput(float, float, Instrument *);
int rtsetinput(float, Instrument *);
int rtgetin(float *, Instrument *, int);
float rtupdate(int, int);  // tag, p-field for return value


#endif /* _INSTRUMENT_H_  */
