#include <bus.h>        /* for MAXBUS */

class STEREO : public Instrument {
	float outspread[MAXBUS];
	float amp, *amptable, tabs[2], *in;
	int skip, branch;

public:
	STEREO();
	virtual ~STEREO();
	int init(float*, int);
	int run();
	};
