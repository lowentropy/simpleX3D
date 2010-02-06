/*
 * Copyright 2009 Nathan Matthews <lowentropy@gmail.com>
 *
 * This file is part of SimpleX3D.
 * 
 * SimpleX3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SimpleX3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with SimpleX3D.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "internal/Browser.h"
#include <float.h>

#include <iostream>
using std::cout;
using std::endl;

namespace X3D {
namespace Time {

void TimeSensor::wake(double time) {
    if (time < next || next < 0) {
        browser()->schedule(time, this);
        next = time;
    }
}

#define swap(type,a,b) do { \
    type __tmp = a; \
    a = b; \
    b = __tmp; \
} while (false)

template <typename A, typename B>
static void bubblesort(A* list, B* idx, int len) {
    bool swaps;
    do {
        swaps = false;
        for (int i = 0; i < len-1; i++) {
            if (list[i] > list[i+1]) {
                swap(A, list[i], list[i+1]);
                swap(B, idx[i], idx[i+1]);
                swaps = true;
            }
        }
    } while (swaps);
}

void TimeSensor::initSensor() {
    wake(startTime());
}

void TimeSensor::evaluate() {
    if (next < 0)
        return;

    // indicate evaluation occured
    next = -1;
    if (!enabled())
        return;

    // get time values
    double tick = now();
    double start = startTime();
    double stop = stopTime();
    double pause = pauseTime();
    double resume = resumeTime();

    // indicators of possible events
    bool _start = start <= tick;
    bool _stop = stop <= tick;
    bool _pause = pause <= tick;
    bool _resume = resume <= tick;

    // eliminate redundant pairs
    if (_start && _stop && start <= stop)
        _start = _stop = false;
    if (_pause && _resume && pause <= resume)
        _pause = _resume = false;

    // get begin state
    bool active = isActive();
    bool paused = isPaused();
    bool _active = false;
    bool _paused = false;

    // sort events in order
    int order[] = { 0, 1, 2, 3 };
    double times[] = {
        _start  ? start  : DBL_MAX, 
        _stop   ? stop   : DBL_MAX,
        _pause  ? pause  : DBL_MAX,
        _resume ? resume : DBL_MAX };
    bubblesort(times, order, 4);

    // process sorted events
    for (int i = 0; i < 3; i++) {
        if (times[i] == DBL_MAX)
            break;
        switch (order[i]) {
            case 0: // start
                if (active) continue;
                active = true;
                _active = true;
                elapsed = 0;
                last = tick;
                break;
            case 1: // stop
                if (!active) continue;
                if (paused) {
                    // XXX could be caused by pause interfering with cycle
                    throw X3DError("tried to stop while paused");
                }
                _active = true;
                _paused = _paused || paused;
                active = false;
                paused = false;
                break;
            case 2: // pause
                if (paused || !active) continue;
                paused = true;
                _paused = true;
                break;
            case 3: // resume
                if (!paused) continue;
                if (!active) throw X3DError("INVALID STATE");
                paused = false;
                _paused = true;
                last = tick;
                break;
        }
    }

    // advance internal clock
    double dt = tick - last;
    elapsed += dt;
    
    // check for cycle ending
    bool _cycle = elapsed >= cycleInterval();
    if (_cycle && !loop() && active) {
        _active = true;
        _paused = _paused || paused;
        active = false;
        paused = false;
    }

    // throw some events around
    if (_active)
        isActive(active);
    if (_paused)
        isPaused(paused);

    // kick the ticker
    if (!active || paused) {
        last = tick;
        return;
    }

    // output continuous events
    if (_cycle) {
        cycleTime.send(tick);
        elapsed = 0;
    }
    time.send(tick);
    elapsedTime.send(elapsedTime() + dt);

    // schedule cycle event
    if (last == tick || _cycle)
        wake(tick + cycleInterval() - elapsed);

    // fraction
    double frac = elapsed / cycleInterval();
    if (frac == 0 && tick > start)
        frac = 1;
    fraction_changed.send(frac);

    // update evaluation time
    last = tick;
}

bool TimeSensor::tick() {
    if (last == now())
        return false;
    double dt = now() - last;
    elapsed += dt;
    double frac = elapsed / cycleInterval();
    if (frac == 0 && now() > startTime())
        frac = 1;
    time.send(now());
    fraction_changed.send(frac);
    elapsedTime.send(elapsedTime() + dt);
    last = now();
    return true;
}

bool TimeSensor::getIsActive() const {
    return isActive.value();
}

}}
