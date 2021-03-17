/*
==============================================================
 Filename    :  functions.h
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  none.
 Description :  The aim of this file is to support the main with functions and structs.
==============================================================
*/

//#include <SDL.h>       // For drawing pixels and getting user input.
#include <chrono>      // For time.
#include <iostream>    // cout.
#include <thread>      // To make more threads.
#include <vector>      // Vector for visited matrix.

// Pixel struct so two integer coordinates can be passed easily
struct Pixel {
    int x;
    int y;

    Pixel() {}

    Pixel(int xIn, int yIn)
    {
        x = xIn;
        y = yIn;
    }
};

// Point struct so two floating coordinates can be passed easily
struct Point {
    float x;
    float y;
};

// TwoSolutions struct so two floating solutions can be passed easily
struct TwoSolutions {
    float x0;
    float x1;
};

// Blob (binary large object) struct to easily model the vector field
struct Blob {
    float wells[2][2] = {{-100, -50}, {100, 50}};

    // potential() returns the potential of the coordinate indicated by Point p.
    // @param p Point struct with x-y-coordinates.
    // @returns Floating number that represents the potential at those
    // coordinates.
    float potential(Point p) { return potential(p.x, p.y); }

    // potential() Returns the potential of the point indicated by the
    // coordinates x and y.
    // @param x x-coordinate.
    // @param y y-coordinate.
    // @returns Floating number that represents the potential at those
    // coordinates.
    float potential(float x, float y)
    {
        const float scale = 100;
        float potential = 0.0f;
        for (auto well : wells) {
            potential +=
                scale / (float)(pow(x - well[0], 2) + pow(y - well[1], 2));
        }
        return potential;
    }

    // update() Updates the position of the wells
    // @param time The current time.
    void update(float time)
    {
        // Move the wells a little
        wells[0][0] = -100 + 30 * sinf(time / 7);
        wells[0][1] = -50 * cosf(time / 5);
        wells[1][0] = -wells[0][0];
        wells[1][1] = -wells[0][1];
    }

    // findXContour() finds the coordinate of the x contour for a given
    // threshold and y coordinate.
    // @param threshold The threshold of which the contour must be found.
    // @param y The y coordinate on which the contour must be found.
    // @returns TwoSolutions struct with two possible x coordinates.
    TwoSolutions findXContour(float threshold, float y)
    {
        TwoSolutions twoSolutions;
        twoSolutions.x0 = NAN;
        const float scale = 100;
        for (auto well : wells) { // Rewritten equation, solve for x
            float solution = (float)-(
                sqrt(((scale) / (threshold)) - pow(y - well[1], 2)) + well[0]);
            if (isnan(twoSolutions.x0)) {
                twoSolutions.x0 = solution;
            } else {
                twoSolutions.x1 = solution;
            }
        }
        return twoSolutions;
    }
};

// compareWithPreviousPixel() returns true if the potential of the current and 
// previous pixel (horizonally) are not on the same side of the threshold.
// @param blob Binary large object so the function can interact with the
// potential scalar field.
// @param x x coordinate of the current pixel.
// @param y y coordinate of the current pixel.
// @param threshold is the threshold (duh).
bool compareWithPreviousPixel(Blob &blob, float x, float y, float threshold)
{
    return ((blob.potential((float)x, (float)y) <= threshold &&
             blob.potential((float)x - 1.0f, (float)y) >
                 threshold) || // check whether the potential field has
            (blob.potential((float)x, (float)y) >= threshold &&
             blob.potential((float)x - 1.0f, (float)y) < threshold));
}

// marchingSquaresSecondPhase() is the second phase of the marching squares
// algorithm. While there are pixels in the worklist it draws the pixel if it
// crosses the threshold and adds surrounding pixels to the worklist.
// @param worklist List with coordinates of the pixels that should be evaluated.
// @param sizeX Width of the window (in pixels).
// @param sizeY Height of the window (in pixels).
// @param visitedlist 2D bool matrix of all pixels. True if visited, false
// otherwise.
// @param ui UI object for interaction with window and user.
// @param blob Blob object for interaction with the scalar potential field.
// @param threshold is the threshold (duh).
void marchingSquaresSecondPhase(List<Pixel> &worklist, int sizeX, int sizeY,
                                std::vector<std::vector<bool>> &visitedlist,
                                UI &ui, Blob &blob, float threshold)
{
    while (!worklist.isEmpty()) {
        Pixel p;
        worklist.removeFromFront(p); // Store first element in the list in p and
                                     // remove it from the list.
        int xIndex = p.x + sizeX / 2 -
                     1; // Convert from potential scalar field coordinates to
                        // the visited matrix coordinates
        int yIndex = sizeY / 2 - p.y -
                     1; // Convert from potential scalar field coordinates to
                        // the visited matrix coordinates
        if (visitedlist[xIndex][yIndex] !=
            1) { // If pixel has already been visited, skip
            visitedlist[xIndex][yIndex] =
                true; // If not pixel has not been visited, make it visited
                      // and...
            if ((blob.potential(float(p.x - 0.5f), float(p.y + 0.5f)) <=
                     threshold && // Check if all corners of the pixel are on
                                  // the same side of the threshold
                 blob.potential(float(p.x + 0.5f), float(p.y + 0.5f)) <=
                     threshold &&
                 blob.potential(float(p.x - 0.5f), float(p.y - 0.5f)) <=
                     threshold &&
                 blob.potential(float(p.x + 0.5f), float(p.y - 0.5f)) <=
                     threshold) ||
                (blob.potential(float(p.x - 0.5f), float(p.y + 0.5f)) >=
                     threshold &&
                 blob.potential(float(p.x + 0.5f), float(p.y + 0.5f)) >=
                     threshold &&
                 blob.potential(float(p.x - 0.5f), float(p.y - 0.5f)) >=
                     threshold &&
                 blob.potential(float(p.x + 0.5f), float(p.y - 0.5f)) >=
                     threshold)) {
            } else { // If the threshold is crossed on the pixel
                ui.drawPixel(p.x, p.y); // draw the current pixel white
                worklist.insertAtFront(Pixel(
                    p.x - 1,
                    p.y + 1)); // And add surrounding pixels to the worklist
                worklist.insertAtFront(Pixel(p.x, p.y + 1));
                worklist.insertAtFront(Pixel(p.x + 1, p.y + 1));
                worklist.insertAtFront(Pixel(p.x - 1, p.y));
                worklist.insertAtFront(Pixel(p.x + 1, p.y));
                worklist.insertAtFront(Pixel(p.x - 1, p.y - 1));
                worklist.insertAtFront(Pixel(p.x, p.y - 1));
                worklist.insertAtFront(Pixel(p.x + 1, p.y - 1));
            }
        }
    }
}

// drawContourScanningThread() Scans a specified part of the screen for
// thresholds so the task can be divided over multiple threads.
// @param ui UI object so the function can interact with the pixels.
// @param blob Blob object so the function can interact with the scalar
// potential field.
// @param threshold The threshold that must be drawn.
// @param sizeX The horizontal size of the window in pixels.
// @param sizeY The vertical size of the window in pixels.
// @param xBegin Fraction of sizeX from where the function should start scanning
// in the x-direction.
// @param xEnd Fraction of sizeX from where the function should stop scanning in
// the x-direction.
// @param yBegin Fraction of sizeY from where the function should start scanning
// in the y-direction.
// @param yEnd Fraction of sizeY from where the function should stop scanning in
// the y-direction.
void drawContourScanningThread(UI &ui, Blob &blob, float threshold, int sizeX, int sizeY, float xBegin, float xEnd, float yBegin, float yEnd)
{
    for (int y = int(yBegin * sizeY); y < int(yEnd * sizeY);
         y++) { // for loop iterates over all Y coords
        for (int x = int(xBegin * sizeX); x < int(xEnd * sizeX);
             x++) { // for loop iterates over all X coords

            if (compareWithPreviousPixel(blob, (float)x, (float)y, threshold)) {
                ui.drawPixel((int)x, (int)y); // draw the current pixel white
            } else {
                continue;
            }
        }
    }
}