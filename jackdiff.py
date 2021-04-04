#!/usr/bin/python

import argparse
import liblo
from liblo import *
import matplotlib.pyplot as plt
import queue
import subprocess
import sys
import time


parser = argparse.ArgumentParser(
    description=('')
)
parser.add_argument('file', default=None, type=str,
                    help="path to audio file to process")
parser.add_argument('length', default=3, type=int,
                    help='length in seconds of audio to process')
parser.add_argument('offset', default=0, type=int,
                    help="offset in seconds of audio file to process")
args = parser.parse_args()

responses = queue.Queue()


class OscServer(ServerThread):
    def __init__(self):
        ServerThread.__init__(self, 10001)

    @make_method('/jackdiff/isready', 'i')
    def osc_isready_handler(self, path, args):
        s = args
        responses.put(s)
        print("received '/jackdiff/isready'")

    @make_method(None, None)
    def fallback(self, path, args):
        print("fallback, received '{}'".format(path))

        
def make_jack_connections(num_inputs, num_outputs):
    mplayer_suffix = list(filter(None, subprocess.check_output("jack_lsp | grep MPlayer", shell=True).decode().split('\n')))[0].split(':')[0]
    for num in range(0, num_inputs):
        subprocess.check_output(f"jack_connect '{mplayer_suffix}:out_{num}' jackdiff:in_{num+1}", shell=True)


def send_is_ready_msg(dest):
    print('send /jackdiff/isready')
    liblo.send(dest, "/jackdiff/isready", 0)
    response = responses.get()
    print('received /jackdiff/isready: ', response)
    
    
def run():
    if not args.file:
        print("no audio file provided, exiting..")
        exit(0)
    mplayer_cmd_prefix = "mplayer -ao jack"
    if args.offset:
        mplayer_cmd_prefix += f" -ss {args.offset}"
    mplayer_cmd = mplayer_cmd_prefix + f" {args.file}"

    dest = liblo.Address('127.0.0.1', 10000)

    osc_server = OscServer()
    osc_server.start()
    
    jack_samplerate = int(subprocess.check_output("jack_samplerate", shell=True).decode())
    sample_length = int(float(args.length) * float(jack_samplerate))

    print('sample_length: ')
    print(sample_length)
    
    print('mplayer_cmd: ')
    print(mplayer_cmd)
    
    subprocess.Popen(f"./jackdiff -l {sample_length}", shell=True);
                     # stdout=subprocess.PIPE,
                     # stderr=subprocess.STDOUT)
    subprocess.Popen(f"{mplayer_cmd}", shell=True,
                     stdout=subprocess.PIPE,
                     stderr=subprocess.STDOUT)
    time.sleep(0.1)
    make_jack_connections(1, 1)
    send_is_ready_msg(dest)

    figure, axis = plt.subplots(2)
    
    in_x = []
    in_y = []
    out_x = []
    out_y = []

    with open("output/signal_in.txt", "r") as fp:
        for index, line in enumerate(fp):
            in_x.append(index)
            in_y.append(float(line.strip()))

    with open("output/signal_out.txt", "r") as fp:
        for index, line in enumerate(fp):
            out_x.append(index)
            out_y.append(float(line.strip()))
            
    axis[0].plot(in_x, in_y)
    axis[0].set_title('signal in')
    axis[1].plot(out_x, out_y)
    axis[1].set_title('signal out')

    plt.show()

    print('exiting..')
    exit(0)
    

if __name__ == "__main__":
    run()
