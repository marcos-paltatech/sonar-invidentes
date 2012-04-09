#ifndef AUDIOTRACKS_H
#define AUDIOTRACKS_H

#define TRACKS_COUNT  9
const uint16_t TRACKS_PAGES[] = {
       0,  // Track Index  0: "1khz.raw"
    1563,  // Track Index  1: "Track0.raw"
    1715,  // Track Index  2: "Track1.raw"
    1966,  // Track Index  3: "Track2.raw"
    2169,  // Track Index  4: "Track3.raw"
    2567,  // Track Index  5: "Track4.raw"
    2826,  // Track Index  6: "Track5.raw"
    3154,  // Track Index  7: "Track6.raw"
    3285,  // Track Index  8: "chirp.raw"
    3910   // Not a track, used to calculate the last track's size
};

#endif // AUDIOTRACKS_H
