#!/usr/bin/env python

import commands, curses

def drawer(timer, mod, queit_frames):
  f=0

  flip = True;  move = False
  consec_quiet = 0

  while f!=-1:
      move = False
      try:
         inp = screen.getch()
      except IOError:
         pass
      except TypeError:
         pass
      screen.nodelay(True);
      if inp == ord('a'):
         move = True;
      try:
      # -- Move logic, halves on movement.
         if move:
            if timer> 100:
               timer = int(timer*mod)
            consec_quiet = 0
         else:
            consec_quiet = consec_quiet+1

      # -- Timer doubled if quiet for (10) frames
         if consec_quiet > quiet_frames:
            timer = int(timer / mod);

      # -- Alternates on clearing and printing per interval
         if flip:
            screen.addstr(10,10,str(timer) )
            flip = False
         else:
           screen.addstr(10,10,"      " )
           flip = True
      except:
          pass
      curses.napms(timer)
      screen.refresh();

screen = curses.initscr();
curses.curs_set(0)
curses.noecho()
try:
  drawer(timer=1000, mod=0.7, quiet_frames=10)

except KeyboardInterrupt:
    curses.endwin()
    exit()