#!/bin/bash
./vote-zero-tcp-nonblocking localhost 11632 &
./add-voter-tcp-nonblocking localhost 11632 1 &
./vote-tcp-nonblocking localhost 11632 Bush 1 &
./vote-count-tcp-nonblocking localhost 11632 Bush &
./list-candidates-tcp-nonblocking localhost 11632 &
