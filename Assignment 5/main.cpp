// Program that draws contour lines of scalar potential field.
// Pressing 'm' or 's' switches between the marching ('m') and scanning ('s')
// algorithms. Pressing 'm' or 's' a second time switches to the multithreaded
// or improved version of the algorithms. Also prints the time needed to draw
// one frame to stdout.

/*
 *  Created on: May 14, 2018
 *      Author: Johan Engelen
 *  Ported from D source by same author.
 */

/*
==============================================================
 Filename    :  main.cpp
 Authors     :  Hendrik van Gils    (s1920677)  h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)  d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  Edited file by Johan Engelen.
 Description :  The aim of this file is to draw contour lines of scalar
potential fields.
==============================================================
*/

#include "List.h"      // For the worklist.
#include "UI.h"        // For displaying window and drawing pixels through SDL.
#include "functions.h" // All other functions used in this script.
#include <SDL.h>       // For drawing pixels and getting user input.
#include <chrono>      // For time.
#include <iostream>    // cout.
#include <thread>      // To make more threads.
#include <vector>      // Vector for visited matrix.

bool compareWithPreviousPixel(Blob &blob, float x, float y, float threshold);
void marchingSquaresSecondPhase(
    List<Pixel> &worklist, int sizeX, int sizeY,
    std::vector<std::vector<bool>> &visitedlist, UI &ui, Blob &blob,
    float threshold); // The second phase of the marching squares algorithms.
                      // While there are pixels in the worklist it draws the
                      // pixel if it crosses the threshold and adds surrounding
                      // pixels to the worklist.
void drawContourScanningThread(
    UI &ui, Blob &blob, float threshold, int sizeX, int sizeY, float xBegin,
    float xEnd, float yBegin,
    float yEnd); // Scans a specified part of the screen for thresholds so the
                 // task can me divided over multiple threads.

constexpr bool capFramerate = false;
constexpr float thresholds[] = {0.015f, 0.02f, 0.03f}; // Three thresholds.

/// Scans full screen area. Complexity = sizeX*sizeY (n^2).
// drawContourScanning() Scans the entire screen line by line, pixel by pixel
// turning the contours of the thresholds white.
// @param ui UI object for interacting with the pixels on the window.
// @param blob Blob object for interacting with the scalar potential field.
// @param threshold The threshold that must be drawn.
void drawContourScanning(UI &ui, Blob &blob, float threshold = 0.015)
{
    const int sizeX = ui.sizeX;          // Get amount of pixels in x-direction.
    const int sizeY = ui.sizeY;          // Get amount of pixels in y-direction.
    ui.setDrawColor(255, 255, 255, 255); // Set color of pixel to white

    for (int y = -sizeY / 2; y < sizeY / 2;
         y++) { // for loop iterates over all Y coords
        for (int x = -sizeX / 2; x < sizeX / 2;
             x++) { // for loop iterates over all X coords

            if (compareWithPreviousPixel(
                    blob, (float)x, (float)y,
                    threshold)) // Does this pixel cross the threhold value?
            {
                ui.drawPixel(x, y); // Draw the current pixel white.
            } else {
                continue;
            }
        }
    }
}

/// Scans full screen area multithreaded. Complexity = sizeX*sizeY (n^2).
// drawContourScanning() Scans the entire screen line by line, pixel by pixel
// turning the contours of the thresholds white. But the scanning process is
// divided over 4 threads.
// @param ui UI object for interacting with the pixels on the window.
// @param blob Blob object for interacting with the scalar potential field.
// @param threshold The threshold that must be drawn.
void drawContourScanningThreaded(UI &ui, Blob &blob, float threshold = 0.015)
{
    const int sizeX = ui.sizeX;          // Get amount of pixels in x-direction.
    const int sizeY = ui.sizeY;          // Get amount of pixels in y-direction.
    ui.setDrawColor(255, 255, 255, 255); // Set color of pixel to white.

    std::thread th1(drawContourScanningThread, std::ref(ui),
                    std::ref(blob), // Start threads.
                    threshold, sizeX, sizeY, -0.5, 0, -0.5, 0);
    std::thread th2(drawContourScanningThread, std::ref(ui), std::ref(blob),
                    threshold, sizeX, sizeY, 0, 0.5, -0.5, 0);
    std::thread th3(drawContourScanningThread, std::ref(ui), std::ref(blob),
                    threshold, sizeX, sizeY, -0.5, 0, 0, 0.5);
    std::thread th4(drawContourScanningThread, std::ref(ui), std::ref(blob),
                    threshold, sizeX, sizeY, 0, 0.5, 0, 0.5);
    th1.join(); // Wait for all threads to finish before continuing.
    th2.join();
    th3.join();
    th4.join();
}

/// Scans screen area until it finds a pixel on the edge.
/// From then on, uses marching squares algorithm to find other pixels on the
/// edge. Caveat: only draws one of the potentially more than one contour losed
/// loops. Complexity phase 1 = n^2. Complexity phase 2 = n.
/// @param ui UI object so the function can interact with the pixels on the
/// window.
/// @param blob Blob object so the function can interact with the scalar
/// potential field.
/// @param threshold The threshold that should be drawn.
void drawContourMarching(UI &ui, Blob &blob, float threshold = 0.015)
{
    const int sizeX = ui.sizeX;          // Get amount of pixels in x-direction.
    const int sizeY = ui.sizeY;          // Get amount of pixels in y-direction.
    ui.setDrawColor(255, 255, 255, 255); // if so set color of pixel to white
    List<Pixel> worklist;                // Initiate worklist.
    std::vector<std::vector<bool>> visitedlist; // Initiate visitedlist.
    visitedlist.resize(
        sizeX, vector<bool>(sizeY)); // Size visitedlist to [sizeX×sizeY].

    // Phase 1:
    for (int y = -sizeY / 2; y < sizeY / 2;
         y++) { // for loop iterates over all Y coords
        for (int x = -sizeX / 2; x < sizeX / 2;
             x++) { // for loop iterates over all X coords
            if (compareWithPreviousPixel(
                    blob, (float)x, (float)y,
                    threshold)) {             // If pixel crosses threshold.
                Pixel p(x, y);                // Initiate Pixel p
                worklist.insertAtFront(p);    // Add p to worklist.
                goto next;                    // Go to second phase.
            }
        }
    }
next: // Phase 2:
    marchingSquaresSecondPhase(worklist, sizeX, sizeY, visitedlist, ui, blob,
                               threshold); // Use marching squares algorithm to
                                           // draw the rest of the contour.
}

/// Improved marching squares algorithm.
/// Should have better complexity than the initial algorithm described in the
/// manual :) Complexity phase 1 = n^2. Complexity phase 2 = n.
/// @param ui UI object so the function can interact with the pixels on the
/// window.
/// @param blob Blob object so the function can interact with the scalar
/// potential field.
/// @param threshold The threshold that should be drawn.
void drawContourMarchingBetter(UI &ui, Blob &blob, float threshold = 0.015)
{
    const int sizeX = ui.sizeX;          // Get amount of pixels in x-direction.
    const int sizeY = ui.sizeY;          // Get amount of pixels in y-direction.
    ui.setDrawColor(255, 255, 255, 255); // if so set color of pixel to white
    List<Pixel> worklist;                // Initiate worklist.
    std::vector<std::vector<bool>> visitedlist; // Initiate visitedlist.
    visitedlist.resize(
        sizeX, vector<bool>(sizeY)); // Size visitedlist to [sizeX×sizeY].

    for (int y = -sizeY / 2; y < sizeY / 2;
         y++) { // For loop iterates over all y coordinates.
        TwoSolutions xContours = blob.findXContour(
            threshold,
            (float)
                y); // Find x coordinates for given threshold and y coordinate.
        if (!isnan(xContours.x0) && xContours.x0 >= -sizeX / 2 &&
            xContours.x0 <= sizeX / 2) { // If the found x coordinate is a
                                         // number an within bounds
            Pixel p0((int)round(xContours.x0 - 1),
                     y); // Initiate Pixel with by rounding floating solution to
                         // an integer
            worklist.insertAtFront(p0);                // Add to worklist
            Pixel p1((int)round(xContours.x0 + 1), y); // Initiate Pixel
            worklist.insertAtFront(p1);                // Add to worklist
        }
        if (!isnan(xContours.x1) && xContours.x1 >= -sizeX / 2 &&
            xContours.x1 <= sizeX / 2) { // If the found x coordinate is a
                                         // number an within bounds
            Pixel p2((int)round(xContours.x1) - 1,
                     y); // Initiate Pixel with by rounding floating solution to
                         // an integer
            worklist.insertAtFront(p2);                // Add to worklist
            Pixel p3((int)round(xContours.x1) + 1, y); // Initiate Pixel
            worklist.insertAtFront(p3);                // Add to worklist
        }
    }
    marchingSquaresSecondPhase(worklist, sizeX, sizeY, visitedlist, ui, blob,
                               threshold); // Use marching squares algorithm to
                                           // draw the rest of the contour.
}

int main(int /*argc*/, char ** /*argv*/)
{
    using namespace std::chrono; // For keeping time.

    UI gui(1000, 600); // Create window of 1000 by 600 pixels.
    Blob blob;         // Create binary large object.

    unsigned long frameCounter = 0;
    auto drawContour = &drawContourScanning;

    bool pause = false;
    bool quit = false;
    while (!quit) {
        // Set timeout to limit frame rate
        auto timeout = SDL_GetTicks() + 20;

        if (!pause) // If not paused
        {
            blob.update(frameCounter++ /
                        2.0f); // Update wells and go to next frame.
        }

        gui.clear(); // Clear ui.

        high_resolution_clock::time_point t1 =
            high_resolution_clock::now(); // Save current time as t1.
        for (auto t : thresholds)         // For all (3) thresholds...
        {
            drawContour(gui, blob, t); // Draw the contour.
        }
        high_resolution_clock::time_point t2 =
            high_resolution_clock::now(); // Save current time as t2.
        gui.present();                    // Present drawn image.
        auto duration = duration_cast<microseconds>(t2 - t1)
                            .count(); // Initiate duration with the time it took
                                      // to draw the contour.
        std::cout << duration << " ms\n"; // Print the duration that it took

        // Handle the input.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Quit button.
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            // All keydown events
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_m:
                    drawContour = (drawContour == &drawContourMarching)
                                      ? &drawContourMarchingBetter
                                      : &drawContourMarching;
                    break;
                case SDLK_s:
                    drawContour = (drawContour == &drawContourScanning)
                                      ? &drawContourScanningThreaded
                                      : &drawContourScanning;
                    break;
                case SDLK_SPACE:
                    pause = !pause;
                    break;
                default:
                    break;
                }
            }
        }
        while (capFramerate && !SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // do nothing
        }
    }

    return 0;
}