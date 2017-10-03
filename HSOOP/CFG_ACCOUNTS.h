#pragma once

#include <string>
using namespace std;

const enum ACCOUNT_CHEATS
{
	FIRST_ELEMENT_OF_AVAILIABLE_CHEATS = 1337,
	//---------------------------

	eESP,
	eFB,
	eNOSMOKE,
	eNOFOG,
	eGLOW,
	eAIM,
	eBH,
	eCEILING,
	eINCAPNORECOIL,
	eNORECOIL,

	//---------------------------
	LAST_ELEMENT_OF_AVAILIABLE_CHEATS
};

const typedef struct
{
	string sNICKNAME;
	long long int iSTEAM_ID;
	bool bSTEAMID_CHECK;

	string sHARDWARE_ID;
	bool bHARDWAREID_CHECK;

	const int iDATE_LICENSE[3];
	const int iTIME_LICENSE[3];
	bool bSUBSCRIPTION_CHECK;

	int iAVAIL_CHEATS[LAST_ELEMENT_OF_AVAILIABLE_CHEATS - FIRST_ELEMENT_OF_AVAILIABLE_CHEATS - 1];

} Account;

// EXAMPLE:
// Account acc_var		= { nickname,            steam_id,    check_steamid, "hardware-id",  check_hard, { d,m,year }, { h, m, s }, check_date, { cheats_for_this_account_avaliable } };

Account ACC_HAVENICEDAY	= { "Have a nice day, Happy New Year 2017 :D", 76561198044433497, false, "c5ac8c4b25baab46fb32bf2fdc7d881a3372a6df85ddb3021230ea2133cc67e1", true, { 1, 3, 2017 }, { 0, 0, 0 }, true, { eFB, eBH, eCEILING } };

Account ACC_TEST		= { "MaKapoIIIka", 76561198012936235, true, "a2533a380469113f8471ce93640c0eb85fee3ead79a02dd0f9d0b38ee440beaf", false, { 4, 1, 2017, }, { 17, 39, 0 }, true, { eCEILING, eBH } };
Account ACC_TEST2		= { "Santa", 76561198078455299, true, "00000000000000000", false, { 4, 6, 2017, }, { 18, 35, 49 }, true, { eGLOW, eESP, eFB } };

Account ACC_ARTEM		= { "DeadGhost1903", 76561198018916609, true, "00-FF-BB-E9-02-39", false, { 1, 8, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_ASTARION	= { "Astarion", 76561198116778643, false, "5e0b190f5a6ba1c94c9f1f0f652cadee2415ef97fdeae19b914e03908291bdd8", true, { 12, 9, 2017 }, { 20, 21, 14 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_JACOB 	= { "Jacob", 76561198078455299, true, "5e0b190f5a6ba1c94c9f1f0f652cadee2415ef97fdeae19b914e03908291bdd8", false, { 12, 9, 2017 }, { 20, 21, 14 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_KPUOH		= { "KpuoH", 76561198003928964, false, "9a4da283dd6eae70ea3da98e7c348dbb42eace07e64134b31c1c2c042282f8ee", true, { 1, 6, 2016 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_KPUOH2		= { "KpuoH", 76561198003928964, false, "40fbc7620da1e85a4294461eb9223c4754e2ada0db87621569c0e3e6125fec80", true, { 1, 6, 2016 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_FROST		= { "frost", 76561198150813246, true, "00000000000000000", false, { 1, 7, 2016 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_FROST2		= { "frost", 76561198021767753, true, "00000000000000000", false, { 1, 7, 2016 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_ENGINE		= { "engine", 76561197961723395, true, "00000000000000000", false, { 1, 7, 2016 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_ZORKA		= { "3opbka", 76561198006698139, true, "00000000000000000", false, { 1, 7, 2016 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_INVIRICO	= { "INVISIBLE and RiCOSHET", 76561197993648040, false, "6affb87505c22b9ae993eae746e71f1c69c04575c9bc56a5be0380a215bdbee6", true, { 4, 1, 2017 }, { 17, 39, 0 }, true, { eBH, eCEILING } };

Account ACC_REAL1		= { "REAL", 76561198040543233, true, "00000000000000000", false, { 1, 7, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_REAL2		= { "REAL", 76561198301554705, true, "00000000000000000", false, { 1, 7, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_BAD			= { "BAD", 76561198203180051, true, "BC-EE-7B-75-6B-7D", true, { 1, 9, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_SECRED		= { "SecreD", 76561198074755730, true, "00000000000000000", false, { 17, 5, 2016 }, { 16, 30, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_RUSTAM_FUNKYSOUL	= { "FunkySoul", 76561198120074705, false, "d4165dc720f726e9c5650b4b971afb1b48865062e4ec9e928375311ea40fc7b9", true, { 6, 4, 2017 }, { 12, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_GINTER		= { "GINTER", 76561198098699120, false, "83f769dd457039193b61d5bc08a87c0b8e33d0152278ea89c39af7f9f70a48c6", true, { 25, 6, 2016 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_ZHANGIR		= { "Zhangir", 76561198070199951, true, "00000000000000000", false, { 6, 7, 2016 }, { 0, 0, 0 },  true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_KNOPKA		= { "Knopka", 76561198070199951, false, "a7427a291cd1e01dbb440f4f032e72f1c0dfa9f61a7bcab79325566ade7a1883", true, { 1, 7, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_NAR			= { "NAR", 76561198006225436, true, "00000000000000000", false, { 5, 6, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_PANTILEI	= { "PANTILEI", 76561198069609796, true, "E8-40-F2-8C-9E-9C", true, { 1, 12, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_HARDSTYLE	= { "Hardstyle", 76561198282289416, false, "62b7e9560b3ba31abcccfc17661215af8211f5059d6a31aff498802c961a638d", true, { 1, 11, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_VASYA		= { "Vasya", 76561198304384224, false, "218e25a56d9897437d0f9ed337d66c4ebc7df9c06676d2fa2cdb16831fcdb00a", true, { 1, 11, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_MEOWLY		= { "Meowly", 76561198021767753, false, "00-25-22-D0-B4-CB", true, { 7, 8, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_WIZKID		= { "Wizkid, Enjoy!", 76561198033341507, true, "00000000000000000", false, { 1, 2, 2017 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_WIZKID2		= { "Wizkid, 2nd acc", 76561198267202191, true, "00000000000000000", false, { 1, 2, 2017 }, { 0, 0, 0 }, false, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_MOTYA		= { "Motya", 76561198080367200, true, "00000000000000000", false, { 1, 11, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_YANOCHKA1	= { "Yanochka", 76561198005714731, false, "2e791e4d6c254b65291051014de1ea351761727679c218c714f8c4ff861d5740", true, { 1, 4, 2017 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_YANOCHKA2	= { "Yanochka", 76561198005714731, false, "31bfdf38ed20ff7f79d981921b6eb68f9b26500253c82662048439ada1cad5af", true, { 1, 4, 2017 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };
Account ACC_YANOCHKA3	= { "Yanochka", 76561198005714731, false, "2489694fdd9e4a0f7b3b114d1ee7e74aabfc9e1c47ac353e1534b06d791f2913", true, { 1, 4, 2017 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_UK_HULK		= { "Incredible HULK", 76561198096946767, false, "a77e3b0e79b6eb643fab64dd9a3a88a357013274f8b2ab6016e86693ecb5a0bd", true, { 1, 11, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_STAFF		= { "StaFF", 76561198024451238, false, "1ab8f1d32a93f70cfef2480897c015b79bc95590999e5f7af523cdd192c844c0", true, { 7, 11, 2016 }, { 0, 0, 0 }, true, { eESP, eFB, eNOSMOKE, eNOFOG, eGLOW, eAIM, eBH, eCEILING, eINCAPNORECOIL, eNORECOIL } };

Account ACC_OKSI		= { "OksI", 76561198081883922, false, "c83c299f3cd0da04195dc9e5ddf6487244a87ab632e7ab0e28f62152e488c480", true, { 30, 12, 2016 }, { 20, 0, 0 }, true, { eGLOW } };

Account ACC_N2K		= { "n2k c:", 76561198165639670, true, "c83c299f3cd0da04195dc9e5ddf6487244a87ab632e7ab0e28f62152e488c480", false, { 1, 11, 2017 }, { 0, 0, 0 }, true, { eCEILING, eBH } };

