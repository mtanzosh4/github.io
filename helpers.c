// Helper functions for music

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';
    return 8.0 * (double) numerator / denominator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char n[3];
    int octave = 0;
    if (strlen(note) == 2)
    {
        n[0] = note[0];
        n[1] = '\0';
        octave = note[1] - '0';
    }
    else if (strlen(note) == 3)
    {
        n[0] = note[0];
        n[1] = note[1];
        n[2] = '\0';
        octave = note[2] - '0';
    }

    // Calculate relative to A440
    double f = 440;

    // Determine how many semitones away to move
    int semitones = 0;
    switch (toupper((unsigned char) n[0]))
    {
        case 'A':
            octave++;
            break;
        case 'B':
            semitones = 2;
            octave++;
            break;
        case 'C':
            semitones = 3;
            break;
        case 'D':
            semitones = 5;
            break;
        case 'E':
            semitones = 7;
            break;
        case 'F':
            semitones = 8;
            break;
        case 'G':
            semitones = 10;
            break;
        default:
            f = 0;
    }

    // Adjust for sharps and flats
    if (n[1] == '#')
    {
        semitones++;
    }
    else if (n[1] == 'b')
    {
        semitones--;
    }

    // Compute the final frequency
    return round(f * pow(2.0, semitones / 12.0 + octave - 5.0));
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
