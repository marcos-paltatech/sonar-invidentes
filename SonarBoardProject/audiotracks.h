#ifndef AUDIOTRACKS_H
#define AUDIOTRACKS_H

#include <stdint.h>

#define TRACKS_COUNT  24
const uint16_t TRACKS_PAGES[] = {
       0,  // Track Index  0: "dir_front.raw"
      28,  // Track Index  1: "dir_left.raw"
      64,  // Track Index  2: "dir_right.raw"
      98,  // Track Index  3: "dist_close.raw"
     131,  // Track Index  4: "dist_far.raw"
     167,  // Track Index  5: "dist_nearby.raw"
     221,  // Track Index  6: "dist_veryclose.raw"
     265,  // Track Index  7: "lowbatt.raw"
     314,  // Track Index  8: "meters_01.raw"
     362,  // Track Index  9: "meters_02.raw"
     413,  // Track Index 10: "meters_03.raw"
     465,  // Track Index 11: "meters_04.raw"
     515,  // Track Index 12: "meters_05.raw"
     572,  // Track Index 13: "meters_06.raw"
     629,  // Track Index 14: "meters_07.raw"
     685,  // Track Index 15: "meters_08.raw"
     736,  // Track Index 16: "meters_09.raw"
     787,  // Track Index 17: "meters_10.raw"
     840,  // Track Index 18: "meters_half.raw"
     889,  // Track Index 19: "mode_dist.raw"
     953,  // Track Index 20: "mode_fuzzy.raw"
    1006,  // Track Index 21: "starting.raw"
    1055,  // Track Index 22: "test_chirp.raw"
    1680,  // Track Index 23: "text_foxy.raw"
    2010   // Not a track, used to calculate the last track's size
};

#endif // AUDIOTRACKS_H
