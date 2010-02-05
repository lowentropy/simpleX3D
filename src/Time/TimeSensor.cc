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

#include <iostream>
using std::cout;
using std::endl;

namespace X3D {
namespace Time {

void TimeSensor::predict() {
    double next = -1;
    if (!enabled()) {
        return;
    } else if (isPaused()) {
        next = resumeTime();
    } else if (!isActive()) {
        if (startTime() > now())
            next = startTime();
    } else {
        next = cycleTime() + cycleInterval();
        if (stopTime() > now() && stopTime() < next)
            next = stopTime();
        if (pauseTime() > now() && pauseTime() < next)
            next = pauseTime();
    }
    if (next > now())
        browser()->wake(next);
}

void TimeSensor::setEnabled(bool enabled) {
    if (enabled) {
        evaluate();
    } else {
        if (isActive() && !isPaused())
            tick();
        isActive(false);
    }
}

void TimeSensor::evaluate() {
    if (!enabled())
        return;

    bool active = isActive();
    bool paused = isPaused();
    bool couldStart = now() >= startTime();
    bool noStopping = stopTime() <= startTime();
    bool couldStop = !noStopping && (now() >= stopTime());
    bool pausable = pauseTime() < resumeTime();
    bool couldPause = pausable && (now() >= pauseTime());
    bool couldResume = now() >= resumeTime();
    bool cycleOver = now() >= (cycleTime() + cycleInterval());

    if (active && !paused)
        tick();

    if (!active && couldStart && !couldStop) {
        start();
        if (couldPause)
            pause();
    } else if (paused && couldResume) {
        resume();
        if (couldStop)
            stop();
        else if (cycleOver)
            cycle();
    } else if (couldStop) {
        stop();
    } else if (couldPause) {
        pause();
    } else if (cycleOver) {
        cycle();
    }
}

void TimeSensor::tick() {
    time.send(now());
    elapsedTime.send(elapsedTime() + now() - last);
    // cout << "TICK: " << last << " -> " << now() << ": " << elapsedTime() << endl;
    last = now();
    frac();
}

void TimeSensor::pause() {
    pauseTime.send(now());
    isPaused.send(true);
}

void TimeSensor::start() {
    last = now();
    startTime.send(last);
    cycleTime.send(last);
    isActive.send(true);
    tick();
}

void TimeSensor::stop() {
    stopTime.send(now());
    isActive.send(false);
}

void TimeSensor::resume() {
    last = now();
    resumeTime.send(last);
    isPaused.send(false);
    tick();
}

void TimeSensor::cycle() {
    if (loop()) {
        cycleTime.send(now());
    } else {
        stop();
    }
}

void TimeSensor::frac() {
    double frac = (now() - startTime()) / cycleInterval();
    frac -= (double) (int) frac;
    if (frac == 0 && now() > startTime())
        frac = 1;
    fraction_changed.send(frac);
}

bool TimeSensor::getIsActive() const {
    return isActive.value();
}

#define COMPARE(DATA,INDX,A,B) \
    if (DATA[A] > DATA[B]) { \
        double __d; int __i; \
        __d = DATA[A]; DATA[A] = DATA[B]; DATA[B] = __d; \
        __i = INDX[A]; INDX[A] = INDX[B]; INDX[B] = __i;  TimeSensor::sortEvents(double* times, int* indexes) {
    compare(times, indexes, 0, 2);
    compare(times, indexes, 1, 3);
    compare(times, indexes, 0, 1);
    compare(times, indexes, 2, 3);
    compare(times, indexes, 1, 2);
}

}}
