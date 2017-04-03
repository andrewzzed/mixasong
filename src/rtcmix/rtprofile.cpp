// this is for non-rt instruments to link to in order to resolve
// the rtprofile symbol.  rt instruments use this to make a symbol
// entry for Minc
#include <rt.h>

#ifndef EMBEDDED
extern "C" void rtprofile() {};

#else // EMBEDDED
void
rtprofile()
{
// base
	RT_INTRO("MIX",makeMIX);
	RT_INTRO("WAVETABLE",makeWAVETABLE);
	RT_INTRO("CHAIN",makeCHAIN);
// std
	RT_INTRO("AM",makeAM);
	RT_INTRO("AMINST",makeAMINST);
	RT_INTRO("CLAR",makeCLAR);
	RT_INTRO("COMBIT",makeCOMBIT);
	RT_INTRO("DEL1",makeDEL1);
	RT_INTRO("DELAY",makeDELAY);
	RT_INTRO("FIR",makeFIR);
	RT_INTRO("FMINST",makeFMINST);
	RT_INTRO("HOLO",makeHOLO);
	RT_INTRO("INPUTSIG",makeINPUTSIG);
	RT_INTRO("IINOISE",makeIINOISE);
	RT_INTRO("BUZZ",makeBUZZ);
	RT_INTRO("PULSE",makePULSE);
	RT_INTRO("LPCPLAY", makeLPCPLAY);
	RT_INTRO("LPCIN", makeLPCIN);
	RT_INTRO("SGRANR",makeSGRANR);
	RT_INTRO("STGRANR",makeSTGRANR);
	RT_INTRO("SFLUTE",makeSFLUTE);
	RT_INTRO("BSFLUTE",makeBSFLUTE);
	RT_INTRO("VSFLUTE",makeVSFLUTE);
	RT_INTRO("LSFLUTE",makeLSFLUTE);
#ifndef USE_MMOVE
	RT_INTRO("MOVE", makeMOVE);
	RT_INTRO("PLACE", makePLACE);
#else
	RT_INTRO("DMOVE", makeDMOVE);
	RT_INTRO("MMOVE", makeMMOVE);
	RT_INTRO("MPLACE", makeMPLACE);
	RT_INTRO("RVB", makeRVB);
#endif
	RT_INTRO("MOCKBEND", makeMOCKBEND);
	RT_INTRO("MULTICOMB",makeMULTICOMB);
	RT_INTRO("NOISE",makeNOISE);
	RT_INTRO("PANECHO",makePANECHO);
	RT_INTRO("PHASER", makePHASER);
	RT_INTRO("PVOC", makePVOC);
	RT_INTRO("REVMIX", makeREVMIX);
	RT_INTRO("SCRUB", makeSCRUB);
	RT_INTRO("SCULPT",makeSCULPT);
	RT_INTRO("STEREO",makeSTEREO);
	RT_INTRO("BEND",makeBEND);
	RT_INTRO("BEND1",makeBEND1);
	RT_INTRO("FRET",makeFRET);
	RT_INTRO("FRET1",makeFRET1);
	RT_INTRO("START",makeSTART);
	RT_INTRO("START1",makeSTART1);
	RT_INTRO("VFRET1",makeVFRET1);
	RT_INTRO("VSTART1",makeVSTART1);
	RT_INTRO("STRUM2",makeSTRUM2);
	RT_INTRO("STRUMFB",makeSTRUMFB);
	RT_INTRO("TRANS", makeTRANS);
	RT_INTRO("TRANS3", makeTRANS3);
	RT_INTRO("TRANSBEND", makeTRANSBEND);
	RT_INTRO("WAVESHAPE",makeWAVESHAPE);
// jg
	RT_INTRO("BUTTER", makeBUTTER);
	RT_INTRO("COMPLIMIT", makeCOMPLIMIT);
	RT_INTRO("CONVOLVE1", makeCONVOLVE1);
	RT_INTRO("DCBLOCK", makeDCBLOCK);
	RT_INTRO("DECIMATE", makeDECIMATE);
	RT_INTRO("DISTORT", makeDISTORT);
	RT_INTRO("ELL", makeELL);
	RT_INTRO("EQ",makeEQ);
	RT_INTRO("FILTERBANK", makeFILTERBANK);
	RT_INTRO("FILTSWEEP", makeFILTSWEEP);
	RT_INTRO("FLANGE", makeFLANGE);
	RT_INTRO("FOLLOWBUTTER", makeFOLLOWBUTTER);
	RT_INTRO("FOLLOWER", makeFOLLOWER);
	RT_INTRO("FOLLOWGATE", makeFOLLOWGATE);
	RT_INTRO("FREEVERB", makeFREEVERB);
	RT_INTRO("GRANSYNTH", makeGRANSYNTH);
	RT_INTRO("JCHOR", makeJCHOR);
	RT_INTRO("JDELAY", makeJDELAY);
	RT_INTRO("JFIR", makeJFIR);
	RT_INTRO("JGRAN", makeJGRAN);
	RT_INTRO("MOOGVCF", makeMOOGVCF);
	RT_INTRO("MROOM", makeMROOM);
	RT_INTRO("MULTEQ", makeMULTEQ);
	RT_INTRO("MULTIWAVE", makeMULTIWAVE);
	RT_INTRO("PAN", makePAN);
	RT_INTRO("REV", makeREV);
	RT_INTRO("REVERBIT", makeREVERBIT);
	RT_INTRO("ROOM", makeROOM);
	RT_INTRO("SHAPE", makeSHAPE);
	RT_INTRO("SPECTACLE", makeSPECTACLE);
	RT_INTRO("SPECTEQ", makeSPECTEQ);
	RT_INTRO("TVSPECTACLE", makeTVSPECTACLE);
	RT_INTRO("SPECTACLE2", makeSPECTACLE2);
	RT_INTRO("SPECTEQ2", makeSPECTEQ2);
	RT_INTRO("SPLITTER", makeSPLITTER);
	RT_INTRO("VOCODE2", makeVOCODE2);
	RT_INTRO("VOCODE3", makeVOCODE3);
	RT_INTRO("VOCODESYNTH", makeVOCODESYNTH);
	RT_INTRO("WAVY", makeWAVY);
	RT_INTRO("WIGGLE", makeWIGGLE);
// stk
	RT_INTRO("MBANDEDWG", makeMBANDEDWG);
	RT_INTRO("MBLOWBOTL", makeMBLOWBOTL);
	RT_INTRO("MBLOWHOLE", makeMBLOWHOLE);
	RT_INTRO("MBOWED", makeMBOWED);
	RT_INTRO("MBRASS", makeMBRASS);
	RT_INTRO("MCLAR", makeMCLAR);
	RT_INTRO("MMESH2D", makeMMESH2D);
	RT_INTRO("MMODALBAR", makeMMODALBAR);
	RT_INTRO("MSAXOFONY", makeMSAXOFONY);
	RT_INTRO("MSHAKERS", makeMSHAKERS);
	RT_INTRO("MSITAR", makeMSITAR);
// maxmsp
	RT_INTRO("MAXBANG",makeMAXBANG);
	RT_INTRO("MAXMESSAGE",makeMAXMESSAGE);
// bgg
	RT_INTRO("GVERB",makeGVERB);
	RT_INTRO("HALFWAVE",makeHALFWAVE);
	RT_INTRO("PFSCHED",makePFSCHED);
	RT_INTRO("SYNC",makeSYNC);
	RT_INTRO("VWAVE",makeVWAVE);
// neil
	RT_INTRO("BROWN", makeBROWN);
	RT_INTRO("CRACKLE", makeCRACKLE);
	RT_INTRO("DUST", makeDUST);
	RT_INTRO("HENON", makeHENON)
	RT_INTRO("LATOOCARFIAN", makeLATOOCARFIAN);
	RT_INTRO("MULTIFM", makeMULTIFM);
	RT_INTRO("PINK", makePINK);
}
#endif
