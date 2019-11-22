 // Helper functions for music

#include <cs50.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = fraction[0] - '0';
    int y = fraction[2] - '0';

    return round(8.0/y * x);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int octave;
    char accidental = '\0';
    char letter = note[0];
    if (note[1] == '#' || note[1] == 'b')
    {
        accidental = note[1];
        octave = note[2] - '0';

    }
    else
    {
        octave = note[1] - '0';
    }

    int interval;

    switch (letter) {
        case 'A':
            interval = 0;
            break;
        case 'B':
            interval = 2;
            break;
        case 'C':
            interval = -9;
            break;
        case 'D':
            interval = -7;
            break;
        case 'E':
            interval = -5;
            break;
        case 'F':
            interval = -4;
            break;
        case 'G':
            interval = -2;
            break;
        default:
            interval = 0;
    }

    if (accidental == '#')
    {
        interval++;
    }
    else if (accidental == 'b')
    {
        interval--;
    }

    // make interval include octave
    interval = interval + 12 * (octave - 4);

    int frequency = round(pow(2, interval/12.0) * 440);

    return frequency;


}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\n' || s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}
