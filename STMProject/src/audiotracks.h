#ifndef AUDIOTRACKS_H
#define AUDIOTRACKS_H

#define TRACKS_COUNT  7
const uint16_t TRACKS_PAGES[] = {
       0,  // Track Index  0: "Track0.raw"
     152,  // Track Index  1: "Track1.raw"
     403,  // Track Index  2: "Track2.raw"
     606,  // Track Index  3: "Track3.raw"
    1004,  // Track Index  4: "Track4.raw"
    1263,  // Track Index  5: "Track5.raw"
    1591,  // Track Index  6: "Track6.raw"
    1722,  // Not a track, used to calculate the last track's size
};

#endif // AUDIOTRACKS_H
