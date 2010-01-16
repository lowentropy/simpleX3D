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
#include "Time/TimeSensor.h"

namespace X3D {
namespace Time {

void TimeSensor::predict() {
    double next = -1;
    if (!enabled())
        return;
    else if (isPaused())
        next = resumeTime();
    else if (!isActive()) {
        if (startTime() > now())
            next = startTime();
    } else {
        next = cycleTime() + cycleInterval();
        if (stopTime() > now())
            if (stopTime() < next)
                next = stopTime();
        if (pauseTime() > now())
            if (pauseTime() < next)
                next = pauseTime();
    }
    if (next > now())
        browser()->wake(next);
}

void TimeSensor::tick() {
    time(now());
    elapsedTime(elapsedTime.value() + now() - last);
    last = now();
    frac();
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

    predict();
}

void TimeSensor::pause() {
    pauseTime(now());
    isPaused(true);
}

void TimeSensor::start() {
    last = now();
    startTime(last);
    cycleTime(last);
    isActive(true);
    frac();
}

void TimeSensor::stop() {
    stopTime(now());
    isActive(false);
}

void TimeSensor::resume() {
    last = now();
    resumeTime(last);
    isPaused(false);
    elapsedTime.changed();
    frac();
}

void TimeSensor::cycle() {
    if (loop()) {
        cycleTime(now());
    } else {
        stop();
    }
}

void TimeSensor::frac() {
    double frac = (now() - startTime()) / cycleInterval();
    frac -= (double) (int) frac;
    if (frac == 0 && now() > startTime())
        frac = 1;
    fraction_changed(frac);
}

}}
