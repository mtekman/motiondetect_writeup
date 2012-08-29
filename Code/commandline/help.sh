usage: motiondetect [OPTION...]
  -h, --help    * Print this help
  -v, --version   * Display version
  -m, --mask INT   * Size of mask in square pixels
  -q, --quiet   * Silent mode. Messages recorded to log file
  -i, --images DIRECTORY  * Where images are saved. Default:~/MyDocs/DCIM/MISC/
  -c, --convert   * Convert all images in image directory  to an MPG file
  -d, --delete   * Delete images on exit. Convert flag must be specified too
  -s, --size WIDTH HEIGHT   * Valid sizes: 320 240, 640 480, 800 600, 1280 960
  -w, --whitepix INT   * White pixel count threshold. Default: 100
  -r, --range MIN MAX   * Intervals (secs) to restrict camera. Default: 1 10
  -a, --adapt FLOAT   * Adaptiveness of interval. Default: 0.16 (v.responsive)
  -t, --time secs OR mm:ss OR hh:mm:ss OR dd:hh:mm:ss
  -l, --log   * Output to log file: ~/.config/motion_detect.log
  -e, --email ADDRESS MESSAGE SUBJECT [Y/N]
	* Email upon movement. Y attaches the last image to email.

