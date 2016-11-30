#include "Track.h"

Track::Track() {
  bottomTrack(Constants::bottomTrackInSole, Constants::bottomTrackOutSole),
  topTrack(Constants::topTrackInSole, Constants::topTrackOutSole)
}

void Track::openBottom() {
  bottomTrack.Set(true);
}

void Track::closeBottom() {
  bottomTrack.Set(false);
}

void Track::openTop() {
  topTrack.Set(true);
}

void Track::closeTop() {
  topTrack.Set(false);
}
