#jackdiff
quick and dirty plot-vomiting skeleton jack client

this repository isn't really meant to be used by anyone but me.
it's helping me test dsp algorithms for another project.

the main branch serves as a skeleton jack client, other branches
are filled-in with algorithms that i'm testing and there's
probably a bit of trash lying around.

there's two parts to this:
1. c binary jack skeleton client that's intended to be filled in
   with some dsp algorithm. when run will write the input signal
   and the output signal to line-separated text files for a
   given number of samples
2. python wrapper that handles setting up jack connections,
   playing signal using mplayer, and synchronizes c binary
   and python script using open-sound-control.

## Dependencies
 - linux (maybe mac?)
 - python3, pyliblo, matplotlib
 - [JACK](http://jackaudio.org/)
 - [liblo](http://liblo.sourceforge.net/)
 - [mplayer](http://www.mplayerhq.hu/)

## Installing
```
$ git clone https://github.com/bonemurmurer/jackdiff.git
```

## Building
```
$ cd jackdiff
$ make
```
