class PULSE : public Instrument {
	float myrsnetc[64][5],myamp[64];
	int mynresons;
	float oamp,*amparr,amptabs[2];
	float si,phase;
	int skip;
	float spread;

public:
	PULSE();
	int init(float*, short);
	int run();
	};
