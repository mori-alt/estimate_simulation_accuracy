#include <iostream>
#include "spectra_data.h"

const unsigned long MIN_WAVELENGTH = 360; //[nm]
const unsigned long MAX_WAVELENGTH = 830; //[nm]

/* data */
const double g_ColorMatchingFunction_x[] = {
        //360nm
        0.000000122200,
        //361 -> 370
        0.000000185138, 0.00000027883, 0.00000041747, 0.00000062133, 0.00000091927,
        0.00000135198, 0.00000197654, 0.0000028725, 0.0000041495, 0.0000059586,
        //371 -> 380
        0.0000085056, 0.0000120686, 0.0000170226, 0.000023868, 0.000033266,
        0.000046087, 0.000063472, 0.000086892, 0.000118246, 0.000159952,
        //381 -> 390
        0.000215080, 0.00028749, 0.00038199, 0.00050455, 0.00066244,
        0.00086450, 0.00112150, 0.00144616, 0.00185359, 0.0023616,
        //391 -> 400
        0.0029906, 0.0037645, 0.0047102, 0.0058581, 0.0072423,
        0.0088996, 0.0108709, 0.0131989, 0.0159292, 0.0191097,
        //401 -> 410
        0.022788, 0.027011, 0.031829, 0.037278, 0.043400,
        0.050223, 0.057764, 0.066038, 0.075033, 0.084736,
        //411 -> 420
        0.095041, 0.105836, 0.117066, 0.128682, 0.140638,
        0.152893, 0.165416, 0.178191, 0.191214, 0.204492,
        //421 -> 430
        0.217650, 0.230267, 0.242311, 0.253793, 0.264737,
        0.275195, 0.285301, 0.295143, 0.304869, 0.314679,
        //431 -> 440
        0.324355, 0.333570, 0.342243, 0.350312, 0.357719,
        0.364482, 0.370493, 0.375727, 0.380158, 0.383734,
        //441 -> 450
        0.386327, 0.387858, 0.388396, 0.387978, 0.386726,
        0.384696, 0.382006, 0.378709, 0.374915, 0.370702,
        //451 -> 460
        0.366089, 0.361045, 0.355518, 0.349486, 0.342957,
        0.335893, 0.328284, 0.320150, 0.311475, 0.302273,
        //461 -> 470
        0.292858, 0.283502, 0.274044, 0.264263, 0.254085,
        0.243392, 0.232187, 0.220488, 0.208198, 0.195618,
        //471 -> 480
        0.183034, 0.170222, 0.157348, 0.144650, 0.132349,
        0.120584, 0.109456, 0.099042, 0.089388, 0.080507,
        //481 -> 490
        0.072034, 0.063710, 0.055694, 0.048117, 0.041072,
        0.034642, 0.028896, 0.023876, 0.019628, 0.016172,
        //491 -> 500
        0.013300, 0.010759, 0.008542, 0.006661, 0.005132,
        0.003982, 0.003239, 0.002934, 0.003114, 0.003816,
        //501 -> 510
        0.005095, 0.006936, 0.009299, 0.012147, 0.015444,
        0.019156, 0.023250, 0.027690, 0.032444, 0.037465,
        //511 -> 520
        0.042956, 0.049114, 0.055920, 0.063349, 0.071358,
        0.079901, 0.088909, 0.098293, 0.107949, 0.117749,
        //521 -> 530
        0.127839, 0.138450, 0.149516, 0.161041, 0.172953,
        0.185209, 0.197755, 0.210538, 0.223460, 0.236491,
        //531 -> 540
        0.249633, 0.262972, 0.276515, 0.290269, 0.304213,
        0.318361, 0.332705, 0.347232, 0.361926, 0.376772,
        //541 -> 550
        0.391683, 0.406594, 0.421539, 0.436517, 0.451584,
        0.466782, 0.482147, 0.497738, 0.513606, 0.529826,
        //551 -> 560
        0.546440, 0.563426, 0.580726, 0.598290, 0.616053,
        0.633948, 0.651901, 0.669824, 0.687632, 0.705224,
        //561 -> 570
        0.722773, 0.740483, 0.758273, 0.776083, 0.793832,
        0.811436, 0.828822, 0.845879, 0.862525, 0.878655,
        //571 -> 580
        0.894208, 0.909206, 0.923672, 0.937638, 0.951162,
        0.964283, 0.977068, 0.989590, 1.00191, 1.01416,
        //581 -> 590
        1.02650, 1.03880, 1.05100, 1.06290, 1.07430,
        1.08520, 1.09520, 1.10420, 1.11200, 1.11852,
        //591 -> 600
        1.12380, 1.12800, 1.13110, 1.13320, 1.13430,
        1.13430, 1.13330, 1.13120, 1.12810, 1.12399,
        //601 -> 610
        1.11890, 1.11290, 1.10590, 1.09800, 1.08910,
        1.07920, 1.06840, 1.05670, 1.04400, 1.03048,
        //611 -> 620
        1.01600, 1.00080, 0.984790, 0.968080, 0.950740,
        0.932800, 0.914340, 0.895390, 0.876030, 0.856297,
        //621 -> 630
        0.836350, 0.816290, 0.796050, 0.775610, 0.754930,
        0.733990, 0.712780, 0.691290, 0.669520, 0.647467,
        //631 -> 640
        0.625110, 0.602520, 0.579890, 0.557370, 0.535110,
        0.513240, 0.491860, 0.471080, 0.450960, 0.431567,
        //641 -> 650
        0.412870, 0.394750, 0.377210, 0.360190, 0.343690,
        0.327690, 0.312170, 0.297110, 0.282500, 0.268329,
        //651 -> 660
        0.254590, 0.241300, 0.228480, 0.216140, 0.204300,
        0.192950, 0.182110, 0.171770, 0.161920, 0.152568,
        //661 -> 670
        0.143670, 0.135200, 0.127130, 0.119480, 0.112210,
        0.105310, 0.0987860, 0.0926100, 0.0867730, 0.0812606,
        //671 -> 680
        0.0760480, 0.0711140, 0.0664540, 0.0620620, 0.0579300,
        0.0540500, 0.0504120, 0.0470060, 0.0438230, 0.0408508,
        //681 -> 690
        0.0380720, 0.0354680, 0.0330310, 0.0307530, 0.0286230,
        0.0266350, 0.0247810, 0.0230520, 0.0214410, 0.0199413,
        //691 -> 700
        0.0185440, 0.0172410, 0.0160270, 0.0148960, 0.0138420,
        0.0128620, 0.0119490, 0.0111000, 0.0103110, 0.00957688,
        //701 -> 710
        0.00889400, 0.00825810, 0.00766640, 0.00711630, 0.00660520,
        0.00613060, 0.00569030, 0.00528190, 0.00490330, 0.00455263,
        //711 -> 720
        0.00422750, 0.00392580, 0.00364570, 0.00338590, 0.00314470,
        0.00292080, 0.00271300, 0.00252020, 0.00234110, 0.00217496,
        //721 -> 730
        0.00202060, 0.00187730, 0.00174410, 0.00162050, 0.00150570,
        0.00139920, 0.00130040, 0.00120870, 0.00112360, 0.00104476,
        //731 -> 740
        0.000971560, 0.000903600, 0.000840480, 0.000781870, 0.000727450,
        0.000676900, 0.000629960, 0.000586370, 0.000545870, 0.000508258,
        //741 -> 750
        0.000473300, 0.000440800, 0.000410580, 0.000382490, 0.000356380,
        0.000332110, 0.000309550, 0.000288580, 0.000269090, 0.000250969,
        //751 -> 760
        0.000234130, 0.000218470, 0.000203910, 0.000190350, 0.000177730,
        0.000165970, 0.00015502, 0.000144800, 0.000135280, 0.000126390,
        //761 -> 770
        0.000118100, 0.000110370, 0.000103150, 0.0000964270, 0.0000901510,
        0.0000842940, 0.0000788300, 0.0000737290, 0.0000689690, 0.0000645258,
        //771 -> 780
        0.0000603760, 0.0000565000, 0.0000528800, 0.0000494980, 0.0000463390,
        0.0000433890, 0.0000406340, 0.0000380600, 0.0000356570, 0.0000334117,
        //781 -> 790
        0.0000313150, 0.0000293550, 0.0000275240, 0.0000258110, 0.0000242090,
        0.0000227110, 0.0000213080, 0.0000199940, 0.0000187640, 0.0000176115,
        //791 -> 800
        0.0000165320, 0.0000155210, 0.0000145740, 0.0000136860, 0.0000128550,
        0.0000120750, 0.0000113450, 0.0000106590, 0.0000100170, 0.00000941363,
        //801 -> 810
        0.00000884790, 0.00000831710, 0.00000781900, 0.00000735160, 0.00000691300,
        0.00000650150, 0.00000611530, 0.00000575290, 0.00000541270, 0.00000509347,
        //811 -> 820
        0.00000479380, 0.00000451250, 0.00000424830, 0.00000400020, 0.00000376710,
        0.00000354800, 0.00000334210, 0.00000314850, 0.00000296650, 0.00000279531,
        //821 -> 830
        0.00000263450, 0.00000248340, 0.00000234140, 0.00000220780, 0.00000208200,
        0.00000196360, 0.00000185190, 0.00000174650, 0.00000164710, 0.00000155314
};

const double g_ColorMatchingFunction_y[] = {
        //360nm
        0.000000013398,
        //361 -> 370
        0.000000020294, 0.00000003056, 0.00000004574, 0.00000006805, 0.00000010065,
        0.00000014798, 0.00000021627, 0.0000003142, 0.0000004537, 0.0000006511,
        //371 -> 380
        0.0000009288, 0.0000013175, 0.0000018572, 0.000002602, 0.000003625,
        0.000005019, 0.000006907, 0.000009449, 0.000012848, 0.000017364,
        //381 -> 390
        0.000023327, 0.00003115, 0.00004135, 0.00005456, 0.00007156,
        0.00009330, 0.00012087, 0.00015564, 0.00019920, 0.0002534,
        //391 -> 400
        0.0003202, 0.0004024, 0.0005023, 0.0006232, 0.0007685,
        0.0009417, 0.0011478, 0.0013903, 0.0016740, 0.0020044,
        //401 -> 410
        0.002386, 0.002822, 0.003319, 0.003880, 0.004509,
        0.005209, 0.005985, 0.006833, 0.007757, 0.008756,
        //411 -> 420
        0.009816, 0.010918, 0.012058, 0.013237, 0.014456,
        0.015717, 0.017025, 0.018399, 0.019848, 0.021391,
        //421 -> 430
        0.022992, 0.024598, 0.026213, 0.027841, 0.029497,
        0.031195, 0.032927, 0.034738, 0.036654, 0.038676,
        //431 -> 440
        0.040792, 0.042946, 0.045114, 0.047333, 0.049602,
        0.051934, 0.054337, 0.056822, 0.059399, 0.062077,
        //441 -> 450
        0.064737, 0.067285, 0.069764, 0.072218, 0.074704,
        0.077272, 0.079979, 0.082874, 0.086000, 0.089456,
        //451 -> 460
        0.092947, 0.096275, 0.099535, 0.102829, 0.106256,
        0.109901, 0.113835, 0.118167, 0.122932, 0.128201,
        //461 -> 470
        0.133457, 0.138323, 0.143042, 0.147787, 0.152761,
        0.158102, 0.163941, 0.170362, 0.177425, 0.185190,
        //471 -> 480
        0.193025, 0.200313, 0.207156, 0.213644, 0.219940,
        0.226170, 0.232467, 0.239025, 0.245997, 0.253589,
        //481 -> 490
        0.261876, 0.270643, 0.279645, 0.288694, 0.297665,
        0.306469, 0.315035, 0.323335, 0.331366, 0.339133,
        //491 -> 500
        0.347860, 0.358326, 0.370001, 0.382464, 0.395379,
        0.408482, 0.421588, 0.434619, 0.447601, 0.460777,
        //501 -> 510
        0.474340, 0.488200, 0.502340, 0.516740, 0.531360,
        0.546190, 0.561180, 0.576290, 0.591500, 0.606741,
        //511 -> 520
        0.622150, 0.637830, 0.653710, 0.669680, 0.685660,
        0.701550, 0.717230, 0.732570, 0.747460, 0.761757,
        //521 -> 530
        0.775340, 0.788220, 0.800460, 0.812140, 0.823330,
        0.834120, 0.844600, 0.854870, 0.865040, 0.875211,
        //531 -> 540
        0.885370, 0.895370, 0.905150, 0.914650, 0.923810,
        0.932550, 0.940810, 0.948520, 0.955600, 0.961988,
        //541 -> 550
        0.967540, 0.972230, 0.976170, 0.979460, 0.982200,
        0.984520, 0.986520, 0.988320, 0.990020, 0.991761,
        //551 -> 560
        0.993530, 0.995230, 0.996770, 0.998090, 0.999110,
        0.999770, 1.000000, 0.999710, 0.998850, 0.997340,
        //561 -> 570
        0.995260, 0.992740, 0.989750, 0.986300, 0.982380,
        0.977980, 0.973110, 0.967740, 0.961890, 0.955552,
        //571 -> 580
        0.948601, 0.940981, 0.932798, 0.924158, 0.915175,
        0.905954, 0.896608, 0.887249, 0.877986, 0.868934,
        //581 -> 590
        0.860164, 0.851519, 0.842963, 0.834393, 0.825623,
        0.816764, 0.807544, 0.797947, 0.787893, 0.777405,
        //591 -> 600
        0.766490, 0.755309, 0.743845, 0.732190, 0.720353,
        0.708281, 0.696055, 0.683621, 0.671048, 0.658341,
        //601 -> 610
        0.645545, 0.632718, 0.619815, 0.606887, 0.593878,
        0.580781, 0.567653, 0.554490, 0.541228, 0.527963,
        //611 -> 620
        0.514634, 0.501363, 0.488124, 0.474935, 0.461834,
        0.448823, 0.435917, 0.423153, 0.410526, 0.398057,
        //621 -> 630
        0.385835, 0.373951, 0.362311, 0.350863, 0.339554,
        0.328309, 0.317118, 0.305936, 0.294737, 0.283493,
        //631 -> 640
        0.272222, 0.260990, 0.249877, 0.238946, 0.228254,
        0.217853, 0.207780, 0.198072, 0.188748, 0.179828,
        //641 -> 650
        0.171285, 0.163059, 0.155151, 0.147535, 0.140211,
        0.133170, 0.126400, 0.119892, 0.113640, 0.107633,
        //651 -> 660
        0.101870, 0.096347, 0.091063, 0.086010, 0.081187,
        0.076583, 0.072198, 0.068024, 0.064052, 0.060281,
        //661 -> 670
        0.056697, 0.053292, 0.050059, 0.046998, 0.044096,
        0.041345, 0.0387507, 0.0362978, 0.0339832, 0.0318004,
        //671 -> 680
        0.0297395, 0.0277918, 0.0259551, 0.0242263, 0.0226017,
        0.0210779, 0.0196505, 0.0183153, 0.0170686, 0.0159051,
        //681 -> 690
        0.0148183, 0.0138008, 0.0128495, 0.0119607, 0.0111303,
        0.0103555, 0.0096332, 0.0089599, 0.0083324, 0.0077488,
        //691 -> 700
        0.0072046, 0.0066975, 0.0062251, 0.0057850, 0.0053751,
        0.0049941, 0.0046392, 0.0043093, 0.0040028, 0.00371774,
        //701 -> 710
        0.00345262, 0.00320583, 0.00297623, 0.00276281, 0.00256456,
        0.00238048, 0.00220971, 0.00205132, 0.00190449, 0.00176847,
        //711 -> 720
        0.00164236, 0.00152535, 0.00141672, 0.00131595, 0.00122239,
        0.00113555, 0.00105494, 0.00098014, 0.00091066, 0.00084619,
        //721 -> 730
        0.00078629, 0.00073068, 0.00067899, 0.00063101, 0.00058644,
        0.00054511, 0.00050672, 0.00047111, 0.00043805, 0.00040741,
        //731 -> 740
        0.000378962, 0.000352543, 0.000328001, 0.000305208, 0.000284041,
        0.000264375, 0.000246109, 0.000229143, 0.000213376, 0.000198730,
        //741 -> 750
        0.000185115, 0.000172454, 0.000160678, 0.000149730, 0.000139550,
        0.000130086, 0.000121290, 0.000113106, 0.000105501, 0.000098428,
        //751 -> 760
        0.000091853, 0.000085738, 0.000080048, 0.000074751, 0.000069819,
        0.000065222, 0.000060939, 0.000056942, 0.000053217, 0.000049737,
        //761 -> 770
        0.000046491, 0.000043464, 0.000040635, 0.0000380000, 0.0000355405,
        0.0000332448, 0.0000311006, 0.0000290990, 0.0000272307, 0.0000254860,
        //771 -> 780
        0.0000238561, 0.0000223332, 0.0000209104, 0.0000195808, 0.0000183384,
        0.0000171777, 0.0000160934, 0.0000150800, 0.0000141336, 0.0000132490,
        //781 -> 790
        0.0000124226, 0.0000116499, 0.0000109277, 0.0000102519, 0.0000096196,
        0.0000090281, 0.0000084740, 0.0000079548, 0.0000074686, 0.0000070128,
        //791 -> 800
        0.0000065858, 0.0000061857, 0.0000058107, 0.0000054590, 0.0000051298,
        0.0000048206, 0.0000045312, 0.0000042591, 0.0000040042, 0.00000376473,
        //801 -> 810
        0.00000353995, 0.00000332914, 0.00000313115, 0.00000294529, 0.00000277081,
        0.00000260705, 0.00000245329, 0.00000230894, 0.00000217338, 0.00000204613,
        //811 -> 820
        0.00000192662, 0.00000181440, 0.00000170895, 0.00000160988, 0.00000151677,
        0.00000142921, 0.00000134686, 0.00000126945, 0.00000119662, 0.00000112809,
        //821 -> 830
        0.00000106368, 0.00000100313, 0.00000094622, 0.00000089263, 0.00000084216,
        0.00000079464, 0.00000074978, 0.00000070744, 0.00000066748, 0.00000062970
};

const double g_ColorMatchingFunction_z[] = {
        //360nm
        0.000000535027,
        //361 -> 370
        0.000000810720, 0.00000122120, 0.00000182870, 0.00000272220, 0.00000402830,
        0.00000592570, 0.00000866510, 0.0000125960, 0.0000182010, 0.0000261437,
        //371 -> 380
        0.0000373300, 0.0000529870, 0.0000747640, 0.000104870, 0.000146220,
        0.000202660, 0.000279230, 0.000382450, 0.000520720, 0.000704776,
        //381 -> 390
        0.000948230, 0.00126820, 0.00168610, 0.00222850, 0.00292780,
        0.00382370, 0.00496420, 0.00640670, 0.00821930, 0.0104822,
        //391 -> 400
        0.0132890, 0.0167470, 0.0209800, 0.0261270, 0.0323440,
        0.0398020, 0.0486910, 0.0592100, 0.0715760, 0.0860109,
        //401 -> 410
        0.102740, 0.122000, 0.144020, 0.168990, 0.197120,
        0.228570, 0.263470, 0.301900, 0.343870, 0.389366,
        //411 -> 420
        0.437970, 0.489220, 0.542900, 0.598810, 0.656760,
        0.716580, 0.778120, 0.841310, 0.906110, 0.972542,
        //421 -> 430
        1.03890, 1.10310, 1.16510, 1.22490, 1.28250,
        1.33820, 1.39260, 1.44610, 1.49940, 1.53348,
        //431 -> 440
        1.60720, 1.65890, 1.70820, 1.75480, 1.79850,
        1.83920, 1.87660, 1.91050, 1.94080, 1.96728,
        //441 -> 450
        1.98910, 2.00570, 2.01740, 2.02440, 2.02730,
        2.02640, 2.02230, 2.01530, 2.00600, 1.99480,
        //451 -> 460
        1.98140, 1.96530, 1.94640, 1.92480, 1.90070,
        1.87410, 1.84510, 1.81390, 1.78060, 1.74537,
        //461 -> 470
        1.70910, 1.67230, 1.63470, 1.59560, 1.55490,
        1.51220, 1.46730, 1.41990, 1.37000, 1.31756,
        //471 -> 480
        1.26240, 1.20500, 1.14660, 1.08800, 1.03020,
        0.973830, 0.919430, 0.867460, 0.818280, 0.772125,
        //481 -> 490
        0.728290, 0.686040, 0.645530, 0.606850, 0.570060,
        0.535220, 0.502340, 0.471400, 0.442390, 0.415254,
        //491 -> 500
        0.390024, 0.366399, 0.344015, 0.322689, 0.302356,
        0.283036, 0.264816, 0.247848, 0.232318, 0.218502,
        //501 -> 510
        0.205851, 0.193596, 0.181736, 0.170281, 0.159249,
        0.148673, 0.138609, 0.129096, 0.120215, 0.112044,
        //511 -> 520
        0.104710, 0.098196, 0.092361, 0.087088, 0.082248,
        0.077744, 0.073456, 0.069268, 0.065060, 0.060709,
        //521 -> 530
        0.056457, 0.052609, 0.049122, 0.045954, 0.043050,
        0.040368, 0.037839, 0.035384, 0.032949, 0.030451,
        //531 -> 540
        0.028029, 0.025862, 0.023920, 0.022174, 0.020584,
        0.019127, 0.017740, 0.016403, 0.015064, 0.013676,
        //541 -> 550
        0.012308, 0.011056, 0.009915, 0.008872, 0.007918,
        0.007030, 0.006223, 0.005453, 0.004714, 0.003988,
        //551 -> 560
        0.003289, 0.002646, 0.002063, 0.001533, 0.001091,
        0.000711, 0.000407, 0.000184, 0.000047, 0.000000,
        //561 -> 570
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //571 -> 580
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //581 -> 590
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //591 -> 600
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //601 -> 610
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //611 -> 620
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //621 -> 630
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //631 -> 640
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //641 -> 650
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //651 -> 660
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //661 -> 670
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //671 -> 680
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //681 -> 690
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //691 -> 700
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //701 -> 710
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //711 -> 720
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //721 -> 730
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //731 -> 740
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //741 -> 750
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //751 -> 760
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //761 -> 770
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //771 -> 780
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //781 -> 790
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //791 -> 800
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //801 -> 810
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //811 -> 820
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        //821 -> 830
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0
};

// make conversion xyz from spectra
void getXYZForSpectraWindow( const unsigned long in_Lambda, const unsigned long in_DeltaLambda, Eigen::Vector3d& out_XYZ )
{
    const int minL = in_Lambda - ( in_DeltaLambda>>1 );
    const int maxL = minL + in_DeltaLambda - 1;

    out_XYZ.setZero();

    for(int k=minL; k<=maxL; k++)
    {
        const int w = k - MIN_WAVELENGTH;
//        std::cout << "w : " << w << std::endl;
        out_XYZ.x() += g_ColorMatchingFunction_x[w];
        out_XYZ.y() += g_ColorMatchingFunction_y[w];
        out_XYZ.z() += g_ColorMatchingFunction_z[w];
    }
    out_XYZ /= in_DeltaLambda;
}

void convertSpectraData2RGB( Eigen::Vector3d& out_RGB, const int in_NumSpect, const std::vector<Eigen::Vector3d>& in_Spectra2XYZ, const std::array<double, 16>& in_SpectraData, const double in_Ratio )
{
    out_RGB.setZero();

    for( int k=0; k<in_NumSpect; k++ )
    {
        out_RGB += in_SpectraData[k] * in_Spectra2XYZ[k] * in_Ratio;
    }

    //const double r =  max(0.0, 3.24071 * x - 1.53726 * y - 0.498571 * z);
    //const double g = max(0.0, -0.969258 * x + 1.87599 * y - 0.0415557 * z);
    //const double b =  max(0.0, 0.0556352 * x - 0.203996 * y + 1.05707 * z);

    //sRGB; http://www005.upp.so-net.ne.jp/fumoto/linkp25.htm
    const double r = std::max<double>( 0.0, 3.5064 * out_RGB.x() - 1.7400 * out_RGB.y() - 0.5441 * out_RGB.z() );
    const double g = std::max<double>( 0.0, -1.0690 * out_RGB.x() + 1.9777 * out_RGB.y() - 0.0352 * out_RGB.z() );
    const double b = std::max<double>( 0.0, 0.0563 * out_RGB.x() - 0.1970 * out_RGB.y() + 1.0511 * out_RGB.z() );

    const double R = ( r <= 0.0031308 ) ? 12.92 * r : 1.055 * pow( r, 1.0/2.4 ) - 0.055;
    const double G = ( g <= 0.0031308 ) ? 12.92 * g : 1.055 * pow( g, 1.0/2.4 ) - 0.055;
    const double B = ( b <= 0.0031308 ) ? 12.92 * b : 1.055 * pow( b, 1.0/2.4 ) - 0.055;

    //const double exposure = 0.75;

    out_RGB.x() = std::max<double>( 0.0, r ) * 255;//R;//1.0 - exp(-R*exposure);
    out_RGB.y() = std::max<double>( 0.0, g ) * 255;//G;//1.0 - exp(-G*exposure);
    out_RGB.z() = std::max<double>( 0.0, b ) * 255;//B;//1.0 - exp(-B*exposure);

    if(out_RGB.x() > 255 | out_RGB.y() > 255 | out_RGB.z() > 255){
        std::cout << "over 225" << std::endl;
        std::cout << out_RGB.transpose() << std::endl;
    }

    // normalize 0 - 255 to output pdf with python
    out_RGB.x() = std::min<double>( 255, r );//R;//1.0 - exp(-R*exposure);
    out_RGB.y() = std::min<double>( 255, g );//G;//1.0 - exp(-G*exposure);
    out_RGB.z() = std::min<double>( 255, b );//B;//1.0 - exp(-B*exposure);



//    out_RGB.x() = std::max<double>( 0.0, r );//R;//1.0 - exp(-R*exposure);
//    out_RGB.y() = std::max<double>( 0.0, g );//G;//1.0 - exp(-G*exposure);
//    out_RGB.z() = std::max<double>( 0.0, b );//B;//1.0 - exp(-B*exposure);
}
