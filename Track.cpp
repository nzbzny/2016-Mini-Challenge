#include "Track.h"

Track::Track() :
  bottomTrack(Constants::bottomTrackInSole, Constants::bottomTrackOutSole),
  topTrack(Constants::topTrackInSole, Constants::topTrackOutSole)
{}

void Track::bottom(bool state) {
  bottomTrack.set(state);
}

void Track::top(bool state) {
  topTrack.set(state);
}

bool Track::getBottom() {
  return bottomTrack.get();
}

bool Track::getTop() {
  return topTrack.get();
}
